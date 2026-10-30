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

#pragma once

#include <functional>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <util/fs.h>

// ─── Firmware status ────────────────────────────────────────────────────────

struct FirmwareStatus {
    bool preinst_installed = false; // pd0/ exists and non-empty
    bool firmware_installed = false; // vs0/ exists and non-empty
    bool font_installed = false;     // sa0/ exists and non-empty

    bool all_installed() const { return preinst_installed && firmware_installed && font_installed; }
    bool any_installed() const { return preinst_installed || firmware_installed || font_installed; }
};

/// Check which firmware components are installed under pref_path.
FirmwareStatus check_firmware_status(const fs::path &pref_path);

// ─── Firmware installation ──────────────────────────────────────────────────

/// At a game's load: each firmware part that is not installed is installed
/// from its .pup in system_dir, if there is one; whether the system firmware
/// is then installed. A part still missing is logged with where to get it,
/// and said on screen.
bool check_firmware_installed(const fs::path &pref_path, const fs::path &system_dir);

/// A .pup loaded as content: installed, whichever of the three packages it is
/// (upstream's install_pup tells them apart by their content, as they all
/// download under one name), and what is still missing said on screen. False
/// if it could not be installed.
bool install_firmware_content(const fs::path &pref_path, const fs::path &pup_path);

// ─── Game installation ──────────────────────────────────────────────────────

// An option of the loaded game's own, beside the core's: which of its updates
// and DLC - the PKGs, VPK/ZIPs and folders found for it, and what is installed - are used
struct ContentOption {
    std::string key;
    std::string label;
    std::string info;
    std::vector<std::pair<std::string, std::string>> values; // value, its label
    std::string default_value;
    // Not empty: the frontend's value is set to this one first
    std::string set_value;
    // The core options category it is listed under
    std::string category = "install";
};

// Declares them to the frontend and answers with each key's current value.
// Set by the core's frontend glue before a game is loaded.
using ContentOptionsHandler = std::function<std::map<std::string, std::string>(const std::vector<ContentOption> &)>;
void set_content_options_handler(ContentOptionsHandler handler);
// A key's current value at the frontend (empty when it has none), and a value
// set there; for what is asked after the options were declared
void set_content_option_accessors(std::function<std::string(const std::string &)> get,
    std::function<void(const std::string &, const std::string &)> set);
// Whether a Content option (game, update, DLC) changed since it was last asked; each takes
// effect when the content is started again. removal_changed: whether a Remove Content option
// did, which takes effect when the content is closed or reset (i30817)
bool content_options_changed(bool *removal_changed = nullptr);
// Called when the content is closed, the game stopped and what was laid out
// for a run without installing removed: deletes what was turned off meanwhile,
// and measures the title that ran again for Remove Content's list
void content_closed();
// Remove Content (i30817): the titles turned ON whose data a crash or a killed
// frontend left in place, or deleted only in part, are deleted now; called
// before the content is started
void finish_pending_removals(const fs::path &pref_path);
// The title just started, in Remove Content's list (titles.tsv): its name, how
// it runs (install, cache or run) and, when it is new to the list or runs
// another way, the size of its data
void record_started_title(const fs::path &pref_path, const std::string &title_id, const std::string &name, const std::string &mode);
// The running title's save data folder and trophy sets (NP communication
// IDs), kept for Remove Content's Delete user saves and trophies, which may
// remove the title when it is no longer laid out
void record_title_user_data(const fs::path &pref_path, const std::string &title_id, const std::string &savedata, const std::vector<std::string> &trophy_ids);

// What runs without installing left laid out in ux0 when they were not closed (the
// frontend killed): every game, DLC and update layout whose marker under
// ux0/libretro_pkg is still there. Called when content is loaded, before anything is
// laid out; an installed game never has a marker.
void remove_dead_runs(const fs::path &pref_path);

struct GameInstallResult {
    bool success = false;
    std::string title_id;
    std::string title;
    std::string category;
    std::string content_id;
};

/// The loaded content made ready to start: a PKG, VPK/ZIP, folder or eboot.bin
/// (its folder). A game installed already runs installed. Otherwise, with
/// run_pkg (Run Mode: Run Without Installing or Persistent Cache), it is
/// laid out to be read where it lies (lazy_pkg); else it is installed into
/// ux0. Its updates and DLC are declared in Content and used as chosen there.
/// An update or DLC loaded on its own is installed.
GameInstallResult ensure_game_installed(const fs::path &game_path, const fs::path &pref_path, int sys_lang, bool run_pkg = false);
