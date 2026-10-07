#include "libretro_lazy_pkg.h"

#include "libretro_state.h"

#include <io/vfs.h>
#include <packages/pkg.h>
#include <util/bytes.h>
#include <util/string_utils.h>

#include <CryptoOperationsFactory.h>
#include <F00DKeyEncryptorFactory.h>
#include <FilesDbParser.h>
#include <PfsFile.h>
#include <PfsPageMapper.h>
#include <UnicvDbParser.h>
#include <zRIF/licdec.h>

#include <openssl/evp.h>

#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <map>
#include <memory>
#include <mutex>
#include <set>
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
        // The rest of a placeholder is a hole: the right size, no disk space
        if (length < e.size)
            fs::resize_file(to, e.size);
        return true;
    }

    const std::vector<Entry> &entries() const { return m_entries; }

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
    std::recursive_mutex mutex;

    bool materialize(Pending &p);
};

std::unique_ptr<Mount> s_mount;

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

void on_host_file(const fs::path &host) {
    Mount *m = s_mount.get();
    if (!m)
        return;
    std::lock_guard lock(m->mutex);
    auto it = m->pending.find(upper(host.lexically_normal().generic_string()));
    if (it == m->pending.end())
        return;
    Mount::Pending p = it->second;
    m->pending.erase(it);
    if (m->materialize(p))
        lr_log(RETRO_LOG_DEBUG, "PKG: decrypted %s on first read\n", p.entry->name.c_str());
    else
        lr_log(RETRO_LOG_ERROR, "PKG: could not decrypt %s\n", p.entry->name.c_str());
}

} // namespace

bool mount(const fs::path &pkg_path, const fs::path &app_dir, const std::string &zrif, std::string &error) {
    unmount();
    auto m = std::make_unique<Mount>();
    if (!m->pkg.open(pkg_path, error))
        return false;

    const auto lic = decode_license_np(zrif);
    if (!lic) {
        error = "no license (zRIF) for the PKG";
        return false;
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
                return false;
            }
        } else
            rest.push_back(&e);
    }

    m->cryptops = CryptoOperationsFactory::create(CryptoOperationsTypes::openssl);
    m->f00d = F00DKeyEncryptorFactory::create(F00DEncryptorTypes::native, m->cryptops);
    m->unicv_db = std::make_unique<UnicvDbParser>(m->app_dir, m->log);
    if (m->unicv_db->parse() < 0) {
        error = "cannot read the PFS (unicv.db)";
        return false;
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
            return false;
        }
    }

    m->files_db = std::make_unique<FilesDbParser>(m->cryptops, m->f00d, m->log, m->klicensee, m->app_dir);
    m->pages = std::make_unique<PfsPageMapper>(m->cryptops, m->f00d, m->log, m->klicensee, m->app_dir);
    if (m->files_db->parse() < 0 || m->pages->bruteforce_map(m->files_db, m->unicv_db) < 0) {
        lr_log(RETRO_LOG_ERROR, "PKG: PFS mount failed:\n%s\n", m->log.str().c_str());
        error = "cannot mount the PFS (a wrong license?)";
        return false;
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
            return false;
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

    lr_log(RETRO_LOG_INFO, "PKG: running without installing, %u of %u files decrypted at start\n",
        static_cast<unsigned>(m->pkg.entries().size() - m->pending.size()), static_cast<unsigned>(m->pkg.entries().size()));
    s_mount = std::move(m);
    vfs::host_file_hook = on_host_file;
    return true;
}

void unmount() {
    vfs::host_file_hook = nullptr;
    if (!s_mount)
        return;
    boost::system::error_code ec;
    fs::remove_all(s_mount->app_host, ec);
    fs::remove_all(s_mount->dec_host, ec);
    s_mount.reset();
}

bool mounted() {
    return s_mount != nullptr;
}

} // namespace lazy_pkg
