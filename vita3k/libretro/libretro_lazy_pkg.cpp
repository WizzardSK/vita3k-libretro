#include "libretro_lazy_pkg.h"

#include "libretro_state.h"

#include <io/filesystem.h>
#include <io/util.h>
#include <io/vfs.h>
#include <packages/pkg.h>
#include <packages/sfo.h>
#include <util/bytes.h>
#include <util/string_utils.h>

#include <CryptoOperationsFactory.h>
#include <F00DKeyEncryptorFactory.h>
#include <FilesDbParser.h>
#include <FlagOperations.h>
#include <PfsCryptEngine.h>
#include <PfsKeyGenerator.h>
#include <PfsFile.h>
#include <PfsPageMapper.h>
#include <UnicvDbParser.h>
#include <zRIF/licdec.h>

#include <openssl/evp.h>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <winioctl.h>
#endif

#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <map>
#include <memory>
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

// The outer layer: the PKG's own AES-128-CTR, which can start at any offset
class PkgReader {
public:
    struct Entry {
        std::string name;
        std::uint64_t offset = 0; // from the start of the data area
        std::uint64_t size = 0;
        bool directory = false;
    };

    ~PkgReader() {
        if (m_file)
            fclose(m_file);
    }

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
        if (content_type != 0x15) {
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

    int seek(std::uint64_t at) {
#ifdef _WIN32
        return _fseeki64(m_file, static_cast<__int64>(at), SEEK_SET);
#else
        return fseeko(m_file, static_cast<off_t>(at), SEEK_SET);
#endif
    }

    // Decrypted bytes of the data area, from offset
    bool read(std::uint64_t offset, void *out, std::size_t size) {
        std::lock_guard lock(m_mutex);
        const std::uint64_t aligned = offset & ~std::uint64_t(15);
        const std::size_t skip = static_cast<std::size_t>(offset - aligned);
        std::vector<std::uint8_t> buf(skip + size);
        if (seek(m_data_offset + aligned) != 0
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

    // An entry's bytes, as they are on the console: still PFS-encrypted
    bool write_entry(const Entry &e, const fs::path &to, std::uint64_t length) {
        fs::ofstream out(to, std::ios::binary | std::ios::trunc);
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
    const std::vector<std::uint8_t> &sfo() const { return m_sfo; }

private:
    FILE *m_file = nullptr;
    std::uint64_t m_data_offset = 0;
    std::uint8_t m_iv[16]{};
    std::uint8_t m_key[16]{};
    std::vector<std::uint8_t> m_sfo;
    std::vector<Entry> m_entries;
    std::mutex m_mutex;
};

// The inner layer: the PFS, mounted over the placeholders with psvpfstools'
// own parsers, and decrypted one file at a time with its PfsFile
struct Mount {
    PkgReader pkg;
    // The same two directories as Vita3K's paths and as psvpfstools' own
    fs::path app_host;
    fs::path dec_host; // where PfsFile writes a decrypted file, next to app_host
    psvpfs::path app_dir;
    psvpfs::path dec_dir;
    std::ostringstream log;
    std::shared_ptr<ICryptoOperations> cryptops;
    std::shared_ptr<IF00DKeyEncryptor> f00d;
    unsigned char klicensee[0x10]{};
    std::unique_ptr<FilesDbParser> files_db;
    std::unique_ptr<UnicvDbParser> unicv_db;
    std::unique_ptr<PfsPageMapper> pages;

    struct Pending {
        const PkgReader::Entry *entry = nullptr;
        const sce_ng_pfs_file_t *file = nullptr;
        std::shared_ptr<sce_iftbl_base_t> table;
        sce_junction junction{ psvpfs::path() };
    };
    // Placeholders still to be decrypted, by upper-case host path
    std::map<std::string, Pending> pending;
    // Placeholders whose file an update replaces, by upper-case host path:
    // read from the update's own file in ux0/patch, never copied
    std::map<std::string, fs::path> redirects;
    bool take_redirect(const std::string &key, const fs::path &host);
    std::recursive_mutex mutex;

    bool materialize(Pending &p);

    // Persistent Cache (set_cache_root): one sparse file per PKG entry with
    // the blocks decrypted so far at their place, and a list of which
    fs::path cache_dir;
    struct DiskFile {
        bool loaded = false;
        std::set<std::uint32_t> blocks;
    };
    std::map<std::string, DiskFile> disk;
    fs::path disk_path(const Pending &p, const char *ext) const;
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
fs::path s_cache_root;

std::uint32_t fnv1a(const std::string &text) {
    std::uint32_t h = 2166136261u;
    for (unsigned char c : text) {
        h ^= c;
        h *= 16777619u;
    }
    return h;
}

fs::path Mount::disk_path(const Pending &p, const char *ext) const {
    char name[32];
    snprintf(name, sizeof(name), "%08x%s", fnv1a(p.entry->name), ext);
    return cache_dir / name;
}

Mount::DiskFile &Mount::disk_file(const Pending &p) {
    DiskFile &f = disk[p.entry->name];
    if (!f.loaded) {
        f.loaded = true;
        std::ifstream in(disk_path(p, ".idx").string());
        std::uint32_t index;
        while (in >> index)
            f.blocks.insert(index);
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
    boost::system::error_code ec;
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
    std::ofstream idx(disk_path(p, ".idx").string(), std::ios::app);
    idx << index << "\n";
    f.blocks.insert(index);
}

bool Mount::materialize(Pending &p) {
    const fs::path host = app_host / p.entry->name;
    if (!pkg.write_entry(*p.entry, host, p.entry->size))
        return false;
    if (!p.file || !is_encrypted(p.file->file.m_info.header.type))
        return true; // unencrypted in the PFS: the PKG's bytes are the file
    const sce_ng_pfs_header_t &ngpfs = files_db->get_header();
    PfsFile file(cryptops, f00d, log, klicensee, app_dir, *p.file, p.junction, ngpfs, p.table);
    if (file.decrypt_file(dec_dir) < 0)
        return false;
    const fs::path decrypted = dec_host / p.entry->name;
    boost::system::error_code ec;
    fs::rename(decrypted, host, ec);
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
        if (!pkg.read(p.entry->offset + at, out.data(), out.size()))
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
    if (!pkg.read(p.entry->offset + at, out.data(), out.size()))
        return false;
    std::uint32_t tail = static_cast<std::uint32_t>(length % sector_size);
    if (tail == 0)
        tail = static_cast<std::uint32_t>(sector_size);

    // PfsFile::init_crypt_ctx for a unicv file
    const sce_ng_pfs_header_t &ngpfs = files_db->get_header();
    sig_tbl_t &block = p.table->m_blocks[index];
    CryptEngineData data;
    memset(&data, 0, sizeof(data));
    data.klicensee = klicensee;
    data.files_salt = ngpfs.files_salt;
    data.icv_salt = p.table->get_icv_salt();
    data.mode_index = img_spec_to_mode_index(ngpfs.image_spec);
    data.crypto_engine_flag = img_spec_to_crypto_engine_flag(ngpfs.image_spec) | CRYPTO_ENGINE_THROW_ERROR;
    data.key_id = ngpfs.key_id;
    data.fs_attr = p.file->file.m_info.get_original_type();
    data.block_size = static_cast<std::uint32_t>(sector_size);
    derive_keys_ctx drv;
    memset(&drv, 0, sizeof(drv));
    drv.db_type = settings_to_db_type(data.mode_index, data.fs_attr);
    drv.icv_version = header->get_version();
    if (is_gamedata(data.mode_index) && has_dbseed(drv.db_type, drv.icv_version))
        memcpy(drv.dbseed, header->get_dbseed(), 0x14);
    setup_crypt_packet_keys(cryptops, f00d, &data, &drv);

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

// open_file_hook: a pending file opened to read is served from the PKG
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
    for (const auto &layer : s_layers) {
        std::lock_guard lock(layer->mutex);
        if (layer->pending.contains(key))
            return layer;
    }
    return nullptr;
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
    boost::system::error_code ec;
    fs::copy_file(target, host, fs::copy_options::overwrite_existing, ec);
    return true;
}

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
    if (it == m->pending.end() || !m->streamable(it->second))
        return nullptr;
    return make_stream(m, it->second);
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
    if (it == m->pending.end())
        return;
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
        if (it == m->pending.end())
            return;
        if (!can_write(open_mode) && m->streamable(it->second))
            return;
    }
    on_host_file(host);
}

// A PKG laid out lazily in dir: its metadata and small files decrypted, the
// rest placeholders served out of the PKG. cache_name names its Persistent
// Cache folder.
std::shared_ptr<Mount> build(const fs::path &pkg_path, const fs::path &app_dir, const std::string &zrif,
    const std::string &cache_name, std::string &error) {
    auto m = std::make_shared<Mount>();
    if (!m->pkg.open(pkg_path, error))
        return nullptr;

    const auto lic = decode_license_np(zrif);
    if (!lic) {
        error = "no license (zRIF) for the PKG";
        return nullptr;
    }
    memcpy(m->klicensee, lic->key, sizeof(m->klicensee));

    boost::system::error_code ec;
    fs::remove_all(app_dir, ec);
    fs::create_directories(app_dir);
    m->app_host = app_dir.lexically_normal();
    m->dec_host = fs_utils::path_concat(m->app_host, "_dec");
    fs::remove_all(m->dec_host, ec);
    m->app_dir = psvpfs::path(m->app_host.native());
    m->dec_dir = psvpfs::path(m->dec_host.native());

    // Directories and the files read before or as the game starts first, in
    // full: the PFS metadata is needed to mount the rest
    std::vector<const PkgReader::Entry *> rest;
    for (const auto &e : m->pkg.entries()) {
        const fs::path host = app_dir / e.name;
        if (e.directory) {
            fs::create_directories(host);
            continue;
        }
        fs::create_directories(host.parent_path());
        const std::string name = string_utils::tolower(e.name);
        const bool eager = e.size <= EAGER_SIZE || name.starts_with("sce_sys/") || name.starts_with("sce_pfs/")
            || name.starts_with("sce_module/") || name == "eboot.bin";
        if (eager) {
            if (!m->pkg.write_entry(e, host, e.size)) {
                error = "cannot write " + e.name;
                return nullptr;
            }
        } else
            rest.push_back(&e);
    }

    m->cryptops = CryptoOperationsFactory::create(CryptoOperationsTypes::openssl);
    m->f00d = F00DKeyEncryptorFactory::create(F00DEncryptorTypes::native, m->cryptops);
    m->unicv_db = std::make_unique<UnicvDbParser>(m->app_dir, m->log);
    if (m->unicv_db->parse() < 0) {
        error = "cannot read the PFS (unicv.db)";
        return nullptr;
    }

    // The rest as placeholders: as much as the page mapper reads to tell which
    // file is which - one sector - and a hole for the remainder
    std::uint64_t sector = 0;
    for (const auto &t : m->unicv_db->get_idatabase()->m_tables)
        sector = std::max<std::uint64_t>(sector, t->get_header()->get_fileSectorSize());
    if (sector == 0)
        sector = 0x8000;
    for (const PkgReader::Entry *e : rest) {
        if (!m->pkg.write_entry(*e, app_dir / e->name, std::min(sector, e->size))) {
            error = "cannot write " + e->name;
            return nullptr;
        }
    }

    m->files_db = std::make_unique<FilesDbParser>(m->cryptops, m->f00d, m->log, m->klicensee, m->app_dir);
    m->pages = std::make_unique<PfsPageMapper>(m->cryptops, m->f00d, m->log, m->klicensee, m->app_dir);
    if (m->files_db->parse() < 0 || m->pages->bruteforce_map(m->files_db, m->unicv_db) < 0) {
        lr_log(RETRO_LOG_ERROR, "PKG: PFS mount failed:\n%s\n", m->log.str().c_str());
        error = "cannot mount the PFS (a wrong license?)";
        return nullptr;
    }

    // Which PFS file and table each placeholder is
    std::map<std::string, const sce_ng_pfs_file_t *> files;
    for (const auto &f : m->files_db->get_files())
        files[upper(f.path().get_value().lexically_normal().generic_string())] = &f;
    std::map<std::string, const PkgReader::Entry *> entries;
    for (const auto &e : m->pkg.entries())
        if (!e.directory)
            entries[upper((app_dir / e.name).lexically_normal().generic_string())] = &e;
    const auto &page_map = m->pages->get_pageMap();
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
        p.junction = page->second;
        m->pending[key] = p;
        if (std::find(rest.begin(), rest.end(), entry->second) == rest.end())
            eager_now.push_back(key);
    }

    // The files written in full are still PFS-encrypted: decrypt them now
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
    for (const PkgReader::Entry *e : rest) {
        const std::string key = upper((app_dir / e->name).lexically_normal().generic_string());
        if (!m->pending.contains(key)) {
            Mount::Pending p;
            p.entry = e;
            m->pending[key] = p;
        }
    }

    if (!s_cache_root.empty()) {
        // Kept across sessions for this PKG only: another file under the same
        // name (a re-dump) starts the cache over
        m->cache_dir = s_cache_root / cache_name;
        const fs::path id_file = m->cache_dir / "pkg.id";
        const std::string id = std::to_string(fs::file_size(pkg_path, ec)) + " " + std::to_string(m->pkg.entries().size());
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
    return m;
}

// Lays src_dir's files over the game's: a placeholder of each file's size in
// the game's folder, its reads redirected to the file in src_dir (an update,
// kept or read out of its own PKG). Nothing is copied. Returns the count.
unsigned overlay_dir(Mount &game, const fs::path &src_dir, bool skip_pfs) {
    boost::system::error_code ec;
    unsigned replaced = 0;
    for (fs::recursive_directory_iterator it(src_dir, ec), end; it != end; it.increment(ec)) {
        if (ec)
            break;
        const fs::path rel = it->path().lexically_relative(src_dir);
        const std::string first = string_utils::tolower(rel.begin()->string());
        // Each package's own PFS metadata stays its own; _dec is a layer's
        // decrypting scratch
        if (first == "_dec" || (skip_pfs && first == "sce_pfs")) {
            if (fs::is_directory(it->path(), ec))
                it.disable_recursion_pending();
            continue;
        }
        if (!fs::is_regular_file(it->path(), ec))
            continue;
        const fs::path to = game.app_host / rel;
        fs::create_directories(to.parent_path(), ec);
        {
            fs::ofstream create(to, std::ios::binary | std::ios::trunc);
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
    boost::system::error_code ec;

    // An update kept for this game (ux0/patch/<title id>, see the installer):
    // its files over the game's, and those are no longer read from the PKG
    const fs::path patch_dir = app_dir.parent_path().parent_path() / "patch" / app_dir.filename();
    if (fs::is_directory(patch_dir, ec)) {
        const unsigned replaced = overlay_dir(*m, patch_dir, false);
        lr_log(RETRO_LOG_INFO, "PKG: update from %s laid over the game, %u files read from there\n", patch_dir.generic_string().c_str(), replaced);
    }

    lr_log(RETRO_LOG_INFO, "PKG: running without installing, %u of %u files decrypted at start\n",
        static_cast<unsigned>(m->pkg.entries().size() - m->pending.size()), static_cast<unsigned>(m->pkg.entries().size()));
    s_mount = std::move(m);
    vfs::host_file_hook = on_host_file;
    vfs::host_open_hook = on_host_open;
    open_file_hook = on_open_file;
    return true;
}

bool pkg_info(const fs::path &pkg_path, PkgInfo &info) {
    PkgReader reader;
    std::string error;
    if (!reader.open(pkg_path, error))
        return false;
    sfo::SfoAppInfo sfo_info;
    sfo::get_param_info(sfo_info, reader.sfo(), 1);
    info.title_id = sfo_info.app_title_id;
    info.category = sfo_info.app_category;
    info.version = sfo_info.app_version;
    return !info.title_id.empty();
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
    boost::system::error_code ec;
    for (const auto &layer : s_layers) {
        fs::remove_all(layer->app_host, ec);
        fs::remove_all(layer->dec_host, ec);
    }
    s_layers.clear();
    if (!s_mount)
        return;
    fs::remove_all(s_mount->app_host, ec);
    fs::remove_all(s_mount->dec_host, ec);
    s_mount.reset();
}

void set_cache_root(const fs::path &cache_root) {
    s_cache_root = cache_root;
}

bool mounted() {
    return s_mount != nullptr;
}

} // namespace lazy_pkg
