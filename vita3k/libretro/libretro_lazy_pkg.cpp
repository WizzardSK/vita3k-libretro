#include "libretro_lazy_pkg.h"

#include "libretro_state.h"

#include <io/filesystem.h>
#include <io/util.h>
#include <io/vfs.h>
#include <packages/pkg.h>
#include <miniz.h>
#include <packages/sfo.h>
#include <util/bytes.h>
#include <fmt/format.h>
#include <util/string_utils.h>

#include <CryptoOperationsFactory.h>
#include <F00DKeyEncryptorFactory.h>
#include <FilesDbParser.h>
#include <FlagOperations.h>
#include <PfsCryptEngine.h>
#include <PfsKeyGenerator.h>
#include <MerkleTree.hpp>
#include <PfsPageMapper.h>
#include <SecretGenerator.h>
#include <UnicvDbParser.h>
#include <zRIF/licdec.h>

#include <openssl/evp.h>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <winioctl.h>
#else
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#ifdef __APPLE__
#include <sys/mount.h>
#else
#include <sys/vfs.h>
#endif
#endif

#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <map>
#include <memory>
#include <optional>
#include <mutex>
#include <set>
#include <fstream>
#include <sstream>
#include <vector>

namespace lazy_pkg {

namespace {

void lr_log(enum retro_log_level level, const char *fmt, ...) {
    if (!libretro.log_cb)
        return;
    va_list ap;
    va_start(ap, fmt);
    char buf[4096];
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    libretro.log_cb(level, "[Vita3K] %s", buf);
}

// Files written out in full when the package is laid out, decrypted before the
// game starts: what the core reads itself (param.sfo, the executable, its
// modules) and what is too small to be worth waiting for
constexpr std::uint64_t EAGER_SIZE = 1024 * 1024;

std::string upper(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return static_cast<char>(std::toupper(c)); });
    return s;
}

// NTFS leaves holes only in a file marked sparse; elsewhere every file can
// have them
void mark_sparse(const fs::path &path) {
#ifdef _WIN32
    HANDLE h = CreateFileW(path.wstring().c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, nullptr,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (h != INVALID_HANDLE_VALUE) {
        DWORD returned = 0;
        DeviceIoControl(h, FSCTL_SET_SPARSE, nullptr, 0, nullptr, 0, &returned, nullptr);
        CloseHandle(h);
    }
#else
    (void)path;
#endif
}

// fseek past 2 GB on every host
int seek_file(FILE *file, std::uint64_t at) {
#ifdef _WIN32
    return _fseeki64(file, static_cast<__int64>(at), SEEK_SET);
#else
    return fseeko(file, static_cast<off_t>(at), SEEK_SET);
#endif
}

// What a game's files are read out of: a PKG (PkgReader), a VPK/ZIP
// (ArchiveReader) or a folder (FolderReader). Each entry's bytes are at its
// offset, as the console has them: still PFS-encrypted where the game is.
class Source {
public:
    struct Entry {
        std::string name;
        std::uint64_t offset = 0;
        std::uint64_t size = 0;
        bool directory = false;
    };

    virtual ~Source() = default;
    virtual bool read(std::uint64_t offset, void *out, std::size_t size) = 0;
    // What it is, for the log: "PKG", "VPK/ZIP" or "folder"
    virtual const char *kind() const = 0;

    // An entry's bytes, as they are on the console: still PFS-encrypted where the game is
    bool write_entry(const Entry &e, const fs::path &to, std::uint64_t length) {
        std::ofstream out(to, std::ios::binary | std::ios::trunc);
        if (!out)
            return false;
        std::vector<std::uint8_t> buf(1024 * 1024);
        for (std::uint64_t done = 0; done < length;) {
            const std::size_t n = static_cast<std::size_t>(std::min<std::uint64_t>(buf.size(), length - done));
            if (!read(e.offset + done, buf.data(), n))
                return false;
            out.write(reinterpret_cast<const char *>(buf.data()), n);
            done += n;
        }
        out.close();
        // The rest of a placeholder is a hole: the right size, no disk space.
        // NTFS makes one only for a file marked sparse; without it extending
        // the file allocates all of it
        if (length < e.size) {
            mark_sparse(to);
            fs::resize_file(to, e.size);
        }
        return true;
    }

    const std::vector<Entry> &entries() const { return m_entries; }

protected:
    std::vector<Entry> m_entries;
};

// The outer layer: the PKG's own AES-128-CTR, which can start at any offset
class PkgReader final : public Source {
public:
    ~PkgReader() {
        if (m_file)
            fclose(m_file);
    }

    // Also a DLC's PKG (content type 0x16), for mount_dlc and pkg_info
    bool allow_dlc = false;

    bool open(const fs::path &path, std::string &error) {
        m_file = FOPEN(path.c_str(), "rb");
        if (!m_file) {
            error = "cannot open the PKG";
            return false;
        }
        PkgHeader header{};
        PkgExtHeader ext{};
        if (fread(&header, sizeof(header), 1, m_file) != 1 || fread(&ext, sizeof(ext), 1, m_file) != 1
            || byte_swap(header.magic) != 0x7F504b47) {
            error = "not a PKG";
            return false;
        }
        memcpy(m_iv, header.pkg_data_iv, sizeof(m_iv));
        m_data_offset = byte_swap(header.data_offset);

        std::uint32_t content_type = 0, items_offset = 0, sfo_offset = 0, sfo_size = 0;
        std::uint32_t info_offset = byte_swap(header.info_offset);
        for (std::uint32_t i = 0; i < byte_swap(header.info_count); i++) {
            std::uint32_t block[4];
            fseek(m_file, info_offset, SEEK_SET);
            if (fread(block, sizeof(block), 1, m_file) != 1)
                break;
            const auto type = byte_swap(block[0]);
            const auto size = byte_swap(block[1]);
            if (type == 2)
                content_type = byte_swap(block[2]);
            else if (type == 13)
                items_offset = byte_swap(block[2]);
            else if (type == 14) {
                sfo_offset = byte_swap(block[2]);
                sfo_size = byte_swap(block[3]);
            }
            info_offset += 2 * sizeof(std::uint32_t) + size;
        }
        if (content_type != 0x15 && !(allow_dlc && content_type == 0x16)) {
            error = "not a game's PKG (an update, DLC or theme is installed)";
            return false;
        }
        m_sfo.resize(sfo_size);
        fseek(m_file, sfo_offset, SEEK_SET);
        if (sfo_size && fread(m_sfo.data(), sfo_size, 1, m_file) != 1) {
            error = "cannot read the PKG's param.sfo";
            return false;
        }

        const uint8_t *key = nullptr;
        switch (byte_swap(ext.data_type2) & 7) {
        case 2: key = pkg_vita_2; break;
        case 3: key = pkg_vita_3; break;
        case 4: key = pkg_vita_4; break;
        default:
            error = "unknown PKG key";
            return false;
        }
        EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
        int len = 0;
        EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), nullptr, key, nullptr);
        EVP_CIPHER_CTX_set_padding(ctx, 0);
        EVP_EncryptUpdate(ctx, m_key, &len, m_iv, 16);
        EVP_CIPHER_CTX_free(ctx);

        for (std::uint32_t i = 0; i < byte_swap(header.file_count); i++) {
            PkgEntry raw{};
            const std::uint64_t at = items_offset + i * sizeof(PkgEntry);
            if (!read(at, &raw, sizeof(raw))) {
                error = "cannot read the PKG's file table";
                return false;
            }
            Entry e;
            std::vector<char> name(byte_swap(raw.name_size));
            if (!read(byte_swap(raw.name_offset), name.data(), name.size())) {
                error = "cannot read the PKG's file names";
                return false;
            }
            e.name.assign(name.begin(), name.end());
            e.offset = byte_swap(raw.data_offset);
            e.size = byte_swap(raw.data_size);
            const auto kind = byte_swap(raw.type) & 0xFF;
            e.directory = kind == 4 || kind == 18;
            m_entries.push_back(std::move(e));
        }
        return true;
    }

    const char *kind() const override { return "PKG"; }

    // Decrypted bytes of the data area, from offset
    bool read(std::uint64_t offset, void *out, std::size_t size) override {
        std::lock_guard lock(m_mutex);
        const std::uint64_t aligned = offset & ~std::uint64_t(15);
        const std::size_t skip = static_cast<std::size_t>(offset - aligned);
        std::vector<std::uint8_t> buf(skip + size);
        if (seek_file(m_file, m_data_offset + aligned) != 0
            || fread(buf.data(), buf.size(), 1, m_file) != 1)
            return false;
        std::uint8_t counter[16];
        std::uint64_t n = aligned / 16;
        for (int i = 15; i >= 0; i--) {
            n += m_iv[i];
            counter[i] = static_cast<std::uint8_t>(n);
            n >>= 8;
        }
        EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
        int len = 0;
        EVP_DecryptInit_ex(ctx, EVP_aes_128_ctr(), nullptr, m_key, counter);
        EVP_DecryptUpdate(ctx, buf.data(), &len, buf.data(), static_cast<int>(buf.size()));
        EVP_CIPHER_CTX_free(ctx);
        memcpy(out, buf.data() + skip, size);
        return true;
    }

    const std::vector<std::uint8_t> &sfo() const { return m_sfo; }

private:
    FILE *m_file = nullptr;
    std::uint64_t m_data_offset = 0;
    std::uint8_t m_iv[16]{};
    std::uint8_t m_key[16]{};
    std::vector<std::uint8_t> m_sfo;
    std::mutex m_mutex;
};

// A VPK/ZIP's files under one folder of it (the game's), read where they lie:
// a stored file straight out of the archive, a compressed one inflated as it
// is read, from its start again only when an earlier part is asked for
class ArchiveReader final : public Source {
public:
    ~ArchiveReader() override {
        for (auto &s : m_streams)
            mz_zip_reader_extract_iter_free(s.state);
        if (m_open)
            mz_zip_reader_end(&m_zip);
        if (m_file)
            fclose(m_file);
    }

    // prefix: the game's folder in the archive, "" or ending in '/'
    bool open(const fs::path &path, const std::string &prefix, std::string &error) {
        m_file = FOPEN(path.c_str(), "rb");
        if (!m_file) {
            error = "cannot open the archive";
            return false;
        }
        memset(&m_zip, 0, sizeof(m_zip));
        if (!mz_zip_reader_init_cfile(&m_zip, m_file, 0, 0)) {
            error = "not a ZIP";
            return false;
        }
        m_open = true;
        std::uint64_t offset = 0;
        const mz_uint count = mz_zip_reader_get_num_files(&m_zip);
        for (mz_uint i = 0; i < count; i++) {
            mz_zip_archive_file_stat st;
            if (!mz_zip_reader_file_stat(&m_zip, i, &st))
                continue;
            std::string name = st.m_filename;
            if (!name.starts_with(prefix) || name.size() == prefix.size())
                continue;
            name.erase(0, prefix.size());
            Entry e;
            e.directory = st.m_is_directory;
            if (e.directory && !name.empty() && name.back() == '/')
                name.pop_back();
            if (!e.directory && (st.m_is_encrypted || !st.m_is_supported)) {
                error = "cannot read " + name + " out of the archive";
                return false;
            }
            e.name = name;
            e.offset = offset;
            e.size = e.directory ? 0 : st.m_uncomp_size;
            offset += e.size;
            if (e.size)
                m_with_data.push_back(m_entries.size());
            m_entries.push_back(std::move(e));
            m_files.push_back({ i, st.m_method == 0 ? data_start(st) : 0, st.m_method == 0 });
        }
        if (m_entries.empty()) {
            error = "nothing of the game in the archive";
            return false;
        }
        return true;
    }

    const char *kind() const override { return "VPK/ZIP"; }

    bool read(std::uint64_t offset, void *out, std::size_t size) override {
        std::lock_guard lock(m_mutex);
        // The file with bytes at offset: the last one starting at or before it
        const auto it = std::upper_bound(m_with_data.begin(), m_with_data.end(), offset,
            [&](std::uint64_t at, std::size_t i) { return at < m_entries[i].offset; });
        if (it == m_with_data.begin())
            return false;
        const Entry *e = &m_entries[*std::prev(it)];
        if (offset + size > e->offset + e->size)
            return false;
        const File &f = m_files[*std::prev(it)];
        const std::uint64_t at = offset - e->offset;
        if (f.stored) {
            if (seek_file(m_file, f.data + at) != 0)
                return false;
            return size == 0 || fread(out, size, 1, m_file) == 1;
        }
        return inflate_at(f.index, at, static_cast<std::uint8_t *>(out), size);
    }

private:
    struct File {
        mz_uint index;
        std::uint64_t data; // where a stored file's bytes start
        bool stored;
    };
    struct Inflating {
        mz_uint index;
        mz_zip_reader_extract_iter_state *state;
        std::uint64_t position;
    };

    // After the local header: its 30 bytes, the name and the extra field
    std::uint64_t data_start(const mz_zip_archive_file_stat &st) {
        std::uint8_t header[30];
        if (seek_file(m_file, st.m_local_header_ofs) != 0 || fread(header, sizeof(header), 1, m_file) != 1)
            return 0;
        const std::uint32_t name_length = header[26] | (header[27] << 8);
        const std::uint32_t extra_length = header[28] | (header[29] << 8);
        return st.m_local_header_ofs + sizeof(header) + name_length + extra_length;
    }

    bool inflate_at(mz_uint index, std::uint64_t at, std::uint8_t *out, std::size_t size) {
        auto s = std::find_if(m_streams.begin(), m_streams.end(), [&](const Inflating &i) { return i.index == index; });
        if (s != m_streams.end() && s->position > at) {
            mz_zip_reader_extract_iter_free(s->state);
            m_streams.erase(s);
            s = m_streams.end();
        }
        if (s == m_streams.end()) {
            // A few files at a time, each with its own inflate state
            if (m_streams.size() >= 4) {
                mz_zip_reader_extract_iter_free(m_streams.front().state);
                m_streams.erase(m_streams.begin());
            }
            mz_zip_reader_extract_iter_state *state = mz_zip_reader_extract_iter_new(&m_zip, index, 0);
            if (!state)
                return false;
            m_streams.push_back({ index, state, 0 });
            s = std::prev(m_streams.end());
        }
        std::vector<std::uint8_t> skip;
        while (s->position < at) {
            skip.resize(static_cast<std::size_t>(std::min<std::uint64_t>(at - s->position, 1 << 20)));
            const std::size_t n = mz_zip_reader_extract_iter_read(s->state, skip.data(), skip.size());
            if (n == 0)
                return false;
            s->position += n;
        }
        std::size_t done = 0;
        while (done < size) {
            const std::size_t n = mz_zip_reader_extract_iter_read(s->state, out + done, size - done);
            if (n == 0)
                return false;
            done += n;
            s->position += n;
        }
        return true;
    }

    FILE *m_file = nullptr;
    mz_zip_archive m_zip{};
    bool m_open = false;
    std::vector<File> m_files; // beside m_entries
    std::vector<std::size_t> m_with_data; // the entries with bytes, in offset order
    std::vector<Inflating> m_streams;
    std::mutex m_mutex;
};

// A game folder's files (an extracted VPK or a NoNpDrm dump), read where they lie
class FolderReader final : public Source {
public:
    ~FolderReader() override {
        if (m_file)
            fclose(m_file);
    }

    bool open(const fs::path &dir, std::string &error) {
        std::error_code ec;
        std::uint64_t offset = 0;
        for (fs::recursive_directory_iterator it(dir, ec), end; !ec && it != end; it.increment(ec)) {
            Entry e;
            e.name = fs::relative(it->path(), dir, ec).generic_string();
            e.directory = fs::is_directory(it->path(), ec);
            e.offset = offset;
            e.size = e.directory ? 0 : fs::file_size(it->path(), ec);
            offset += e.size;
            if (e.size)
                m_with_data.push_back(m_entries.size());
            m_entries.push_back(std::move(e));
            m_paths.push_back(it->path());
        }
        if (ec || m_entries.empty()) {
            error = "cannot read the game's directory";
            return false;
        }
        return true;
    }

    const char *kind() const override { return "folder"; }

    bool read(std::uint64_t offset, void *out, std::size_t size) override {
        std::lock_guard lock(m_mutex);
        const auto it = std::upper_bound(m_with_data.begin(), m_with_data.end(), offset,
            [&](std::uint64_t at, std::size_t i) { return at < m_entries[i].offset; });
        if (it == m_with_data.begin())
            return false;
        const std::size_t index = *std::prev(it);
        const Entry &e = m_entries[index];
        if (offset + size > e.offset + e.size)
            return false;
        if (index != m_open) {
            if (m_file)
                fclose(m_file);
            m_file = FOPEN(m_paths[index].c_str(), "rb");
            m_open = m_file ? index : SIZE_MAX;
            if (!m_file)
                return false;
        }
        if (seek_file(m_file, offset - e.offset) != 0)
            return false;
        return size == 0 || fread(out, size, 1, m_file) == 1;
    }

private:
    std::vector<fs::path> m_paths; // beside m_entries
    std::vector<std::size_t> m_with_data;
    FILE *m_file = nullptr;
    std::size_t m_open = SIZE_MAX;
    std::mutex m_mutex;
};

bool is_archive_path(const fs::path &path) {
    const std::string ext = string_utils::tolower(path.extension().string());
    return ext == ".vpk" || ext == ".zip";
}

// The folder of an archive that holds the content ("" or ending in '/'): the one
// with sce_sys/param.sfo nearest the top. Empty optional when it has none.
std::optional<std::string> archive_prefix(const fs::path &path) {
    FILE *file = FOPEN(path.c_str(), "rb");
    if (!file)
        return std::nullopt;
    mz_zip_archive zip{};
    std::optional<std::string> best;
    if (mz_zip_reader_init_cfile(&zip, file, 0, 0)) {
        const std::string marker = "sce_sys/param.sfo";
        const mz_uint count = mz_zip_reader_get_num_files(&zip);
        for (mz_uint i = 0; i < count; i++) {
            mz_zip_archive_file_stat st;
            if (!mz_zip_reader_file_stat(&zip, i, &st))
                continue;
            const std::string name = st.m_filename;
            if (name.size() < marker.size() || name.compare(name.size() - marker.size(), marker.size(), marker) != 0)
                continue;
            const std::string prefix = name.substr(0, name.size() - marker.size());
            if (!prefix.empty() && prefix.back() != '/')
                continue;
            if (!best || prefix.size() < best->size())
                best = prefix;
        }
        mz_zip_reader_end(&zip);
    }
    fclose(file);
    return best;
}

// A PKG, VPK or ZIP opened as a source of a content's files
std::unique_ptr<Source> open_source(const fs::path &path, bool allow_dlc, std::string &error) {
    std::error_code ec;
    if (fs::is_directory(path, ec)) {
        auto reader = std::make_unique<FolderReader>();
        if (!reader->open(path, error))
            return nullptr;
        return reader;
    }
    if (is_archive_path(path)) {
        const auto prefix = archive_prefix(path);
        if (!prefix) {
            error = "no sce_sys/param.sfo in the archive";
            return nullptr;
        }
        auto reader = std::make_unique<ArchiveReader>();
        if (!reader->open(path, *prefix, error))
            return nullptr;
        return reader;
    }
    auto reader = std::make_unique<PkgReader>();
    reader->allow_dlc = allow_dlc;
    if (!reader->open(path, error))
        return nullptr;
    return reader;
}

// The inner layer: the PFS, mounted over the placeholders with psvpfstools'
// own parsers, and decrypted one block at a time out of the source
struct Mount {
    std::unique_ptr<Source> source;
    // The same directory as Vita3K's path and as psvpfstools' own
    fs::path app_host;
    psvpfs::path app_dir;
    std::ostringstream log;
    std::shared_ptr<ICryptoOperations> cryptops;
    std::shared_ptr<IF00DKeyEncryptor> f00d;
    unsigned char klicensee[0x10]{};
    std::unique_ptr<FilesDbParser> files_db;
    std::unique_ptr<UnicvDbParser> unicv_db;
    std::unique_ptr<PfsPageMapper> pages;

    struct Pending {
        const Source::Entry *entry = nullptr;
        const sce_ng_pfs_file_t *file = nullptr;
        std::shared_ptr<sce_iftbl_base_t> table;
    };
    // Placeholders still to be decrypted, by upper-case host path
    std::map<std::string, Pending> pending;
    // Placeholders whose file an update replaces, by upper-case host path:
    // read from the update's own file in ux0/patch, never copied
    std::map<std::string, fs::path> redirects;
    bool take_redirect(const std::string &key, const fs::path &host);
    std::recursive_mutex mutex;

    // A file decrypted out of the PKG whole, in memory (an icv file, or one
    // the PFS keeps unencrypted), written beside its place and renamed into it
    bool materialize(Pending &p);
    // A streamable file decrypted out of the PKG a block at a time, written
    // beside its place and renamed into it: written once
    bool stream_to_place(const Pending &p);
    // The keys a pending file is decrypted with, as PfsFile::init_crypt_ctx
    // derives them
    void crypt_keys(const Pending &p, CryptEngineData &data, derive_keys_ctx &drv);

    // Persistent Cache (set_cache_root): one sparse file per entry of the source
    // with the blocks decrypted so far at their place, and a list of which,
    // kept in memory and written when the mount goes (disk_flush): after a
    // crash the blocks of that run are only decrypted again (sco8487)
    fs::path cache_dir;
    // A DLC's: says its folder in ux0/addcont is this run's, not an install
    fs::path marker;
    struct DiskFile {
        bool loaded = false;
        bool dirty = false;
        std::set<std::uint32_t> blocks;
    };
    std::map<std::string, DiskFile> disk;
    fs::path disk_path(const Pending &p, const char *ext) const;
    fs::path disk_path(const std::string &name, const char *ext) const;
    // Every list a block was added to, written out whole
    void disk_flush();
    ~Mount() { disk_flush(); }
    DiskFile &disk_file(const Pending &p);
    bool disk_read(const Pending &p, std::uint32_t index, std::uint64_t at, std::vector<std::uint8_t> &out);
    void disk_write(const Pending &p, std::uint32_t index, std::uint64_t at, const std::vector<std::uint8_t> &data);

    // Whether a pending file can be read straight out of the PKG, decrypted a
    // signature block at a time: a unicv (game data) file or one the PFS
    // keeps unencrypted. An icv file has one hash tree over all of it, and is
    // decrypted whole on first open as before.
    bool streamable(const Pending &p) const;
    // Signature block `index` of a pending file, decrypted
    bool decrypt_block(const Pending &p, std::uint32_t index, std::vector<std::uint8_t> &out);
};

std::shared_ptr<Mount> s_mount;
// Updates laid over the game (mount_update), each read out of its own PKG
std::vector<std::shared_ptr<Mount>> s_layers;
// DLC laid out lazily in ux0/addcont (mount_dlc), read where they lie
std::vector<std::shared_ptr<Mount>> s_dlcs;

// Persistent Cache's folder (set_cache_root), empty for none
fs::path s_cache_root;

// The mount of `mounts` with a placeholder at key still to be read out of its source
std::shared_ptr<Mount> with_pending(const std::vector<std::shared_ptr<Mount>> &mounts, const std::string &key) {
    for (const auto &m : mounts) {
        std::lock_guard lock(m->mutex);
        if (m->pending.contains(key))
            return m;
    }
    return nullptr;
}
std::shared_ptr<Mount> dlc_pending(const std::string &key) {
    return with_pending(s_dlcs, key);
}

std::uint32_t fnv1a(const std::string &text) {
    std::uint32_t h = 2166136261u;
    for (unsigned char c : text) {
        h ^= c;
        h *= 16777619u;
    }
    return h;
}

fs::path Mount::disk_path(const Pending &p, const char *ext) const {
    return disk_path(p.entry->name, ext);
}

fs::path Mount::disk_path(const std::string &entry, const char *ext) const {
    char name[32];
    snprintf(name, sizeof(name), "%08x%s", fnv1a(entry), ext);
    return cache_dir / name;
}

// A file's data on the disk, not only in the system's cache, before the list
// that names its blocks goes in: a power cut right after the game closed left
// a new list over blocks not yet written (sco8487)
static void sync_to_disk(const fs::path &path) {
#ifdef _WIN32
    HANDLE h = CreateFileW(path.wstring().c_str(), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL, nullptr);
    if (h != INVALID_HANDLE_VALUE) {
        FlushFileBuffers(h);
        CloseHandle(h);
    }
#else
    const int fd = ::open(path.string().c_str(), O_RDONLY);
    if (fd >= 0) {
        ::fsync(fd);
        ::close(fd);
    }
#endif
}

void Mount::disk_flush() {
    if (cache_dir.empty())
        return;
    for (auto &[name, f] : disk) {
        if (!f.dirty)
            continue;
        // Runs of blocks, a line each, written beside the list and renamed
        // over it: a crash leaves the old list or the new one, never half of
        // one; the blocks' data and the new list are on the disk before the
        // rename (sco8487)
        sync_to_disk(disk_path(name, ".bin"));
        const fs::path idx = disk_path(name, ".idx");
        const fs::path tmp = disk_path(name, ".idx.tmp");
        {
            std::ofstream out(tmp.string(), std::ios::trunc);
            for (auto it = f.blocks.begin(); it != f.blocks.end();) {
                const std::uint32_t first = *it;
                std::uint32_t last = first;
                for (++it; it != f.blocks.end() && *it == last + 1; ++it)
                    last = *it;
                if (first == last)
                    out << first << "\n";
                else
                    out << first << "-" << last << "\n";
            }
            if (!out.flush())
                continue;
        }
        sync_to_disk(tmp);
        std::error_code ec;
        fs::rename(tmp, idx, ec);
        if (ec)
            fs::remove(tmp, ec);
        else
            f.dirty = false;
    }
#ifndef _WIN32
    // and the renames themselves, which live in the directory
    const int dir = ::open(cache_dir.string().c_str(), O_RDONLY);
    if (dir >= 0) {
        ::fsync(dir);
        ::close(dir);
    }
#endif
}

Mount::DiskFile &Mount::disk_file(const Pending &p) {
    DiskFile &f = disk[p.entry->name];
    if (!f.loaded) {
        f.loaded = true;
        // A line a run of blocks, "first-last", or one block alone (as
        // the lists of the builds that wrote a line per block have them)
        std::ifstream in(disk_path(p, ".idx").string());
        std::string line;
        while (std::getline(in, line)) {
            char *end = nullptr;
            const unsigned long first = std::strtoul(line.c_str(), &end, 10);
            if (end == line.c_str())
                continue;
            unsigned long last = first;
            if (*end == '-')
                last = std::strtoul(end + 1, nullptr, 10);
            for (unsigned long i = first; i <= last && i - first < (1u << 24); i++)
                f.blocks.insert(static_cast<std::uint32_t>(i));
        }
    }
    return f;
}

bool Mount::disk_read(const Pending &p, std::uint32_t index, std::uint64_t at, std::vector<std::uint8_t> &out) {
    if (cache_dir.empty() || !disk_file(p).blocks.count(index))
        return false;
    std::ifstream in(disk_path(p, ".bin").string(), std::ios::binary);
    in.seekg(static_cast<std::streamoff>(at));
    in.read(reinterpret_cast<char *>(out.data()), static_cast<std::streamsize>(out.size()));
    return static_cast<std::size_t>(in.gcount()) == out.size();
}

void Mount::disk_write(const Pending &p, std::uint32_t index, std::uint64_t at, const std::vector<std::uint8_t> &data) {
    if (cache_dir.empty())
        return;
    DiskFile &f = disk_file(p);
    if (f.blocks.count(index))
        return;
    const fs::path bin = disk_path(p, ".bin");
    std::error_code ec;
    if (!fs::exists(bin, ec)) {
        { std::ofstream create(bin.string(), std::ios::binary); }
        mark_sparse(bin);
    }
    {
        std::fstream out(bin.string(), std::ios::binary | std::ios::in | std::ios::out);
        if (!out)
            return;
        out.seekp(static_cast<std::streamoff>(at));
        out.write(reinterpret_cast<const char *>(data.data()), static_cast<std::streamsize>(data.size()));
        if (!out)
            return;
    }
    f.blocks.insert(index);
    f.dirty = true;
}

void Mount::crypt_keys(const Pending &p, CryptEngineData &data, derive_keys_ctx &drv) {
    const sce_ng_pfs_header_t &ngpfs = files_db->get_header();
    const auto header = p.table->get_header();
    memset(&data, 0, sizeof(data));
    data.klicensee = klicensee;
    data.files_salt = ngpfs.files_salt;
    data.icv_salt = p.table->get_icv_salt();
    data.mode_index = img_spec_to_mode_index(ngpfs.image_spec);
    data.crypto_engine_flag = img_spec_to_crypto_engine_flag(ngpfs.image_spec) | CRYPTO_ENGINE_THROW_ERROR;
    data.key_id = ngpfs.key_id;
    data.fs_attr = p.file->file.m_info.get_original_type();
    data.block_size = header->get_fileSectorSize();
    memset(&drv, 0, sizeof(drv));
    drv.db_type = settings_to_db_type(data.mode_index, data.fs_attr);
    drv.icv_version = header->get_version();
    if (is_gamedata(data.mode_index) && has_dbseed(drv.db_type, drv.icv_version))
        memcpy(drv.dbseed, header->get_dbseed(), 0x14);
    setup_crypt_packet_keys(cryptops, f00d, &data, &drv);
}

// Collects a merkle tree's leaves (as PfsFile.cpp's collect_leaf)
int collect_leaf_node(std::shared_ptr<merkle_tree_node<icv>> node, void *ctx) {
    if (node->isLeaf())
        static_cast<std::vector<std::shared_ptr<merkle_tree_node<icv>>> *>(ctx)->push_back(node);
    return 0;
}

// What PfsFile::decrypt_icv_file does, with the file read out of the PKG into
// memory rather than from disk: an icv file has its sectors' hashes in one
// signature page, so it is a few sectors at most (psvpfstools refuses one with
// more), and those hashes are the leaves of a merkle tree, put back into the
// order of the sectors here
bool Mount::materialize(Pending &p) {
    std::vector<std::uint8_t> data(static_cast<std::size_t>(p.entry->size));
    if (!source->read(p.entry->offset, data.data(), data.size()))
        return false;
    std::size_t length = data.size();
    if (p.file && is_encrypted(p.file->file.m_info.header.type)) {
        if (!p.table || p.table->m_blocks.empty())
            return false;
        const auto header = p.table->get_header();
        if (header->get_numHashes() > header->get_binTreeNumMaxAvail())
            return false;
        CryptEngineData keys;
        derive_keys_ctx drv;
        crypt_keys(p, keys, drv);
        const std::uint32_t sector_size = header->get_fileSectorSize();
        std::uint32_t tail = static_cast<std::uint32_t>(data.size() % sector_size);
        if (tail == 0)
            tail = sector_size;

        sig_tbl_t &block = p.table->m_blocks.front();
        const std::uint32_t sig_size = block.get_header()->get_sigSize();
        std::vector<std::uint8_t> signatures;
        const bool unicv = db_type_to_is_unicv(drv.db_type);
        if (unicv) {
            for (const auto &sig : block.m_signatures)
                signatures.insert(signatures.end(), sig.m_data.begin(), sig.m_data.begin() + sig_size);
        } else {
            std::shared_ptr<merkle_tree<icv>> tree = generate_merkle_tree<icv>(header->get_numSectors());
            index_merkle_tree(tree);
            std::vector<std::shared_ptr<merkle_tree_node<icv>>> leaves;
            walk_tree(tree, collect_leaf_node, &leaves);
            if (tree->nLeaves != leaves.size())
                return false;
            std::map<std::uint32_t, const icv *> by_sector;
            for (std::uint32_t i = tree->nNodes - tree->nLeaves, j = 0; i < block.m_signatures.size() && j < leaves.size(); i++, j++)
                by_sector.emplace(leaves[j]->m_index, &block.m_signatures[i]);
            for (const auto &[sector, sig] : by_sector)
                signatures.insert(signatures.end(), sig->m_data.begin(), sig->m_data.begin() + sig_size);
        }

        CryptEngineSubctx sub;
        memset(&sub, 0, sizeof(sub));
        sub.opt_code = CRYPT_ENGINE_READ;
        sub.data = &keys;
        sub.nBlocks = unicv ? block.get_header()->get_nSignatures() : header->get_numSectors();
        sub.sector_base = 0;
        sub.tail_size = tail;
        sub.signature_table = signatures.data();
        sub.work_buffer0 = data.data();
        sub.work_buffer1 = data.data();
        CryptEngineWorkCtx work;
        work.subctx = &sub;
        work.error = 0;
        try {
            pfs_decrypt(cryptops, f00d, &work);
        } catch (const std::exception &e) {
            lr_log(RETRO_LOG_ERROR, "PKG: %s: %s\n", p.entry->name.c_str(), e.what());
            return false;
        }
        if (work.error < 0)
            return false;
        // the PFS pads an icv file to a whole sector; files.db has its size
        length = static_cast<std::size_t>(std::min<std::uint64_t>(p.file->file.m_info.header.size, data.size()));
    }
    const fs::path host = app_host / p.entry->name;
    const fs::path part = fs_utils::path_concat(host, ".part");
    {
        std::ofstream out(part, std::ios::binary | std::ios::trunc);
        out.write(reinterpret_cast<const char *>(data.data()), static_cast<std::streamsize>(length));
        if (!out)
            return false;
    }
    std::error_code ec;
    fs::rename(part, host, ec);
    return !ec;
}

bool Mount::stream_to_place(const Pending &p) {
    const fs::path host = app_host / p.entry->name;
    const fs::path part = fs_utils::path_concat(host, ".part");
    std::uint64_t written = 0;
    {
        std::ofstream out(part, std::ios::binary | std::ios::trunc);
        std::vector<std::uint8_t> block;
        for (std::uint32_t index = 0; out && decrypt_block(p, index, block); index++) {
            out.write(reinterpret_cast<const char *>(block.data()), static_cast<std::streamsize>(block.size()));
            written += block.size();
        }
        if (!out)
            written = 0;
    }
    std::error_code ec;
    if (written != p.entry->size) {
        fs::remove(part, ec);
        return false;
    }
    fs::rename(part, host, ec);
    return !ec;
}

bool Mount::streamable(const Pending &p) const {
    if (!p.file || !is_encrypted(p.file->file.m_info.header.type))
        return true;
    if (!p.table)
        return false;
    const sce_ng_pfs_header_t &ngpfs = files_db->get_header();
    const auto mode_index = img_spec_to_mode_index(ngpfs.image_spec);
    const auto db_type = settings_to_db_type(mode_index, p.file->file.m_info.get_original_type());
    return db_type_to_is_unicv(db_type);
}

// What PfsFile::decrypt_unicv_file does for each block of a file, for one
// block: block `index` covers sectors index * binTreeNumMaxAvail on, has its
// own signature table, and the last one may end in a part sector
bool Mount::decrypt_block(const Pending &p, std::uint32_t index, std::vector<std::uint8_t> &out) {
    const std::uint64_t size = p.entry->size;
    if (!p.file || !is_encrypted(p.file->file.m_info.header.type)) {
        // The PKG's bytes are the file; blocks of 1 MB
        const std::uint64_t at = std::uint64_t(index) << 20;
        if (at >= size)
            return false;
        out.resize(static_cast<std::size_t>(std::min<std::uint64_t>(1 << 20, size - at)));
        if (disk_read(p, index, at, out))
            return true;
        if (!source->read(p.entry->offset + at, out.data(), out.size()))
            return false;
        disk_write(p, index, at, out);
        return true;
    }
    const auto header = p.table->get_header();
    const std::uint64_t sector_size = header->get_fileSectorSize();
    const std::uint64_t per_block = header->get_binTreeNumMaxAvail();
    const std::uint64_t block_bytes = per_block * sector_size;
    const bool single = header->get_numSectors() <= per_block;
    const std::uint64_t at = single ? 0 : index * block_bytes;
    if (at >= size || (single && index != 0) || index >= p.table->m_blocks.size())
        return false;
    const std::uint64_t length = single ? size : std::min(block_bytes, size - at);
    out.resize(static_cast<std::size_t>(length));
    if (disk_read(p, index, at, out))
        return true;
    if (!source->read(p.entry->offset + at, out.data(), out.size()))
        return false;
    std::uint32_t tail = static_cast<std::uint32_t>(length % sector_size);
    if (tail == 0)
        tail = static_cast<std::uint32_t>(sector_size);

    // PfsFile::init_crypt_ctx for a unicv file
    sig_tbl_t &block = p.table->m_blocks[index];
    CryptEngineData data;
    derive_keys_ctx drv;
    crypt_keys(p, data, drv);

    std::vector<std::uint8_t> signatures(block.m_signatures.size() * block.get_header()->get_sigSize());
    std::size_t sig_at = 0;
    for (const auto &sig : block.m_signatures) {
        memcpy(signatures.data() + sig_at, sig.m_data.data(), block.get_header()->get_sigSize());
        sig_at += block.get_header()->get_sigSize();
    }
    CryptEngineSubctx sub;
    memset(&sub, 0, sizeof(sub));
    sub.opt_code = CRYPT_ENGINE_READ;
    sub.data = &data;
    sub.nBlocks = block.get_header()->get_nSignatures();
    sub.sector_base = static_cast<std::uint32_t>(single ? 0 : index * per_block);
    sub.tail_size = tail;
    sub.signature_table = signatures.data();
    sub.work_buffer0 = out.data();
    sub.work_buffer1 = out.data();
    CryptEngineWorkCtx work;
    work.subctx = &sub;
    work.error = 0;
    try {
        pfs_decrypt(cryptops, f00d, &work);
    } catch (const std::exception &e) {
        lr_log(RETRO_LOG_ERROR, "PKG: %s, block %u: %s\n", p.entry->name.c_str(), index, e.what());
        return false;
    }
    if (work.error < 0)
        return false;
    disk_write(p, index, at, out);
    return true;
}

// A pending file read straight out of the PKG: what FileStats reads through
// in place of the file on disk (open_file_hook), decrypting the blocks it is
// asked for and keeping the last few. Holds the mount, so a file the game
// still has open outlives unmount().
struct Stream final : ServedFile {
    std::shared_ptr<Mount> mount;
    Mount::Pending pending;
    std::uint64_t position = 0;
    std::uint64_t block_bytes = 0;
    struct Cached {
        std::uint32_t index;
        std::vector<std::uint8_t> data;
    };
    std::vector<Cached> cache; // most recent last

    const std::vector<std::uint8_t> *block(std::uint32_t index) {
        for (std::size_t i = 0; i < cache.size(); i++) {
            if (cache[i].index == index) {
                if (i + 1 != cache.size())
                    std::rotate(cache.begin() + i, cache.begin() + i + 1, cache.end());
                return &cache.back().data;
            }
        }
        Cached c{ index, {} };
        {
            std::lock_guard lock(mount->mutex);
            if (!mount->decrypt_block(pending, index, c.data))
                return nullptr;
        }
        if (cache.size() >= 4)
            cache.erase(cache.begin());
        cache.push_back(std::move(c));
        return &cache.back().data;
    }

    std::int64_t read(void *data, std::size_t size) override {
        char *buf = static_cast<char *>(data);
        const std::uint64_t file_size = pending.entry->size;
        std::size_t done = 0;
        while (done < size && position < file_size) {
            const std::uint32_t index = static_cast<std::uint32_t>(position / block_bytes);
            const std::vector<std::uint8_t> *bytes = block(index);
            if (!bytes)
                return done ? static_cast<std::int64_t>(done) : -1;
            const std::uint64_t in_block = position - std::uint64_t(index) * block_bytes;
            if (in_block >= bytes->size())
                break;
            const std::size_t n = static_cast<std::size_t>(std::min<std::uint64_t>(size - done, bytes->size() - in_block));
            memcpy(buf + done, bytes->data() + in_block, n);
            done += n;
            position += n;
        }
        return static_cast<std::int64_t>(done);
    }

    std::int64_t seek(std::int64_t offset, int whence) override {
        const std::int64_t base = whence == SEEK_SET ? 0
            : whence == SEEK_CUR                     ? static_cast<std::int64_t>(position)
                                                     : static_cast<std::int64_t>(pending.entry->size);
        if (base + offset < 0)
            return -1;
        position = static_cast<std::uint64_t>(base + offset);
        return static_cast<std::int64_t>(position);
    }
};

// An update's file in ux0/patch, served for the game's placeholder
struct PlainFile final : ServedFile {
    FILE *file = nullptr;
    ~PlainFile() override {
        if (file)
            fclose(file);
    }
    std::int64_t read(void *data, std::size_t size) override {
        const std::size_t n = fread(data, 1, size, file);
        return n == 0 && ferror(file) ? -1 : static_cast<std::int64_t>(n);
    }
    std::int64_t seek(std::int64_t offset, int whence) override {
        // seek_file is SEEK_SET only
#ifdef _WIN32
        if (_fseeki64(file, offset, whence) != 0)
            return -1;
        return _ftelli64(file);
#else
        if (fseeko(file, static_cast<off_t>(offset), whence) != 0)
            return -1;
        return static_cast<std::int64_t>(ftello(file));
#endif
    }
};

std::shared_ptr<ServedFile> make_stream(const std::shared_ptr<Mount> &m, const Mount::Pending &pending) {
    auto s = std::make_shared<Stream>();
    s->mount = m;
    s->pending = pending;
    if (!s->pending.file || !is_encrypted(s->pending.file->file.m_info.header.type))
        s->block_bytes = 1 << 20;
    else {
        const auto header = s->pending.table->get_header();
        s->block_bytes = header->get_numSectors() <= header->get_binTreeNumMaxAvail()
            ? std::max<std::uint64_t>(s->pending.entry->size, 1)
            : std::uint64_t(header->get_binTreeNumMaxAvail()) * header->get_fileSectorSize();
    }
    return s;
}

// The update layer whose not yet decrypted file a redirect points to
std::shared_ptr<Mount> layer_pending(const std::string &key) {
    return with_pending(s_layers, key);
}

// An update layer's file decrypted in full where its layer laid it out
void materialize_in_layer(const fs::path &target) {
    const std::string key = upper(target.lexically_normal().generic_string());
    std::shared_ptr<Mount> layer = layer_pending(key);
    if (!layer)
        return;
    std::lock_guard lock(layer->mutex);
    auto it = layer->pending.find(key);
    if (it == layer->pending.end())
        return;
    Mount::Pending p = it->second;
    layer->pending.erase(it);
    if (!layer->materialize(p))
        lr_log(RETRO_LOG_ERROR, "PKG: could not decrypt the update's %s\n", p.entry->name.c_str());
}

// A file opened to write, or read whole (read_file): the update's copy put in
// the placeholder's place, and no longer redirected
bool Mount::take_redirect(const std::string &key, const fs::path &host) {
    auto it = redirects.find(key);
    if (it == redirects.end())
        return false;
    const fs::path target = it->second;
    redirects.erase(it);
    materialize_in_layer(target);
    std::error_code ec;
    fs::copy_file(target, host, fs::copy_options::overwrite_existing, ec);
    return true;
}

// open_file_hook: a pending file opened to read is served out of its source
std::shared_ptr<ServedFile> on_open_file(const fs::path &host, int open_mode) {
    std::shared_ptr<Mount> m = s_mount;
    if (!m || can_write(open_mode))
        return nullptr;
    std::lock_guard lock(m->mutex);
    const std::string key = upper(host.lexically_normal().generic_string());
    if (auto r = m->redirects.find(key); r != m->redirects.end()) {
        // An update's file: out of the update's PKG while it is not decrypted,
        // from where it lies once it is
        const fs::path target = r->second;
        const std::string target_key = upper(target.lexically_normal().generic_string());
        if (std::shared_ptr<Mount> layer = layer_pending(target_key)) {
            std::lock_guard layer_lock(layer->mutex);
            auto lp = layer->pending.find(target_key);
            if (lp != layer->pending.end() && layer->streamable(lp->second))
                return make_stream(layer, lp->second);
        }
        materialize_in_layer(target);
        auto f = std::make_shared<PlainFile>();
        f->file = FOPEN(target.c_str(), "rb");
        return f->file ? f : nullptr;
    }
    auto it = m->pending.find(key);
    if (it != m->pending.end())
        return m->streamable(it->second) ? make_stream(m, it->second) : nullptr;
    if (std::shared_ptr<Mount> dlc = dlc_pending(key)) {
        std::lock_guard dlc_lock(dlc->mutex);
        auto d = dlc->pending.find(key);
        if (d != dlc->pending.end() && dlc->streamable(d->second))
            return make_stream(dlc, d->second);
    }
    return nullptr;
}

// A DLC's file decrypted in full where it lies
void materialize_dlc(const std::string &key) {
    std::shared_ptr<Mount> dlc = dlc_pending(key);
    if (!dlc)
        return;
    std::lock_guard lock(dlc->mutex);
    auto it = dlc->pending.find(key);
    if (it == dlc->pending.end())
        return;
    Mount::Pending p = it->second;
    dlc->pending.erase(it);
    if (!dlc->materialize(p))
        lr_log(RETRO_LOG_ERROR, "PKG: could not decrypt the DLC's %s\n", p.entry->name.c_str());
}

void on_host_file(const fs::path &host) {
    Mount *m = s_mount.get();
    if (!m)
        return;
    std::lock_guard lock(m->mutex);
    const std::string key = upper(host.lexically_normal().generic_string());
    if (m->take_redirect(key, host))
        return;
    auto it = m->pending.find(key);
    if (it == m->pending.end()) {
        materialize_dlc(key);
        return;
    }
    Mount::Pending p = it->second;
    m->pending.erase(it);
    if (m->materialize(p))
        lr_log(RETRO_LOG_DEBUG, "PKG: decrypted %s on first read\n", p.entry->name.c_str());
    else
        lr_log(RETRO_LOG_ERROR, "PKG: could not decrypt %s\n", p.entry->name.c_str());
}

// host_open_hook: a file opened to write, or one that cannot be read out of
// the PKG as it goes, is decrypted whole first, as before
void on_host_open(const fs::path &host, int open_mode) {
    Mount *m = s_mount.get();
    if (!m)
        return;
    {
        std::lock_guard lock(m->mutex);
        const std::string key = upper(host.lexically_normal().generic_string());
        if (m->redirects.count(key)) {
            if (can_write(open_mode))
                m->take_redirect(key, host);
            return;
        }
        auto it = m->pending.find(key);
        if (it == m->pending.end()) {
            if (std::shared_ptr<Mount> dlc = dlc_pending(key)) {
                bool stream = false;
                {
                    std::lock_guard dlc_lock(dlc->mutex);
                    auto d = dlc->pending.find(key);
                    stream = d != dlc->pending.end() && !can_write(open_mode) && dlc->streamable(d->second);
                }
                if (!stream)
                    materialize_dlc(key);
            }
            return;
        }
        if (!can_write(open_mode) && m->streamable(it->second))
            return;
    }
    on_host_file(host);
}

// Which file each unicv.db table is, as psvpfstools' bruteforce_map finds it -
// the HMAC of a file's first sector against the table's first signature - but
// with the first sectors read out of the PKG into memory rather than from the
// files on disk
bool map_by_first_sector(Mount &m, const std::vector<const Source::Entry *> &candidates, std::uint64_t sector,
    std::map<std::uint32_t, sce_junction> &map) {
    const sce_ng_pfs_header_t &ngpfs = m.files_db->get_header();
    std::vector<std::pair<const Source::Entry *, std::vector<std::uint8_t>>> firsts;
    for (const Source::Entry *e : candidates) {
        if (e->size == 0)
            continue;
        std::vector<std::uint8_t> data(static_cast<std::size_t>(std::min(sector, e->size)));
        if (!m.source->read(e->offset, data.data(), data.size()))
            return false;
        firsts.emplace_back(e, std::move(data));
    }
    for (const auto &t : m.unicv_db->get_idatabase()->m_tables) {
        if (t->get_header()->get_numSectors() == 0)
            continue;
        unsigned char secret[0x14];
        scePfsUtilGetSecret(m.cryptops, m.f00d, secret, m.klicensee, ngpfs.files_salt,
            img_spec_to_crypto_engine_flag(ngpfs.image_spec), t->get_icv_salt(), 0);
        // the sector number, 0, is the salt
        unsigned char key[0x14];
        int sector_salt = 0;
        m.cryptops->hmac_sha1(reinterpret_cast<unsigned char *>(&sector_salt), key, 4, secret, 0x14);
        const unsigned char *zero_sector = t->m_blocks.front().m_signatures.front().m_data.data();
        auto it = firsts.begin();
        for (; it != firsts.end(); ++it) {
            unsigned char signature[0x14];
            m.cryptops->hmac_sha1(it->second.data(), signature, static_cast<int>(it->second.size()), key, 0x14);
            if (memcmp(signature, zero_sector, 0x14) == 0)
                break;
        }
        if (it == firsts.end()) {
            m.log << "No file for unicv.db table " << std::hex << t->get_icv_salt() << std::endl;
            return false;
        }
        const psvpfs::path real((m.app_host / it->first->name).lexically_normal().native());
        sce_junction junction(real);
        junction.link_to_real(real);
        map.emplace(t->get_icv_salt(), junction);
        firsts.erase(it);
    }
    return true;
}

// A content's folder (app_dir) laid out from a source: its PFS metadata and
// what is needed at start written, the rest placeholders of their size read
// out of the source as the game goes. A source with no PFS (an unencrypted
// VPK/ZIP or folder) has its files as they are. cache_name names its
// Persistent Cache folder, and source_id tells this source's cache from
// another's under the same name. For an install (for_install) there is no
// cache, only the PFS metadata is written out in full, and install() decrypts
// every other file straight out of the source afterwards.
std::shared_ptr<Mount> build_from(std::unique_ptr<Source> source, const std::string &source_id, const fs::path &app_dir,
    const std::string &zrif, const std::string &cache_name, std::string &error, bool for_install) {
    auto m = std::make_shared<Mount>();
    m->source = std::move(source);

    std::error_code ec;
    const bool has_pfs = std::any_of(m->source->entries().begin(), m->source->entries().end(),
        [](const Source::Entry &e) { return string_utils::tolower(e.name).starts_with("sce_pfs/"); });
    if (has_pfs) {
        const auto lic = decode_license_np(zrif);
        if (!lic) {
            error = "no license (zRIF) for the game";
            return nullptr;
        }
        memcpy(m->klicensee, lic->key, sizeof(m->klicensee));
    }

    // Persistent Cache: set before anything is decrypted, so that the files the game starts
    // with are read out of it too on the next run (sco8487)
    if (!for_install && !s_cache_root.empty()) {
        // Kept across sessions for this source only: another file under the same
        // name (a re-dump) starts the cache over
        m->cache_dir = s_cache_root / cache_name;
        const fs::path id_file = m->cache_dir / "pkg.id";
        const std::string id = source_id + " " + std::to_string(m->source->entries().size());
        std::string had;
        {
            std::ifstream in(id_file.string());
            std::getline(in, had);
        }
        if (had != id) {
            fs::remove_all(m->cache_dir, ec);
            fs::create_directories(m->cache_dir, ec);
            std::ofstream out(id_file.string());
            out << id << "\n";
        }
        lr_log(RETRO_LOG_INFO, "PKG: persistent cache in %s\n", m->cache_dir.string().c_str());
    }

    // Room for all of it that is not in the cache yet, the worst case, in both modes, or
    // the game is not started, as an install is not (sco8487): Run Without Installing
    // fills its placeholders in app_dir as the game reads them, the cache keeps them too
    if (!for_install) {
        std::uint64_t total = 0, cached = 0;
        for (const auto &e : m->source->entries())
            total += e.size;
        if (!m->cache_dir.empty()) {
            for (fs::directory_iterator it(m->cache_dir, ec), end; !ec && it != end; it.increment(ec))
                cached += fs::file_size(it->path(), ec);
        }
        const fs::path where = m->cache_dir.empty() ? app_dir.parent_path() : s_cache_root;
        fs::create_directories(where, ec);
        const fs::space_info space = fs::space(where, ec);
        if (!ec && total > cached && space.available < total - cached) {
            error = fmt::format("{} {:.1f} GiB needed, {:.1f} GiB free", NO_ROOM, (total - cached) / 1073741824.0,
                space.available / 1073741824.0);
            return nullptr;
        }
    }

    fs::remove_all(app_dir, ec);
    fs::create_directories(app_dir);
    m->app_host = app_dir.lexically_normal();
    m->app_dir = psvpfs::path(m->app_host.native());

    // A PFS with one hash per block (unicv.db, as every game's has) has its
    // files told apart here, by their first sectors read out of the PKG
    // (map_by_first_sector), so nothing of them is written before it is
    // decrypted. One with icv.db goes to psvpfstools' page mapper, which reads
    // the first sectors from disk.
    const bool unicv_image = std::any_of(m->source->entries().begin(), m->source->entries().end(),
        [](const Source::Entry &e) { return string_utils::tolower(e.name) == "sce_pfs/unicv.db"; });

    // Directories, and the PFS metadata in full: it is needed to mount the
    // rest. The files read before or as the game starts are decrypted once the
    // PFS is mounted (for an icv.db PFS they are written out in full first).
    std::vector<const Source::Entry *> rest, at_start;
    for (const auto &e : m->source->entries()) {
        const fs::path host = app_dir / e.name;
        if (e.directory) {
            fs::create_directories(host);
            continue;
        }
        fs::create_directories(host.parent_path());
        const std::string name = string_utils::tolower(e.name);
        const bool metadata = name.starts_with("sce_pfs/");
        const bool start = !for_install && !metadata
            && (e.size <= EAGER_SIZE || name.starts_with("sce_sys/") || name.starts_with("sce_module/") || name == "eboot.bin");
        if (metadata || (start && !unicv_image)) {
            if (!m->source->write_entry(e, host, e.size)) {
                error = "cannot write " + e.name;
                return nullptr;
            }
        } else {
            rest.push_back(&e);
            if (start)
                at_start.push_back(&e);
        }
    }

    if (!has_pfs) {
        // Unencrypted: each placeholder is read out of the source as it is
        for (const Source::Entry *e : rest) {
            if (!m->source->write_entry(*e, app_dir / e->name, 0)) {
                error = "cannot write " + e->name;
                return nullptr;
            }
            Mount::Pending p;
            p.entry = e;
            m->pending[upper((app_dir / e->name).lexically_normal().generic_string())] = p;
        }
    } else {
        m->cryptops = CryptoOperationsFactory::create(CryptoOperationsTypes::openssl);
        m->f00d = F00DKeyEncryptorFactory::create(F00DEncryptorTypes::native, m->cryptops);
        m->unicv_db = std::make_unique<UnicvDbParser>(m->app_dir, m->log);
        if (m->unicv_db->parse() < 0) {
            error = "cannot read the PFS (unicv.db)";
            return nullptr;
        }

        // The rest as placeholders of their size, which files.db is checked
        // against: holes, no data, for a unicv.db PFS; for an icv.db one the page
        // mapper reads the first sector from each, so that much is written
        std::uint64_t sector = 0;
        for (const auto &t : m->unicv_db->get_idatabase()->m_tables)
            sector = std::max<std::uint64_t>(sector, t->get_header()->get_fileSectorSize());
        if (sector == 0)
            sector = 0x8000;
        for (const Source::Entry *e : rest) {
            if (!m->source->write_entry(*e, app_dir / e->name, unicv_image ? 0 : std::min(sector, e->size))) {
                error = "cannot write " + e->name;
                return nullptr;
            }
        }

        m->files_db = std::make_unique<FilesDbParser>(m->cryptops, m->f00d, m->log, m->klicensee, m->app_dir);
        std::map<std::uint32_t, sce_junction> first_sector_map;
        const std::map<std::uint32_t, sce_junction> *page_map_ptr = &first_sector_map;
        bool mapped = m->files_db->parse() >= 0;
        if (mapped && unicv_image)
            mapped = map_by_first_sector(*m, rest, sector, first_sector_map);
        else if (mapped) {
            m->pages = std::make_unique<PfsPageMapper>(m->cryptops, m->f00d, m->log, m->klicensee, m->app_dir);
            mapped = m->pages->bruteforce_map(m->files_db, m->unicv_db) >= 0;
            page_map_ptr = &m->pages->get_pageMap();
        }
        if (!mapped) {
            lr_log(RETRO_LOG_ERROR, "PKG: PFS mount failed:\n%s\n", m->log.str().c_str());
            error = "cannot mount the PFS (a wrong license?)";
            return nullptr;
        }

        // Which PFS file and table each placeholder is
        std::map<std::string, const sce_ng_pfs_file_t *> files;
        for (const auto &f : m->files_db->get_files())
            files[upper(f.path().get_value().lexically_normal().generic_string())] = &f;
        std::map<std::string, const Source::Entry *> entries;
        for (const auto &e : m->source->entries())
            if (!e.directory)
                entries[upper((app_dir / e.name).lexically_normal().generic_string())] = &e;
        const auto &page_map = *page_map_ptr;
        std::vector<std::string> eager_now;
        for (const auto &t : m->unicv_db->get_idatabase()->m_tables) {
            if (t->get_header()->get_numSectors() == 0)
                continue;
            const auto page = page_map.find(t->get_icv_salt());
            if (page == page_map.end())
                continue;
            const std::string key = upper(page->second.get_value().lexically_normal().generic_string());
            const auto file = files.find(key);
            const auto entry = entries.find(key);
            if (file == files.end() || entry == entries.end())
                continue;
            Mount::Pending p;
            p.entry = entry->second;
            p.file = file->second;
            p.table = t;
            m->pending[key] = p;
            if (std::find(rest.begin(), rest.end(), entry->second) == rest.end())
                eager_now.push_back(key);
        }

        // An icv.db PFS: the files written in full are still PFS-encrypted, and are
        // decrypted now
        for (const std::string &key : eager_now) {
            Mount::Pending p = m->pending[key];
            m->pending.erase(key);
            if (!m->materialize(p)) {
                error = "cannot decrypt " + p.entry->name;
                return nullptr;
            }
        }
        // Files the PFS lists without data are only what the PKG holds; anything
        // still pending that the PFS did not map is copied as it is
        for (const Source::Entry *e : rest) {
            const std::string key = upper((app_dir / e->name).lexically_normal().generic_string());
            if (!m->pending.contains(key)) {
                Mount::Pending p;
                p.entry = e;
                m->pending[key] = p;
            }
        }
        // A unicv.db PFS: the files the game starts with are decrypted into their
        // place now, each written once (an icv file whole, in memory)
        for (const Source::Entry *e : at_start) {
            const std::string key = upper((app_dir / e->name).lexically_normal().generic_string());
            Mount::Pending p = m->pending[key];
            m->pending.erase(key);
            if (!(m->streamable(p) ? m->stream_to_place(p) : m->materialize(p))) {
                error = "cannot decrypt " + e->name;
                return nullptr;
            }
        }
    }

    return m;
}

std::shared_ptr<Mount> build(const fs::path &path, const fs::path &app_dir, const std::string &zrif,
    const std::string &cache_name, std::string &error, bool allow_dlc = false, bool for_install = false) {
    auto reader = open_source(path, allow_dlc, error);
    if (!reader)
        return nullptr;
    std::error_code ec;
    const std::string id = std::to_string(fs::file_size(path, ec));
    return build_from(std::move(reader), id, app_dir, zrif, cache_name, error, for_install);
}

// Lays src_dir's files over the game's: a placeholder of each file's size in
// the game's folder, its reads redirected to the file in src_dir (an update,
// kept or read out of its own PKG). Nothing is copied. Returns the count.
unsigned overlay_dir(Mount &game, const fs::path &src_dir, bool skip_pfs) {
    std::error_code ec;
    unsigned replaced = 0;
    for (fs::recursive_directory_iterator it(src_dir, ec), end; it != end; it.increment(ec)) {
        if (ec)
            break;
        const fs::path rel = it->path().lexically_relative(src_dir);
        const std::string first = string_utils::tolower(rel.begin()->string());
        // Each package's own PFS metadata stays its own
        if (skip_pfs && first == "sce_pfs") {
            if (fs::is_directory(it->path(), ec))
                it.disable_recursion_pending();
            continue;
        }
        if (!fs::is_regular_file(it->path(), ec))
            continue;
        const fs::path to = game.app_host / rel;
        fs::create_directories(to.parent_path(), ec);
        {
            std::ofstream create(to, std::ios::binary | std::ios::trunc);
        }
        mark_sparse(to);
        fs::resize_file(to, fs::file_size(it->path(), ec), ec);
        const std::string key = upper(to.lexically_normal().generic_string());
        game.pending.erase(key);
        game.redirects[key] = it->path();
        replaced++;
    }
    return replaced;
}

void start(std::shared_ptr<Mount> m, const fs::path &app_dir);

} // namespace

bool mount(const fs::path &pkg_path, const fs::path &app_dir, const std::string &zrif, std::string &error) {
    unmount();
    {
        // An update's PKG is installed, not run (an update loaded on its own)
        PkgReader probe;
        if (!probe.open(pkg_path, error))
            return false;
        sfo::SfoAppInfo info;
        sfo::get_param_info(info, probe.sfo(), 1);
        if (info.app_category.find("gp") != std::string::npos) {
            error = "an update, not a game";
            return false;
        }
    }
    std::shared_ptr<Mount> m = build(pkg_path, app_dir, zrif, app_dir.filename().string(), error);
    if (!m)
        return false;
    start(std::move(m), app_dir);
    return true;
}

bool mount_folder(const fs::path &dir, const fs::path &app_dir, const std::string &zrif, std::string &error) {
    unmount();
    auto reader = std::make_unique<FolderReader>();
    if (!reader->open(dir, error))
        return false;
    // the folder's file count and size of its entries tell one dump from another under the name
    std::uint64_t total = 0;
    for (const auto &e : reader->entries())
        total += e.size;
    const std::string id = std::to_string(total);
    std::shared_ptr<Mount> m = build_from(std::move(reader), id, app_dir, zrif, app_dir.filename().string(), error, false);
    if (!m)
        return false;
    start(std::move(m), app_dir);
    return true;
}

bool mount_archive(const fs::path &archive_path, const std::string &prefix, const fs::path &app_dir,
    const std::string &zrif, std::string &error) {
    unmount();
    auto reader = std::make_unique<ArchiveReader>();
    if (!reader->open(archive_path, prefix, error))
        return false;
    std::error_code ec;
    const std::string id = std::to_string(fs::file_size(archive_path, ec)) + " " + prefix;
    std::shared_ptr<Mount> m = build_from(std::move(reader), id, app_dir, zrif, app_dir.filename().string(), error, false);
    if (!m)
        return false;
    start(std::move(m), app_dir);
    return true;
}

namespace {

// The game's folder served from its mount from now on: an update kept for it
// laid over it, and the file system hooks set
void start(std::shared_ptr<Mount> m, const fs::path &app_dir) {
    std::error_code ec;

    // An update kept for this game (ux0/patch/<title id>, see the installer):
    // its files over the game's, and those are no longer read from the PKG
    const fs::path patch_dir = app_dir.parent_path().parent_path() / "patch" / app_dir.filename();
    if (fs::is_directory(patch_dir, ec)) {
        const unsigned replaced = overlay_dir(*m, patch_dir, false);
        lr_log(RETRO_LOG_INFO, "PKG: update from %s laid over the game, %u files read from there\n", patch_dir.generic_string().c_str(), replaced);
    }

    // And how much of the game that is, by size: what is written out at start
    // against what is read out of the source as the game goes (sco8487). The
    // sizes are the source's own entries, nothing is read for them.
    std::uint64_t total_bytes = 0, pending_bytes = 0;
    for (const auto &e : m->source->entries())
        if (!e.directory)
            total_bytes += e.size;
    for (const auto &p : m->pending)
        pending_bytes += p.second.entry ? p.second.entry->size : 0;
    const std::uint64_t start_bytes = total_bytes - pending_bytes;
    lr_log(RETRO_LOG_INFO, "%s: running without installing, %u of %u files decrypted at start: %.1f MiB of %.1f MiB (%.0f%%), the other %.1f MiB read out of the %s as the game goes\n",
        m->source->kind(), static_cast<unsigned>(m->source->entries().size() - m->pending.size()), static_cast<unsigned>(m->source->entries().size()),
        start_bytes / 1048576.0, total_bytes / 1048576.0, total_bytes ? 100.0 * start_bytes / total_bytes : 0.0,
        pending_bytes / 1048576.0, m->source->kind());
    s_mount = std::move(m);
    vfs::host_file_hook = on_host_file;
    vfs::host_open_hook = on_host_open;
    open_file_hook = on_open_file;
}

} // namespace

bool install(const fs::path &pkg_path, const fs::path &dir, const std::string &zrif, std::string &error) {
    std::shared_ptr<Mount> m = build(pkg_path, dir, zrif, {}, error, true, true);
    std::error_code ec;
    const auto fail = [&](const std::string &why) {
        error = why;
        fs::remove_all(dir, ec);
        return false;
    };
    if (!m)
        return fail(error);

    std::uint64_t total = 0, done = 0;
    for (const auto &p : m->pending)
        total += p.second.entry->size;
    // Room for it all, or nothing is written (sco8487)
    const fs::space_info space = fs::space(dir, ec);
    if (!ec && space.available < total)
        return fail(fmt::format("{} {:.1f} GiB needed, {:.1f} GiB free", NO_ROOM, total / 1073741824.0,
            space.available / 1073741824.0));
    int reported = -1;
    for (auto &pending : m->pending) {
        Mount::Pending &p = pending.second;
        // An icv file has one hash tree over all of it and is decrypted whole
        if (!(m->streamable(p) ? m->stream_to_place(p) : m->materialize(p)))
            return fail("cannot decrypt " + p.entry->name);
        done += p.entry->size;
        const int percent = total ? static_cast<int>(100 * done / total) : 100;
        if (percent / 10 != reported / 10) {
            reported = percent;
            lr_log(RETRO_LOG_INFO, "PKG install: %d%% (%.1f of %.1f MiB)\n", percent, done / 1048576.0, total / 1048576.0);
        }
    }
    // Decrypted, as upstream's install leaves a package: its PFS metadata goes,
    // and with it what marks a folder as an install left encrypted
    fs::remove_all(m->app_host / "sce_pfs", ec);
    return true;
}

bool is_archive(const fs::path &path) {
    return is_archive_path(path);
}

bool pkg_sfo(const fs::path &pkg_path, std::vector<std::uint8_t> &sfo) {
    std::string error;
    std::error_code ec;
    if (fs::is_directory(pkg_path, ec)) {
        return fs_utils::read_data(pkg_path / "sce_sys" / "param.sfo", sfo) && !sfo.empty();
    }
    if (is_archive_path(pkg_path)) {
        auto reader = open_source(pkg_path, true, error);
        if (!reader)
            return false;
        for (const auto &e : reader->entries()) {
            if (!e.directory && string_utils::tolower(e.name) == "sce_sys/param.sfo") {
                sfo.resize(static_cast<std::size_t>(e.size));
                return !sfo.empty() && reader->read(e.offset, sfo.data(), sfo.size());
            }
        }
        return false;
    }
    PkgReader reader;
    reader.allow_dlc = true;
    if (!reader.open(pkg_path, error))
        return false;
    sfo = reader.sfo();
    return !sfo.empty();
}

bool pkg_info(const fs::path &pkg_path, PkgInfo &info) {
    std::vector<std::uint8_t> sfo;
    if (!pkg_sfo(pkg_path, sfo))
        return false;
    sfo::SfoAppInfo sfo_info;
    sfo::get_param_info(sfo_info, sfo, 1);
    info.title_id = sfo_info.app_title_id;
    info.category = sfo_info.app_category;
    info.version = sfo_info.app_version;
    info.content_id = sfo_info.app_content_id;
    info.title = sfo_info.app_title;
    return !info.title_id.empty();
}

bool mount_dlc(const fs::path &pkg_path, const std::string &content_id, const std::string &zrif, std::string &error) {
    if (!s_mount) {
        error = "no game mounted";
        return false;
    }
    const std::string title = s_mount->app_host.filename().string();
    const std::string dlc_id = content_id.size() > 20 ? content_id.substr(20) : content_id;
    const fs::path dir = s_mount->app_host.parent_path().parent_path() / "addcont" / title / dlc_id;
    std::error_code ec;
    // Left by a run the frontend did not end (its marker still there): no
    // installation, it goes
    const fs::path marker = s_mount->app_host.parent_path().parent_path() / "libretro_pkg" / ("dlc_" + title + "_" + dlc_id);
    if (fs::exists(marker, ec)) {
        fs::remove_all(dir, ec);
        fs::remove(marker, ec);
    }
    // Installed already: that installation is used
    if (fs::exists(dir, ec)) {
        error = "installed already";
        return false;
    }
    std::shared_ptr<Mount> dlc = build(pkg_path, dir, zrif, title + "_" + dlc_id, error, true);
    if (!dlc) {
        fs::remove_all(dir, ec);
        return false;
    }
    lr_log(RETRO_LOG_INFO, "PKG: DLC %s laid out in %s, read out of its PKG\n", pkg_path.generic_string().c_str(),
        dir.generic_string().c_str());
    fs::create_directories(marker.parent_path(), ec);
    std::ofstream(marker.string()).put('\n');
    dlc->marker = marker;
    s_dlcs.push_back(std::move(dlc));
    return true;
}

bool mount_update(const fs::path &pkg_path, const std::string &zrif, std::string &error) {
    if (!s_mount) {
        error = "no game mounted";
        return false;
    }
    const std::string title = s_mount->app_host.filename().string();
    // Laid out next to the game's lazy marker, removed with the game
    const fs::path dir = s_mount->app_host.parent_path().parent_path() / "libretro_pkg" / ("update_" + title);
    std::shared_ptr<Mount> layer = build(pkg_path, dir, zrif, title + "_update", error);
    if (!layer)
        return false;
    unsigned replaced;
    {
        std::lock_guard lock(s_mount->mutex);
        replaced = overlay_dir(*s_mount, layer->app_host, true);
    }
    lr_log(RETRO_LOG_INFO, "PKG: update %s laid over the game, %u files read out of it\n",
        pkg_path.generic_string().c_str(), replaced);
    s_layers.push_back(std::move(layer));
    return true;
}

void unmount() {
    vfs::host_file_hook = nullptr;
    vfs::host_open_hook = nullptr;
    open_file_hook = nullptr;
    std::error_code ec;
    for (const auto &layer : s_layers)
        fs::remove_all(layer->app_host, ec);
    s_layers.clear();
    for (const auto &dlc : s_dlcs) {
        fs::remove_all(dlc->app_host, ec);
        fs::remove(dlc->marker, ec);
    }
    s_dlcs.clear();
    if (!s_mount)
        return;
    fs::remove_all(s_mount->app_host, ec);
    s_mount.reset();
}

void set_cache_root(const fs::path &cache_root) {
    s_cache_root = cache_root;
}

// What tells one file system from another under dir: the volume's serial
// number and file system name (Windows), or the device and file system type;
// empty when it cannot be told
static std::string fs_signature(const fs::path &dir) {
#ifdef _WIN32
    wchar_t root[MAX_PATH] = {};
    if (!GetVolumePathNameW(dir.wstring().c_str(), root, MAX_PATH))
        return {};
    DWORD serial = 0;
    wchar_t name[MAX_PATH + 1] = {};
    if (!GetVolumeInformationW(root, nullptr, 0, &serial, nullptr, nullptr, name, MAX_PATH + 1))
        return {};
    return fmt::format("{:08x} {}", serial, fs::path(name).string());
#else
    struct stat st {};
    struct statfs sf {};
    if (stat(dir.string().c_str(), &st) != 0 || statfs(dir.string().c_str(), &sf) != 0)
        return {};
#ifdef __APPLE__
    return fmt::format("{:x} {}", static_cast<unsigned long long>(st.st_dev), sf.f_fstypename);
#else
    return fmt::format("{:x} {:x}", static_cast<unsigned long long>(st.st_dev), static_cast<unsigned long long>(sf.f_type));
#endif
#endif
}

// A file extended without a byte written: with holes, next to nothing of it is
// on the disk. Holes come in whole blocks (4 KiB; on NTFS, 64 KiB units), so
// one sector would not tell; 256 KiB is several of them on every file system,
// and where there are no holes it is little to write once (sco8487)
static bool probe_holes(const fs::path &dir) {
    constexpr std::uint64_t size = 256 * 1024;
    std::error_code ec;
    const fs::path probe = dir / "libretro_holes_probe.tmp";
    { std::ofstream create(probe, std::ios::binary | std::ios::trunc); }
    mark_sparse(probe);
    fs::resize_file(probe, size, ec);
    // Unknown counts as supported: the modes keep working either way, they only
    // save less
    bool holes = true;
    if (!ec) {
#ifdef _WIN32
        DWORD high = 0;
        const DWORD low = GetCompressedFileSizeW(probe.wstring().c_str(), &high);
        if (low != INVALID_FILE_SIZE || GetLastError() == NO_ERROR)
            holes = ((static_cast<std::uint64_t>(high) << 32) | low) < size / 2;
#else
        struct stat st {};
        if (stat(probe.string().c_str(), &st) == 0)
            holes = static_cast<std::uint64_t>(st.st_blocks) * 512 < size / 2;
#endif
    }
    fs::remove(probe, ec);
    return holes;
}

bool holes_supported(const fs::path &dir) {
    std::error_code ec;
    fs::create_directories(dir / "libretro_pkg", ec);
    // The answer is kept in ux0/libretro_pkg/holes with what file system it is
    // for, and tried again only when that changes (another drive, a copy onto
    // another file system) - once per system otherwise (sco8487)
    const fs::path note = dir / "libretro_pkg" / "holes";
    const std::string signature = fs_signature(dir);
    if (!signature.empty()) {
        std::ifstream in(note.string());
        std::string had, answer;
        std::getline(in, had);
        std::getline(in, answer);
        if (had == signature && (answer == "yes" || answer == "no"))
            return answer == "yes";
    }
    const bool holes = probe_holes(dir);
    if (!signature.empty()) {
        std::ofstream out(note.string(), std::ios::trunc);
        out << signature << "\n" << (holes ? "yes" : "no") << "\n";
    }
    lr_log(RETRO_LOG_INFO, "Sparse files on %s: %s\n", dir.string().c_str(), holes ? "yes" : "no");
    return holes;
}

bool has_cache_root() {
    return !s_cache_root.empty();
}

std::uint64_t disk_size(const fs::path &file) {
    std::error_code ec;
#ifdef _WIN32
    DWORD high = 0;
    const DWORD low = GetCompressedFileSizeW(file.wstring().c_str(), &high);
    if (low != INVALID_FILE_SIZE || GetLastError() == NO_ERROR)
        return (static_cast<std::uint64_t>(high) << 32) | low;
#else
    struct stat st {};
    if (stat(file.string().c_str(), &st) == 0)
        return static_cast<std::uint64_t>(st.st_blocks) * 512;
#endif
    const std::uint64_t size = fs::file_size(file, ec);
    return ec ? 0 : size;
}

bool mounted() {
    return s_mount != nullptr;
}

} // namespace lazy_pkg
