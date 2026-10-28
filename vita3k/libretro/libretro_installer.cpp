// Vita3K emulator project
// Copyright (C) 2026 Vita3K team
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include "libretro_installer.h"

#include <cstdarg>
#include <set>
#include "libretro_state.h"

#include <config/state.h>
#include <emuenv/state.h>
#include <io/functions.h>
#include <packages/functions.h>
#include <packages/license.h>
#include <packages/pkg.h>
#include "libretro_lazy_pkg.h"
#include "libretro_vfs.h"
#include <zrif2rif.h>
#include <packages/sfo.h>
#include <util/fs.h>
#include <util/log.h>
#include <util/string_utils.h>

#include <F00DKeyEncryptorFactory.h>
#include <PsvPfsParserConfig.h>
#include <rif2zrif.h>

#include <miniz.h>

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iterator>
#include <map>
#include <tuple>
#include <vector>

// ─── Firmware files ──────────────────────────────────────────────────────────
// The three packages are told apart by their names, whatever the case: a
// .pup with "preinst" in its name is the preinstalled package, one with
// "font" in it the fonts, and any other .pup the system firmware. Sony's
// downloads all carry the same name (PSP2UPDAT.PUP), so the two smaller ones
// have to be renamed by the user either way.

enum class PupKind { Firmware, Preinst, Font };

// ─── Logging helpers ────────────────────────────────────────────────────────

static void lr_log(enum retro_log_level level, const char *fmt, ...) {
    if (!libretro.log_cb)
        return;
    va_list ap;
    va_start(ap, fmt);
    char buf[4096];
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    libretro.log_cb(level, "[Vita3K] %s", buf);
}

static void lr_msg(const char *msg, unsigned frames = 300) {
    if (!libretro.environ_cb)
        return;
    struct retro_message rmsg;
    rmsg.msg = msg;
    rmsg.frames = frames;
    libretro.environ_cb(RETRO_ENVIRONMENT_SET_MESSAGE, &rmsg);
}

// ─── Firmware status ────────────────────────────────────────────────────────

FirmwareStatus check_firmware_status(const fs::path &pref_path) {
    FirmwareStatus status;

    const auto pd0_path = pref_path / "pd0";
    const auto vs0_path = pref_path / "vs0";
    const auto sa0_path = pref_path / "sa0";

    status.preinst_installed = fs::exists(pd0_path) && !fs::is_empty(pd0_path);
    status.firmware_installed = fs::exists(vs0_path) && !fs::is_empty(vs0_path);
    status.font_installed = fs::exists(sa0_path) && !fs::is_empty(sa0_path);

    lr_log(RETRO_LOG_INFO, "Firmware status: preinst(pd0)=%s firmware(vs0)=%s font(sa0)=%s\n",
        status.preinst_installed ? "YES" : "NO",
        status.firmware_installed ? "YES" : "NO",
        status.font_installed ? "YES" : "NO");

    return status;
}

// ─── Firmware installation ──────────────────────────────────────────────────

static std::string lower_case(std::string text) {
    for (char &c : text)
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return text;
}

static PupKind pup_kind(const fs::path &path) {
    const std::string name = lower_case(path.filename().string());
    if (name.find("preinst") != std::string::npos)
        return PupKind::Preinst;
    if (name.find("font") != std::string::npos)
        return PupKind::Font;
    return PupKind::Firmware;
}

// The first .pup of a kind in a folder, by name, so that the choice between
// two of them does not depend on the order the folder lists them in. Outside
// the core's own folders only the names a PS Vita firmware comes with count:
// RetroArch's system directory holds other consoles' .pup files too.
static fs::path find_pup_file(const fs::path &search_dir, PupKind kind, bool vita_names_only = false) {
    boost::system::error_code ec;
    if (!fs::is_directory(search_dir, ec))
        return {};

    std::vector<fs::path> found;
    for (fs::directory_iterator it(search_dir, ec), end; !ec && it != end; it.increment(ec)) {
        const fs::path &path = it->path();
        const std::string name = lower_case(path.filename().string());
        if (lower_case(path.extension().string()) != ".pup" || pup_kind(path) != kind)
            continue;
        if (vita_names_only && name != "psp2updat.pup" && name != "psvupdat.pup")
            continue;
        boost::system::error_code file_ec;
        if (fs::is_regular_file(path, file_ec) && fs::file_size(path, file_ec) > 0)
            found.push_back(path);
    }
    if (found.empty())
        return {};
    std::sort(found.begin(), found.end());
    lr_log(RETRO_LOG_INFO, "Found PUP file: %s\n", found.front().generic_string().c_str());
    return found.front();
}

static bool install_pup_file(const fs::path &pref_path, const fs::path &pup_path, const char *label) {
    lr_log(RETRO_LOG_INFO, "Installing %s from PUP: %s\n", label, pup_path.generic_string().c_str());
    lr_msg(fmt::format("Installing {}... this may take a minute.", label).c_str(), 600);

    std::string fw_version;
    try {
        fw_version = install_pup(pref_path, pup_path, [label](uint32_t progress) {
            lr_log(RETRO_LOG_INFO, "%s install progress: %u%%\n", label, progress);
        });
    } catch (const std::exception &e) {
        lr_log(RETRO_LOG_ERROR, "%s installation threw exception: %s\n", label, e.what());
        lr_log(RETRO_LOG_ERROR, "PUP file may be corrupted or wrong format: %s\n", pup_path.generic_string().c_str());
        lr_msg(fmt::format("{} installation failed (exception)!", label).c_str(), 600);
        return false;
    } catch (...) {
        lr_log(RETRO_LOG_ERROR, "%s installation threw unknown exception\n", label);
        lr_log(RETRO_LOG_ERROR, "PUP file may be corrupted or wrong format: %s\n", pup_path.generic_string().c_str());
        lr_msg(fmt::format("{} installation failed!", label).c_str(), 600);
        return false;
    }

    if (fw_version.empty()) {
        lr_log(RETRO_LOG_WARN, "%s installation returned no version (may still have partially installed).\n", label);
    } else {
        lr_log(RETRO_LOG_INFO, "%s version %s installed successfully!\n", label, fw_version.c_str());
    }

    return true;
}

// The .pup of one firmware part: in the firmware directory, else in the
// emulated storage's root, and for the system firmware also under its own
// Vita names one folder up
static fs::path firmware_pup(const fs::path &pref_path, const fs::path &system_dir, PupKind kind) {
    fs::path pup = find_pup_file(system_dir, kind);
    if (pup.empty() && system_dir != pref_path)
        pup = find_pup_file(pref_path, kind);
    if (pup.empty() && kind == PupKind::Firmware && system_dir.has_parent_path())
        pup = find_pup_file(system_dir.parent_path(), kind, true);
    return pup;
}

static std::string missing_parts(const FirmwareStatus &status) {
    std::string missing;
    if (!status.firmware_installed)
        missing += missing.empty() ? "system firmware" : ", system firmware";
    if (!status.preinst_installed)
        missing += missing.empty() ? "preinstalled package" : ", preinstalled package";
    if (!status.font_installed)
        missing += missing.empty() ? "fonts" : ", fonts";
    return missing;
}

// Each firmware part that is not installed, from its .pup in system_dir if
// there is one: a prepared system directory gives a working core at the first
// start, as with other cores' BIOS files (i30817, sco8487). An installed part
// is left as it is; loading a .pup as content installs over it.
static void install_missing_firmware(const fs::path &pref_path, const fs::path &system_dir) {
    const FirmwareStatus status = check_firmware_status(pref_path);
    const std::tuple<PupKind, const char *, bool> parts[] = {
        { PupKind::Preinst, "Preinstalled package", status.preinst_installed },
        { PupKind::Firmware, "System firmware", status.firmware_installed },
        { PupKind::Font, "Font package", status.font_installed },
    };
    for (const auto &[kind, label, installed] : parts) {
        if (installed)
            continue;
        const fs::path pup = firmware_pup(pref_path, system_dir, kind);
        if (!pup.empty())
            install_pup_file(pref_path, pup, label);
    }
}

bool check_firmware_installed(const fs::path &pref_path, const fs::path &system_dir) {
    fs::create_directories(pref_path);
    install_missing_firmware(pref_path, system_dir);
    const FirmwareStatus status = check_firmware_status(pref_path);
    if (status.all_installed()) {
        lr_log(RETRO_LOG_INFO, "All firmware components are installed.\n");
        return true;
    }
    // The system firmware missing is the case games do not start in. With it
    // there and another part missing (the fonts, say, in folders copied from
    // the standalone) most games run: said as what it is, not as no firmware.
    const enum retro_log_level level = status.firmware_installed ? RETRO_LOG_WARN : RETRO_LOG_ERROR;
    if (status.firmware_installed) {
        lr_log(level, "=== FIRMWARE INCOMPLETE ===\n");
        lr_log(level, "The system firmware is installed; a part some games need is not.\n");
    } else {
        lr_log(level, "=== FIRMWARE MISSING ===\n");
        lr_log(level, "Vita3K requires PS Vita firmware to run games.\n");
    }
    lr_log(level, "Place the following PUP files in %s, to be installed at the next start, or load each .pup as content:\n", system_dir.generic_string().c_str());
    if (!status.preinst_installed)
        lr_log(level, "  - preinst.pup, or any .pup name with preinst in it (pd0/) → https://bit.ly/4hlePsX\n");
    if (!status.firmware_installed)
        lr_log(level, "  - the system firmware, any .pup name without preinst or font in it (vs0/) → https://www.playstation.com/en-us/support/hardware/psvita/system-software\n");
    if (!status.font_installed)
        lr_log(level, "  - font.pup, or any .pup name with font in it (sa0/) → https://bit.ly/48ouDaa\n");
    lr_msg(fmt::format("Firmware missing: {}. Put the .pup files in system/vita3k; they are installed at the next start.", missing_parts(status)).c_str(), 600);
    return status.firmware_installed;
}

bool install_firmware_content(const fs::path &pref_path, const fs::path &pup_path) {
    boost::system::error_code ec;
    if (!fs::is_regular_file(pup_path, ec)) {
        lr_log(RETRO_LOG_ERROR, "%s is not a file the core can open directly; copy it into a folder and load it from there\n", pup_path.generic_string().c_str());
        lr_msg("Firmware: load the .pup from a regular directory", 600);
        return false;
    }
    fs::create_directories(pref_path, ec);
    if (!install_pup_file(pref_path, pup_path, "Firmware package"))
        return false;
    const std::string missing = missing_parts(check_firmware_status(pref_path));
    const std::string text = missing.empty()
        ? std::string("Firmware installed: all three parts are there. Load a game.")
        : "Firmware package installed. Still missing: " + missing + " - load that .pup too.";
    lr_log(RETRO_LOG_INFO, "%s\n", text.c_str());
    lr_msg(text.c_str(), 600);
    return true;
}

// ─── Game installation ──────────────────────────────────────────────────────

// Miniz helpers
struct ZipDeleter {
    void operator()(mz_zip_archive *zip) const {
        mz_zip_reader_end(zip);
        delete zip;
    }
};
using ZipPtr = std::unique_ptr<mz_zip_archive, ZipDeleter>;

static size_t write_to_buffer(void *pOpaque, mz_uint64 file_ofs, const void *pBuf, size_t n) {
    auto *buffer = static_cast<std::vector<uint8_t> *>(pOpaque);
    const uint8_t *first = static_cast<const uint8_t *>(pBuf);
    const uint8_t *last = &first[n];
    buffer->insert(buffer->end(), first, last);
    return n;
}

/// Read param.sfo from a VPK/ZIP to extract game metadata.
static bool read_sfo_from_archive(const ZipPtr &zip, const std::string &content_path, sfo::SfoAppInfo &app_info, int sys_lang) {
    std::string sfo_path = content_path + "sce_sys/param.sfo";
    std::vector<uint8_t> buffer;

    lr_log(RETRO_LOG_DEBUG, "Reading SFO from archive path: %s\n", sfo_path.c_str());

    if (!mz_zip_reader_extract_file_to_callback(zip.get(), sfo_path.c_str(), &write_to_buffer, &buffer, 0)) {
        lr_log(RETRO_LOG_DEBUG, "Failed to extract SFO from: %s (error: %s)\n",
            sfo_path.c_str(), mz_zip_get_error_string(mz_zip_get_last_error(zip.get())));
        return false;
    }

    lr_log(RETRO_LOG_DEBUG, "SFO buffer size: %zu bytes\n", buffer.size());
    sfo::get_param_info(app_info, buffer, sys_lang);

    lr_log(RETRO_LOG_DEBUG, "SFO parsed: title='%s' title_id='%s' category='%s'\n",
        app_info.app_title.c_str(), app_info.app_title_id.c_str(), app_info.app_category.c_str());

    return !app_info.app_title_id.empty();
}

/// Find content paths within a VPK/ZIP (paths that contain sce_sys/param.sfo).
static std::vector<std::string> find_archive_content_paths(const ZipPtr &zip) {
    mz_uint num_files = mz_zip_reader_get_num_files(zip.get());
    std::vector<std::string> content_paths;
    std::string sfo_marker = "sce_sys/param.sfo";

    lr_log(RETRO_LOG_DEBUG, "Scanning archive with %u files for content paths\n", num_files);

    for (mz_uint i = 0; i < num_files; i++) {
        mz_zip_archive_file_stat file_stat;
        if (!mz_zip_reader_file_stat(zip.get(), i, &file_stat))
            continue;

        std::string filename = file_stat.m_filename;

        // Check for Vitamin dumps (unsupported)
        if (filename.find("sce_module/steroid.suprx") != std::string::npos) {
            lr_log(RETRO_LOG_ERROR, "Vitamin dump detected - these are not supported!\n");
            lr_msg("Vitamin dumps are not supported!", 600);
            return {};
        }

        if (filename.find(sfo_marker) != std::string::npos) {
            std::string path = filename.substr(0, filename.find(sfo_marker));
            // Avoid duplicates
            bool found = false;
            for (const auto &p : content_paths) {
                if (p == path) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                lr_log(RETRO_LOG_DEBUG, "Found content path: '%s'\n", path.c_str());
                content_paths.push_back(path);
            }
        }
    }

    lr_log(RETRO_LOG_DEBUG, "Found %zu content path(s) in archive\n", content_paths.size());
    return content_paths;
}

/// Extract a single content entry from the archive to the output directory.
static bool extract_archive_content(const ZipPtr &zip, const std::string &content_path,
    const fs::path &output_path) {

    lr_log(RETRO_LOG_INFO, "Extracting content to: %s\n", output_path.generic_string().c_str());

    // Remove existing installation if present
    if (fs::exists(output_path)) {
        lr_log(RETRO_LOG_INFO, "Removing existing installation at: %s\n", output_path.generic_string().c_str());
        fs::remove_all(output_path);
    }

    fs::create_directories(output_path);

    mz_uint num_files = mz_zip_reader_get_num_files(zip.get());
    mz_uint extracted_count = 0;

    for (mz_uint i = 0; i < num_files; i++) {
        mz_zip_archive_file_stat file_stat;
        if (!mz_zip_reader_file_stat(zip.get(), i, &file_stat))
            continue;

        const std::string m_filename = file_stat.m_filename;
        if (m_filename.find(content_path) != 0)
            continue;

        std::string relative_path = m_filename.substr(content_path.size());
        if (relative_path.empty())
            continue;

        const fs::path file_output = output_path / fs_utils::utf8_to_path(relative_path);

        if (mz_zip_reader_is_file_a_directory(zip.get(), i)) {
            fs::create_directories(file_output);
        } else {
            fs::create_directories(file_output.parent_path());
            if (!mz_zip_reader_extract_to_file(zip.get(), i, fs_utils::path_to_utf8(file_output).c_str(), 0)) {
                lr_log(RETRO_LOG_WARN, "Failed to extract: %s (error: %s)\n",
                    m_filename.c_str(), mz_zip_get_error_string(mz_zip_get_last_error(zip.get())));
                continue;
            }
            extracted_count++;
            if (extracted_count % 100 == 0) {
                lr_log(RETRO_LOG_DEBUG, "Extracted %u files...\n", extracted_count);
            }
        }
    }

    lr_log(RETRO_LOG_INFO, "Extracted %u files to: %s\n", extracted_count, output_path.generic_string().c_str());
    return extracted_count > 0;
}

// Resolve folder to the actual game content directory.
// Supports multiple structures:
//   1. Direct: <folder>/sce_sys/param.sfo  (flat game folder)
//   2. Dump:   <folder>/app/<TITLE_ID>/sce_sys/param.sfo  (NoNpDrm dump)
//   3. Named:  <folder>/<TITLE_ID>/sce_sys/param.sfo
static fs::path resolve_game_folder(const fs::path &game_path) {
    // Direct structure
    if (fs::exists(game_path / "sce_sys" / "param.sfo"))
        return game_path;

    // NoNpDrm dump structure: app/<TITLE_ID>/
    if (fs::is_directory(game_path / "app")) {
        for (const auto &entry : fs::directory_iterator(game_path / "app")) {
            if (entry.is_directory() && fs::exists(entry.path() / "sce_sys" / "param.sfo"))
                return entry.path();
        }
    }

    // Subdirectory named as title_id
    for (const auto &entry : fs::directory_iterator(game_path)) {
        if (entry.is_directory() && fs::exists(entry.path() / "sce_sys" / "param.sfo"))
            return entry.path();
    }

    return {}; // Not found
}

// A NoNpDrm app (sce_sys/package/work.bin beside its encrypted PFS): decrypts it
// in place with the zRIF made from work.bin, and keeps work.bin as the app's
// license in ux0/license/<title id>/. Hands back work.bin and the zRIF, which
// a patch that shares the app's license is decrypted with.
//
// Only for a NoNpDrm game that is installed - Run Mode: Install, or a
// folder or VPK/ZIP that cannot be run from where it lies. Vita3K has no PFS
// driver, so an installed game has to be decrypted on disk, and psvpfstools'
// execute() writes a whole decrypted tree into a folder in ux0/libretro_pkg
// (install_decrypt_folder), which then replaces it: twice the game's size for a
// while, and nothing encrypted is left. Run Without Installing and Persistent
// Cache read a VPK/ZIP's or folder's files decrypted as they go
// (lazy_pkg::mount_archive, mount_folder), with no decryption folder.
static bool decrypt_nonpdrm_app(const fs::path &install_path, const fs::path &pref_path, const GameInstallResult &result,
    std::vector<uint8_t> &work_bin_data, std::string &app_zRIF, bool keep_license = true) {
    const auto work_bin = install_path / "sce_sys" / "package" / "work.bin";
    lr_log(RETRO_LOG_INFO, "Detected NoNpDrm encrypted content, decrypting PFS layer...\n");
    {
        char msg[256];
        snprintf(msg, sizeof(msg), "Decrypting %s...", result.title.c_str());
        lr_msg(msg, 600);
    }

    // Save work.bin before decryption (decryption replaces the directory)
    {
        std::ifstream wf(work_bin.string(), std::ios::binary);
        work_bin_data.assign(std::istreambuf_iterator<char>(wf), std::istreambuf_iterator<char>());
    }

    std::string src_str = install_path.generic_string();
    std::string dst_str = install_decrypt_folder(pref_path, install_path).generic_string();

    {
        std::ifstream binfile(work_bin.string(), std::ios::in | std::ios::binary | std::ios::ate);
        app_zRIF = rif2zrif(binfile);
    }
    F00DEncryptorTypes f00d_enc_type = F00DEncryptorTypes::native;
    std::string f00d_arg;

    lr_log(RETRO_LOG_INFO, "Running PFS decryption: %s -> %s\n", src_str.c_str(), dst_str.c_str());
    lr_log(RETRO_LOG_DEBUG, "zRIF length: %d, work.bin size: %d bytes\n", (int)app_zRIF.size(), (int)work_bin_data.size());
    int dec_result = execute(app_zRIF, src_str, dst_str, f00d_enc_type, f00d_arg);
    if (dec_result < 0) {
        lr_log(RETRO_LOG_ERROR, "PFS decryption failed (error %d)!\n", dec_result);
        lr_msg("NoNpDrm decryption failed!", 300);
        fs::path dst_path(dst_str);
        if (fs::exists(dst_path))
            fs::remove_all(dst_path);
        return false;
    }

    lr_log(RETRO_LOG_INFO, "PFS decryption succeeded, replacing encrypted files...\n");
    try {
        fs::remove_all(install_path);
        fs::rename(fs::path(dst_str), install_path);
    } catch (const fs::filesystem_error &e) {
        lr_log(RETRO_LOG_ERROR, "Failed to replace decrypted files: %s\n", e.what());
        return false;
    }

    // An update's or DLC's own license is not kept: the game's stays where it is
    if (!keep_license) {
        lr_log(RETRO_LOG_INFO, "NoNpDrm decryption completed.\n");
        return true;
    }

    // Copy license to ux0/license/{title_id}/{content_id}.rif
    const auto license_dir = pref_path / "ux0" / "license" / result.title_id;
    fs::create_directories(license_dir);
    try {
        // Save as {content_id}.rif (what get_license() expects)
        std::string lic_filename = result.content_id.empty() ? "work.bin" : (result.content_id + ".rif");
        const auto dst_license = license_dir / lic_filename;
        std::ofstream lf(dst_license.string(), std::ios::binary);
        lf.write(reinterpret_cast<const char *>(work_bin_data.data()), work_bin_data.size());
        lr_log(RETRO_LOG_INFO, "License saved to: %s\n", dst_license.generic_string().c_str());
        // Also save as work.bin for compatibility
        const auto dst_workbin = license_dir / "work.bin";
        if (dst_license != dst_workbin) {
            std::ofstream wf(dst_workbin.string(), std::ios::binary);
            wf.write(reinterpret_cast<const char *>(work_bin_data.data()), work_bin_data.size());
        }
    } catch (const std::exception &e) {
        lr_log(RETRO_LOG_DEBUG, "License copy failed: %s\n", e.what());
    }

    lr_log(RETRO_LOG_INFO, "NoNpDrm app decryption completed.\n");
    return true;
}

// An install left encrypted: its PFS and license are still in the app folder,
// as an earlier install that did not decrypt it left them
static bool install_still_encrypted(const fs::path &path) {
    return fs::exists(path / "sce_pfs") && fs::exists(path / "sce_sys" / "package" / "work.bin");
}

// A NoNpDrm update or DLC installed by copying it (a folder or VPK/ZIP), decrypted in
// place as a game is: with its own work.bin, or an update with its game's license, which
// an update shares and need not carry (sco8487). False, with a message, without one.
static bool decrypt_nonpdrm_extra(const fs::path &install_path, const fs::path &pref_path, const GameInstallResult &result) {
    const fs::path work_bin = install_path / "sce_sys" / "package" / "work.bin";
    boost::system::error_code ec;
    if (!fs::exists(work_bin, ec)) {
        const fs::path lic_dir = pref_path / "ux0" / "license" / result.title_id;
        fs::path game_license = lic_dir / "work.bin";
        if (!fs::exists(game_license, ec))
            game_license = lic_dir / (result.content_id + ".rif");
        if (result.category.find("gp") == std::string::npos || !fs::exists(game_license, ec)) {
            lr_log(RETRO_LOG_ERROR, "%s is encrypted and has no license: neither its own sce_sys/package/work.bin nor, for an update, its game's in %s\n",
                install_path.generic_string().c_str(), lic_dir.generic_string().c_str());
            lr_msg("This update or DLC is encrypted and its license is missing (install the game first, or add its work.bin)", 600);
            return false;
        }
        fs::create_directories(work_bin.parent_path(), ec);
        fs::copy_file(game_license, work_bin, fs::copy_options::overwrite_existing, ec);
        if (ec)
            return false;
    }
    std::vector<uint8_t> work_bin_data;
    std::string zrif;
    return decrypt_nonpdrm_app(install_path, pref_path, result, work_bin_data, zrif, false);
}

// Whether the drive under pref_path has room for bytes more; a message says it when not
// (sco8487: refuse rather than fill the drive)
static bool has_room(const fs::path &pref_path, std::uint64_t bytes) {
    boost::system::error_code ec;
    const fs::space_info space = fs::space(pref_path, ec);
    if (ec || space.available >= bytes)
        return true;
    lr_log(RETRO_LOG_ERROR, "Not enough free space: %.1f MiB needed, %.1f MiB free\n", bytes / 1048576.0, space.available / 1048576.0);
    lr_msg(fmt::format("Not enough free space to install: {:.1f} GiB needed, {:.1f} GiB free", bytes / 1073741824.0,
               space.available / 1073741824.0)
               .c_str(),
        600);
    return false;
}

static std::uint64_t folder_size(const fs::path &dir) {
    std::uint64_t total = 0;
    boost::system::error_code ec;
    for (fs::recursive_directory_iterator it(dir, ec), end; !ec && it != end; it.increment(ec)) {
        if (fs::is_regular_file(it->path(), ec))
            total += fs::file_size(it->path(), ec);
    }
    return total;
}

static fs::path manual_install_mark(const fs::path &pref_path, const std::string &title_id, const std::string &dlc_id = {});
static void mark_forced_install(const fs::path &pref_path, const std::string &title_id, const std::string &category,
    const std::string &content_id, const fs::path &source);
static void drop_shelved_copy(const fs::path &pref_path, const std::string &title_id, const std::string &dlc_id);

// Handle an extracted game folder (NoNpDrm dump, extracted VPK, etc.)
static GameInstallResult handle_folder_game(const fs::path &game_path, const fs::path &pref_path, int sys_lang) {
    GameInstallResult result;

    lr_log(RETRO_LOG_INFO, "Detected folder-based game: %s\n", game_path.generic_string().c_str());

    // Resolve to actual content directory
    const fs::path content_dir = resolve_game_folder(game_path);
    if (content_dir.empty()) {
        lr_log(RETRO_LOG_ERROR, "No sce_sys/param.sfo found in folder or subfolders: %s\n", game_path.generic_string().c_str());
        lr_log(RETRO_LOG_ERROR, "Expected: <folder>/sce_sys/param.sfo or <folder>/app/<ID>/sce_sys/param.sfo\n");
        lr_msg("No param.sfo found in the game's directory!", 300);
        return result;
    }

    if (content_dir != game_path) {
        lr_log(RETRO_LOG_INFO, "Resolved game content to: %s\n", content_dir.generic_string().c_str());
    }

    // Look for param.sfo
    const auto sfo_path = content_dir / "sce_sys" / "param.sfo";
    if (!fs::exists(sfo_path)) {
        lr_log(RETRO_LOG_ERROR, "No sce_sys/param.sfo found at: %s\n", sfo_path.generic_string().c_str());
        lr_msg("No param.sfo found!", 300);
        return result;
    }

    // Read param.sfo
    lr_log(RETRO_LOG_DEBUG, "Reading param.sfo from: %s\n", sfo_path.generic_string().c_str());
    std::ifstream sfo_file(sfo_path.native(), std::ios::binary);
    if (!sfo_file) {
        lr_log(RETRO_LOG_ERROR, "Failed to open param.sfo: %s\n", sfo_path.generic_string().c_str());
        lr_msg("Failed to read game info!", 300);
        return result;
    }
    std::vector<uint8_t> sfo_data((std::istreambuf_iterator<char>(sfo_file)), std::istreambuf_iterator<char>());
    sfo_file.close();

    sfo::SfoAppInfo app_info;
    sfo::get_param_info(app_info, sfo_data, sys_lang);

    if (app_info.app_title_id.empty()) {
        lr_log(RETRO_LOG_ERROR, "Could not determine title_id from param.sfo\n");
        lr_msg("Invalid param.sfo - no title_id!", 300);
        return result;
    }

    result.title_id = app_info.app_title_id;
    result.title = app_info.app_title;
    result.category = app_info.app_category;
    result.content_id = app_info.app_content_id;

    lr_log(RETRO_LOG_INFO, "Game: '%s' [%s] (category: %s)\n",
        result.title.c_str(), result.title_id.c_str(), result.category.c_str());

    // Encrypted (a NoNpDrm dump) without the license it is decrypted with: it cannot run
    if (fs::is_directory(content_dir / "sce_pfs") && !fs::exists(content_dir / "sce_sys" / "package" / "work.bin")) {
        lr_log(RETRO_LOG_ERROR, "%s is encrypted and its license, sce_sys/package/work.bin, is missing\n",
            content_dir.generic_string().c_str());
        lr_msg("This game is encrypted and its license (sce_sys/package/work.bin) is missing", 600);
        return result;
    }

    const auto app_path = pref_path / "ux0" / "app" / result.title_id;

    // Determine output path based on category
    fs::path install_path;
    if (app_info.app_category.find("gp") != std::string::npos) {
        install_path = pref_path / "ux0" / "patch" / result.title_id;
    } else if (app_info.app_category == "ac") {
        if (!app_info.app_content_id.empty() && app_info.app_content_id.size() > 20) {
            std::string cid = app_info.app_content_id.substr(20);
            install_path = pref_path / "ux0" / "addcont" / result.title_id / cid;
        } else {
            install_path = pref_path / "ux0" / "addcont" / result.title_id;
        }
    } else {
        install_path = app_path;
    }

    // Check if this specific content is already installed
    if (fs::exists(install_path) && !fs::is_empty(install_path)) {
        if (app_info.app_category.find("gd") != std::string::npos
            && fs::exists(app_path / "eboot.bin") && !install_still_encrypted(app_path)) {
            lr_log(RETRO_LOG_INFO, "Game '%s' [%s] is already installed.\n",
                result.title.c_str(), result.title_id.c_str());
            result.success = true;
            return result;
        } else if (app_info.app_category.find("gp") != std::string::npos || app_info.app_category == "ac") {
            // An update or DLC loaded on its own is installed again over what is there, which
            // also mends a broken install (sco8487)
            lr_log(RETRO_LOG_INFO, "'%s' [%s] is installed already: replaced\n", result.title.c_str(), result.title_id.c_str());
            fs::remove_all(install_path);
        }
    }

    // For patches/DLC, verify base game exists
    if (app_info.app_category.find("gp") != std::string::npos
        || app_info.app_category == "ac") {
        if (!fs::exists(app_path) || fs::is_empty(app_path)) {
            lr_log(RETRO_LOG_ERROR, "Base game not installed — install app before patch/DLC\n");
            lr_msg("Install base game first!", 300);
            return result;
        }
    }

    lr_log(RETRO_LOG_INFO, "Installing '%s' [%s] to: %s\n",
        result.title.c_str(), result.title_id.c_str(), install_path.generic_string().c_str());
    {
        char msg[256];
        snprintf(msg, sizeof(msg), "Installing %s [%s]...", result.title.c_str(), result.title_id.c_str());
        lr_msg(msg, 600);
    }

    // An encrypted one twice over for a while: decrypting writes a second copy
    if (!has_room(pref_path, folder_size(content_dir) * (fs::is_directory(content_dir / "sce_pfs") ? 2 : 1)))
        return result;
    try {
        fs::create_directories(install_path);
        fs::copy(content_dir, install_path, fs::copy_options::recursive | fs::copy_options::overwrite_existing);
        lr_log(RETRO_LOG_INFO, "App folder copy completed.\n");
    } catch (const fs::filesystem_error &e) {
        lr_log(RETRO_LOG_ERROR, "Failed to copy game folder: %s\n", e.what());
        lr_msg("Failed to copy the game's directory!", 300);
        return result;
    }

    // A NoNpDrm copy is decrypted in place: a game with its own license, kept; an update
    // or DLC with its own or the game's. An update stays in ux0/patch and is laid over the
    // game when it starts, as one from a PKG or VPK/ZIP (sco8487), never merged into it.
    if (fs::is_directory(install_path / "sce_pfs")) {
        bool decrypted;
        if (app_info.app_category.find("gd") != std::string::npos) {
            std::vector<uint8_t> work_bin_data;
            std::string app_zRIF;
            decrypted = decrypt_nonpdrm_app(install_path, pref_path, result, work_bin_data, app_zRIF);
        } else
            decrypted = decrypt_nonpdrm_extra(install_path, pref_path, result);
        if (!decrypted) {
            fs::remove_all(install_path);
            return result;
        }
    }
    // Loaded on its own (not through the game's Content options), an update or DLC stays
    // installed whatever Run Mode says
    mark_forced_install(pref_path, result.title_id, app_info.app_category, app_info.app_content_id, game_path);

    // Verify installation
    if (fs::exists(install_path) && !fs::is_empty(install_path)) {
        lr_log(RETRO_LOG_INFO, "'%s' [%s] installed successfully!\n",
            result.title.c_str(), result.title_id.c_str());
        {
            char msg[256];
            snprintf(msg, sizeof(msg), "%s installed!", result.title.c_str());
            lr_msg(msg, 300);
        }
        result.success = true;
    } else {
        lr_log(RETRO_LOG_ERROR, "Installation verification failed at: %s\n",
            install_path.generic_string().c_str());
        lr_msg("Installation failed!", 300);
    }

    return result;
}

// The content's own files - the archive or PKG and the licenses beside it -
// through the frontend's VFS when the path is a URI (saf://, which the OS
// cannot open), with the OS otherwise.
static bool content_stat(const fs::path &path, bool *is_directory, std::uint64_t *size) {
    const std::string p = path.string();
    if (lr_vfs_is_uri(p))
        return lr_vfs_stat(p, is_directory, size);
    boost::system::error_code ec;
    if (!fs::exists(path, ec))
        return false;
    const bool directory = fs::is_directory(path, ec);
    if (is_directory)
        *is_directory = directory;
    if (size)
        *size = directory ? 0 : fs::file_size(path, ec);
    return true;
}

static bool content_read(const fs::path &path, std::string &out) {
    const std::string p = path.string();
    if (lr_vfs_is_uri(p))
        return lr_vfs_read_file(p, out);
    fs::ifstream in(path, std::ios::in | std::ios::binary);
    if (!in)
        return false;
    out.assign(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
    return true;
}

static std::vector<fs::path> content_list(const fs::path &dir) {
    std::vector<fs::path> entries;
    const std::string d = dir.string();
    if (lr_vfs_is_uri(d)) {
        for (const std::string &e : lr_vfs_list(d))
            entries.emplace_back(e);
        return entries;
    }
    boost::system::error_code ec;
    for (fs::directory_iterator it(dir, ec), end; !ec && it != end; it.increment(ec))
        entries.push_back(it->path());
    return entries;
}

// rif2zrif reads a license from a file: the license's bytes are written to a
// scratch file in the emulator's folder first (one read through the VFS, or
// out of an archive, has no file of its own).
static std::string zrif_of_license(const std::string &bytes, const fs::path &pref_path) {
    // A license is 512 bytes (up to 2048): rif2zrif reads the whole file into a buffer of
    // that size on the stack, and a larger file next to the PKG under a license's name
    // overran it and crashed the frontend (Shoegzer)
    if (bytes.size() < 512 || bytes.size() > 2048) {
        if (!bytes.empty())
            lr_log(RETRO_LOG_WARN, "Not a license: %u bytes\n", static_cast<unsigned>(bytes.size()));
        return {};
    }
    const fs::path scratch = pref_path / "ux0" / "libretro_license.tmp";
    boost::system::error_code ec;
    fs::create_directories(scratch.parent_path(), ec);
    {
        fs::ofstream out(scratch, std::ios::out | std::ios::binary | std::ios::trunc);
        out.write(bytes.data(), bytes.size());
    }
    std::string zrif;
    {
        std::ifstream bin(scratch.string(), std::ios::in | std::ios::binary | std::ios::ate);
        if (bin)
            zrif = rif2zrif(bin);
    }
    fs::remove(scratch, ec);
    return zrif;
}

static std::string license_to_zrif(const fs::path &license, const fs::path &pref_path) {
    std::string bytes;
    if (!content_read(license, bytes))
        return {};
    return zrif_of_license(bytes, pref_path);
}

// The zRIF of a NoNpDrm game in an archive, from its work.bin; empty without one
static std::string archive_zrif(const ZipPtr &zip, const std::string &content_path, const fs::path &pref_path) {
    std::vector<uint8_t> bytes;
    const std::string path = content_path + "sce_sys/package/work.bin";
    if (mz_zip_reader_locate_file(zip.get(), path.c_str(), nullptr, 0) < 0
        || !mz_zip_reader_extract_file_to_callback(zip.get(), path.c_str(), &write_to_buffer, &bytes, 0))
        return {};
    return zrif_of_license(std::string(bytes.begin(), bytes.end()), pref_path);
}

// The marker of a game run without installing (lazy_pkg), there while its
// files are laid out in ux0/app: one left by a run the frontend did not end
// says that folder is no installation
static fs::path lazy_marker(const fs::path &pref_path, const std::string &title_id) {
    return pref_path / "ux0" / "libretro_pkg" / fmt::format("lazy_{}", title_id);
}

void remove_dead_runs(const fs::path &pref_path) {
    const fs::path notes = pref_path / "ux0" / "libretro_pkg";
    const fs::path ux0 = pref_path / "ux0";
    boost::system::error_code ec;
    std::vector<fs::path> entries;
    for (fs::directory_iterator it(notes, ec), end; !ec && it != end; it.increment(ec))
        entries.push_back(it->path());
    for (const fs::path &entry : entries) {
        const std::string name = entry.filename().string();
        fs::path layout;
        if (name.starts_with("lazy_"))
            layout = ux0 / "app" / name.substr(5);
        else if (name.starts_with("dlc_") && name.size() > 4 + 9 + 1 && name[4 + 9] == '_')
            layout = ux0 / "addcont" / name.substr(4, 9) / name.substr(4 + 9 + 1);
        else if (!name.starts_with("update_") || !fs::is_directory(entry, ec))
            continue; // (update_choice_<title> is a note, not a layout)
        if (!layout.empty())
            fs::remove_all(layout, ec);
        fs::remove_all(entry, ec);
        lr_log(RETRO_LOG_INFO, "Left by a run that was not closed, removed: %s\n",
            (layout.empty() ? entry : layout).generic_string().c_str());
    }
}

// Marked as laid out, before lazy_pkg lays it out
static void mark_lazy_run(const fs::path &pref_path, const std::string &title_id) {
    const fs::path marker = lazy_marker(pref_path, title_id);
    boost::system::error_code ec;
    fs::create_directories(marker.parent_path(), ec);
    fs::ofstream(marker).put('\n');
}

// A license where the console keeps it, ux0/license/<title id>/<content id>.rif,
// for NpDrm to find
static void write_license(const fs::path &pref_path, const std::string &title_id, const std::string &content_id, const std::string &zrif) {
    if (zrif.empty() || content_id.empty())
        return;
    const fs::path lic_dir = pref_path / "ux0" / "license" / title_id;
    boost::system::error_code ec;
    fs::create_directories(lic_dir, ec);
    std::ofstream lic((lic_dir / (content_id + ".rif")).string(), std::ios::binary);
    zrif2rif(zrif, lic);
}

static std::string find_pkg_license(const fs::path &pkg_path, const fs::path &pref_path);

// Whether a content is encrypted, so that it cannot be used without its license: a PKG
// always counts as one, a folder or VPK/ZIP when it has a PFS
static bool needs_license(const fs::path &path) {
    boost::system::error_code ec;
    if (!lr_vfs_is_uri(path.string()) && fs::is_directory(path, ec))
        return fs::is_directory(path / "sce_pfs", ec);
    if (!lazy_pkg::is_archive(path))
        return true;
    FILE *fp = FOPEN(path.c_str(), "rb");
    if (!fp)
        return true;
    bool encrypted = false;
    mz_zip_archive zip{};
    if (mz_zip_reader_init_cfile(&zip, fp, 0, 0)) {
        const mz_uint count = mz_zip_reader_get_num_files(&zip);
        for (mz_uint i = 0; i < count && !encrypted; i++) {
            mz_zip_archive_file_stat st;
            encrypted = mz_zip_reader_file_stat(&zip, i, &st) && std::string_view(st.m_filename).find("sce_pfs/") != std::string_view::npos;
        }
        mz_zip_reader_end(&zip);
    }
    fclose(fp);
    return encrypted;
}

static ContentOptionsHandler s_content_options;

static std::function<std::string(const std::string &)> s_content_value;
static std::function<void(const std::string &, const std::string &)> s_set_content_value;

void set_content_option_accessors(std::function<std::string(const std::string &)> get,
    std::function<void(const std::string &, const std::string &)> set) {
    s_content_value = std::move(get);
    s_set_content_value = std::move(set);
}

void set_content_options_handler(ContentOptionsHandler handler) {
    s_content_options = std::move(handler);
}

// An option key holds letters, digits and underscores
static std::string option_key_part(const std::string &text) {
    std::string part = text;
    for (char &c : part) {
        if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
            c = '_';
    }
    return part;
}

static std::string file_name_of(const std::string &path) {
    const size_t slash = path.find_last_of('/');
    return slash == std::string::npos ? path : path.substr(slash + 1);
}

// An Update or DLC value as "Installed (Enabled)", "Direct (Disabled)" or,
// with several updates, "Installed (1.05)": how it is used, with the state or
// version in brackets (Shoegzer). The file it comes from is not shown.
static std::string value_with_source(const std::string &value, const std::string &mode, const std::string &path) {
    (void)path;
    return fmt::format("{} ({})", mode, value);
}

static bool read_installed_sfo(const fs::path &dir, sfo::SfoAppInfo &info) {
    vfs::FileBuffer sfo;
    if (!fs_utils::read_data(dir / "sce_sys" / "param.sfo", sfo))
        return false;
    sfo::get_param_info(info, sfo, 1);
    return true;
}

// The "installed once" markers (handle_pkg_game) of what was just deleted, so
// that loading its PKG installs it again
static void forget_install_markers(const fs::path &pref_path, const std::function<bool(const std::string &)> &matches) {
    boost::system::error_code ec;
    std::vector<fs::path> gone;
    for (fs::directory_iterator it(pref_path / "ux0" / "libretro_pkg", ec), end; !ec && it != end; it.increment(ec)) {
        if (matches(it->path().filename().string()))
            gone.push_back(it->path());
    }
    for (const fs::path &marker : gone)
        fs::remove(marker, ec);
}

// Notes kept under ux0/libretro_pkg about an update or DLC installed by
// loading its own file (PKG, VPK/ZIP or folder). manual_<title>_update and manual_<title>_dlc_<id>: it
// was installed since the game last started, so the game's option for it is
// turned on again - left at None or Disabled from before, the option would
// delete at the game's next start what was just installed. patch_<title>:
// the name of the marker of the update kept in ux0/patch.
static fs::path manual_update_note(const fs::path &pref_path, const std::string &title_id) {
    return pref_path / "ux0" / "libretro_pkg" / ("manual_" + title_id + "_update");
}

static fs::path manual_dlc_note(const fs::path &pref_path, const std::string &title_id, const std::string &dlc_id) {
    return pref_path / "ux0" / "libretro_pkg" / ("manual_" + title_id + "_dlc_" + option_key_part(dlc_id));
}

// Kept as long as an update or DLC stays installed the way it last was:
// manualinstall_<title>_update and manualinstall_<title>_dlc_<id> say it was
// installed by loading its own file. Made by such
// an install, removed by an install from the game's folder.
static fs::path manual_install_mark(const fs::path &pref_path, const std::string &title_id, const std::string &dlc_id) {
    return pref_path / "ux0" / "libretro_pkg"
        / (dlc_id.empty() ? "manualinstall_" + title_id + "_update" : "manualinstall_" + title_id + "_dlc_" + option_key_part(dlc_id));
}

// An update or DLC (by its category) installed by loading its own file, marked as
// such, so that it stays installed whatever the Run Mode. The mark holds the path of the
// file (or folder) it was installed from.
static void mark_forced_install(const fs::path &pref_path, const std::string &title_id, const std::string &category,
    const std::string &content_id, const fs::path &source) {
    std::string dlc_id;
    if (category == "ac" && content_id.size() > 20)
        dlc_id = content_id.substr(20);
    else if (category.find("gp") == std::string::npos)
        return;
    boost::system::error_code ec;
    fs::create_directories(pref_path / "ux0" / "libretro_pkg", ec);
    fs::ofstream(manual_install_mark(pref_path, title_id, dlc_id)) << source.string() << '\n';
    drop_shelved_copy(pref_path, title_id, dlc_id);
}

static fs::path patch_marker_note(const fs::path &pref_path, const std::string &title_id) {
    return pref_path / "ux0" / "libretro_pkg" / ("patch_" + title_id);
}

// What is done about a game's updates and DLC once the game itself is there
struct ContentPlan {
    // An update merged into the installed game (by an install before updates
    // stayed in ux0/patch) is no longer the one chosen: the game's folder goes,
    // and the game is installed again from its PKG
    bool reinstall_game = false;
    std::string update_path, update_version;
    struct Dlc {
        std::string path, content_id;
    };
    std::vector<Dlc> dlcs;
};

// What content_closed needs of the game that was loaded
static struct {
    fs::path pref_path;
    std::string title_id;
    std::string game_key, update_key;
    struct Dlc {
        std::string key, dlc_id, content_id;
    };
    std::vector<Dlc> dlcs;
    // Remove Content's entries: each one's key and title ID
    std::vector<std::pair<std::string, std::string>> removals;
    // The Content options as declared, without the values set first, to
    // declare again when the title being run is measured
    std::vector<ContentOption> options;
    // The name Remove Content shows for the title being run
    std::string shown_name;
    // Each Content option's value as last seen, to tell a change of one
    std::map<std::string, std::string> seen;
} s_loaded_content;

// An installed game deleted: its folder in ux0/app, and every install marker
// of the title's, so that its PKG - and a DLC's, loaded again - installs again.
// The shader cache goes too when the user removes the title's data (Remove Content), and
// stays when only the way it is run changes (Run Mode).
static void uninstall_game(const fs::path &pref_path, const std::string &title_id, bool shader_cache) {
    boost::system::error_code ec;
    fs::remove_all(pref_path / "ux0" / "app" / title_id, ec);
    if (shader_cache)
        fs::remove_all(pref_path / "cache" / "shaders" / title_id, ec);
    forget_install_markers(pref_path, [&](const std::string &name) { return name.size() > 16 && name[6] == '-' && name.compare(7, 9, title_id) == 0; });
}

// Remove Content - what the core wrote for a title besides its saves: the
// installed game, update and DLC with their install markers (Run Mode:
// Installed), the Persistent Cache of the game, its update and its DLC
// (Direct with Cache), and its shader cache (every method). Saves and
// trophies in ux0/user stay.
// A DLC turned off, or an installed update another version or None is chosen
// over, is set aside here rather than deleted, and comes back when it is
// chosen again: only Remove Content deletes what was installed (Shoegzer)
static fs::path shelf_dir(const fs::path &pref_path) {
    return pref_path / "ux0" / "libretro_pkg" / "off";
}
static fs::path dlc_shelf(const fs::path &pref_path, const std::string &title_id, const std::string &dlc_id) {
    return shelf_dir(pref_path) / "addcont" / title_id / dlc_id;
}
static fs::path patch_shelf(const fs::path &pref_path, const std::string &title_id, const std::string &version) {
    return shelf_dir(pref_path) / "patch" / title_id / version;
}

// An update or DLC just installed by loading it on its own: a copy of the same one set aside
// before is no longer needed, and it would only sit there, listed once,
// taking space until Remove Content (i30817). An update by the version it
// installed with, a DLC by its ID.
static void drop_shelved_copy(const fs::path &pref_path, const std::string &title_id, const std::string &dlc_id) {
    boost::system::error_code ec;
    if (!dlc_id.empty()) {
        fs::remove_all(dlc_shelf(pref_path, title_id, dlc_id), ec);
        return;
    }
    sfo::SfoAppInfo info;
    if (read_installed_sfo(pref_path / "ux0" / "patch" / title_id, info) && !info.app_version.empty())
        fs::remove_all(patch_shelf(pref_path, title_id, info.app_version), ec);
}

// One directory moved to another place on the same memory card
static bool move_dir(const fs::path &from, const fs::path &to) {
    boost::system::error_code ec;
    fs::remove_all(to, ec);
    fs::create_directories(to.parent_path(), ec);
    fs::rename(from, to, ec);
    return !ec;
}

// The titles the core holds data of, for Remove Content's list (i30817), in one
// file, ux0/libretro_pkg/titles.tsv: each title's ID, when it was first seen,
// how it last ran, the size of its data and its name. The list is read from
// it at the start, with no walk through the titles' directories; only the
// title being run is measured: when it is new to the list or runs another
// way, and again when it is closed or reset.
struct TitleRecord {
    std::time_t first_seen = 0;
    std::string mode; // install, cache or run
    std::uint64_t size = 0;
    std::string name;
};
static fs::path titles_file(const fs::path &pref_path) {
    return pref_path / "ux0" / "libretro_pkg" / "titles.tsv";
}
static std::map<std::string, TitleRecord> load_titles(const fs::path &pref_path) {
    std::map<std::string, TitleRecord> titles;
    std::ifstream in(titles_file(pref_path).string());
    std::string line;
    while (std::getline(in, line)) {
        std::vector<std::string> f;
        size_t start = 0;
        for (size_t tab; (tab = line.find('\t', start)) != std::string::npos && f.size() < 4; start = tab + 1)
            f.push_back(line.substr(start, tab - start));
        f.push_back(line.substr(start));
        if (f.size() != 5 || f[0].empty())
            continue;
        TitleRecord r;
        r.first_seen = static_cast<std::time_t>(std::strtoll(f[1].c_str(), nullptr, 10));
        r.mode = f[2];
        r.size = std::strtoull(f[3].c_str(), nullptr, 10);
        r.name = f[4];
        titles[f[0]] = r;
    }
    return titles;
}
static void save_titles(const fs::path &pref_path, const std::map<std::string, TitleRecord> &titles) {
    boost::system::error_code ec;
    fs::create_directories(titles_file(pref_path).parent_path(), ec);
    const fs::path tmp = titles_file(pref_path).string() + ".tmp";
    {
        std::ofstream out(tmp.string(), std::ios::trunc);
        for (const auto &[id, r] : titles)
            out << id << '\t' << static_cast<long long>(r.first_seen) << '\t' << r.mode << '\t' << r.size << '\t' << r.name << '\n';
    }
    fs::rename(tmp, titles_file(pref_path), ec);
}

// The title being run, measured again when it is closed or reset
static struct {
    fs::path pref_path;
    std::string title_id;
} s_running_title;

// A title turned ON in Remove Content has a note here while it is ON: what a
// crash or a killed frontend left undone - its data not removed, or removed
// only in part - is finished at the next start, before anything runs
// (i30817)
static fs::path removal_note(const fs::path &pref_path, const std::string &title_id) {
    return pref_path / "ux0" / "libretro_pkg" / ("remove_" + title_id);
}

// A title's Persistent Cache folders in cache/pkg: lazy_pkg names them
// <title>, <title>_update and <title>_<DLC>
static std::vector<fs::path> persistent_cache_dirs(const fs::path &pref_path, const std::string &title_id) {
    std::vector<fs::path> dirs;
    boost::system::error_code ec;
    for (fs::directory_iterator it(pref_path / "cache" / "pkg", ec), end; !ec && it != end; it.increment(ec)) {
        const std::string name = it->path().filename().string();
        if (name == title_id || name.rfind(title_id + "_", 0) == 0)
            dirs.push_back(it->path());
    }
    return dirs;
}

static void remove_title_data(const fs::path &pref_path, const std::string &title_id) {
    boost::system::error_code ec;
    // the game, its install markers and its shader cache, and whatever was
    // installed for it besides: its update and DLC, also those set aside
    uninstall_game(pref_path, title_id, true);
    fs::remove_all(pref_path / "ux0" / "patch" / title_id, ec);
    fs::remove_all(pref_path / "ux0" / "addcont" / title_id, ec);
    fs::remove_all(shelf_dir(pref_path) / "patch" / title_id, ec);
    fs::remove_all(shelf_dir(pref_path) / "addcont" / title_id, ec);
    fs::remove(patch_marker_note(pref_path, title_id), ec);
    for (const auto &dir : persistent_cache_dirs(pref_path, title_id))
        fs::remove_all(dir, ec);
    auto titles = load_titles(pref_path);
    if (titles.erase(title_id))
        save_titles(pref_path, titles);
    fs::remove(removal_note(pref_path, title_id), ec);
}

void finish_pending_removals(const fs::path &pref_path) {
    boost::system::error_code ec;
    std::vector<std::string> pending;
    for (fs::directory_iterator it(pref_path / "ux0" / "libretro_pkg", ec), end; !ec && it != end; it.increment(ec)) {
        const std::string name = it->path().filename().string();
        if (name.rfind("remove_", 0) == 0 && name.size() > 7)
            pending.push_back(name.substr(7));
    }
    for (const std::string &id : pending) {
        remove_title_data(pref_path, id);
        lr_log(RETRO_LOG_INFO, "%s: its data is removed (Remove Content, not finished when the core last closed)\n", id.c_str());
    }
}

// The space everything under a directory takes on the disk: a Persistent
// Cache's files are sparse, holding only what was read so far
static std::uint64_t disk_usage(const fs::path &dir) {
    std::uint64_t total = 0;
    boost::system::error_code ec;
    for (fs::recursive_directory_iterator it(dir, ec), end; !ec && it != end; it.increment(ec)) {
        if (fs::is_regular_file(it->path(), ec))
            total += lazy_pkg::disk_size(it->path());
    }
    return total;
}

// The size of what Remove Content deletes for a title (remove_title_data): its
// install, update and DLC, also those set aside, its Persistent Cache and its
// shader cache. While a title runs without installing (laid_out), what is
// laid out for the run in ux0/app and ux0/addcont is not counted: it goes
// when the title is closed.
static std::uint64_t title_size(const fs::path &pref_path, const std::string &title_id, bool laid_out) {
    std::uint64_t size = 0;
    boost::system::error_code ec;
    if (!laid_out)
        size += disk_usage(pref_path / "ux0" / "app" / title_id);
    for (fs::directory_iterator it(pref_path / "ux0" / "addcont" / title_id, ec), end; !ec && it != end; it.increment(ec)) {
        boost::system::error_code marker_ec;
        if (!laid_out || !fs::exists(pref_path / "ux0" / "libretro_pkg" / ("dlc_" + title_id + "_" + it->path().filename().string()), marker_ec))
            size += disk_usage(it->path());
    }
    for (const fs::path &dir : { pref_path / "ux0" / "patch" / title_id, shelf_dir(pref_path) / "patch" / title_id,
             shelf_dir(pref_path) / "addcont" / title_id, pref_path / "cache" / "shaders" / title_id })
        size += disk_usage(dir);
    for (const fs::path &dir : persistent_cache_dirs(pref_path, title_id))
        size += disk_usage(dir);
    return size;
}

// A size for the screen, as the system's own file manager has it: MB and GB
// of 1024 on Windows (the Xbox too), as Windows names them, and of 1000
// elsewhere (sco8487). Three digits at most, rounded to the nearest, with no
// trailing zeros (printf's %g): GB from what would be 1000 MB (0.977 GB,
// 1.5 GB, 2 GB, 12.3 GB, 123 GB). Only the display: titles.tsv holds bytes
// (i30817).
static std::string human_size(std::uint64_t bytes) {
#ifdef _WIN32
    constexpr double unit = 1024;
#else
    constexpr double unit = 1000;
#endif
    const double mb = bytes / (unit * unit);
    if (mb < 999.5)
        return fmt::format("{:.3g} MB", std::max(mb, 0.01));
    const double gb = mb / unit;
    // %g would write 1000 GB and over as 1e+03
    return gb < 999.5 ? fmt::format("{:.3g} GB", gb) : fmt::format("{:.0f} GB", gb);
}

// "Name (ID) - size", the size of what would be deleted (i30817)
static std::string removal_label(const std::string &title_id, const TitleRecord &r) {
    std::string label = r.name.empty() ? title_id : fmt::format("{} ({})", r.name, title_id);
    if (r.size)
        label += " - " + human_size(r.size);
    return label;
}

static std::string removal_key(const std::string &title_id) {
    return "vita3k_zremove_" + option_key_part(title_id);
}

void record_started_title(const fs::path &pref_path, const std::string &title_id, const std::string &name, const std::string &mode) {
    s_running_title = {};
    if (title_id.empty())
        return;
    s_running_title = { pref_path, title_id };

    // Run another way than Direct with Cache, the title's Persistent Cache
    // goes, as an install goes when Run Mode no longer installs (sco8487);
    // its shader cache stays, every Run Mode uses it
    if (mode != "cache") {
        boost::system::error_code ec;
        const std::vector<fs::path> gone = persistent_cache_dirs(pref_path, title_id);
        for (const auto &dir : gone)
            fs::remove_all(dir, ec);
        if (!gone.empty())
            lr_log(RETRO_LOG_INFO, "%s runs %s: its Persistent Cache in cache/pkg is deleted\n",
                title_id.c_str(), mode == "install" ? "installed" : "without a cache");
    }

    auto titles = load_titles(pref_path);
    const bool fresh = !titles.contains(title_id);
    TitleRecord &r = titles[title_id];
    // new to the list, or run another way: a new line, measured now
    if (fresh || r.mode != mode) {
        r.first_seen = std::time(nullptr);
        r.mode = mode;
        r.size = title_size(pref_path, title_id, mode != "install");
    } else if (name.empty() || r.name == name)
        return;
    if (!name.empty())
        r.name = name;
    save_titles(pref_path, titles);

    // Its entry in Remove Content was made before the title was installed or
    // measured: declared again with what it holds now (i30817)
    if (s_loaded_content.title_id != title_id || !s_content_options)
        return;
    const auto entry = std::find_if(s_loaded_content.options.begin(), s_loaded_content.options.end(),
        [&](const ContentOption &o) { return o.key == removal_key(title_id); });
    if (entry == s_loaded_content.options.end())
        return;
    TitleRecord shown = r;
    if (shown.name.empty())
        shown.name = s_loaded_content.shown_name;
    const std::string label = removal_label(title_id, shown);
    if (label != entry->label) {
        entry->label = label;
        s_content_options(s_loaded_content.options);
    }
}

// The title that was run, measured again now that it is closed; not when its
// data was just removed
static void measure_closed_title() {
    const auto title = std::move(s_running_title);
    s_running_title = {};
    if (title.title_id.empty())
        return;
    auto titles = load_titles(title.pref_path);
    const auto found = titles.find(title.title_id);
    if (found == titles.end())
        return;
    const std::uint64_t size = title_size(title.pref_path, title.title_id, false);
    if (size != found->second.size) {
        found->second.size = size;
        save_titles(title.pref_path, titles);
    }
}

// Every title the core holds data of that Remove Content deletes - an install,
// an update or DLC installed or set aside, a persistent cache, a shader cache
// - each with the time its newest directory was last written. Read once, to
// fill titles.tsv when there is none yet (data of a core from before it).
static std::map<std::string, std::time_t> titles_with_data(const fs::path &pref_path) {
    std::map<std::string, std::time_t> titles;
    boost::system::error_code ec;
    const auto add = [&](const fs::path &parent, bool cache_names) {
        for (fs::directory_iterator it(parent, ec), end; !ec && it != end; it.increment(ec)) {
            std::string id = it->path().filename().string();
            // lazy_pkg's cache folders are <title>, <title>_update and <title>_<DLC>
            if (cache_names)
                id = id.substr(0, id.find('_'));
            if (id.empty() || !fs::is_directory(it->path(), ec))
                continue;
            const std::time_t when = fs::last_write_time(it->path(), ec);
            auto found = titles.find(id);
            if (found == titles.end())
                titles.emplace(id, when);
            else if (when > found->second)
                found->second = when;
        }
        ec.clear();
    };
    add(pref_path / "ux0" / "app", false);
    add(pref_path / "ux0" / "patch", false);
    add(pref_path / "ux0" / "addcont", false);
    add(shelf_dir(pref_path) / "patch", false);
    add(shelf_dir(pref_path) / "addcont", false);
    add(pref_path / "cache" / "pkg", true);
    add(pref_path / "cache" / "shaders", false);
    return titles;
}

// A title's name from its installed param.sfo, or from the param.sfo in its
// Persistent Cache (a file named by a hash of its path, so found by what it
// starts with); empty when there is neither - Direct leaves none behind
static std::string installed_title_name(const fs::path &pref_path, const std::string &title_id) {
    sfo::SfoAppInfo info;
    for (const char *dir : { "app", "patch" }) {
        if (read_installed_sfo(pref_path / "ux0" / dir / title_id, info) && !info.app_title.empty())
            return info.app_title;
    }
    boost::system::error_code ec;
    for (fs::directory_iterator it(pref_path / "cache" / "pkg" / title_id, ec), end; !ec && it != end; it.increment(ec)) {
        if (it->path().extension() != ".bin" || fs::file_size(it->path(), ec) > 1024 * 1024)
            continue;
        vfs::FileBuffer sfo;
        if (fs_utils::read_data(it->path(), sfo) && sfo.size() > 4 && memcmp(sfo.data(), "\0PSF", 4) == 0) {
            sfo::get_param_info(info, sfo, 1);
            if (!info.app_title.empty())
                return info.app_title;
        }
    }
    return std::string();
}

// titles.tsv filled from what is on the memory card, once
static std::map<std::string, TitleRecord> titles_from_disk(const fs::path &pref_path) {
    std::map<std::string, TitleRecord> titles;
    boost::system::error_code ec;
    for (const auto &[id, when] : titles_with_data(pref_path)) {
        TitleRecord &r = titles[id];
        r.first_seen = when;
        r.name = installed_title_name(pref_path, id);
        // a game run without installing leaves no eboot.bin of its own behind
        r.mode = !persistent_cache_dirs(pref_path, id).empty() ? "cache" : fs::exists(pref_path / "ux0" / "app" / id / "eboot.bin", ec) ? "install" : "run";
        r.size = title_size(pref_path, id, false);
    }
    save_titles(pref_path, titles);
    return titles;
}

// Update versions as numbers: "01.09" against "01.10" part by part
static bool version_less(const std::string &a, const std::string &b) {
    std::vector<long> pa, pb;
    for (const auto *p : { &a, &b }) {
        auto &out = p == &a ? pa : pb;
        size_t start = 0;
        while (start <= p->size()) {
            const size_t dot = p->find('.', start);
            out.push_back(std::strtol(p->substr(start, dot == std::string::npos ? std::string::npos : dot - start).c_str(), nullptr, 10));
            if (dot == std::string::npos)
                break;
            start = dot + 1;
        }
    }
    return std::lexicographical_compare(pa.begin(), pa.end(), pb.begin(), pb.end());
}

// The update version a game was last started with, kept so that when its PKG
// is taken out of the folder the next lower version is used in its place
// (sco8487); the frontend itself only falls back to the default, the newest
static fs::path update_choice_note(const fs::path &pref_path, const std::string &title_id) {
    return pref_path / "ux0" / "libretro_pkg" / ("update_choice_" + title_id);
}

// The updates and DLC of a game loaded from its PKG, VPK/ZIP or folder
// (sco8487: everything for a game in one folder): the update and DLC PKGs,
// VPKs and ZIPs lying next to the game's (and inside a game's folder),
// and what is installed - an update merged into ux0/app/<title> or kept in
// ux0/patch/<title>, DLC in ux0/addcont/<title>. They are declared as options
// of the game's own (Content), in every Run Mode: the game, one update
// of those there are, or none, and each DLC on or off. A new game starts
// with the newest update and every DLC.
//
// An installed DLC that is turned off, and the installed update when another
// one or None is chosen, are set aside when the content is closed
// (content_closed) and come back when chosen again; here, before the game is
// started, the same is done for what a close that never ran left over. What
// is chosen and not installed is returned as the plan, carried out by
// apply_content once the game is installed or laid out.
//
// The keys start with vita3k_zinstall_ because the frontend writes its
// options file sorted by key, which puts the part that grows with every game
// after the core's own options.
static ContentPlan plan_content(const fs::path &pkg_path, const std::string &title_id, const fs::path &pref_path, bool run_pkg) {
    ContentPlan plan;
    s_loaded_content = {};

    // Not for an update or DLC PKG loaded on its own to install it
    lazy_pkg::PkgInfo game_info;
    if (!lazy_pkg::pkg_info(pkg_path, game_info) || game_info.category.find("gp") != std::string::npos
        || game_info.category.find("ac") != std::string::npos)
        return plan;

    const std::string game = pkg_path.generic_string();
    std::vector<std::string> candidates;
    if (lr_vfs_is_uri(game)) {
        // Through the frontend's VFS (SAF, Samba): what lies beside the game,
        // and with Include Subdirectories every directory below it, as for a
        // local game (sco8487: DLC in subdirectories over Samba were not found)
        const size_t slash = game.find_last_of('/');
        if (slash != std::string::npos)
            candidates = lr_vfs_list(game.substr(0, slash));
        if (s_content_value && s_content_value("vita3k_content_subdirs") == "enabled") {
            for (size_t i = 0; i < candidates.size() && candidates.size() < 4096; i++) {
                bool is_directory = false;
                if (candidates[i] == game || !lr_vfs_stat(candidates[i], &is_directory, nullptr) || !is_directory)
                    continue;
                for (std::string &entry : lr_vfs_list(candidates[i]))
                    candidates.push_back(std::move(entry));
            }
        }
        lr_log(RETRO_LOG_INFO, "Content of %s through the frontend's VFS: %zu entries beside and below it\n",
            title_id.c_str(), candidates.size());
    } else {
        boost::system::error_code ec;
        for (fs::directory_iterator it(pkg_path.parent_path(), ec), end; it != end; it.increment(ec)) {
            if (ec)
                break;
            candidates.push_back(it->path().generic_string());
        }
        // A game folder: its updates and DLC may be inside it too, and a NoNpDrm dump's
        // (app/<title id>) are its patch/<title id> and addcont/<title id>/<DLC> beside it
        if (fs::is_directory(pkg_path, ec)) {
            for (fs::directory_iterator it(pkg_path, ec), end; it != end; it.increment(ec)) {
                if (ec)
                    break;
                candidates.push_back(it->path().generic_string());
            }
            if (pkg_path.parent_path().filename() == "app") {
                const fs::path root = pkg_path.parent_path().parent_path();
                candidates.push_back((root / "patch" / title_id).generic_string());
                for (fs::directory_iterator it(root / "addcont" / title_id, ec), end; !ec && it != end; it.increment(ec))
                    candidates.push_back(it->path().generic_string());
            }
        }
        // Include Subdirectories (i30817, Shoegzer): every directory below the
        // title's, at any depth - a directory per DLC with its license. An
        // extracted title (sce_sys/param.sfo) is a candidate itself, not looked into.
        if (s_content_value && s_content_value("vita3k_content_subdirs") == "enabled") {
            const size_t beside = candidates.size();
            for (size_t i = 0; i < beside; i++) {
                const fs::path dir(candidates[i]);
                if (dir == pkg_path || !fs::is_directory(dir, ec) || fs::exists(dir / "sce_sys" / "param.sfo", ec))
                    continue;
                for (fs::recursive_directory_iterator it(dir, ec), end; !ec && it != end; it.increment(ec)) {
                    candidates.push_back(it->path().generic_string());
                    boost::system::error_code sub_ec;
                    if (fs::is_directory(it->path(), sub_ec) && fs::exists(it->path() / "sce_sys" / "param.sfo", sub_ec))
                        it.disable_recursion_pending();
                }
                ec.clear();
            }
        }
    }

    struct Update {
        std::string path, version;
    };
    struct Dlc {
        std::string path, content_id, dlc_id, title;
        bool installed = false;
        // installed, and set aside while turned off
        bool shelved = false;
    };
    std::vector<Update> updates;
    std::vector<Dlc> dlcs;
    boost::system::error_code ec;
    const fs::path app = pref_path / "ux0" / "app" / title_id;
    const fs::path patch = pref_path / "ux0" / "patch" / title_id;
    const fs::path addcont = pref_path / "ux0" / "addcont" / title_id;
    const auto dlc_marker = [&](const std::string &dlc_id) {
        return pref_path / "ux0" / "libretro_pkg" / ("dlc_" + title_id + "_" + dlc_id);
    };

    // The game follows Run Mode too (sco8487): installed while Run Mode
    // now runs it from its PKG, it is uninstalled before this start and run
    // from the PKG, with its update and DLC as chosen. Saves are not touched.
    // Only when the PKG can be run without installing - with no license for it
    // the start would install it again at once.
    if (run_pkg && fs::exists(app / "eboot.bin", ec)
        && (lazy_pkg::is_archive(pkg_path) || fs::is_directory(pkg_path, ec)
            || !find_pkg_license(pkg_path, pref_path).empty())) {
        uninstall_game(pref_path, title_id, false);
        lr_log(RETRO_LOG_INFO, "%s was installed and Run Mode runs it from its PKG: ux0/app/%s is deleted, the game is read out of its PKG\n",
            title_id.c_str(), title_id.c_str());
    }

    for (const std::string &candidate : candidates) {
        // A PKG, VPK/ZIP or folder of a content (a NoNpDrm dump's update or DLC)
        const bool folder = !lr_vfs_is_uri(candidate) && fs::is_regular_file(fs::path(candidate) / "sce_sys" / "param.sfo", ec);
        if (candidate == game || candidate.size() < 4
            || (string_utils::tolower(candidate.substr(candidate.size() - 4)) != ".pkg"
                && !lazy_pkg::is_archive(fs::path(candidate)) && !folder))
            continue;
        lazy_pkg::PkgInfo info;
        if (!lazy_pkg::pkg_info(fs::path(candidate), info)) {
            if (lr_vfs_is_uri(candidate))
                lr_log(RETRO_LOG_WARN, "Content: %s could not be read through the frontend's VFS\n", candidate.c_str());
            continue;
        }
        if (info.title_id != title_id)
            continue;
        if (info.category.find("ac") != std::string::npos) {
            Dlc dlc;
            dlc.path = candidate;
            dlc.content_id = info.content_id;
            dlc.dlc_id = info.content_id.size() > 20 ? info.content_id.substr(20) : info.content_id;
            dlc.title = info.title;
            // A folder with its marker is what a run the frontend did not
            // end left behind, not an installation
            dlc.installed = fs::exists(addcont / dlc.dlc_id, ec) && !fs::exists(dlc_marker(dlc.dlc_id), ec);
            // One set aside while turned off, whose PKG is here beside the game:
            // the PKG has it all, so the copy goes now (i30817), and turning it
            // on again reads it out of the PKG or installs it again
            if (!dlc.installed && fs::exists(dlc_shelf(pref_path, title_id, dlc.dlc_id), ec)) {
                fs::remove_all(dlc_shelf(pref_path, title_id, dlc.dlc_id), ec);
                forget_install_markers(pref_path, [&](const std::string &name) { return name.rfind(dlc.content_id + "_", 0) == 0; });
                lr_log(RETRO_LOG_INFO, "DLC %s of %s: the copy set aside is deleted, its PKG is beside the game\n", dlc.dlc_id.c_str(), title_id.c_str());
            }
            const bool listed = std::any_of(dlcs.begin(), dlcs.end(), [&](const Dlc &other) { return other.dlc_id == dlc.dlc_id; });
            if (!listed)
                dlcs.push_back(std::move(dlc));
        } else if (info.category.find("gp") != std::string::npos) {
            const bool listed = std::any_of(updates.begin(), updates.end(), [&](const Update &other) { return other.version == info.version; });
            if (!listed)
                updates.push_back({ candidate, info.version });
        }
    }

    // DLC installed with no PKG of theirs beside the game
    for (fs::directory_iterator it(addcont, ec), end; !ec && it != end; it.increment(ec)) {
        if (!fs::is_directory(it->path(), ec))
            continue;
        const std::string dlc_id = it->path().filename().string();
        if (fs::exists(dlc_marker(dlc_id), ec))
            continue;
        if (std::any_of(dlcs.begin(), dlcs.end(), [&](const Dlc &other) { return other.dlc_id == dlc_id; }))
            continue;
        Dlc dlc;
        dlc.dlc_id = dlc_id;
        dlc.installed = true;
        sfo::SfoAppInfo info;
        if (read_installed_sfo(it->path(), info)) {
            dlc.title = info.app_title;
            dlc.content_id = info.app_content_id;
        }
        dlcs.push_back(std::move(dlc));
    }
    // ... and those set aside while turned off
    for (fs::directory_iterator it(shelf_dir(pref_path) / "addcont" / title_id, ec), end; !ec && it != end; it.increment(ec)) {
        const std::string dlc_id = it->path().filename().string();
        if (std::any_of(dlcs.begin(), dlcs.end(), [&](const Dlc &other) { return other.dlc_id == dlc_id; }))
            continue;
        Dlc dlc;
        dlc.dlc_id = dlc_id;
        dlc.installed = dlc.shelved = true;
        sfo::SfoAppInfo info;
        if (read_installed_sfo(it->path(), info)) {
            dlc.title = info.app_title;
            dlc.content_id = info.app_content_id;
        }
        dlcs.push_back(std::move(dlc));
    }
    ec.clear();

    // A DLC follows Run Mode (sco8487): one that was installed from the
    // game's folder, while the game now runs from its PKG, is read out of its
    // PKG like the game instead - its installed copy goes, the PKG beside the
    // game has it all. One installed by loading its own PKG
    // stays installed, as its PKG may be anywhere, and so does one with no PKG
    // in the game's folder.
    if (run_pkg && !fs::exists(app / "eboot.bin", ec)) {
        for (Dlc &dlc : dlcs) {
            if (!dlc.installed || dlc.path.empty() || fs::exists(manual_install_mark(pref_path, title_id, dlc.dlc_id), ec))
                continue;
            fs::remove_all(addcont / dlc.dlc_id, ec);
            fs::remove_all(dlc_shelf(pref_path, title_id, dlc.dlc_id), ec);
            if (!dlc.content_id.empty())
                forget_install_markers(pref_path, [&](const std::string &name) { return name.rfind(dlc.content_id + "_", 0) == 0; });
            dlc.installed = dlc.shelved = false;
            lr_log(RETRO_LOG_INFO, "DLC %s of %s: installed from the game's folder, now read out of its PKG as Run Mode says; the installed copy is deleted\n",
                dlc.dlc_id.c_str(), title_id.c_str());
        }
    }

    // The update follows Run Mode the same way (sco8487): one installed from
    // the game's folder, while the game now runs from its PKG, is read out of
    // its PKG beside the game instead and its installed copy goes. One
    // installed by loading its own PKG stays, and so does one whose PKG is
    // not in the game's folder.
    if (run_pkg && !fs::exists(app / "eboot.bin", ec)
        && !fs::exists(manual_install_mark(pref_path, title_id), ec)) {
        sfo::SfoAppInfo info;
        if (read_installed_sfo(patch, info) && !info.app_version.empty()
            && std::any_of(updates.begin(), updates.end(), [&](const Update &u) {
                   return !u.path.empty() && u.version == info.app_version; })) {
            fs::remove_all(patch, ec);
            std::string marker_name;
            {
                fs::ifstream note(patch_marker_note(pref_path, title_id));
                std::getline(note, marker_name);
            }
            fs::remove(patch_marker_note(pref_path, title_id), ec);
            if (!marker_name.empty())
                forget_install_markers(pref_path, [&](const std::string &name) { return name == marker_name; });
            lr_log(RETRO_LOG_INFO, "Update %s of %s: installed from the game's folder, now read out of its PKG as Run Mode says; the installed copy is deleted\n",
                info.app_version.c_str(), title_id.c_str());
        }
    }

    // The installed update: kept in ux0/patch, as every update is installed now,
    // or merged into the installed game by a released build's install, which then
    // carries a version other than its PKG's
    std::string patch_version, merged_version;
    {
        sfo::SfoAppInfo info;
        if (read_installed_sfo(patch, info))
            patch_version = info.app_version;
    }
    if (fs::exists(app / "eboot.bin", ec)) {
        sfo::SfoAppInfo info;
        if (read_installed_sfo(app, info) && !game_info.version.empty() && info.app_version != game_info.version)
            merged_version = info.app_version;
    }
    const std::string installed_version = !patch_version.empty() ? patch_version : merged_version;
    if (!installed_version.empty()
        && std::none_of(updates.begin(), updates.end(), [&](const Update &other) { return other.version == installed_version; }))
        updates.push_back({ std::string(), installed_version });
    // Versions installed before and set aside since, as another one or None
    // was chosen
    std::set<std::string> shelved_versions;
    std::vector<fs::path> shelved_with_file;
    for (fs::directory_iterator it(shelf_dir(pref_path) / "patch" / title_id, ec), end; !ec && it != end; it.increment(ec)) {
        const std::string version = it->path().filename().string();
        // Set aside, but its PKG is here beside the game: the PKG has it all,
        // so the copy goes (i30817), and choosing it again reads it out of
        // the PKG or installs it again
        if (std::any_of(updates.begin(), updates.end(), [&](const Update &other) { return other.version == version && !other.path.empty(); })) {
            shelved_with_file.push_back(it->path());
            continue;
        }
        shelved_versions.insert(version);
        if (std::none_of(updates.begin(), updates.end(), [&](const Update &other) { return other.version == version; }))
            updates.push_back({ std::string(), version });
    }
    ec.clear();
    for (const fs::path &dir : shelved_with_file) {
        fs::remove_all(dir, ec);
        lr_log(RETRO_LOG_INFO, "Update %s of %s: the copy set aside is deleted, its PKG is beside the game\n",
            dir.filename().string().c_str(), title_id.c_str());
    }
    ec.clear();
    std::sort(updates.begin(), updates.end(), [](const Update &a, const Update &b) { return version_less(b.version, a.version); });

    const std::string prefix = "vita3k_zinstall_" + title_id + "_";
    const std::string game_key = prefix + "game";
    const std::string update_key = prefix + "update";
    const auto dlc_key = [&](const Dlc &dlc) { return prefix + "dlc_" + option_key_part(dlc.dlc_id); };
    std::vector<ContentOption> options;

    // The title itself and how it runs (Remove Content is a list of its own, below)
    const bool game_installed = fs::exists(app / "eboot.bin", ec);
    // How an update or DLC that is not installed is used at this start: read out
    // of its PKG like the game, or installed along with an installed game
    const std::string pkg_mode = (run_pkg && !game_installed)
        ? (lazy_pkg::has_cache_root() ? "Direct with Cache" : "Direct")
        : "Installed";
    {
        ContentOption option;
        option.key = game_key;
        option.label = game_info.title.empty() ? fmt::format("Current Title: {}", title_id) : fmt::format("Current Title: {} ({})", game_info.title, title_id);
        if (game_installed || !run_pkg)
            option.values.emplace_back("keep", "Installed");
        else
            option.values.emplace_back("keep", lazy_pkg::has_cache_root() ? "Direct with Cache" : "Direct");
        option.default_value = "keep";
        options.push_back(std::move(option));
    }

    if (!updates.empty()) {
        ContentOption option;
        option.key = update_key;
        const auto update_mode = [&](const Update &update) {
            return update.version == installed_version || shelved_versions.count(update.version) ? std::string("Installed") : pkg_mode;
        };
        // One update (the usual case, a Vita update holds the ones before it):
        // its version in the name, "Installed (Enabled)" / "Installed
        // (Disabled)" as with a DLC (Shoegzer). With several the value has to
        // say which one.
        if (updates.size() == 1) {
            const Update &update = updates.front();
            option.label = fmt::format("Update: {}", update.version);
            option.values.emplace_back(update.version, value_with_source("Enabled", update_mode(update), update.path));
            option.values.emplace_back("none", value_with_source("Disabled", update_mode(update), update.path));
        } else {
            option.label = "Update";
            for (const Update &update : updates)
                option.values.emplace_back(update.version, value_with_source(update.version, update_mode(update), update.path));
            option.values.emplace_back("none", "None");
        }
        option.default_value = installed_version.empty() ? updates.front().version : installed_version;
        if (!installed_version.empty() && fs::exists(manual_update_note(pref_path, title_id), ec))
            option.set_value = installed_version;
        options.push_back(std::move(option));
    }

    for (const Dlc &dlc : dlcs) {
        ContentOption option;
        option.key = dlc_key(dlc);
        option.label = (dlc.title.empty() || dlc.title == dlc.dlc_id) ? fmt::format("DLC: {}", dlc.dlc_id)
                                                                      : fmt::format("DLC: {} ({})", dlc.title, dlc.dlc_id);
        // A PKG without a license beside it cannot be decrypted: the entry only
        // says so
        if (!dlc.installed && !dlc.path.empty() && needs_license(fs::path(dlc.path)) && find_pkg_license(fs::path(dlc.path), pref_path).empty()) {
            option.info = "No license next to it (.zrif, .bin or .rif), so it cannot be used.";
            option.values.emplace_back("inactive", "Inactive (no license)");
            option.default_value = "inactive";
            options.push_back(std::move(option));
            continue;
        }
        const std::string dlc_mode = dlc.installed ? "Installed" : pkg_mode;
        option.values.emplace_back("enabled", value_with_source("Enabled", dlc_mode, dlc.path));
        option.values.emplace_back("disabled", value_with_source("Disabled", dlc_mode, dlc.path));
        option.default_value = "enabled";
        if (dlc.installed && fs::exists(manual_dlc_note(pref_path, title_id, dlc.dlc_id), ec))
            option.set_value = "enabled";
        options.push_back(std::move(option));
    }

    // Remove Content (i30817), a category of its own after Content: each title
    // with data to delete, ON to delete it when the content is closed or reset
    // - the current title first, then the others, the latest seen first, as
    // titles.tsv has them. RetroArch leaves out a category with no options.
    std::vector<std::pair<std::string, std::string>> removals;
    {
        auto titles = fs::exists(titles_file(pref_path), ec) ? load_titles(pref_path) : titles_from_disk(pref_path);
        TitleRecord &current = titles[title_id];
        if (!game_info.title.empty())
            current.name = game_info.title;
        s_loaded_content.shown_name = current.name;
        std::vector<std::string> order;
        for (const auto &t : titles)
            if (t.first != title_id)
                order.push_back(t.first);
        std::stable_sort(order.begin(), order.end(), [&](const std::string &a, const std::string &b) { return titles[a].first_seen > titles[b].first_seen; });
        order.insert(order.begin(), title_id);

        for (const std::string &id : order) {
            ContentOption option;
            option.category = "remove";
            option.key = removal_key(id);
            option.label = removal_label(id, titles[id]);
            option.values = { { "disabled", "OFF" }, { "enabled", "ON" } };
            option.default_value = "disabled";
            removals.emplace_back(option.key, id);
            options.push_back(std::move(option));
        }
    }

    // The notes have done their part once the frontend holds the value; one
    // for something that is no longer installed has none to do
    fs::remove(manual_update_note(pref_path, title_id), ec);
    for (fs::directory_iterator it(pref_path / "ux0" / "libretro_pkg", ec), end; !ec && it != end;) {
        const fs::path note = it->path();
        it.increment(ec);
        if (note.filename().string().rfind("manual_" + title_id + "_dlc_", 0) == 0)
            fs::remove(note, ec);
    }

    std::map<std::string, std::string> chosen;
    if (s_content_options)
        chosen = s_content_options(options);

    // The update the game last ran with is gone from the folder (and not
    // installed): the next lower version that is left, or None
    if (!updates.empty()) {
        std::string last;
        {
            std::ifstream note(update_choice_note(pref_path, title_id).string());
            std::getline(note, last);
        }
        if (!last.empty() && last != "none"
            && std::none_of(updates.begin(), updates.end(), [&](const Update &u) { return u.version == last; })) {
            std::string next = "none";
            for (const Update &u : updates) {
                if (version_less(u.version, last)) {
                    next = u.version;
                    break;
                }
            }
            lr_log(RETRO_LOG_INFO, "Update %s of %s is no longer in the game's folder: %s is used in its place\n",
                last.c_str(), title_id.c_str(), next == "none" ? "none" : next.c_str());
            chosen[update_key] = next;
            if (s_set_content_value)
                s_set_content_value(update_key, next);
        }
    }

    s_loaded_content.pref_path = pref_path;
    s_loaded_content.title_id = title_id;
    s_loaded_content.game_key = game_key;
    s_loaded_content.update_key = updates.empty() ? std::string() : update_key;
    for (const Dlc &dlc : dlcs)
        s_loaded_content.dlcs.push_back({ dlc_key(dlc), dlc.dlc_id, dlc.content_id });
    content_options_changed();

    // Remove Content left on: what it was on for was deleted before the content
    // started (finish_pending_removals), so the entry is only turned off. An
    // entry ON with no note (its note lost) has its title's data deleted now,
    // unless it is the title about to run.
    {
        std::vector<std::string> deleted;
        for (const auto &[key, id] : removals) {
            const auto it = chosen.find(key);
            if (it == chosen.end() || it->second != "enabled")
                continue;
            if (id != title_id) {
                remove_title_data(pref_path, id);
                deleted.push_back(key);
                lr_log(RETRO_LOG_INFO, "%s: its data is removed (Remove Content, left on when the last title was not closed)\n", id.c_str());
            }
            fs::remove(removal_note(pref_path, id), ec);
            if (s_set_content_value)
                s_set_content_value(key, "disabled");
        }
        // Their entries go from the list
        if (!deleted.empty() && s_content_options) {
            options.erase(std::remove_if(options.begin(), options.end(),
                              [&](const ContentOption &o) { return std::find(deleted.begin(), deleted.end(), o.key) != deleted.end(); }),
                options.end());
            removals.erase(std::remove_if(removals.begin(), removals.end(),
                               [&](const auto &r) { return std::find(deleted.begin(), deleted.end(), r.first) != deleted.end(); }),
                removals.end());
            chosen = s_content_options(options);
        }
    }
    s_loaded_content.removals = removals;
    s_loaded_content.options = options;
    for (ContentOption &option : s_loaded_content.options)
        option.set_value.clear();
    const auto value_of = [&](const std::string &key) {
        const auto option = std::find_if(options.begin(), options.end(), [&](const ContentOption &o) { return o.key == key; });
        if (option == options.end())
            return std::string();
        if (!option->set_value.empty())
            return option->set_value;
        const auto it = chosen.find(key);
        // A value kept from before that is no longer offered (its PKG left
        // the folder) counts as none set
        if (it == chosen.end()
            || std::none_of(option->values.begin(), option->values.end(), [&](const auto &value) { return value.first == it->second; }))
            return option->default_value;
        return it->second;
    };

    // A note whose value the frontend did not take stays for the next start
    for (const ContentOption &option : options) {
        if (option.set_value.empty())
            continue;
        const auto it = chosen.find(option.key);
        if (it != chosen.end() && it->second == option.set_value)
            continue;
        const fs::path note = pref_path / "ux0" / "libretro_pkg" / ("manual_" + option.key.substr(sizeof("vita3k_zinstall_") - 1));
        fs::create_directories(note.parent_path(), ec);
        fs::ofstream(note).put('\n');
    }

    for (const Dlc &dlc : dlcs) {
        if (value_of(dlc_key(dlc)) == "inactive")
            continue;
        if (value_of(dlc_key(dlc)) == "disabled") {
            if (dlc.installed && !dlc.shelved) {
                if (move_dir(addcont / dlc.dlc_id, dlc_shelf(pref_path, title_id, dlc.dlc_id)))
                    lr_log(RETRO_LOG_INFO, "DLC %s of %s is turned off: set aside until it is turned on again\n", dlc.dlc_id.c_str(), title_id.c_str());
            } else if (!dlc.installed)
                lr_log(RETRO_LOG_INFO, "PKG: DLC %s is turned off\n", dlc.path.c_str());
            continue;
        }
        if (dlc.shelved) {
            if (move_dir(dlc_shelf(pref_path, title_id, dlc.dlc_id), addcont / dlc.dlc_id))
                lr_log(RETRO_LOG_INFO, "DLC %s of %s is turned on again: back from where it was set aside\n", dlc.dlc_id.c_str(), title_id.c_str());
            continue;
        }
        if (!dlc.installed && !dlc.path.empty())
            plan.dlcs.push_back({ dlc.path, dlc.content_id });
    }

    // What a deletion cut short left of an update: no param.sfo to name it
    if (patch_version.empty() && fs::exists(patch, ec)) {
        fs::remove_all(patch, ec);
        fs::remove(patch_marker_note(pref_path, title_id), ec);
    }
    if (updates.empty())
        return plan;
    const std::string version = value_of(update_key);
    {
        fs::create_directories(update_choice_note(pref_path, title_id).parent_path(), ec);
        std::ofstream(update_choice_note(pref_path, title_id).string()) << version << "\n";
    }
    if (!patch_version.empty() && version != patch_version) {
        move_dir(patch, patch_shelf(pref_path, title_id, patch_version));
        // The marker of the PKG it was installed from, by the name noted then
        std::string marker_name;
        {
            fs::ifstream note(patch_marker_note(pref_path, title_id));
            std::getline(note, marker_name);
        }
        fs::remove(patch_marker_note(pref_path, title_id), ec);
        if (!marker_name.empty())
            forget_install_markers(pref_path, [&](const std::string &name) { return name == marker_name; });
        lr_log(RETRO_LOG_INFO, "Update %s of %s is no longer chosen (Update: %s): set aside\n",
            patch_version.c_str(), title_id.c_str(), version.c_str());
        patch_version.clear();
    }
    // The version chosen was installed before and set aside: it comes back
    if (version != "none" && version != patch_version && shelved_versions.count(version)
        && move_dir(patch_shelf(pref_path, title_id, version), patch)) {
        lr_log(RETRO_LOG_INFO, "Update %s of %s is chosen again: back from where it was set aside\n", version.c_str(), title_id.c_str());
        patch_version = version;
    }
    if (!merged_version.empty() && version != merged_version) {
        // FALLBACK, for games installed by released builds (and by upstream's
        // install), which merged the update into the game's folder: the game's
        // own files are gone, so it is installed again. An update installed now
        // stays in ux0/patch and never gets here.
        // Every marker of this title's, the game's among them: the game is
        // installed again, and a DLC's PKG loaded again just installs again
        forget_install_markers(pref_path, [&](const std::string &name) { return name.size() > 16 && name[6] == '-' && name.compare(7, 9, title_id) == 0; });
        lr_log(RETRO_LOG_INFO, "Update %s merged into %s is no longer chosen (Update: %s): the game is installed again from its PKG\n",
            merged_version.c_str(), title_id.c_str(), version.c_str());
        plan.reinstall_game = true;
        merged_version.clear();
    }
    if (version == "none")
        lr_log(RETRO_LOG_INFO, "No update is used with %s (Update: None)\n", title_id.c_str());
    else if (version == merged_version) {
        // in the game's folder already
    } else if (version == patch_version) {
        // in ux0/patch already, laid over the game
    } else {
        const auto update = std::find_if(updates.begin(), updates.end(), [&](const Update &u) { return u.version == version && !u.path.empty(); });
        if (update != updates.end()) {
            plan.update_path = update->path;
            plan.update_version = update->version;
        }
    }
    return plan;
}

// Whether a Content option changed since it was last asked (each takes effect
// when the content is started again)
bool content_options_changed() {
    if (s_loaded_content.title_id.empty() || !s_content_value)
        return false;
    // Remove Content: a note for each title while it is ON, so that a crash
    // before the close still has it deleted at the next start
    for (const auto &[key, id] : s_loaded_content.removals) {
        boost::system::error_code ec;
        const fs::path note = removal_note(s_loaded_content.pref_path, id);
        if (s_content_value(key) == "enabled") {
            if (!fs::exists(note, ec)) {
                fs::create_directories(note.parent_path(), ec);
                fs::ofstream(note).put('\n');
            }
        } else if (fs::exists(note, ec))
            fs::remove(note, ec);
    }
    std::vector<std::string> keys = { s_loaded_content.game_key };
    if (!s_loaded_content.update_key.empty())
        keys.push_back(s_loaded_content.update_key);
    for (const auto &dlc : s_loaded_content.dlcs)
        keys.push_back(dlc.key);
    bool changed = false;
    for (const std::string &key : keys) {
        const std::string value = s_content_value(key);
        const auto [it, inserted] = s_loaded_content.seen.try_emplace(key, value);
        if (!inserted && it->second != value) {
            it->second = value;
            changed = true;
        }
    }
    return changed;
}

// The content is closed: what was turned off while it ran is set aside now
// rather than at the game's next start (sco8487) - an installed DLC set to
// Disabled, the update kept in ux0/patch when another one or None is chosen -
// and the data of each title turned ON in Remove Content is removed; the title
// that ran is measured again for Remove Content's list, unless its data was
// removed. Nothing is half done if this never runs (the frontend killed, a
// crash): plan_content sets aside the same at the next start, and removes the
// other titles' data. An update merged into the installed game waits for that
// start too, which installs the game again.
void content_closed() {
    const auto content = std::move(s_loaded_content);
    s_loaded_content = {};
    if (content.title_id.empty() || !s_content_value) {
        measure_closed_title();
        return;
    }

    boost::system::error_code ec;
    const fs::path &pref_path = content.pref_path;
    const std::string &title_id = content.title_id;

    // Each title turned ON in Remove Content; its entry is turned off only once
    // its data is gone, so that one cut short is finished at the next start
    bool current_removed = false;
    for (const auto &[key, id] : content.removals) {
        if (s_content_value(key) != "enabled")
            continue;
        remove_title_data(pref_path, id);
        lr_log(RETRO_LOG_INFO, "%s: its data is removed (Remove Content)\n", id.c_str());
        if (s_set_content_value)
            s_set_content_value(key, "disabled");
        current_removed |= id == title_id;
    }
    if (current_removed) {
        s_running_title = {};
        return;
    }

    for (const auto &dlc : content.dlcs) {
        const fs::path dir = pref_path / "ux0" / "addcont" / title_id / dlc.dlc_id;
        // one with its marker was read out of its PKG, not installed
        if (s_content_value(dlc.key) != "disabled" || !fs::exists(dir, ec)
            || fs::exists(pref_path / "ux0" / "libretro_pkg" / ("dlc_" + title_id + "_" + dlc.dlc_id), ec))
            continue;
        if (move_dir(dir, dlc_shelf(pref_path, title_id, dlc.dlc_id)))
            lr_log(RETRO_LOG_INFO, "DLC %s of %s is turned off: set aside until it is turned on again\n", dlc.dlc_id.c_str(), title_id.c_str());
    }

    if (!content.update_key.empty()) {
        const fs::path patch = pref_path / "ux0" / "patch" / title_id;
        const std::string version = s_content_value(content.update_key);
        sfo::SfoAppInfo info;
        if (!version.empty() && read_installed_sfo(patch, info) && !info.app_version.empty() && info.app_version != version) {
            move_dir(patch, patch_shelf(pref_path, title_id, info.app_version));
            std::string marker_name;
            {
                fs::ifstream note(patch_marker_note(pref_path, title_id));
                std::getline(note, marker_name);
            }
            fs::remove(patch_marker_note(pref_path, title_id), ec);
            if (!marker_name.empty())
                forget_install_markers(pref_path, [&](const std::string &name) { return name == marker_name; });
            lr_log(RETRO_LOG_INFO, "Update %s of %s is no longer chosen (Update: %s): set aside\n",
                info.app_version.c_str(), title_id.c_str(), version.c_str());
        }
    }
    measure_closed_title();
}

// A PKG installed much as upstream's install_pkg does it - into ux0/app,
// ux0/patch or ux0/addcont, the license written, emuenv.app_info filled in -
// but decrypted as it is read out of the package (lazy_pkg::install), so each
// file is written once, and an update left in ux0/patch rather than merged
// into the game's folder.
// Anything but a game, an update or a DLC goes to install_pkg.
static bool install_pkg_file(const fs::path &pkg_path, EmuEnvState &emuenv, std::string &zrif) {
    std::vector<std::uint8_t> sfo;
    if (!lazy_pkg::pkg_sfo(pkg_path, sfo))
        return install_pkg(pkg_path, emuenv, zrif);
    sfo::get_param_info(emuenv.app_info, sfo, emuenv.cfg.sys_lang);
    auto &app = emuenv.app_info;
    const fs::path ux0 = emuenv.vita_fs_path / "ux0";
    fs::path dir;
    if (app.app_category.find("gp") != std::string::npos) {
        dir = ux0 / "patch" / app.app_title_id;
        app.app_title += " (Update)";
    } else if (app.app_category == "ac") {
        app.app_content_id = app.app_content_id.size() > 20 ? app.app_content_id.substr(20) : app.app_content_id;
        dir = ux0 / "addcont" / app.app_title_id / app.app_content_id;
        app.app_title += " (DLC)";
    } else if (app.app_category.find("gd") != std::string::npos) {
        dir = ux0 / "app" / app.app_title_id;
        app.app_title += " (App)";
    } else
        return install_pkg(pkg_path, emuenv, zrif);

    std::string error;
    if (!lazy_pkg::install(pkg_path, dir, zrif, error)) {
        lr_log(RETRO_LOG_ERROR, "PKG: %s could not be installed: %s\n", pkg_path.generic_string().c_str(), error.c_str());
        lr_msg(fmt::format("PKG install failed: {}", error).c_str(), 600);
        return false;
    }
    if (app.app_category == "ac")
        return true;
    // An update stays in ux0/patch, where it is laid over the game's files
    // (open_content, lazy_pkg), instead of being merged into the game's folder
    // as upstream does: another update or none is then only a different
    // ux0/patch, and the game's files are never overwritten
    create_license(emuenv, zrif);
    return true;
}

// An update or DLC PKG from the game's folder installed, as loading it does
static bool install_extra_pkg(const fs::path &pkg_path, const fs::path &pref_path, int sys_lang, std::string zrif) {
    // An update or DLC in a VPK/ZIP or a folder: installed the way loading it installs it
    boost::system::error_code ec;
    if (lazy_pkg::is_archive(pkg_path) || fs::is_directory(pkg_path, ec))
        return ensure_game_installed(pkg_path, pref_path, sys_lang, false).success;
    auto emuenv = std::make_unique<EmuEnvState>();
    emuenv->vita_fs_path = pref_path;
    emuenv->cfg.sys_lang = sys_lang;
    emuenv->cache_path = pref_path / "cache";
    return install_pkg_file(pkg_path, *emuenv, zrif);
}

// The plan carried out, with the game installed (the chosen update and DLC
// are installed too, the update into ux0/patch, laid over the game's files) or
// laid out for a run without installing (they are read out of their PKGs,
// VPKs or ZIPs the same way, nothing installed)
// False when, run without installing, an update or DLC chosen has no room (all of it, or with
// Persistent Cache what is not cached yet): the game is then not started (sco8487), and a
// message has said why.
static bool apply_content(const ContentPlan &plan, const std::string &title_id, const std::string &zrif, const fs::path &pref_path,
    int sys_lang, bool lazy) {
    boost::system::error_code ec;
    for (const ContentPlan::Dlc &dlc : plan.dlcs) {
        const std::string dlc_zrif = find_pkg_license(fs::path(dlc.path), pref_path);
        if (!lazy) {
            lr_msg("Installing DLC...", 300);
            if (install_extra_pkg(fs::path(dlc.path), pref_path, sys_lang, dlc_zrif)) {
                lr_log(RETRO_LOG_INFO, "DLC %s installed\n", dlc.path.c_str());
                if (dlc.content_id.size() > 20)
                    fs::remove(manual_install_mark(pref_path, title_id, dlc.content_id.substr(20)), ec);
            }
            else
                lr_log(RETRO_LOG_WARN, "DLC %s could not be installed%s\n", dlc.path.c_str(), dlc_zrif.empty() ? ": it has no license next to it" : "");
            continue;
        }
        std::string error;
        if (dlc_zrif.empty() && needs_license(fs::path(dlc.path)))
            lr_log(RETRO_LOG_WARN, "PKG: DLC %s has no license next to it\n", dlc.path.c_str());
        else if (lazy_pkg::mount_dlc(fs::path(dlc.path), dlc.content_id, dlc_zrif, error))
            write_license(pref_path, title_id, dlc.content_id, dlc_zrif);
        else if (error.rfind(lazy_pkg::NO_ROOM, 0) == 0) {
            lr_log(RETRO_LOG_ERROR, "DLC %s: %s\n", dlc.path.c_str(), error.c_str());
            lr_msg(fmt::format("Not started, no room for a DLC: {}", error).c_str(), 600);
            return false;
        } else
            lr_log(RETRO_LOG_INFO, "PKG: DLC %s not laid out: %s\n", dlc.path.c_str(), error.c_str());
    }

    if (plan.update_path.empty())
        return true;
    if (!lazy) {
        lr_msg("Installing update...", 300);
        if (install_extra_pkg(fs::path(plan.update_path), pref_path, sys_lang, zrif)) {
            lr_log(RETRO_LOG_INFO, "Update %s (version %s) installed\n", plan.update_path.c_str(), plan.update_version.c_str());
            fs::remove(manual_install_mark(pref_path, title_id), ec);
        }
        else
            lr_log(RETRO_LOG_WARN, "Update %s could not be installed\n", plan.update_path.c_str());
        return true;
    }
    std::string error;
    if (lazy_pkg::mount_update(fs::path(plan.update_path), zrif, error))
        lr_log(RETRO_LOG_INFO, "PKG: update %s (version %s) laid over the game\n", plan.update_path.c_str(), plan.update_version.c_str());
    else if (error.rfind(lazy_pkg::NO_ROOM, 0) == 0) {
        lr_log(RETRO_LOG_ERROR, "Update %s: %s\n", plan.update_path.c_str(), error.c_str());
        lr_msg(fmt::format("Not started, no room for the update: {}", error).c_str(), 600);
        return false;
    } else
        lr_log(RETRO_LOG_WARN, "PKG: update %s could not be laid over the game: %s\n", plan.update_path.c_str(), error.c_str());
    return true;
}

// The license of a PKG, as a zRIF: one installed already
// (ux0/license/<title id>/<content id>.rif), or one next to the PKG - a
// <pkg name>.zrif text file holding the zRIF (as NoPayStation lists them), or
// a <pkg name>.rif, work.bin or <content id>.rif license file, or a 512-byte
// .bin holding its content ID. Updates and DLC without DRM need none.
static std::string find_pkg_license(const fs::path &pkg_path, const fs::path &pref_path) {
    boost::system::error_code ec;
    // A folder (a NoNpDrm dump's DLC or update) carries its own, if any
    if (!lr_vfs_is_uri(pkg_path.string()) && fs::is_directory(pkg_path, ec))
        return license_to_zrif(pkg_path / "sce_sys" / "package" / "work.bin", pref_path);
    // A VPK/ZIP carries its own: the work.bin of the content in it (NoNpDrm)
    if (lazy_pkg::is_archive(pkg_path)) {
        FILE *fp = FOPEN(pkg_path.c_str(), "rb");
        if (!fp)
            return {};
        ZipPtr zip(new mz_zip_archive);
        std::memset(zip.get(), 0, sizeof(mz_zip_archive));
        std::string zrif;
        if (mz_zip_reader_init_cfile(zip.get(), fp, 0, 0)) {
            const auto paths = find_archive_content_paths(zip);
            if (!paths.empty())
                zrif = archive_zrif(zip, paths.front(), pref_path);
        }
        zip.reset();
        fclose(fp);
        return zrif;
    }
    std::string zrif = find_pkg_zrif(pkg_path, pref_path);
    if (!zrif.empty())
        return zrif;

    const fs::path dir = pkg_path.parent_path();
    const std::string stem = fs_utils::path_to_utf8(pkg_path.stem());
    for (const fs::path &txt : { dir / (stem + ".zrif"), dir / (stem + ".zRIF"), dir / (stem + ".txt") }) {
        std::string text;
        if (content_read(txt, text)) {
            std::string line = text.substr(0, text.find_first_of("\r\n"));
            line = string_utils::trim_copy(line);
            if (!line.empty()) {
                lr_log(RETRO_LOG_INFO, "PKG license (zRIF) from %s\n", txt.generic_string().c_str());
                return line;
            }
        }
    }

    std::vector<fs::path> rifs = { dir / (stem + ".rif"), dir / "work.bin" };
    std::string content_id;
    if (FILE *f = FOPEN(pkg_path.c_str(), "rb")) {
        PkgHeader header{};
        if (fread(&header, sizeof(header), 1, f) == 1) {
            content_id.assign(header.content_id, strnlen(header.content_id, sizeof(header.content_id)));
            if (!content_id.empty())
                rifs.push_back(dir / (content_id + ".rif"));
        }
        fclose(f);
    }
    for (const fs::path &rif : rifs) {
        if (content_stat(rif, nullptr, nullptr)) {
            // A work.bin is any content's (a DLC's beside its game): only one for this PKG
            if (rif.filename() == "work.bin" && !content_id.empty()) {
                std::string bytes;
                if (!content_read(rif, bytes) || bytes.size() < 0x10 + 0x30
                    || content_id.compare(0, std::string::npos, bytes.data() + 0x10, strnlen(bytes.data() + 0x10, 0x30)) != 0)
                    continue;
            }
            const std::string zrif = license_to_zrif(rif, pref_path);
            if (!zrif.empty()) {
                lr_log(RETRO_LOG_INFO, "PKG license from %s\n", rif.generic_string().c_str());
                return zrif;
            }
        }
    }

    // A license under any name, as PSN and No-Intro sets keep them: a 512-byte
    // .bin in the PKG's folder or the one above it (DLC kept a folder below
    // its game), whose content ID is the PKG's - a license holds it at 0x10
    // (sco). Failing that, the only such file there.
    if (content_id.empty())
        return {};
    std::vector<fs::path> candidates;
    for (const fs::path &folder : { dir, dir.parent_path() }) {
        for (const fs::path &p : content_list(folder)) {
            bool directory = false;
            std::uint64_t size = 0;
            if (string_utils::tolower(p.extension().string()) != ".bin" || !content_stat(p, &directory, &size) || directory || size != 512)
                continue;
            candidates.push_back(p);
            std::string bytes;
            if (content_read(p, bytes) && bytes.size() >= 0x10 + 0x30) {
                const char *id = bytes.data() + 0x10;
                if (content_id.compare(0, std::string::npos, id, strnlen(id, 0x30)) == 0) {
                    lr_log(RETRO_LOG_INFO, "PKG license from %s (its content ID)\n", p.generic_string().c_str());
                    return license_to_zrif(p, pref_path);
                }
            }
        }
    }
    if (candidates.size() == 1) {
        lr_log(RETRO_LOG_INFO, "PKG license from %s (the only one there)\n", candidates.front().generic_string().c_str());
        return license_to_zrif(candidates.front(), pref_path);
    }
    return {};
}

// A PKG - a game, its update or DLC - run without installing it, or installed
// into ux0/app, ux0/patch or ux0/addcont (install_pkg_file), as Run Mode
// and the game's Content options say
static GameInstallResult handle_pkg_game(const fs::path &pkg_path, const fs::path &pref_path, int sys_lang, bool run_pkg) {
    GameInstallResult result;

    // Installed once: a marker per package (content ID and size) under
    // ux0/libretro_pkg, as an update or DLC installs into the same title ID
    // as its game and so cannot be told from it by what is in ux0
    std::string content_id;
    if (FILE *f = FOPEN(pkg_path.c_str(), "rb")) {
        PkgHeader header{};
        if (fread(&header, sizeof(header), 1, f) == 1)
            content_id.assign(header.content_id, strnlen(header.content_id, sizeof(header.content_id)));
        fclose(f);
    }
    if (content_id.size() < 16) {
        lr_log(RETRO_LOG_ERROR, "%s is not a PS Vita PKG\n", pkg_path.generic_string().c_str());
        lr_msg("Not a PS Vita PKG!", 300);
        return result;
    }
    std::uint64_t pkg_size = 0;
    content_stat(pkg_path, nullptr, &pkg_size);
    const fs::path marker = pref_path / "ux0" / "libretro_pkg" / fmt::format("{}_{}", content_id, pkg_size);
    const std::string title_id = content_id.substr(7, 9);


    // A game's updates and DLC, as chosen in its options. What was turned
    // off is deleted by now; the rest follows once the game is there.
    const ContentPlan plan = plan_content(pkg_path, title_id, pref_path, run_pkg);
    if (plan.reinstall_game) {
        boost::system::error_code ec;
        fs::remove_all(pref_path / "ux0" / "app" / title_id, ec);
    }

    if (fs::exists(marker) && fs::exists(pref_path / "ux0" / "app" / title_id / "eboot.bin")) {
        lr_log(RETRO_LOG_INFO, "PKG %s is installed already.\n", content_id.c_str());
        result.success = true;
        result.title_id = title_id;
        result.content_id = content_id;
        vfs::FileBuffer sfo;
        if (fs_utils::read_data(pref_path / "ux0" / "app" / title_id / "sce_sys" / "param.sfo", sfo)) {
            sfo::SfoAppInfo info;
            sfo::get_param_info(info, sfo, sys_lang);
            result.title = info.app_title;
            result.category = info.app_category;
        }
        apply_content(plan, title_id, find_pkg_license(pkg_path, pref_path), pref_path, sys_lang, false);
        return result;
    }

    std::string zrif = find_pkg_license(pkg_path, pref_path);

    // Run without installing: a game's PKG not installed in any form
    if (run_pkg && !zrif.empty() && !fs::exists(pref_path / "ux0" / "app" / title_id / "eboot.bin")) {
        std::string error;
        lr_msg("Preparing the PKG...", 300);
        const fs::path app_dir = pref_path / "ux0" / "app" / title_id;
        mark_lazy_run(pref_path, title_id);
        if (lazy_pkg::mount(pkg_path, app_dir, zrif, error)) {
            write_license(pref_path, title_id, content_id, zrif);

            result.success = true;
            result.title_id = title_id;
            result.content_id = content_id;
            vfs::FileBuffer sfo;
            if (fs_utils::read_data(app_dir / "sce_sys" / "param.sfo", sfo)) {
                sfo::SfoAppInfo info;
                sfo::get_param_info(info, sfo, sys_lang);
                result.title = info.app_title;
                result.category = info.app_category;
            }
            if (!apply_content(plan, title_id, zrif, pref_path, sys_lang, true)) {
                lazy_pkg::unmount();
                fs::remove(lazy_marker(pref_path, title_id));
                return GameInstallResult{};
            }
            return result;
        }
        fs::remove(lazy_marker(pref_path, title_id));
        if (error.rfind(lazy_pkg::NO_ROOM, 0) == 0) {
            // No room for the game run without installing: not started, as an install that does not fit
            lr_log(RETRO_LOG_ERROR, "%s: %s\n", pkg_path.generic_string().c_str(), error.c_str());
            lr_msg(fmt::format("Not started: {}", error).c_str(), 600);
            return result;
        }
        lr_log(RETRO_LOG_WARN, "PKG: cannot run %s without installing it (%s), installing it instead\n",
            pkg_path.generic_string().c_str(), error.c_str());
    }

    auto emuenv = std::make_unique<EmuEnvState>();
    emuenv->vita_fs_path = pref_path;
    emuenv->cfg.sys_lang = sys_lang;
    // The install ends with create_license, which writes a temporary license
    // into the cache folder; left empty, that is create_directories("") and an
    // uncaught "Invalid argument" right after the PFS was decrypted (sco: every
    // PKG install crashed at 80%)
    emuenv->cache_path = pref_path / "cache";
    lr_msg("Installing PKG... this may take a while", 600);
    // Whether the game this may be an update for is installed
    const bool game_installed = fs::exists(pref_path / "ux0" / "app" / title_id / "eboot.bin");
    const bool ok = install_pkg_file(pkg_path, *emuenv, zrif);
    if (!ok) {
        lr_log(RETRO_LOG_ERROR, "Could not install %s. A game's PKG needs its license: put the zRIF in %s.zrif, or work.bin / %s.rif, next to it.\n",
            pkg_path.generic_string().c_str(), fs_utils::path_to_utf8(pkg_path.stem()).c_str(), fs_utils::path_to_utf8(pkg_path.stem()).c_str());
        // The reason is in the message install_pkg_file gave; without a license it is that
        if (zrif.empty())
            lr_msg("PKG install failed! A game needs its license (zRIF or work.bin) next to the PKG - see log", 600);
        return result;
    }

    fs::create_directories(marker.parent_path());
    fs::ofstream(marker).put('\n');

    result.title_id = emuenv->app_info.app_title_id;
    result.title = emuenv->app_info.app_title;
    result.category = emuenv->app_info.app_category;
    result.content_id = emuenv->app_info.app_content_id;

    // An update or DLC installed by loading its own PKG: noted, so that the
    // game's option for it is on at the game's next start (plan_content)
    {
        const bool is_update = result.category.find("gp") != std::string::npos;
        const bool is_dlc = result.category.find("ac") != std::string::npos;
        fs::path note;
        if (is_update)
            note = manual_update_note(pref_path, result.title_id);
        else if (is_dlc && result.content_id.size() > 20)
            note = manual_dlc_note(pref_path, result.title_id, result.content_id.substr(20));
        if (!note.empty())
            fs::ofstream(note).put('\n');
        mark_forced_install(pref_path, result.title_id, result.category, result.content_id, pkg_path);
    }

    // An update is installed in ux0/patch/<title id> and laid over the game's
    // files when the game starts, installed or run from its PKG; the note says
    // which install it was, for when it goes
    if (result.category.find("gp") != std::string::npos) {
        fs::ofstream(patch_marker_note(pref_path, result.title_id)) << marker.filename().string() << '\n';
        if (!game_installed) {
            lr_log(RETRO_LOG_INFO, "Update %s installed in ux0/patch/%s, laid over the game when it starts\n",
                result.title.c_str(), result.title_id.c_str());
            lr_msg("Update installed. It is applied when the game is started.", 600);
            return result;
        }
    }

    // An update or DLC on its own does not start; the game it is for does,
    // if that is installed already
    if (!fs::exists(pref_path / "ux0" / "app" / result.title_id / "eboot.bin")) {
        lr_log(RETRO_LOG_ERROR, "Installed %s, but the game %s is not installed.\n", result.title.c_str(), result.title_id.c_str());
        lr_msg("Installed. Start the game's own PKG or VPK to play.", 600);
        return result;
    }
    lr_log(RETRO_LOG_INFO, "Installed %s [%s] from PKG\n", result.title.c_str(), result.title_id.c_str());
    apply_content(plan, title_id, zrif, pref_path, sys_lang, false);
    result.success = true;
    return result;
}

// A game folder (or its eboot.bin): its Content options as a PKG's, and with Run Without
// Installing or Persistent Cache read where it lies, as a PKG or archive is (sco8487). The
// folder of an installed game (in ux0) runs as it is; Install copies the folder in.
static GameInstallResult handle_folder_content(const fs::path &game_path, const fs::path &pref_path, int sys_lang, bool run_pkg) {
    const fs::path content_dir = resolve_game_folder(game_path);
    lazy_pkg::PkgInfo info;
    if (content_dir.empty() || !lazy_pkg::pkg_info(content_dir, info) || info.category.find("gd") == std::string::npos)
        return handle_folder_game(game_path, pref_path, sys_lang);
    const std::string ux0 = (pref_path / "ux0").lexically_normal().generic_string();
    if (content_dir.lexically_normal().generic_string().rfind(ux0, 0) == 0)
        return handle_folder_game(game_path, pref_path, sys_lang);

    const fs::path app_path = pref_path / "ux0" / "app" / info.title_id;
    const fs::path work_bin = content_dir / "sce_sys" / "package" / "work.bin";
    const bool encrypted = fs::is_directory(content_dir / "sce_pfs");
    if (encrypted && !fs::exists(work_bin))
        return handle_folder_game(game_path, pref_path, sys_lang); // which says the license is missing

    const ContentPlan plan = plan_content(content_dir, info.title_id, pref_path, run_pkg);
    if (plan.reinstall_game)
        fs::remove_all(app_path);
    const std::string zrif = encrypted ? license_to_zrif(work_bin, pref_path) : std::string();

    if (run_pkg && !fs::exists(app_path / "eboot.bin")) {
        std::string error;
        lr_msg("Preparing the game...", 300);
        mark_lazy_run(pref_path, info.title_id);
        if (lazy_pkg::mount_folder(content_dir, app_path, zrif, error)) {
            write_license(pref_path, info.title_id, info.content_id, zrif);
            if (!apply_content(plan, info.title_id, zrif, pref_path, sys_lang, true)) {
                lazy_pkg::unmount();
                fs::remove(lazy_marker(pref_path, info.title_id));
                return GameInstallResult{};
            }
            GameInstallResult result;
            result.success = true;
            result.title_id = info.title_id;
            result.title = info.title;
            result.category = info.category;
            result.content_id = info.content_id;
            return result;
        }
        fs::remove(lazy_marker(pref_path, info.title_id));
        if (error.rfind(lazy_pkg::NO_ROOM, 0) == 0) {
            // No room for the game run without installing: not started, as an install that does not fit
            lr_log(RETRO_LOG_ERROR, "%s: %s\n", content_dir.generic_string().c_str(), error.c_str());
            lr_msg(fmt::format("Not started: {}", error).c_str(), 600);
            return GameInstallResult{};
        }
        lr_log(RETRO_LOG_WARN, "Folder: cannot run %s where it lies (%s), installing it instead\n",
            content_dir.generic_string().c_str(), error.c_str());
    }

    GameInstallResult result = handle_folder_game(game_path, pref_path, sys_lang);
    if (result.success)
        apply_content(plan, info.title_id, zrif, pref_path, sys_lang, false);
    return result;
}

static GameInstallResult install_or_open(const fs::path &game_path, const fs::path &pref_path, int sys_lang, bool run_pkg) {
    GameInstallResult result;

    lr_log(RETRO_LOG_INFO, "=== Checking game installation ===\n");
    lr_log(RETRO_LOG_INFO, "Game path: %s\n", game_path.generic_string().c_str());
    lr_log(RETRO_LOG_INFO, "Pref path: %s\n", pref_path.generic_string().c_str());

    // Validate game path exists
    bool game_is_directory = false;
    if (!content_stat(game_path, &game_is_directory, nullptr)) {
        lr_log(RETRO_LOG_ERROR, "Game path does not exist: %s\n", game_path.generic_string().c_str());
        lr_msg("Game path not found!", 300);
        return result;
    }

    // If it's a directory, handle as extracted/NoNpDrm game folder. A folder
    // behind a URI (SAF, Samba) cannot be walked by the installer, which
    // copies with the OS; an archive or PKG there is read through the VFS.
    // An eboot.bin there stands for its folder, so it is turned away too: it
    // went on to the folder and only found the game's files missing
    // (sco8487, Samba on Android).
    const bool eboot = !game_is_directory && game_path.filename() == "eboot.bin";
    if ((game_is_directory || eboot) && lr_vfs_is_uri(game_path.string())) {
        lr_log(RETRO_LOG_ERROR, "A game folder through the frontend's VFS is not supported: %s\n", game_path.generic_string().c_str());
        lr_msg("A game folder opened through RetroArch's file access (Android's file picker, Samba) is not supported; load the .vpk, .zip or .pkg", 400);
        return result;
    }
    if (game_is_directory)
        return handle_folder_content(game_path, pref_path, sys_lang, run_pkg);

    // Validate extension for archive files
    const auto extension = string_utils::tolower(game_path.extension().string());
    lr_log(RETRO_LOG_DEBUG, "Game file extension: %s\n", extension.c_str());
    if (extension == ".pkg")
        return handle_pkg_game(game_path, pref_path, sys_lang, run_pkg);
    if (extension != ".vpk" && extension != ".zip") {
        // Maybe it's an eboot.bin directly - check parent folder
        if (game_path.filename() == "eboot.bin") {
            lr_log(RETRO_LOG_INFO, "eboot.bin provided directly, using parent folder\n");
            return handle_folder_content(game_path.parent_path(), pref_path, sys_lang, run_pkg);
        }
        lr_log(RETRO_LOG_ERROR, "Unsupported game format: %s (expected .vpk, .zip, .pkg, or folder)\n", extension.c_str());
        lr_msg("Unsupported format! Use .vpk, .zip, .pkg, or a game directory", 300);
        return result;
    }

    // Open the archive
    lr_log(RETRO_LOG_DEBUG, "Opening archive: %s\n", game_path.generic_string().c_str());
    FILE *fp = FOPEN(game_path.c_str(), "rb");
    if (!fp) {
        lr_log(RETRO_LOG_ERROR, "Failed to open game archive: %s\n", game_path.generic_string().c_str());
        lr_msg("Failed to open game file!", 300);
        return result;
    }

    ZipPtr zip(new mz_zip_archive);
    std::memset(zip.get(), 0, sizeof(mz_zip_archive));

    if (!mz_zip_reader_init_cfile(zip.get(), fp, 0, 0)) {
        lr_log(RETRO_LOG_ERROR, "Failed to read archive: %s (error: %s)\n",
            game_path.generic_string().c_str(),
            mz_zip_get_error_string(mz_zip_get_last_error(zip.get())));
        fclose(fp);
        lr_msg("Failed to read game archive!", 300);
        return result;
    }

    // Find content paths in the archive
    const auto content_paths = find_archive_content_paths(zip);
    if (content_paths.empty()) {
        lr_log(RETRO_LOG_ERROR, "No valid game content found in archive\n");
        lr_log(RETRO_LOG_ERROR, "Archive must contain sce_sys/param.sfo\n");
        fclose(fp);
        lr_msg("No valid game content in archive!", 300);
        return result;
    }

    // Find the main game content (category "gd" = game data)
    sfo::SfoAppInfo app_info;
    std::string game_content_path;
    bool found_game = false;

    for (const auto &cpath : content_paths) {
        sfo::SfoAppInfo info;
        if (read_sfo_from_archive(zip, cpath, info, sys_lang)) {
            lr_log(RETRO_LOG_INFO, "Content found: '%s' [%s] category=%s\n",
                info.app_title.c_str(), info.app_title_id.c_str(), info.app_category.c_str());

            // Prefer game data ("gd") content
            if (info.app_category.find("gd") != std::string::npos) {
                app_info = info;
                game_content_path = cpath;
                found_game = true;
                lr_log(RETRO_LOG_DEBUG, "Selected as primary game content\n");
            } else if (!found_game) {
                // Fall back to first content if no "gd" found
                app_info = info;
                game_content_path = cpath;
            }
        }
    }

    if (app_info.app_title_id.empty()) {
        lr_log(RETRO_LOG_ERROR, "Could not determine title_id from archive\n");
        fclose(fp);
        lr_msg("Could not read game info from archive!", 300);
        return result;
    }

    result.title_id = app_info.app_title_id;
    result.title = app_info.app_title;
    result.category = app_info.app_category;
    result.content_id = app_info.app_content_id;

    lr_log(RETRO_LOG_INFO, "Game: '%s' [%s] (category: %s, content_id: %s)\n",
        result.title.c_str(), result.title_id.c_str(), result.category.c_str(), result.content_id.c_str());

    const auto app_path = pref_path / "ux0" / "app" / result.title_id;

    // Run without installing (Run Mode), as a PKG is: the game's files read
    // out of the archive as it goes, decrypted on the way for a NoNpDrm one,
    // and nothing of it kept in ux0/app once it is closed. An update or DLC in
    // the archive, and a game installed already, go the installed way below.
    // Encrypted (a NoNpDrm dump) without the license it is decrypted with: it cannot run
    // (an update needs none of its own: it is decrypted with its game's)
    const std::string archive_license = archive_zrif(zip, game_content_path, pref_path);
    if (archive_license.empty() && app_info.app_category.find("gp") == std::string::npos) {
        const mz_uint count = mz_zip_reader_get_num_files(zip.get());
        for (mz_uint i = 0; i < count; i++) {
            mz_zip_archive_file_stat st;
            if (mz_zip_reader_file_stat(zip.get(), i, &st)
                && std::string_view(st.m_filename).starts_with(game_content_path + "sce_pfs/")) {
                lr_log(RETRO_LOG_ERROR, "%s is encrypted and its license, sce_sys/package/work.bin, is missing\n",
                    game_path.generic_string().c_str());
                lr_msg("This game is encrypted and its license (sce_sys/package/work.bin) is missing", 600);
                fclose(fp);
                return result;
            }
        }
    }
    // The game's updates and DLC beside it (PKG, VPK or ZIP), as its Content options say
    const bool is_game = app_info.app_category.find("gd") != std::string::npos;
    ContentPlan plan;
    if (is_game) {
        plan = plan_content(game_path, result.title_id, pref_path, run_pkg);
        if (plan.reinstall_game)
            fs::remove_all(app_path);
    }
    if (run_pkg && is_game && !fs::exists(app_path / "eboot.bin")) {
        const std::string &zrif = archive_license;
        std::string error;
        lr_msg("Preparing the game...", 300);
        mark_lazy_run(pref_path, result.title_id);
        if (lazy_pkg::mount_archive(game_path, game_content_path, app_path, zrif, error)) {
            write_license(pref_path, result.title_id, result.content_id, zrif);
            fclose(fp);
            if (!apply_content(plan, result.title_id, zrif, pref_path, sys_lang, true)) {
                lazy_pkg::unmount();
                fs::remove(lazy_marker(pref_path, result.title_id));
                return GameInstallResult{};
            }
            result.success = true;
            return result;
        }
        fs::remove(lazy_marker(pref_path, result.title_id));
        if (error.rfind(lazy_pkg::NO_ROOM, 0) == 0) {
            // No room for the game run without installing: not started, as an install that does not fit
            lr_log(RETRO_LOG_ERROR, "%s: %s\n", game_path.generic_string().c_str(), error.c_str());
            lr_msg(fmt::format("Not started: {}", error).c_str(), 600);
            fclose(fp);
            return GameInstallResult{};
        }
        lr_log(RETRO_LOG_WARN, "Archive: cannot run %s without installing it (%s), installing it instead\n",
            game_path.generic_string().c_str(), error.c_str());
    }

    // Determine output path based on category
    fs::path output_path = pref_path / "ux0";
    if (app_info.app_category.find("gp") != std::string::npos) {
        output_path /= fs::path("patch") / result.title_id;
    } else if (app_info.app_category == "ac") {
        if (!app_info.app_content_id.empty() && app_info.app_content_id.size() > 20) {
            std::string content_id = app_info.app_content_id.substr(20);
            output_path /= fs::path("addcont") / result.title_id / content_id;
        } else {
            output_path /= fs::path("addcont") / result.title_id;
        }
    } else {
        output_path = app_path;
    }

    // Check if this specific content is already installed
    if (fs::exists(output_path) && !fs::is_empty(output_path)) {
        if (app_info.app_category.find("gd") != std::string::npos && !install_still_encrypted(output_path)) {
            // Game: skip if already installed
            lr_log(RETRO_LOG_INFO, "Game '%s' [%s] is already installed.\n",
                result.title.c_str(), result.title_id.c_str());
            fclose(fp);
            apply_content(plan, result.title_id, archive_license, pref_path, sys_lang, false);
            result.success = true;
            return result;
        } else if (app_info.app_category.find("gp") != std::string::npos || app_info.app_category == "ac") {
            // An update or DLC loaded on its own is installed again over what is there, which
            // also mends a broken install (sco8487)
            lr_log(RETRO_LOG_INFO, "'%s' [%s] is installed already: replaced\n", result.title.c_str(), result.title_id.c_str());
            fs::remove_all(output_path);
        }
    }

    // For patches/DLC, verify base game exists
    if (app_info.app_category.find("gp") != std::string::npos
        || app_info.app_category == "ac") {
        if (!fs::exists(app_path) || fs::is_empty(app_path)) {
            lr_log(RETRO_LOG_ERROR, "Base game not installed — install app before patch/DLC\n");
            lr_msg("Install base game first!", 300);
            fclose(fp);
            return result;
        }
    }

    lr_log(RETRO_LOG_INFO, "Installing '%s' [%s] to: %s\n",
        result.title.c_str(), result.title_id.c_str(), output_path.generic_string().c_str());
    {
        char msg[256];
        snprintf(msg, sizeof(msg), "Installing %s [%s]...", result.title.c_str(), result.title_id.c_str());
        lr_msg(msg, 600);
    }

    // Room for what is extracted, or nothing is
    {
        std::uint64_t needed = 0;
        bool encrypted = false;
        const mz_uint count = mz_zip_reader_get_num_files(zip.get());
        for (mz_uint i = 0; i < count; i++) {
            mz_zip_archive_file_stat st;
            if (mz_zip_reader_file_stat(zip.get(), i, &st) && std::string_view(st.m_filename).starts_with(game_content_path)) {
                needed += st.m_uncomp_size;
                encrypted |= std::string_view(st.m_filename).starts_with(game_content_path + "sce_pfs/");
            }
        }
        // An encrypted one twice over for a while: decrypting writes a second copy
        if (encrypted)
            needed *= 2;
        if (!has_room(pref_path, needed)) {
            fclose(fp);
            return result;
        }
    }

    // Extract content
    if (!extract_archive_content(zip, game_content_path, output_path)) {
        lr_log(RETRO_LOG_ERROR, "Failed to extract game content!\n");
        fclose(fp);
        lr_msg("Failed to extract game!", 300);
        return result;
    }

    // Also install any additional content (patches, DLC bundled in same archive)
    for (const auto &cpath : content_paths) {
        if (cpath == game_content_path)
            continue;

        sfo::SfoAppInfo extra_info;
        if (!read_sfo_from_archive(zip, cpath, extra_info, sys_lang))
            continue;

        fs::path extra_output = pref_path / "ux0";
        if (extra_info.app_category.find("gp") != std::string::npos) {
            extra_output /= fs::path("patch") / extra_info.app_title_id;
            lr_log(RETRO_LOG_INFO, "Installing bundled patch: %s\n", extra_info.app_title_id.c_str());
        } else if (extra_info.app_category == "ac") {
            if (!extra_info.app_content_id.empty() && extra_info.app_content_id.size() > 20)
                extra_output /= fs::path("addcont") / extra_info.app_title_id / extra_info.app_content_id.substr(20);
            else
                extra_output /= fs::path("addcont") / extra_info.app_title_id;
            lr_log(RETRO_LOG_INFO, "Installing bundled DLC: %s\n", extra_info.app_title_id.c_str());
        } else {
            continue; // Skip duplicate apps
        }

        extract_archive_content(zip, cpath, extra_output);
    }

    fclose(fp);

    // A NoNpDrm game is decrypted now, as a folder of one is
    if (app_info.app_category.find("gd") != std::string::npos
        && fs::exists(output_path / "sce_sys" / "package" / "work.bin")) {
        std::vector<uint8_t> work_bin_data;
        std::string app_zRIF;
        if (!decrypt_nonpdrm_app(output_path, pref_path, result, work_bin_data, app_zRIF))
            return result;
    } else if (app_info.app_category.find("gd") == std::string::npos && fs::is_directory(output_path / "sce_pfs")
        && !decrypt_nonpdrm_extra(output_path, pref_path, result)) {
        // and so is an update or DLC, which would not work encrypted
        fs::remove_all(output_path);
        return result;
    }
    if (is_game)
        apply_content(plan, result.title_id, archive_license, pref_path, sys_lang, false);

    // An update stays in ux0/patch and is laid over the game when it starts, as one
    // installed from a PKG does; a DLC stays in ux0/addcont. Loaded on its own (not through
    // the game's Content options), it is kept whatever Run Mode says
    mark_forced_install(pref_path, result.title_id, app_info.app_category, app_info.app_content_id, game_path);

    // Verify installation
    if (fs::exists(output_path) && !fs::is_empty(output_path)) {
        lr_log(RETRO_LOG_INFO, "'%s' [%s] installed successfully!\n",
            result.title.c_str(), result.title_id.c_str());
        {
            char msg[256];
            snprintf(msg, sizeof(msg), "%s installed!", result.title.c_str());
            lr_msg(msg, 300);
        }
        result.success = true;
    } else {
        lr_log(RETRO_LOG_ERROR, "Installation verification failed at: %s\n",
            output_path.generic_string().c_str());
        lr_msg("Installation failed!", 300);
    }

    return result;
}

GameInstallResult ensure_game_installed(const fs::path &game_path, const fs::path &pref_path, int sys_lang, bool run_pkg) {
    GameInstallResult result = install_or_open(game_path, pref_path, sys_lang, run_pkg);
    // An update or DLC loaded on its own starts its installed game, which then
    // gets its Content options like a game loaded itself (Shoegzer): its
    // update and DLC as they are installed, and Current Title
    boost::system::error_code ec;
    const fs::path app = pref_path / "ux0" / "app" / result.title_id;
    if (result.success && !result.title_id.empty() && s_loaded_content.title_id.empty()
        && fs::exists(app / "eboot.bin", ec)) {
        lr_log(RETRO_LOG_INFO, "%s: Content options from the installed game\n", result.title_id.c_str());
        plan_content(app, result.title_id, pref_path, false);
    }
    return result;
}
