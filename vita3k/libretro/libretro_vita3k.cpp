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

#include "libretro_state.h"
#include "libretro_core_options.h"
#include "libretro_input.h"
#include "libretro_installer.h"
#include "libretro_vfs.h"
#include "libretro_lazy_pkg.h"
#include "libretro_log.h"
#include "libretro_game_loader.h"
#include "libretro_accounts.h"
#include "libretro_input_state.h"

#include <app/functions.h>
#include <camera/camera.h>
#include <audio/impl/libretro_audio.h>
#include <config/functions.h>
#include <config/state.h>
#include <config/version.h>
#include <fmt/format.h>
#include <display/functions.h>
#include <display/state.h>
#include <emuenv/state.h>
#include <gxm/functions.h>
#include <gxm/state.h>
#include <io/state.h>
#include <io/vfs.h>
#include <overlay/display_manager.h>
#include <overlay/shader_compile_notice.h>
#include <overlay/shader_precompile_progress.h>
#include <kernel/state.h>
#include <mem/functions.h>
#include <renderer/frame_host.h>
#include <renderer/functions.h>
#include <renderer/gl/state.h>
#include <renderer/shaders.h>
#include <renderer/state.h>
#include <renderer/vulkan/state.h>
#include <vkutil/objects.h>
#include <vkutil/vkutil.h>
#include <util/fs.h>
#include <util/log.h>
#include <util/string_utils.h>
#include <np/state.h>
#include <np/trophy/collection.h>

#ifndef _WIN32
#include <signal.h>
#endif

#include <glad/glad.h>

#include <SDL3/SDL_hints.h>

#include <miniz.h>

#include <algorithm>
#include <string_view>
#include <limits>
#include <array>
#include <atomic>
#include <thread>
#include <cstdarg>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <mutex>

#ifdef _WIN32
#include <Windows.h>
#endif

LibretroState libretro;

LibretroInputState &libretro_input_state() {
    return libretro.input;
}

// Forward declarations for core options functions
static void read_core_option(const char *key, const char *default_value, std::function<void(const char *)> apply_func);
static void apply_config_changes();
static void read_core_options();
static void stop_render_thread();
static void request_guest_shutdown(EmuEnvState &emuenv, const char *reason);
static bool perform_core_reset();

static void lr_message(const std::string &msg, unsigned frames = 240) {
    if (!libretro.environ_cb)
        return;
    retro_message m{};
    m.msg = msg.c_str();
    m.frames = frames;
    libretro.environ_cb(RETRO_ENVIRONMENT_SET_MESSAGE, &m);
}

void lr_log(enum retro_log_level level, const char *fmt, ...);

extern const unsigned char g_vita3k_bundled_zip[];
extern const std::size_t g_vita3k_bundled_zip_size;
extern const char g_vita3k_bundled_version[];

// The emulator's data, built-in shaders and dialog icons are compiled into the
// core (embed_system_files.cmake) and unpacked into system/vita3k, where
// static_assets points: only when what is there is not this build's, as
// bundled_files.txt says, so a start normally writes nothing. The folders are
// emptied first, so a file the new build no longer has does not linger.
static void install_bundled_files(const fs::path &pref_path) {
    const fs::path version_file = pref_path / "bundled_files.txt";
    {
        std::ifstream in(version_file.string());
        std::string had;
        std::getline(in, had);
        if (had == g_vita3k_bundled_version)
            return;
    }

    mz_zip_archive zip{};
    if (!mz_zip_reader_init_mem(&zip, g_vita3k_bundled_zip, g_vita3k_bundled_zip_size, 0)) {
        lr_log(RETRO_LOG_ERROR, "The files compiled into the core could not be opened\n");
        return;
    }
    std::error_code ec;
    for (const char *dir : { "data", "shaders-builtin", "icons" })
        fs::remove_all(pref_path / dir, ec);

    unsigned written = 0;
    bool ok = true;
    const mz_uint count = mz_zip_reader_get_num_files(&zip);
    for (mz_uint i = 0; i < count; i++) {
        mz_zip_archive_file_stat st;
        if (!mz_zip_reader_file_stat(&zip, i, &st))
            continue;
        const std::string name = st.m_filename;
        if (name.empty() || name.find("..") != std::string::npos || name.front() == '/')
            continue;
        const fs::path path = pref_path / fs_utils::utf8_to_path(name);
        if (mz_zip_reader_is_file_a_directory(&zip, i)) {
            fs::create_directories(path, ec);
            continue;
        }
        fs::create_directories(path.parent_path(), ec);
        size_t size = 0;
        void *data = mz_zip_reader_extract_to_heap(&zip, i, &size, 0);
        if (!data) {
            ok = false;
            continue;
        }
        std::ofstream out(path, std::ios::binary | std::ios::trunc);
        out.write(static_cast<const char *>(data), static_cast<std::streamsize>(size));
        mz_free(data);
        if (out)
            written++;
        else
            ok = false;
    }
    mz_zip_reader_end(&zip);

    // Written only when all went in, so that a start cut short tries again
    if (ok) {
        std::ofstream out(version_file.string(), std::ios::trunc);
        out << g_vita3k_bundled_version << "\n";
    }
    lr_log(RETRO_LOG_INFO, "Unpacked the %u files compiled into the core (data, built-in shaders, icons) into %s\n",
        written, pref_path.string().c_str());
}

// Whether the system folder's file system can hold files with holes
// (lazy_pkg::holes_supported). Without, Run Mode offers Install only:
// Run Without Installing and Persistent Cache would take as much space as an
// install and save nothing (sco8487).
static bool s_holes_supported = true;

static const retro_core_option_v2_definition install_only_preload = [] {
    retro_core_option_v2_definition def{};
    for (const retro_core_option_v2_definition *d = option_defs_us; d->key; d++) {
        if (std::string_view(d->key) == "vita3k_pkg_mode")
            def = *d;
    }
    def.info = "Installed: the title, its update and downloadable content are installed to the emulated Vita's memory card. Direct and Direct with Cache are not offered: the system directory is on a file system without sparse files (such as FAT32 or exFAT), where they would take as much space as an install.";
    def.values[0] = { "install", "Installed" };
    def.values[1] = { nullptr, nullptr };
    def.default_value = "install";
    return def;
}();

// The loaded game's own options (its updates and DLC, libretro_installer.cpp)
// and the accounts' (libretro_accounts.cpp), declared after the core's: the
// frontend is given the whole list again whenever either changes, and the
// texts are kept here for as long as it holds on to them.
static std::vector<ContentOption> s_kept_content_options;
static std::vector<ContentOption> s_kept_account_options;
static std::vector<ContentOption> s_kept_module_options;
static std::vector<ContentOption> s_kept_network_options;
static std::vector<ContentOption> s_kept_trophy_options;

static bool show_trophy_entries();

static std::map<std::string, std::string> declare_extra_options(const std::vector<ContentOption> &options, std::vector<ContentOption> &kept_for) {
    static std::vector<retro_core_option_v2_definition> definitions;

    std::map<std::string, std::string> values;
    if (!libretro.environ_cb)
        return values;

    kept_for = options;
    std::vector<const ContentOption *> kept;
    for (const ContentOption &option : s_kept_content_options)
        kept.push_back(&option);
    for (const ContentOption &option : s_kept_account_options)
        kept.push_back(&option);
    for (const ContentOption &option : s_kept_module_options)
        kept.push_back(&option);
    for (const ContentOption &option : s_kept_network_options)
        kept.push_back(&option);
    for (const ContentOption &option : s_kept_trophy_options)
        kept.push_back(&option);
    definitions.clear();
    for (const retro_core_option_v2_definition *def = option_defs_us; def->key; def++)
        definitions.push_back(!s_holes_supported && std::string_view(def->key) == "vita3k_pkg_mode" ? install_only_preload : *def);
    for (const ContentOption *kept_option : kept) {
        const ContentOption &option = *kept_option;
        retro_core_option_v2_definition def{};
        def.key = option.key.c_str();
        def.desc = option.label.c_str();
        def.info = option.info.c_str();
        def.category_key = option.category.c_str();
        size_t count = 0;
        for (const auto &value : option.values) {
            if (count >= RETRO_NUM_CORE_OPTION_VALUES_MAX - 1)
                break;
            def.values[count].value = value.first.c_str();
            def.values[count].label = value.second.c_str();
            count++;
        }
        def.default_value = option.default_value.c_str();
        definitions.push_back(def);
    }
    // RetroArch lists the categories in the order their first options come:
    // Remove Content's go right after the first run of Content's, so that
    // it follows Content rather than every category of the core's own
    // (sco8487)
    {
        const auto in = [](const retro_core_option_v2_definition &d, std::string_view category) {
            return d.category_key && category == d.category_key;
        };
        std::vector<retro_core_option_v2_definition> removals;
        for (const auto &d : definitions)
            if (in(d, "remove"))
                removals.push_back(d);
        definitions.erase(std::remove_if(definitions.begin(), definitions.end(),
                              [&](const auto &d) { return in(d, "remove"); }),
            definitions.end());
        auto at = std::find_if(definitions.begin(), definitions.end(),
            [&](const auto &d) { return in(d, "install"); });
        while (at != definitions.end() && in(*at, "install"))
            ++at;
        definitions.insert(at, removals.begin(), removals.end());
    }
    definitions.push_back(retro_core_option_v2_definition{});

    // The translations are matched by key, so the core's own options keep
    // theirs; the game's have none
    options_us.definitions = definitions.data();
    bool categories_supported = false;
    libretro_set_core_options(libretro.environ_cb, &categories_supported);
    // Declaring shows every option again
    show_trophy_entries();

    for (const ContentOption &option : kept_for) {
        if (!option.set_value.empty()) {
            retro_variable set{};
            set.key = option.key.c_str();
            set.value = option.set_value.c_str();
            libretro.environ_cb(RETRO_ENVIRONMENT_SET_VARIABLE, &set);
        }
        retro_variable variable{};
        variable.key = option.key.c_str();
        if (libretro.environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &variable) && variable.value)
            values[option.key] = variable.value;
    }
    return values;
}

static std::map<std::string, std::string> declare_content_options(const std::vector<ContentOption> &options) {
    return declare_extra_options(options, s_kept_content_options);
}

static std::map<std::string, std::string> declare_account_options(const std::vector<ContentOption> &options) {
    return declare_extra_options(options, s_kept_account_options);
}

// The firmware's modules (vs0/sys/external/<name>.suprx) under Modules, each
// on or off: the ones loaded from it when Modules Mode is not Automatic, as
// upstream's per-game module list. Saved per game with RetroArch's game options.
static std::vector<std::string> s_module_names;
static constexpr const char *MODULE_KEY_PREFIX = "vita3k_module_";

// The address adhoc networking uses, one of the host's (by its index among
// them, as upstream's setting), its subnet mask shown beside it
static void declare_adhoc_address_option() {
    ContentOption option;
    option.key = "vita3k_adhoc_addr";
    option.category = "network";
    option.label = "Adhoc Address";
    option.info = "Select the IP address to be used in adhoc networking, among the host's network interfaces; its subnet mask is shown beside it. Applies the next time the game is started.";
    const auto addresses = app::get_available_adhoc_address_options();
    for (size_t i = 0; i < addresses.size() && i < RETRO_NUM_CORE_OPTION_VALUES_MAX - 1; i++)
        option.values.emplace_back(std::to_string(i), addresses[i].label + ", subnet mask " + addresses[i].subnet_mask);
    if (option.values.empty())
        option.values.emplace_back("0", "No network interface");
    option.default_value = "0";
    declare_extra_options({ option }, s_kept_network_options);
}

// The frontend's camera, for a Vita camera set to Host Camera. Asked for only
// then: it can be asked for only while the content is loaded, and asking turns
// on the frontend's camera driver. RetroArch hands frames in from its main
// loop, between retro_run calls.
static const char *get_core_option_value(const char *key, const char *fallback);
static retro_camera_callback s_host_camera{};

static void RETRO_CALLCONV host_camera_frame(const uint32_t *buffer, unsigned width, unsigned height, size_t pitch) {
    push_host_camera_frame(buffer, width, height, pitch);
}

static void request_host_camera() {
    if (std::string_view(get_core_option_value("vita3k_front_camera", "host")) != "host"
        && std::string_view(get_core_option_value("vita3k_back_camera", "host")) != "host") {
        set_host_camera_control(nullptr, nullptr);
        return;
    }
    s_host_camera = {};
    s_host_camera.caps = 1 << RETRO_CAMERA_BUFFER_RAW_FRAMEBUFFER;
    s_host_camera.width = 640;
    s_host_camera.height = 480;
    s_host_camera.frame_raw_framebuffer = host_camera_frame;
    if (!libretro.environ_cb(RETRO_ENVIRONMENT_GET_CAMERA_INTERFACE, &s_host_camera) || !s_host_camera.start) {
        lr_log(RETRO_LOG_INFO, "The frontend has no camera to give; Host Camera falls back to Image or Solid Color\n");
        set_host_camera_control(nullptr, nullptr);
        return;
    }
    set_host_camera_control([] { return s_host_camera.start && s_host_camera.start(); },
        [] {
            if (s_host_camera.stop)
                s_host_camera.stop();
        });
}

// Trophies (Shoegzer): the running title's trophy list under Trophies, one
// entry per trophy - grade and name, earned or not and when, its description
// and ID - after a Progress entry. RetroArch's options are text, so there are
// no icons. The list is declared once in each Sort Method order; the Display
// options and Sort Method only change which entries are visible, so they apply
// in the menu right away. Empty rows above and below Progress set it apart.
// Declared again when the title's trophy data changes.
static const char *const TROPHY_GRADES[] = { "", "Platinum", "Gold", "Silver", "Bronze" };
static const char *const TROPHY_SORTS[] = { "type", "name", "date" };

struct TrophyEntry {
    std::string key, sort;
    bool earned = false;
    int grade = 0;
    // 0: always, 2: only with Display: Hidden on (a hidden trophy not earned)
    int hidden_variant = 0;
};
static std::vector<TrophyEntry> s_trophy_entries;

static std::vector<std::string> title_trophy_ids(const EmuEnvState &emuenv) {
    std::vector<std::string> ids;
    std::error_code ec;
    const fs::path dir = emuenv.vita_fs_path / "ux0" / "app" / emuenv.io.title_id / "sce_sys" / "trophy";
    for (fs::directory_iterator it(dir, ec), end; !ec && it != end; it.increment(ec))
        ids.push_back(it->path().filename().string());
    return ids;
}

static bool show_trophy_entries() {
    if (!libretro.environ_cb || s_trophy_entries.empty())
        return false;
    const std::string_view show = get_core_option_value("vita3k_trophy_show", "all");
    const std::string_view grade = get_core_option_value("vita3k_trophy_grade", "all");
    const std::string_view sort = get_core_option_value("vita3k_trophy_sort", "type");
    const bool show_hidden = std::string_view(get_core_option_value("vita3k_trophy_hidden", "disabled")) == "enabled";
    for (const TrophyEntry &entry : s_trophy_entries) {
        bool visible = entry.sort == sort
            && !(show == "earned" && !entry.earned) && !(show == "unearned" && entry.earned)
            && (grade == "all" || string_utils::tolower(TROPHY_GRADES[entry.grade]) == grade)
            && !(entry.hidden_variant == 2 && !show_hidden);
        if (entry.sort.empty())
            visible = true;
        retro_core_option_display display{ entry.key.c_str(), visible };
        libretro.environ_cb(RETRO_ENVIRONMENT_SET_CORE_OPTIONS_DISPLAY, &display);
    }
    return true;
}

static bool RETRO_CALLCONV update_trophy_display() {
    return show_trophy_entries();
}

static void declare_trophy_options(EmuEnvState &emuenv) {
    np::trophy::CollectionSource source;
    source.io = &emuenv.io;
    source.vita_fs_path = emuenv.vita_fs_path;
    source.user_id = emuenv.io.user_id;
    source.lang = static_cast<uint32_t>(emuenv.cfg.sys_lang);
    const std::vector<std::string> collections = np::trophy::list_collection_ids(source);

    std::vector<ContentOption> options;
    std::vector<TrophyEntry> entries;
    for (const std::string &id : title_trophy_ids(emuenv)) {
        if (std::find(collections.begin(), collections.end(), id) == collections.end())
            continue;
        np::trophy::CollectionSnapshot snapshot;
        if (!np::trophy::load_collection(source, id, snapshot) || snapshot.trophies.empty())
            continue;

        const int total = static_cast<int>(snapshot.trophies.size());
        // Empty rows above and below Progress set it apart from the Display
        // options and from the list (Shoegzer): a space for the label and the
        // value, as RetroArch shows the key or the value's name for an empty
        // one
        const auto add_spacer = [&](const char *where) {
            ContentOption spacer;
            spacer.key = fmt::format("vita3k_trophy_spacer_{}_{}", where, id);
            spacer.category = "trophies";
            spacer.label = " ";
            spacer.values.emplace_back("_", " ");
            spacer.default_value = "_";
            options.push_back(std::move(spacer));
            entries.push_back({ options.back().key, "" });
        };
        add_spacer("above");
        ContentOption progress;
        progress.key = "vita3k_trophy_progress_" + id;
        progress.category = "trophies";
        progress.label = "Progress";
        // The title as Content's Current Title names it (Shoegzer), not by the
        // trophy set's own name and ID
        progress.info = emuenv.current_app_title.empty() ? emuenv.io.title_id
                                                         : fmt::format("{} ({})", emuenv.current_app_title, emuenv.io.title_id);
        const std::string count = fmt::format("{}/{} ({}%)", snapshot.unlocked, total, snapshot.unlocked * 100 / total);
        progress.values.emplace_back(count, count);
        progress.default_value = count;
        progress.set_value = count;
        options.push_back(std::move(progress));
        entries.push_back({ options.back().key, "" });
        add_spacer("below");

        for (const char *sort : TROPHY_SORTS) {
            std::vector<const np::trophy::TrophyRecord *> sorted;
            for (const np::trophy::TrophyRecord &trophy : snapshot.trophies)
                sorted.push_back(&trophy);
            // Type: Platinum to Bronze; Name: alphabetical; Completion Date:
            // earned first, oldest first, the ones not earned last. Ties by ID.
            std::stable_sort(sorted.begin(), sorted.end(), [&](const np::trophy::TrophyRecord *a, const np::trophy::TrophyRecord *b) {
                if (std::string_view(sort) == "type")
                    return a->grade < b->grade;
                if (std::string_view(sort) == "name")
                    return string_utils::tolower(a->name) < string_utils::tolower(b->name);
                if (a->earned != b->earned)
                    return a->earned;
                return a->earned && a->timestamp < b->timestamp;
            });
            for (const np::trophy::TrophyRecord *record : sorted) {
                const np::trophy::TrophyRecord &trophy = *record;
                const int grade = trophy.grade >= 1 && trophy.grade <= 4 ? trophy.grade : 0;
                const char *grade_name = TROPHY_GRADES[grade];
                std::string state = "Not Earned";
                if (trophy.earned) {
                    state = "Earned";
                    const std::time_t when = static_cast<std::time_t>(trophy.timestamp);
                    std::tm tm{};
#ifdef _WIN32
                    const bool have = when > 0 && localtime_s(&tm, &when) == 0;
#else
                    const bool have = when > 0 && localtime_r(&when, &tm);
#endif
                    if (have)
                        state += fmt::format(" {:04}-{:02}-{:02} {:02}:{:02}", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min);
                }
                // A hidden trophy not earned yet is listed only with Display:
                // Hidden on (Shoegzer); once earned it is not hidden any more
                const int variant = trophy.hidden && !trophy.earned ? 2 : 0;
                ContentOption option;
                option.key = fmt::format("vita3k_trophy_{}_{}_{}", sort, id, trophy.id);
                option.category = "trophies";
                option.label = fmt::format("{}: {}", grade_name, trophy.name);
                option.info = fmt::format("{}{} ID {}.", trophy.detail, trophy.hidden ? " (Hidden.)" : "", trophy.id);
                option.values.emplace_back(state, state);
                option.default_value = state;
                option.set_value = state;
                options.push_back(std::move(option));
                entries.push_back({ options.back().key, sort, trophy.earned, grade, variant });
            }
        }
    }
    s_trophy_entries = std::move(entries);
    declare_extra_options(options, s_kept_trophy_options);
}

// What the list was made from - the title's trophy configuration, written when
// the game opens its trophies, and its progress, written when one is earned;
// checked every few seconds of play
static void refresh_trophy_options(EmuEnvState &emuenv) {
    static std::string made_from;
    if (emuenv.io.title_id.empty())
        return;
    std::string now = emuenv.io.title_id;
    std::error_code ec;
    const fs::path trophy = emuenv.vita_fs_path / "ux0" / "user" / emuenv.io.user_id / "trophy";
    for (const std::string &id : title_trophy_ids(emuenv)) {
        now += " " + id + (fs::exists(trophy / "conf" / id / "TROP.SFM", ec) ? "+" : "-");
        const auto stamp = fs_utils::to_time_t(fs::last_write_time(trophy / "data" / id / "TROPUSR.DAT", ec));
        now += ec ? std::string("-") : std::to_string(static_cast<long long>(stamp));
        ec.clear();
    }
    if (now == made_from)
        return;
    made_from = now;
    record_title_user_data(emuenv.vita_fs_path, emuenv.io.title_id, emuenv.io.savedata, title_trophy_ids(emuenv));
    declare_trophy_options(emuenv);
}

static void declare_module_options(const fs::path &pref_path) {
    s_module_names.clear();
    std::error_code ec;
    const fs::path external = pref_path / "vs0" / "sys" / "external";
    if (fs::is_directory(external, ec)) {
        for (const auto &entry : fs::directory_iterator(external, ec)) {
            if (entry.path().extension() == ".suprx")
                s_module_names.push_back(entry.path().stem().string());
        }
    }
    std::sort(s_module_names.begin(), s_module_names.end());

    std::vector<ContentOption> options;
    for (const std::string &name : s_module_names) {
        ContentOption option;
        option.key = MODULE_KEY_PREFIX + name;
        option.category = "modules";
        option.label = name;
        option.info = "Load vs0:sys/external/" + name + ".suprx from the firmware in place of the core's own implementation, when Modules Mode (in System) is Auto & Manual or Manual. Applies the next time the game is started.";
        option.values = { { "disabled", "OFF" }, { "enabled", "ON" } };
        option.default_value = "disabled";
        options.push_back(std::move(option));
    }
    declare_extra_options(options, s_kept_module_options);
}

static const char *get_core_option_value(const char *key, const char *fallback) {
    if (!libretro.environ_cb)
        return fallback;

    retro_variable variable{};
    variable.key = key;
    if (libretro.environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &variable) && variable.value)
        return variable.value;
    return fallback;
}

static int parse_int_option(const char *value, int fallback) {
    if (!value)
        return fallback;
    char *end = nullptr;
    const long parsed = std::strtol(value, &end, 10);
    if (end == value)
        return fallback;
    return static_cast<int>(parsed);
}

static float parse_float_option(const char *value, float fallback) {
    if (!value)
        return fallback;
    char *end = nullptr;
    const float parsed = std::strtof(value, &end);
    if (end == value)
        return fallback;
    return parsed;
}

static std::string normalize_option_token(const char *value) {
    std::string token = value ? value : "";
    std::transform(token.begin(), token.end(), token.begin(), [](unsigned char c) {
        return static_cast<char>(std::tolower(c));
    });
    return token;
}

static bool parse_enabled_option(const char *value, bool fallback) {
    const std::string token = normalize_option_token(value);
    if (token == "enabled" || token == "enable" || token == "true" || token == "on" || token == "1" || token == "yes")
        return true;
    if (token == "disabled" || token == "disable" || token == "false" || token == "off" || token == "0" || token == "no")
        return false;
    return fallback;
}

static std::string canonical_memory_mapping_option(const char *value) {
    std::string token = normalize_option_token(value);
    std::replace(token.begin(), token.end(), '_', '-');
    std::replace(token.begin(), token.end(), ' ', '-');

    if (token == "doublebuffer")
        token = "double-buffer";
    if (token == "externalhost")
        token = "external-host";
    if (token == "pagetable")
        token = "page-table";
    if (token == "nativebuffer")
        token = "native-buffer";

    if (token != "disabled" && token != "double-buffer" && token != "external-host"
        && token != "page-table" && token != "native-buffer")
        token = "double-buffer";
    return token;
}

static void libretro_log_init() {
    struct retro_log_callback log;
    if (libretro.environ_cb(RETRO_ENVIRONMENT_GET_LOG_INTERFACE, &log))
        libretro.log_cb = log.log;
}

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

static std::atomic<uint64_t> g_lr_trace_seq{ 0 };

#ifdef _WIN32
static PVOID g_lr_vectored_exception_handler_handle = nullptr;
#endif

static void lr_trace(const char *tag, const char *fmt = nullptr, ...) {
    char details[3072] = {};
    if (fmt && fmt[0]) {
        va_list ap;
        va_start(ap, fmt);
        vsnprintf(details, sizeof(details), fmt, ap);
        va_end(ap);
    }

    const uint64_t seq = g_lr_trace_seq.fetch_add(1, std::memory_order_relaxed) + 1;
    const char *safe_tag = tag ? tag : "(null)";

    if (details[0])
        lr_log(RETRO_LOG_INFO, "[TRACE %llu] %s | %s\n", static_cast<unsigned long long>(seq), safe_tag, details);
    else
        lr_log(RETRO_LOG_INFO, "[TRACE %llu] %s\n", static_cast<unsigned long long>(seq), safe_tag);

}

#ifdef _WIN32
static LONG CALLBACK lr_vectored_exception_handler(EXCEPTION_POINTERS *ep) {
    if (!ep || !ep->ExceptionRecord)
        return EXCEPTION_CONTINUE_SEARCH;

    const EXCEPTION_RECORD *record = ep->ExceptionRecord;
    const CONTEXT *ctx = ep->ContextRecord;

    const unsigned long code = static_cast<unsigned long>(record->ExceptionCode);
    const unsigned long flags = static_cast<unsigned long>(record->ExceptionFlags);
    const unsigned long param_count = static_cast<unsigned long>(record->NumberParameters);
    const unsigned long long p0 = (param_count > 0) ? static_cast<unsigned long long>(record->ExceptionInformation[0]) : 0ULL;
    const unsigned long long p1 = (param_count > 1) ? static_cast<unsigned long long>(record->ExceptionInformation[1]) : 0ULL;

#if defined(_M_X64) || defined(__x86_64__)
    const unsigned long long rip = ctx ? static_cast<unsigned long long>(ctx->Rip) : 0ULL;
    const unsigned long long rsp = ctx ? static_cast<unsigned long long>(ctx->Rsp) : 0ULL;
#else
    const unsigned long long rip = ctx ? static_cast<unsigned long long>(ctx->Eip) : 0ULL;
    const unsigned long long rsp = ctx ? static_cast<unsigned long long>(ctx->Esp) : 0ULL;
#endif

    lr_trace("veh.exception",
        "code=0x%08lX flags=0x%08lX addr=%p rip=0x%llX rsp=0x%llX param_count=%lu p0=0x%llX p1=0x%llX",
        code,
        flags,
        record->ExceptionAddress,
        rip,
        rsp,
        param_count,
        p0,
        p1);

    return EXCEPTION_CONTINUE_SEARCH;
}

static void lr_install_vectored_exception_handler() {
    if (g_lr_vectored_exception_handler_handle)
        return;

    g_lr_vectored_exception_handler_handle = AddVectoredExceptionHandler(1, lr_vectored_exception_handler);
    lr_trace("veh.install", "handle=%p", g_lr_vectored_exception_handler_handle);
}

static void lr_remove_vectored_exception_handler() {
    if (!g_lr_vectored_exception_handler_handle)
        return;

    RemoveVectoredExceptionHandler(g_lr_vectored_exception_handler_handle);
    lr_trace("veh.remove", "handle=%p", g_lr_vectored_exception_handler_handle);
    g_lr_vectored_exception_handler_handle = nullptr;
}
#endif

static void libretro_init_paths() {
    const char *sys = nullptr;

    if (libretro.environ_cb(RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY, &sys) && sys)
        libretro.system_dir = std::string(sys) + "/vita3k";
    else
        libretro.system_dir = ".";

}

static struct {
    PFN_vkGetPhysicalDeviceMemoryProperties GetPhysicalDeviceMemoryProperties;
    PFN_vkCreateImage CreateImage;
    PFN_vkDestroyImage DestroyImage;
    PFN_vkGetImageMemoryRequirements GetImageMemoryRequirements;
    PFN_vkAllocateMemory AllocateMemory;
    PFN_vkFreeMemory FreeMemory;
    PFN_vkBindImageMemory BindImageMemory;
    PFN_vkCreateImageView CreateImageView;
    PFN_vkDestroyImageView DestroyImageView;
    PFN_vkCreateCommandPool CreateCommandPool;
    PFN_vkDestroyCommandPool DestroyCommandPool;
    PFN_vkAllocateCommandBuffers AllocateCommandBuffers;
    PFN_vkFreeCommandBuffers FreeCommandBuffers;
    PFN_vkBeginCommandBuffer BeginCommandBuffer;
    PFN_vkEndCommandBuffer EndCommandBuffer;
    PFN_vkResetCommandBuffer ResetCommandBuffer;
    PFN_vkCmdPipelineBarrier CmdPipelineBarrier;
    PFN_vkCmdClearColorImage CmdClearColorImage;
    PFN_vkCmdBlitImage CmdBlitImage;
    PFN_vkDeviceWaitIdle DeviceWaitIdle;
    PFN_vkCreateFence CreateFence;
    PFN_vkDestroyFence DestroyFence;
    PFN_vkWaitForFences WaitForFences;
    PFN_vkResetFences ResetFences;
    PFN_vkQueueSubmit QueueSubmit;
} vkfn = {};

static void libretro_vk_load_functions(const struct retro_hw_render_interface_vulkan *vulkan) {
    auto dpa = vulkan->get_device_proc_addr;
    auto ipa = vulkan->get_instance_proc_addr;
    VkDevice dev = vulkan->device;
    VkInstance inst = vulkan->instance;
#define LOAD_VK_DEV(fn) vkfn.fn = reinterpret_cast<PFN_vk##fn>(dpa(dev, "vk" #fn))
#define LOAD_VK_INST(fn) vkfn.fn = reinterpret_cast<PFN_vk##fn>(ipa(inst, "vk" #fn))
    LOAD_VK_INST(GetPhysicalDeviceMemoryProperties);
    LOAD_VK_DEV(CreateImage);
    LOAD_VK_DEV(DestroyImage);
    LOAD_VK_DEV(GetImageMemoryRequirements);
    LOAD_VK_DEV(AllocateMemory);
    LOAD_VK_DEV(FreeMemory);
    LOAD_VK_DEV(BindImageMemory);
    LOAD_VK_DEV(CreateImageView);
    LOAD_VK_DEV(DestroyImageView);
    LOAD_VK_DEV(CreateCommandPool);
    LOAD_VK_DEV(DestroyCommandPool);
    LOAD_VK_DEV(AllocateCommandBuffers);
    LOAD_VK_DEV(FreeCommandBuffers);
    LOAD_VK_DEV(BeginCommandBuffer);
    LOAD_VK_DEV(EndCommandBuffer);
    LOAD_VK_DEV(ResetCommandBuffer);
    LOAD_VK_DEV(CmdPipelineBarrier);
    LOAD_VK_DEV(CmdClearColorImage);
    LOAD_VK_DEV(CmdBlitImage);
    LOAD_VK_DEV(DeviceWaitIdle);
    LOAD_VK_DEV(CreateFence);
    LOAD_VK_DEV(DestroyFence);
    LOAD_VK_DEV(WaitForFences);
    LOAD_VK_DEV(ResetFences);
    LOAD_VK_DEV(QueueSubmit);
#undef LOAD_VK_DEV
#undef LOAD_VK_INST
}

static bool libretro_vk_validate_functions() {
    bool ok = true;
    auto check_fn = [&](const void *fn, const char *name) {
        if (!fn) {
            ok = false;
            lr_log(RETRO_LOG_ERROR, "Missing required Vulkan function pointer: %s\n", name);
            lr_trace("vk.fn_missing", "name=%s", name);
        }
    };

    check_fn(reinterpret_cast<const void *>(vkfn.GetPhysicalDeviceMemoryProperties), "vkGetPhysicalDeviceMemoryProperties");
    check_fn(reinterpret_cast<const void *>(vkfn.CreateImage), "vkCreateImage");
    check_fn(reinterpret_cast<const void *>(vkfn.DestroyImage), "vkDestroyImage");
    check_fn(reinterpret_cast<const void *>(vkfn.GetImageMemoryRequirements), "vkGetImageMemoryRequirements");
    check_fn(reinterpret_cast<const void *>(vkfn.AllocateMemory), "vkAllocateMemory");
    check_fn(reinterpret_cast<const void *>(vkfn.FreeMemory), "vkFreeMemory");
    check_fn(reinterpret_cast<const void *>(vkfn.BindImageMemory), "vkBindImageMemory");
    check_fn(reinterpret_cast<const void *>(vkfn.CreateImageView), "vkCreateImageView");
    check_fn(reinterpret_cast<const void *>(vkfn.DestroyImageView), "vkDestroyImageView");
    check_fn(reinterpret_cast<const void *>(vkfn.CreateCommandPool), "vkCreateCommandPool");
    check_fn(reinterpret_cast<const void *>(vkfn.DestroyCommandPool), "vkDestroyCommandPool");
    check_fn(reinterpret_cast<const void *>(vkfn.AllocateCommandBuffers), "vkAllocateCommandBuffers");
    check_fn(reinterpret_cast<const void *>(vkfn.FreeCommandBuffers), "vkFreeCommandBuffers");
    check_fn(reinterpret_cast<const void *>(vkfn.BeginCommandBuffer), "vkBeginCommandBuffer");
    check_fn(reinterpret_cast<const void *>(vkfn.EndCommandBuffer), "vkEndCommandBuffer");
    check_fn(reinterpret_cast<const void *>(vkfn.ResetCommandBuffer), "vkResetCommandBuffer");
    check_fn(reinterpret_cast<const void *>(vkfn.CmdPipelineBarrier), "vkCmdPipelineBarrier");
    check_fn(reinterpret_cast<const void *>(vkfn.CmdClearColorImage), "vkCmdClearColorImage");
    check_fn(reinterpret_cast<const void *>(vkfn.CmdBlitImage), "vkCmdBlitImage");
    check_fn(reinterpret_cast<const void *>(vkfn.DeviceWaitIdle), "vkDeviceWaitIdle");
    return ok;
}

static uint32_t libretro_vk_find_memory_type(VkPhysicalDevice gpu, uint32_t type_bits, VkMemoryPropertyFlags flags) {
    VkPhysicalDeviceMemoryProperties mem_props;
    vkfn.GetPhysicalDeviceMemoryProperties(gpu, &mem_props);
    for (uint32_t i = 0; i < mem_props.memoryTypeCount; i++) {
        if ((type_bits & (1u << i)) && (mem_props.memoryTypes[i].propertyFlags & flags) == flags)
            return i;
    }
    return 0;
}

static void libretro_vk_create_presentation_resources() {
    auto &vkp = libretro.vk_presentation;
    const auto *vulkan = vkp.vulkan;
    if (!vulkan)
        return;

    VkDevice device = vulkan->device;
    VkPhysicalDevice gpu = vulkan->gpu;
    const uint32_t w = vkp.width;
    const uint32_t h = vkp.height;

    uint32_t mask = vulkan->get_sync_index_mask(vulkan->handle);
    vkp.num_images = 0;
    for (uint32_t i = 0; i < 32; i++)
        if (mask & (1u << i))
            vkp.num_images = i + 1;
    if (vkp.num_images > LIBRETRO_MAX_SWAPCHAIN)
        vkp.num_images = LIBRETRO_MAX_SWAPCHAIN;
    if (vkp.num_images == 0)
        vkp.num_images = 3;

    lr_log(RETRO_LOG_INFO, "Creating %u presentation images (%ux%u)\n", vkp.num_images, w, h);
    for (uint32_t i = 0; i < vkp.num_images; i++) {
        VkImageCreateInfo img_info = { VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO };
        img_info.imageType = VK_IMAGE_TYPE_2D;
        img_info.format = VK_FORMAT_R8G8B8A8_UNORM;
        img_info.flags = VK_IMAGE_CREATE_MUTABLE_FORMAT_BIT;
        img_info.extent = { w, h, 1 };
        img_info.mipLevels = 1;
        img_info.arrayLayers = 1;
        img_info.samples = VK_SAMPLE_COUNT_1_BIT;
        img_info.tiling = VK_IMAGE_TILING_OPTIMAL;
        img_info.usage = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        img_info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

        vkfn.CreateImage(device, &img_info, nullptr, &vkp.vk_images[i]);

        VkMemoryRequirements mem_reqs;
        vkfn.GetImageMemoryRequirements(device, vkp.vk_images[i], &mem_reqs);

        VkMemoryAllocateInfo alloc_info = { VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO };
        alloc_info.allocationSize = mem_reqs.size;
        alloc_info.memoryTypeIndex = libretro_vk_find_memory_type(gpu, mem_reqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        vkfn.AllocateMemory(device, &alloc_info, nullptr, &vkp.vk_memory[i]);
        vkfn.BindImageMemory(device, vkp.vk_images[i], vkp.vk_memory[i], 0);

        VkImageViewCreateInfo view_info = { VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO };
        view_info.image = vkp.vk_images[i];
        view_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
        view_info.format = VK_FORMAT_R8G8B8A8_UNORM;
        view_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        view_info.subresourceRange.levelCount = 1;
        view_info.subresourceRange.layerCount = 1;
        view_info.components = { VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G, VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A };

        vkfn.CreateImageView(device, &view_info, nullptr, &vkp.vk_views[i]);

        vkp.images[i].image_view = vkp.vk_views[i];
        vkp.images[i].image_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        vkp.images[i].create_info = view_info;
    }

    VkCommandPoolCreateInfo pool_info = { VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO };
    pool_info.queueFamilyIndex = vulkan->queue_index;
    pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    vkfn.CreateCommandPool(device, &pool_info, nullptr, &vkp.cmd_pool);

    VkCommandBufferAllocateInfo cmd_alloc = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };
    cmd_alloc.commandPool = vkp.cmd_pool;
    cmd_alloc.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cmd_alloc.commandBufferCount = vkp.num_images;
    vkfn.AllocateCommandBuffers(device, &cmd_alloc, vkp.cmd_buffers);

    VkFenceCreateInfo fence_info = { VK_STRUCTURE_TYPE_FENCE_CREATE_INFO };
    for (uint32_t i = 0; i < vkp.num_images; i++) {
        vkfn.CreateFence(device, &fence_info, nullptr, &vkp.fences[i]);
        vkp.fence_pending[i] = false;
    }

}

static void libretro_vk_destroy_presentation_resources() {
    auto &vkp = libretro.vk_presentation;
    const auto *vulkan = vkp.vulkan;
    if (!vulkan || !vulkan->device)
        return;

    VkDevice device = vulkan->device;
    vkfn.DeviceWaitIdle(device);

    for (uint32_t i = 0; i < vkp.num_images; i++) {
        if (vkp.fences[i])
            vkfn.DestroyFence(device, vkp.fences[i], nullptr);
        vkp.fences[i] = VK_NULL_HANDLE;
        vkp.fence_pending[i] = false;
    }

    if (vkp.cmd_pool) {
        vkfn.FreeCommandBuffers(device, vkp.cmd_pool, vkp.num_images, vkp.cmd_buffers);
        vkfn.DestroyCommandPool(device, vkp.cmd_pool, nullptr);
        vkp.cmd_pool = VK_NULL_HANDLE;
    }

    for (uint32_t i = 0; i < vkp.num_images; i++) {
        if (vkp.vk_views[i]) vkfn.DestroyImageView(device, vkp.vk_views[i], nullptr);
        if (vkp.vk_images[i]) vkfn.DestroyImage(device, vkp.vk_images[i], nullptr);
        if (vkp.vk_memory[i]) vkfn.FreeMemory(device, vkp.vk_memory[i], nullptr);
        vkp.vk_views[i] = VK_NULL_HANDLE;
        vkp.vk_images[i] = VK_NULL_HANDLE;
        vkp.vk_memory[i] = VK_NULL_HANDLE;
    }
    vkp.num_images = 0;

}

// What the renderer asks of the window it draws to (renderer/frame_host.h).
// The core has none: frames go to RetroArch through the core's own
// presentation (retro_run), so there is no display handle and no swapchain.
// For OpenGL the frontend's context is current on the thread RetroArch calls
// the core on, and its functions come from the frontend.
// The on-screen keyboard's visibility, which the Android app's Java side
// implements (android/jni/ime.cpp, not in this repository) and the IME and
// common dialog modules call on Android. The core has no keyboard of its own
// to show: RetroArch's input reaches the guest's IME as key presses.
namespace ime {
void set_keyboard_active(bool) {}
} // namespace ime

class LibretroFrameHost final : public renderer::FrameHost {
public:
    renderer::DisplayHandle handle() const override {
        return std::monostate{};
    }

    int drawable_width() const override {
        return 960;
    }

    int drawable_height() const override {
        return 544;
    }

    std::vector<std::string> font_dirs() const override {
        return {};
    }

    void *get_proc_address(const char *name) const override {
        return libretro.hw_render.get_proc_address ? reinterpret_cast<void *>(libretro.hw_render.get_proc_address(name)) : nullptr;
    }

    // RetroArch owns the vsync; nothing for the core to turn on or off
    bool set_vsync(bool) override {
        return true;
    }
    unsigned int default_fbo() const override {
        return libretro.hw_render.get_current_framebuffer ? static_cast<unsigned int>(libretro.hw_render.get_current_framebuffer()) : 0;
    }

    bool make_current() override {
        return true;
    }
};

static renderer::FrameHost &libretro_frame_host() {
    static LibretroFrameHost host;
    return host;
}

// Upstream's apply_renderer_config, which also adds the trophy notification's
// unlock callback each time. Upstream calls it once per title, the core at
// every context reset, so the one added before is dropped first: otherwise a
// trophy earned after RetroArch reset the context was shown once per reset.
static void apply_renderer_config(EmuEnvState &emuenv) {
    emuenv.np.trophy_state.clear_trophy_unlock_callbacks();
    app::apply_renderer_config(emuenv);
}

static void context_reset_vulkan() {
    lr_trace("context_reset_vulkan.enter", "renderer_ready=%d emuenv=%d", libretro.renderer_ready ? 1 : 0, libretro.emuenv ? 1 : 0);

    const struct retro_hw_render_interface_vulkan *vulkan = nullptr;
    if (!libretro.environ_cb(RETRO_ENVIRONMENT_GET_HW_RENDER_INTERFACE, (void **)&vulkan) || !vulkan) {
        lr_log(RETRO_LOG_ERROR, "Failed to get Vulkan HW render interface!\n");
        lr_trace("context_reset_vulkan.error", "RETRO_ENVIRONMENT_GET_HW_RENDER_INTERFACE failed");
        return;
    }

    if (vulkan->interface_type != RETRO_HW_RENDER_INTERFACE_VULKAN) {
        lr_log(RETRO_LOG_ERROR, "HW render interface is not Vulkan (got %u)!\n", vulkan->interface_type);
        lr_trace("context_reset_vulkan.error", "interface_type=%u", vulkan->interface_type);
        return;
    }

    lr_trace("context_reset_vulkan.interface",
        "instance=%p device=%p gpu=%p queue=%p queue_index=%u handle=%p",
        vulkan->instance,
        vulkan->device,
        vulkan->gpu,
        vulkan->queue,
        vulkan->queue_index,
        vulkan->handle);

    libretro.vk_presentation.vulkan = vulkan;
    libretro_vk_load_functions(vulkan);
    if (!libretro_vk_validate_functions()) {
        lr_trace("context_reset_vulkan.error", "required Vulkan functions missing");
        return;
    }

    LibretroVulkanHandles handles;
    handles.instance = vulkan->instance;
    handles.gpu = vulkan->gpu;
    handles.device = vulkan->device;
    handles.queue = vulkan->queue;
    handles.queue_family_index = vulkan->queue_index;
    handles.get_instance_proc_addr = vulkan->get_instance_proc_addr;
    handles.get_device_proc_addr = vulkan->get_device_proc_addr;
    set_libretro_vulkan_handles(handles);

    if (libretro.emuenv) {
        EmuEnvState &emuenv = *libretro.emuenv;
        if (!emuenv.renderer) {
            if (!renderer::init(libretro_frame_host(), emuenv.renderer, renderer::Backend::Vulkan, emuenv.cfg, *libretro.root_paths)) {
                lr_log(RETRO_LOG_ERROR, "Failed to create Vulkan renderer!\n");
                return;
            }
            set_libretro_queue_lock(emuenv.renderer.get(), vulkan->handle,
                vulkan->lock_queue, vulkan->unlock_queue);
            emuenv.renderer->late_init(emuenv.cfg, emuenv.io.app_path, emuenv.mem);
            // Resolution multiplier, filters and the rest, as upstream's
            // app start applies them: without it res_multiplier stayed
            // unset and the first render target was zero-sized
            apply_renderer_config(emuenv);
            if (!emuenv.io.title_id.empty()) {
                emuenv.renderer->set_app(emuenv.io.title_id.c_str(), emuenv.self_name.c_str());
                // The shader cache is the title's; its hash list says which renderer
                // features its shaders were built for, and reading it drops a cache
                // built for others. Upstream reads it when it starts a title (the
                // precompile, which the core does not run); without it the core took
                // shaders built without memory mapping into pipelines with it.
                renderer::get_shaders_cache_hashs(*emuenv.renderer);
            }
        }
    }

    libretro_vk_create_presentation_resources();
    libretro.renderer_ready = true;
    lr_log(RETRO_LOG_INFO, "Vulkan context reset complete\n");
}

static void context_reset_opengl() {
    lr_trace("context_reset_opengl.enter", "starting");
    
    auto get_proc = libretro.hw_render.get_proc_address;
    if (!get_proc) {
        lr_log(RETRO_LOG_ERROR, "No get_proc_address callback from frontend!\n");
        lr_trace("context_reset_opengl.error", "no get_proc_address");
        return;
    }
    lr_trace("context_reset_opengl.have_get_proc", "get_proc=%p", (void*)get_proc);

    lr_trace("context_reset_opengl.loading_glad", "calling gladLoadGLLoader");
    if (!gladLoadGLLoader((GLADloadproc)get_proc)) {
        lr_log(RETRO_LOG_ERROR, "Failed to load OpenGL functions via glad!\n");
        lr_trace("context_reset_opengl.error", "gladLoadGLLoader failed");
        return;
    }
    lr_trace("context_reset_opengl.glad_loaded", "OpenGL functions loaded successfully");

    // Log OpenGL version and renderer info for Mesa debugging
    const char* version = (const char*)glGetString(GL_VERSION);
    const char* vendor = (const char*)glGetString(GL_VENDOR);
    const char* renderer = (const char*)glGetString(GL_RENDERER);
    lr_log(RETRO_LOG_INFO, "OpenGL - Version: %s, Vendor: %s, Renderer: %s\n", 
        version ? version : "NULL", 
        vendor ? vendor : "NULL", 
        renderer ? renderer : "NULL");
    lr_trace("context_reset_opengl.gl_info", "version=%s vendor=%s renderer=%s",
        version ? version : "NULL",
        vendor ? vendor : "NULL", 
        renderer ? renderer : "NULL");

    // Check for Mesa specifically
    bool is_mesa = (vendor && strstr(vendor, "Mesa") != nullptr) ||
                   (renderer && strstr(renderer, "Mesa") != nullptr);
    lr_trace("context_reset_opengl.mesa_check", "is_mesa=%d", is_mesa ? 1 : 0);

    if (libretro.emuenv) {
        EmuEnvState &emuenv = *libretro.emuenv;
        if (!emuenv.renderer) {
            lr_trace("context_reset_opengl.creating_renderer", "backend=OpenGL");
            if (!renderer::init(libretro_frame_host(), emuenv.renderer, renderer::Backend::OpenGL, emuenv.cfg, *libretro.root_paths)) {
                lr_log(RETRO_LOG_ERROR, "Failed to create OpenGL renderer!\n");
                lr_trace("context_reset_opengl.error", "renderer::init failed");
                return;
            }
            lr_trace("context_reset_opengl.renderer_created", "success");
            
            lr_trace("context_reset_opengl.late_init", "calling renderer late_init");
            emuenv.renderer->late_init(emuenv.cfg, emuenv.io.app_path, emuenv.mem);
            apply_renderer_config(emuenv);
            lr_trace("context_reset_opengl.late_init_complete", "success");
            
            if (!emuenv.io.title_id.empty()) {
                lr_trace("context_reset_opengl.set_app", "title_id=%s", emuenv.io.title_id.c_str());
                emuenv.renderer->set_app(emuenv.io.title_id.c_str(), emuenv.self_name.c_str());
                // The shader cache is the title's; its hash list says which renderer
                // features its shaders were built for, and reading it drops a cache
                // built for others. Upstream reads it when it starts a title (the
                // precompile, which the core does not run); without it the core took
                // shaders built without memory mapping into pipelines with it.
                renderer::get_shaders_cache_hashs(*emuenv.renderer);
            }
        } else {
            lr_trace("context_reset_opengl.renderer_exists", "skipping creation");
        }
    } else {
        lr_trace("context_reset_opengl.error", "emuenv is null");
        return;
    }

    lr_trace("context_reset_opengl.creating_screen_texture", "size=960x544");
    if (libretro.gl_screen_texture == 0) {
        glGenTextures(1, &libretro.gl_screen_texture);
        glBindTexture(GL_TEXTURE_2D, libretro.gl_screen_texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 960, 544, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glBindTexture(GL_TEXTURE_2D, 0);
        lr_trace("context_reset_opengl.screen_texture_created", "texture_id=%u", libretro.gl_screen_texture);
    } else {
        lr_trace("context_reset_opengl.screen_texture_exists", "texture_id=%u", libretro.gl_screen_texture);
    }

    libretro.renderer_ready = true;
    lr_log(RETRO_LOG_INFO, "OpenGL context reset complete\n");
    lr_trace("context_reset_opengl.complete", "success renderer_ready=1");
}

static void libretro_copy_frame_for_presentation(renderer::vulkan::VKState &vk_state, vk::Image surface,
    vk::Format surface_format, const void *pixels, uint32_t pitch, uint32_t ox, uint32_t oy, uint32_t w, uint32_t h);

// The game's start image (sce_sys/pic0.png), as upstream's
// prepare_game_launch_overlay sets it up: the render thread shows it until the
// game's first frame. Vulkan only, the only renderer the core draws Vita3K's
// overlays with.
static void show_start_image(EmuEnvState &emuenv) {
    auto *vk_state = dynamic_cast<renderer::vulkan::VKState *>(emuenv.renderer.get());
    if (!vk_state || !vk_state->overlay_manager)
        return;
    vfs::FileBuffer png;
    if (!vfs::read_app_file(png, emuenv.vita_fs_path, emuenv.io.app_path, "sce_sys/pic0.png"))
        return;
    auto image = std::make_unique<overlay::image_info>(png);
    if (!image->get_data())
        return;
    auto start = vk_state->overlay_manager->create<overlay::shader_precompile_progress>();
    start->set_background_image(std::move(image));
    start->set_background_only();
}

static void context_reset_finalize() {
    lr_trace("context_reset_finalize.enter",
        "app_started=%d pending_main_module_id=%d active_context=%d renderer_ready=%d",
        libretro.app_started ? 1 : 0,
        libretro.pending_main_module_id,
        static_cast<int>(libretro.active_context),
        libretro.renderer_ready ? 1 : 0);

    lr_trace("context_reset_finalize.check_conditions",
        "emuenv=%d app_started=%d pending_main_module_id=%d",
        libretro.emuenv ? 1 : 0,
        libretro.app_started ? 1 : 0,
        libretro.pending_main_module_id);

    if (libretro.emuenv && !libretro.app_started && libretro.pending_main_module_id >= 0) {
        EmuEnvState &emuenv = *libretro.emuenv;
        lr_log(RETRO_LOG_INFO,
            "context_reset_finalize: starting app (pending_main_module_id=%d)\n",
            libretro.pending_main_module_id);
        
        lr_trace("context_reset_finalize.before_libretro_run_app", "calling libretro_run_app");
        ExitCode run_err = libretro_run_app(emuenv, libretro.pending_main_module_id);
        lr_trace("context_reset_finalize.after_libretro_run_app", "run_err=%d", static_cast<int>(run_err));
        
        if (run_err != Success) {
            lr_log(RETRO_LOG_ERROR, "Failed to start game (error %d)!\n", (int)run_err);
            lr_trace("context_reset_finalize.app_start_failed", "error=%d", static_cast<int>(run_err));
        } else {
            libretro.app_started = true;
            libretro.pending_main_module_id = -1;
            show_start_image(emuenv);
            lr_log(RETRO_LOG_INFO, "context_reset_finalize: app start complete\n");
            lr_trace("context_reset_finalize.app_start_success");
        }
    } else {
        lr_trace("context_reset_finalize.skip_app_start", "conditions not met");
    }

    lr_trace("context_reset_finalize.before_render_thread", "active_context=%d renderer=%p render_thread=%p",
        static_cast<int>(libretro.active_context),
        libretro.emuenv && libretro.emuenv->renderer ? static_cast<void*>(libretro.emuenv->renderer.get()) : nullptr,
        static_cast<void*>(libretro.render_thread.get()));

    if (libretro.active_context == RETRO_HW_CONTEXT_VULKAN
        && libretro.emuenv && libretro.emuenv->renderer && !libretro.render_thread) {
        lr_trace("context_reset_finalize.starting_render_thread");
        libretro.render_thread_running = true;
        libretro.render_thread = std::make_unique<std::thread>([]() {
            EmuEnvState &emuenv = *libretro.emuenv;
            // the start image, shown at once and kept until the game's first
            // frame, as upstream's render_loop does
            if (auto *vk_state = dynamic_cast<renderer::vulkan::VKState *>(emuenv.renderer.get());
                vk_state && vk_state->overlay_manager && vk_state->overlay_manager->get<overlay::shader_precompile_progress>()) {
                const auto w = static_cast<uint32_t>(DEFAULT_RES_WIDTH * vk_state->res_multiplier);
                const auto h = static_cast<uint32_t>(DEFAULT_RES_HEIGHT * vk_state->res_multiplier);
                libretro_copy_frame_for_presentation(*vk_state, nullptr, vk::Format::eUndefined, nullptr, 0, 0, 0, w, h);
            }
            while (libretro.render_thread_running.load()) {
                if (!emuenv.renderer)
                    break;
                emuenv.renderer->should_display = false;
                renderer::process_batches(*emuenv.renderer, emuenv.renderer->features, emuenv.mem, emuenv.cfg);

                // An overlay asking to be drawn again (a dialog's animation,
                // its next state) ends process_batches like a frame to show
                // does, and upstream's loop presents after either. Left set,
                // the request ended every later call at once: this loop spun,
                // cleared should_display each time round, and nothing was
                // shown any more - a dialog froze halfway into its fade
                // (lim2222).
                const bool overlay_flip = emuenv.renderer->async_flip_requested.exchange(false, std::memory_order_relaxed);
                if (emuenv.renderer->should_display || overlay_flip) {
                    DisplayFrameInfo frame;
                    {
                        std::lock_guard<std::mutex> guard(emuenv.display.display_info_mutex);
                        frame = emuenv.display.next_rendered_frame;
                    }

                    auto *vk_state = dynamic_cast<renderer::vulkan::VKState *>(emuenv.renderer.get());
                    if (vk_state && frame.base) {
                        if (vk_state->overlay_manager && vk_state->overlay_manager->get<overlay::shader_precompile_progress>())
                            vk_state->overlay_manager->remove<overlay::shader_precompile_progress>();
                        renderer::vulkan::Viewport viewport;
                        viewport.width = static_cast<uint32_t>(frame.image_size.x * vk_state->res_multiplier);
                        viewport.height = static_cast<uint32_t>(frame.image_size.y * vk_state->res_multiplier);

                        vk::Image surface_image;
                        vk::Format surface_format = vk::Format::eUndefined;
                        vk::ImageView surface_view = vk_state->surface_cache.sourcing_color_surface_for_presentation(
                            frame.base, frame.pitch, viewport, &surface_image, &surface_format);

                        if (surface_view && surface_image && viewport.width && viewport.height)
                            libretro_copy_frame_for_presentation(*vk_state, surface_image, surface_format, nullptr, 0,
                                viewport.offset_x, viewport.offset_y, viewport.width, viewport.height);
                        else if (!surface_view && frame.image_size.x > 0 && frame.image_size.y > 0 && frame.pitch >= static_cast<uint32_t>(frame.image_size.x))
                            // a frame no surface was rendered into (the game
                            // wrote it with the CPU, as some do for their
                            // first screen): from memory, as upstream's
                            // render_frame does
                            libretro_copy_frame_for_presentation(*vk_state, nullptr, vk::Format::eUndefined,
                                frame.base.get(emuenv.mem), frame.pitch, 0, 0,
                                static_cast<uint32_t>(frame.image_size.x), static_cast<uint32_t>(frame.image_size.y));
                    }
                }
            }
        });
    }
    
    lr_trace("context_reset_finalize.complete", "finished");
}

static void context_reset() {
    lr_log(RETRO_LOG_INFO, "context_reset: active_context=%d\n", (int)libretro.active_context);

    if (libretro.active_context == RETRO_HW_CONTEXT_VULKAN) {
        context_reset_vulkan();
    } else if (libretro.active_context == RETRO_HW_CONTEXT_OPENGL_CORE
            || libretro.active_context == RETRO_HW_CONTEXT_OPENGL) {
        context_reset_opengl();
    } else {
        lr_log(RETRO_LOG_ERROR, "context_reset: unknown active_context %d\n", (int)libretro.active_context);
        return;
    }

    if (libretro.renderer_ready)
        context_reset_finalize();
}

static void context_destroy() {
    libretro.renderer_ready = false;

    stop_render_thread();

    if (libretro.active_context == RETRO_HW_CONTEXT_VULKAN) {
        libretro_vk_destroy_presentation_resources();
        libretro.vk_presentation.vulkan = nullptr;
    } else if (libretro.active_context == RETRO_HW_CONTEXT_OPENGL_CORE
            || libretro.active_context == RETRO_HW_CONTEXT_OPENGL) {
        if (libretro.gl_screen_texture) {
            glDeleteTextures(1, &libretro.gl_screen_texture);
            libretro.gl_screen_texture = 0;
        }
    }

    lr_log(RETRO_LOG_INFO, "context_destroy\n");
}

// The frame the core hands RetroArch, in images of the core's own. The game's
// surface is copied into one on the render thread, right where the surface
// cache gives it out - as upstream's render_frame draws from it there - and
// retro_run blits from that copy. Handing over the surface's own VkImage, as
// before, left retro_run blitting from a surface the render thread may have
// destroyed meanwhile, and from the last one handed over on every later
// frame: with memory mapping, which recycles surfaces far more, that ended in
// a lost device. Three images: the one retro_run reads, the newest one
// published to it, and one to write the next frame into.
static struct {
    std::array<vkutil::Image, 3> images;
    vk::CommandPool pool;
    vk::CommandBuffer cmd;
    vk::Fence fence;
    // a frame in memory goes to the image through this
    vkutil::Buffer staging;
    int published = -1; // under rendered_frame_mutex
    int reading = -1; // under rendered_frame_mutex
    // For Vita3K's overlays, drawn over the copy: a pass that keeps what is
    // in the image, and a framebuffer for each image
    vk::RenderPass overlay_pass;
    std::array<vk::Framebuffer, 3> overlay_framebuffers;
} s_present;

// Render thread: the surface's [offset, offset + size) into a free image of
// s_present (or, without a surface, the RGBA8 frame at pixels, pitch in
// pixels), Vita3K's overlays over it when any is shown (the system dialogs,
// trophy and shader notices: upstream's render_frame draws them over the frame
// in the same place), and that published to retro_run. Without a surface
// (before the game's first frame) the overlays are drawn over black.
static void libretro_copy_frame_for_presentation(renderer::vulkan::VKState &vk_state, vk::Image surface,
    vk::Format surface_format, const void *pixels, uint32_t pitch, uint32_t ox, uint32_t oy, uint32_t w, uint32_t h) {
    vk_state.update_overlays();
    bool has_overlays = false;
    if (vk_state.overlay_manager) {
        vk_state.overlay_manager->lock_shared();
        has_overlays = vk_state.overlay_manager->has_visible();
        vk_state.overlay_manager->unlock_shared();
    }

    if (!s_present.pool) {
        s_present.pool = vk_state.device.createCommandPool({ .flags = vk::CommandPoolCreateFlagBits::eResetCommandBuffer,
            .queueFamilyIndex = vk_state.general_family_index });
        s_present.cmd = vk_state.device.allocateCommandBuffers({ .commandPool = s_present.pool,
            .level = vk::CommandBufferLevel::ePrimary, .commandBufferCount = 1 })[0];
        s_present.fence = vk_state.device.createFence({});
    }

    int target = 0;
    {
        std::lock_guard<std::mutex> lock(libretro.rendered_frame_mutex);
        while (target == s_present.published || target == s_present.reading)
            target++;
    }
    vkutil::Image &image = s_present.images[target];
    if (!image.image || image.width != w || image.height != h) {
        // free, so retro_run's last read of it has been submitted; waiting for
        // the device covers it having run
        if (image.image)
            vk_state.device.waitIdle();
        if (s_present.overlay_framebuffers[target]) {
            vk_state.device.destroyFramebuffer(s_present.overlay_framebuffers[target]);
            s_present.overlay_framebuffers[target] = nullptr;
        }
        image = vkutil::Image(w, h, vk::Format::eR8G8B8A8Unorm);
        image.init_image(vk::ImageUsageFlagBits::eTransferSrc | vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eColorAttachment);
    }

    if (has_overlays && !s_present.overlay_pass) {
        const vk::AttachmentDescription attachment{
            .format = vk::Format::eR8G8B8A8Unorm,
            .samples = vk::SampleCountFlagBits::e1,
            .loadOp = vk::AttachmentLoadOp::eLoad,
            .storeOp = vk::AttachmentStoreOp::eStore,
            .stencilLoadOp = vk::AttachmentLoadOp::eDontCare,
            .stencilStoreOp = vk::AttachmentStoreOp::eDontCare,
            .initialLayout = vk::ImageLayout::eGeneral,
            .finalLayout = vk::ImageLayout::eGeneral,
        };
        const vk::AttachmentReference color_ref{ .attachment = 0, .layout = vk::ImageLayout::eGeneral };
        vk::SubpassDescription subpass{ .pipelineBindPoint = vk::PipelineBindPoint::eGraphics };
        subpass.setColorAttachments(color_ref);
        vk::RenderPassCreateInfo pass_info{};
        pass_info.setAttachments(attachment);
        pass_info.setSubpasses(subpass);
        s_present.overlay_pass = vk_state.device.createRenderPass(pass_info);
    }
    if (has_overlays && !s_present.overlay_framebuffers[target]) {
        vk::FramebufferCreateInfo fb_info{
            .renderPass = s_present.overlay_pass,
            .width = w,
            .height = h,
            .layers = 1,
        };
        fb_info.setAttachments(image.view);
        s_present.overlay_framebuffers[target] = vk_state.device.createFramebuffer(fb_info);
    }

    vk::CommandBuffer cmd = s_present.cmd;
    cmd.reset();
    cmd.begin({ .flags = vk::CommandBufferUsageFlagBits::eOneTimeSubmit });
    const vk::ImageSubresourceRange range{ vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1 };
    // the target, after any earlier read of it on the queue; the surface,
    // after the game's rendering into it
    const std::array<vk::ImageMemoryBarrier, 2> before_all{
        vk::ImageMemoryBarrier{ .srcAccessMask = vk::AccessFlagBits::eTransferRead, .dstAccessMask = vk::AccessFlagBits::eTransferWrite,
            .oldLayout = vk::ImageLayout::eUndefined, .newLayout = vk::ImageLayout::eGeneral,
            .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED, .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
            .image = image.image, .subresourceRange = range },
        vk::ImageMemoryBarrier{ .srcAccessMask = vk::AccessFlagBits::eColorAttachmentWrite | vk::AccessFlagBits::eTransferWrite | vk::AccessFlagBits::eShaderWrite,
            .dstAccessMask = vk::AccessFlagBits::eTransferRead,
            .oldLayout = vk::ImageLayout::eGeneral, .newLayout = vk::ImageLayout::eGeneral,
            .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED, .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
            .image = surface, .subresourceRange = range }
    };
    const vk::ArrayProxy<const vk::ImageMemoryBarrier> before = surface
        ? vk::ArrayProxy<const vk::ImageMemoryBarrier>(before_all)
        : vk::ArrayProxy<const vk::ImageMemoryBarrier>(before_all[0]);
    cmd.pipelineBarrier(vk::PipelineStageFlagBits::eAllCommands, vk::PipelineStageFlagBits::eTransfer, {}, {}, {}, before);
    if (surface && surface_format == vk::Format::eR8G8B8A8Srgb) {
        // a game drawing with gamma correction has an sRGB surface. Upstream
        // shows it through a UNORM view, its bytes as they are; a blit would
        // turn them to linear on the way, and the picture came out darker
        // than upstream's (Shoegzer)
        vk::ImageCopy region{
            .srcSubresource = { vk::ImageAspectFlagBits::eColor, 0, 0, 1 },
            .srcOffset = { static_cast<int32_t>(ox), static_cast<int32_t>(oy), 0 },
            .dstSubresource = { vk::ImageAspectFlagBits::eColor, 0, 0, 1 },
            .dstOffset = { 0, 0, 0 },
            .extent = { w, h, 1 },
        };
        cmd.copyImage(surface, vk::ImageLayout::eGeneral, image.image, vk::ImageLayout::eGeneral, region);
    } else if (surface) {
        // a blit, not a copy: the surface may be in another format than RGBA8
        vk::ImageBlit region{
            .srcSubresource = { vk::ImageAspectFlagBits::eColor, 0, 0, 1 },
            .dstSubresource = { vk::ImageAspectFlagBits::eColor, 0, 0, 1 },
        };
        region.srcOffsets[0] = vk::Offset3D{ static_cast<int32_t>(ox), static_cast<int32_t>(oy), 0 };
        region.srcOffsets[1] = vk::Offset3D{ static_cast<int32_t>(ox + w), static_cast<int32_t>(oy + h), 1 };
        region.dstOffsets[0] = vk::Offset3D{ 0, 0, 0 };
        region.dstOffsets[1] = vk::Offset3D{ static_cast<int32_t>(w), static_cast<int32_t>(h), 1 };
        cmd.blitImage(surface, vk::ImageLayout::eGeneral, image.image, vk::ImageLayout::eGeneral, region, vk::Filter::eNearest);
    } else if (pixels) {
        const vk::DeviceSize size = static_cast<vk::DeviceSize>(pitch) * h * 4;
        if (s_present.staging.size < size) {
            // its move assignment does not free the buffer it replaces
            s_present.staging.destroy();
            s_present.staging = vkutil::Buffer(size);
            s_present.staging.init_buffer(vk::BufferUsageFlagBits::eTransferSrc, vkutil::vma_mapped_alloc);
        }
        memcpy(s_present.staging.mapped_data, pixels, size);
        const vk::BufferImageCopy region{
            .bufferOffset = 0,
            .bufferRowLength = pitch,
            .bufferImageHeight = h,
            .imageSubresource = { vk::ImageAspectFlagBits::eColor, 0, 0, 1 },
            .imageOffset = { 0, 0, 0 },
            .imageExtent = { w, h, 1 },
        };
        cmd.copyBufferToImage(s_present.staging.buffer, image.image, vk::ImageLayout::eGeneral, region);
    } else {
        const vk::ClearColorValue black{ std::array<float, 4>{ 0.0f, 0.0f, 0.0f, 1.0f } };
        cmd.clearColorImage(image.image, vk::ImageLayout::eGeneral, black, range);
    }
    if (has_overlays) {
        // their textures and vertices first: uploads cannot be recorded
        // inside the pass
        vk_state.overlay_renderer.prepare(cmd, *vk_state.overlay_manager, static_cast<float>(w), static_cast<float>(h), target);

        const vk::ImageMemoryBarrier to_draw{ .srcAccessMask = vk::AccessFlagBits::eTransferWrite,
            .dstAccessMask = vk::AccessFlagBits::eColorAttachmentRead | vk::AccessFlagBits::eColorAttachmentWrite,
            .oldLayout = vk::ImageLayout::eGeneral, .newLayout = vk::ImageLayout::eGeneral,
            .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED, .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
            .image = image.image, .subresourceRange = range };
        cmd.pipelineBarrier(vk::PipelineStageFlagBits::eTransfer, vk::PipelineStageFlagBits::eColorAttachmentOutput, {}, {}, {}, to_draw);

        const vk::RenderPassBeginInfo pass_begin{
            .renderPass = s_present.overlay_pass,
            .framebuffer = s_present.overlay_framebuffers[target],
            .renderArea = { { 0, 0 }, { w, h } },
        };
        cmd.beginRenderPass(pass_begin, vk::SubpassContents::eInline);
        vk_state.overlay_renderer.render(cmd, s_present.overlay_pass, vk::Extent2D{ w, h },
            0.0f, 0.0f, static_cast<float>(w), static_cast<float>(h));
        cmd.endRenderPass();
    }
    const vk::ImageMemoryBarrier after{ .srcAccessMask = has_overlays ? vk::AccessFlagBits::eColorAttachmentWrite : vk::AccessFlagBits::eTransferWrite,
        .dstAccessMask = vk::AccessFlagBits::eTransferRead,
        .oldLayout = vk::ImageLayout::eGeneral, .newLayout = vk::ImageLayout::eGeneral,
        .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED, .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
        .image = image.image, .subresourceRange = range };
    cmd.pipelineBarrier(has_overlays ? vk::PipelineStageFlagBits::eColorAttachmentOutput : vk::PipelineStageFlagBits::eTransfer,
        vk::PipelineStageFlagBits::eTransfer, {}, {}, {}, after);
    cmd.end();

    vk::SubmitInfo submit{};
    submit.setCommandBuffers(cmd);
    vk_state.locked_queue_submit(vk_state.general_queue, submit, s_present.fence);
    // the copy is done before the surface may change again, and before the
    // command buffer is recorded anew
    (void)vk_state.device.waitForFences(s_present.fence, VK_TRUE, std::numeric_limits<uint64_t>::max());
    vk_state.device.resetFences(s_present.fence);

    std::lock_guard<std::mutex> lock(libretro.rendered_frame_mutex);
    s_present.published = target;
    libretro.vk_surface_image = static_cast<VkImage>(image.image);
    libretro.vk_surface_width = w;
    libretro.vk_surface_height = h;
    libretro.vk_surface_offset_x = 0;
    libretro.vk_surface_offset_y = 0;
    libretro.has_new_frame = true;
}

static void libretro_free_presentation_images(renderer::vulkan::VKState *vk_state) {
    if (vk_state)
        vk_state->device.waitIdle();
    {
        std::lock_guard<std::mutex> lock(libretro.rendered_frame_mutex);
        libretro.vk_surface_image = VK_NULL_HANDLE;
        libretro.has_new_frame = false;
        s_present.published = s_present.reading = -1;
    }
    for (auto &framebuffer : s_present.overlay_framebuffers) {
        if (vk_state && framebuffer)
            vk_state->device.destroyFramebuffer(framebuffer);
        framebuffer = nullptr;
    }
    if (vk_state && s_present.overlay_pass)
        vk_state->device.destroyRenderPass(s_present.overlay_pass);
    s_present.overlay_pass = nullptr;
    for (auto &image : s_present.images)
        image = vkutil::Image();
    s_present.staging.destroy();
    s_present.staging = vkutil::Buffer();
    if (vk_state && s_present.pool) {
        vk_state->device.destroyFence(s_present.fence);
        vk_state->device.destroyCommandPool(s_present.pool);
    }
    s_present.pool = nullptr;
    s_present.cmd = nullptr;
    s_present.fence = nullptr;
}

static void stop_render_thread() {
    if (!libretro.render_thread)
        return;

    lr_log(RETRO_LOG_INFO,
        "Stopping libretro render thread: running=%d, joinable=%d\n",
        libretro.render_thread_running.load() ? 1 : 0,
        libretro.render_thread->joinable() ? 1 : 0);

    libretro.render_thread_running = false;
    if (libretro.render_thread->joinable())
        libretro.render_thread->join();

    libretro.render_thread.reset();
    if (libretro.emuenv && libretro.emuenv->renderer)
        libretro_free_presentation_images(dynamic_cast<renderer::vulkan::VKState *>(libretro.emuenv->renderer.get()));
    lr_log(RETRO_LOG_INFO, "Libretro render thread stopped\n");
}

// The renderer as upstream's shutdown leaves it (shutdown_app_runtime, and
// AppSession for a renderer without a runtime): cleaned up - which stops and
// joins the pipeline compiler threads, among the rest - before it is freed.
// Freed without that, the threads were still joinable and std::thread's
// destructor ended RetroArch at close (sco).
static void release_renderer(EmuEnvState &emuenv) {
    if (!emuenv.renderer)
        return;
    emuenv.renderer->cleanup();
    emuenv.renderer.reset();
}

static void request_guest_shutdown(EmuEnvState &emuenv, const char *reason) {
    const char *shutdown_reason = reason ? reason : "unknown";

    std::size_t guest_thread_count_before = 0;
    {
        std::lock_guard<std::mutex> lock(emuenv.kernel.mutex);
        guest_thread_count_before = emuenv.kernel.threads.size();
    }

    lr_log(RETRO_LOG_INFO,
        "Guest shutdown begin (%s): app_started=%d renderer=%d display_abort=%d guest_threads=%zu\n",
        shutdown_reason,
        libretro.app_started ? 1 : 0,
        emuenv.renderer ? 1 : 0,
        emuenv.display.abort.load() ? 1 : 0,
        guest_thread_count_before);

    if (emuenv.renderer) {
        lr_log(RETRO_LOG_INFO, "Guest shutdown (%s): renderer preclose_action begin\n", shutdown_reason);
        emuenv.renderer->preclose_action();
        lr_log(RETRO_LOG_INFO, "Guest shutdown (%s): renderer preclose_action complete\n", shutdown_reason);
    } else {
        lr_log(RETRO_LOG_INFO, "Guest shutdown (%s): renderer already null before preclose\n", shutdown_reason);
    }

    // A guest audio thread waiting for room in its port leaves only when the
    // ports are stopped, which upstream's shutdown_app_runtime does first too
    emuenv.audio.stop_all_ports();

    // GXM stopped before the guest threads, in upstream's order
    // (shutdown_app_runtime: gxm::shutdown, then process_exit): it wakes the
    // display thread and everything waiting on GXM sync objects
    if (emuenv.renderer) {
        emuenv.renderer->should_display = true;
        gxm::shutdown(emuenv);
    } else {
        emuenv.display.abort = true;
        emuenv.gxm.display_queue.abort();
    }

    emuenv.kernel.exit_delete_all_threads();
    lr_log(RETRO_LOG_INFO, "Guest shutdown (%s): exit_delete_all_threads issued\n", shutdown_reason);

    if (!emuenv.kernel.wait_for_all_threads_exit(5000)) {
        lr_log(RETRO_LOG_WARN,
            "Guest shutdown (%s): timed out waiting for guest thread drain\n",
            shutdown_reason);
        
        // Force-terminate remaining threads
        std::size_t forced_count = 0;
        {
            std::lock_guard<std::mutex> lock(emuenv.kernel.mutex);
            for (auto &[id, thread] : emuenv.kernel.threads) {
                lr_log(RETRO_LOG_WARN, "Guest shutdown (%s): force-terminating stuck thread '%s' (id=%d)\n",
                    shutdown_reason, thread->name.c_str(), id);
                thread->exit_delete(false);
                forced_count++;
            }
        }
        lr_log(RETRO_LOG_WARN, "Guest shutdown (%s): force-terminated %zu stuck threads\n",
            shutdown_reason, forced_count);
        
        // Give them a final chance to exit
        emuenv.kernel.wait_for_all_threads_exit(1000);
    } else {
        lr_log(RETRO_LOG_INFO,
            "Guest shutdown (%s): guest threads drained\n",
            shutdown_reason);
    }

    std::size_t guest_thread_count_after = 0;
    {
        std::lock_guard<std::mutex> lock(emuenv.kernel.mutex);
        guest_thread_count_after = emuenv.kernel.threads.size();
    }
    lr_log(RETRO_LOG_INFO,
        "Guest shutdown (%s): guest thread count after wait=%zu\n",
        shutdown_reason,
        guest_thread_count_after);

    // GXM's display thread joined, as GxmState::deinit does at the end of
    // upstream's shutdown_app_runtime: only aborted, it was still joinable
    // when EmuEnvState was freed and std::thread's destructor ended RetroArch
    // at close (sco, tombstone_13)
    if (emuenv.gxm.display_host_thread.joinable())
        emuenv.gxm.display_host_thread.join();
    lr_log(RETRO_LOG_INFO, "Guest shutdown (%s): gxm display thread joined\n", shutdown_reason);

    {
        std::lock_guard<std::mutex> lock(libretro.rendered_frame_mutex);
        libretro.vk_surface_image = VK_NULL_HANDLE;
        libretro.vk_surface_width = 0;
        libretro.vk_surface_height = 0;
        libretro.vk_surface_offset_x = 0;
        libretro.vk_surface_offset_y = 0;
        libretro.has_new_frame = false;
    }
    lr_log(RETRO_LOG_INFO, "Guest shutdown (%s): cached presented frame cleared\n", shutdown_reason);
}

// The content prepared for a run: the game's entries in Content declared, and
// its PKG installed or mounted as Run Mode and those entries say
static GameInstallResult open_content() {
    const fs::path pref_path = fs::path(libretro.system_dir);
    remove_dead_runs(pref_path);
    // A game loaded before may have left its own options declared
    options_us.definitions = option_defs_us;
    s_kept_content_options.clear();
    s_kept_account_options.clear();
    s_kept_module_options.clear();
    s_kept_network_options.clear();
    s_kept_trophy_options.clear();
    s_trophy_entries.clear();
    set_content_options_handler(declare_content_options);
    s_holes_supported = lazy_pkg::holes_supported(pref_path / "ux0");
    if (!s_holes_supported) {
        lr_log(RETRO_LOG_INFO, "Run Mode: %s has no sparse files, games are installed\n", (pref_path / "ux0").string().c_str());
        declare_content_options({});
        // A Persistent Cache from when the folder was on a file system with them
        // (copied over since) has no use any more (sco8487); what a run without
        // installing left is gone already (remove_dead_runs)
        std::error_code ec;
        if (fs::exists(pref_path / "cache" / "pkg", ec)) {
            fs::remove_all(pref_path / "cache" / "pkg", ec);
            lr_log(RETRO_LOG_INFO, "Run Mode: Persistent Cache removed\n");
        }
    }
    const std::string pkg_mode_name = s_holes_supported ? get_core_option_value("vita3k_pkg_mode", "run") : "install";
    lazy_pkg::set_cache_root(pkg_mode_name == "cache" ? pref_path / "cache" / "pkg" : fs::path());
    set_content_option_accessors(
        [](const std::string &key) { return std::string(get_core_option_value(key.c_str(), "")); },
        [](const std::string &key, const std::string &value) {
            if (!libretro.environ_cb)
                return;
            retro_variable set{};
            set.key = key.c_str();
            set.value = value.c_str();
            libretro.environ_cb(RETRO_ENVIRONMENT_SET_VARIABLE, &set);
        });
    set_account_option_callbacks(declare_account_options,
        [](const std::string &key) { return std::string(get_core_option_value(key.c_str(), "")); },
        [](const std::string &key, const std::string &value) {
            if (!libretro.environ_cb)
                return;
            retro_variable set{};
            set.key = key.c_str();
            set.value = value.c_str();
            libretro.environ_cb(RETRO_ENVIRONMENT_SET_VARIABLE, &set);
        });
    // the game's title and details in the System Language
    const int sys_lang = std::clamp(parse_int_option(get_core_option_value("vita3k_sys_lang", "1"), SCE_SYSTEM_PARAM_LANG_ENGLISH_US), 0, static_cast<int>(SCE_SYSTEM_PARAM_LANG_TURKISH));
    finish_pending_removals(pref_path);
    const GameInstallResult result = ensure_game_installed(fs_utils::utf8_to_path(libretro.game_path), pref_path, sys_lang, pkg_mode_name == "run" || pkg_mode_name == "cache");
    if (result.success)
        // an update or DLC loaded on its own has its kind added to the name
        record_started_title(pref_path, result.title_id, result.category.find("gd") != std::string::npos ? result.title : std::string(),
            lazy_pkg::mounted() ? (lazy_pkg::has_cache_root() ? "cache" : "run") : "install");

    // An installed game's update stays in ux0/patch/<title>, never merged into
    // the game's folder: its files are read in place of the game's here, where
    // a file of the update exists. A game run from its PKG has the update laid
    // over it by lazy_pkg instead.
    vfs::host_path_hook = nullptr;
    vfs::host_dir_hook = nullptr;
    const fs::path app = (pref_path / "ux0" / "app" / result.title_id).lexically_normal();
    const fs::path patch = (pref_path / "ux0" / "patch" / result.title_id).lexically_normal();
    if (result.success && !lazy_pkg::mounted() && fs::is_directory(patch)) {
        // The path below the game's folder, or empty for one outside it
        const auto inside_game = [app](const fs::path &host) {
            fs::path relative = host.lexically_normal().lexically_relative(app);
            if (!relative.empty() && relative.filename() == ".")
                relative = relative.parent_path();
            return (relative.empty() || *relative.begin() == "..") ? fs::path() : relative;
        };
        // A file the update has is read from it; so is a folder only it has
        vfs::host_path_hook = [inside_game, patch](const fs::path &host) -> fs::path {
            const fs::path relative = inside_game(host);
            if (relative.empty())
                return host;
            const fs::path over = patch / relative;
            std::error_code ec;
            if (fs::is_regular_file(over, ec) || (fs::is_directory(over, ec) && !fs::exists(host, ec)))
                return over;
            return host;
        };
        // A folder of the game lists what only the update has after its own
        vfs::host_dir_hook = [inside_game, app, patch](const fs::path &dir) {
            std::vector<std::string> names;
            const fs::path relative = inside_game(dir);
            if (relative.empty() && dir.lexically_normal() != app && dir.lexically_normal() != app / ".")
                return names;
            std::error_code ec;
            for (fs::directory_iterator it(patch / relative, ec), end; !ec && it != end; it.increment(ec)) {
                if (!fs::exists(app / relative / it->path().filename(), ec))
                    names.push_back(it->path().filename().string());
            }
            return names;
        };
        lr_log(RETRO_LOG_INFO, "The update in %s is laid over the installed game\n", patch.generic_string().c_str());
    }
    return result;
}

// The other end of open_content, once the guest has stopped: a game run
// without installing is laid out no more (its marker goes with it), and what
// was turned off in Content is deleted
static void close_content() {
    vfs::host_path_hook = nullptr;
    vfs::host_dir_hook = nullptr;
    if (lazy_pkg::mounted()) {
        lazy_pkg::unmount();
        std::error_code ec;
        fs::remove(fs::path(libretro.system_dir) / "ux0" / "libretro_pkg" / ("lazy_" + libretro.installed_title_id), ec);
    }
    content_closed();
}

// The emulator goes, its memory with it; that memory's fault handler (mem.cpp)
// goes first, as RetroArch's process (and any later crash in it) outlives the game
static void drop_emuenv() {
    if (libretro.emuenv)
        unregister_access_violation_handler();
    libretro.emuenv.reset();
}

static bool perform_core_reset() {
    lr_log(RETRO_LOG_INFO,
        "perform_core_reset: begin (game_loaded=%d, emuenv=%d, cfg=%d, root=%d, context=%d)\n",
        libretro.game_loaded ? 1 : 0,
        libretro.emuenv ? 1 : 0,
        libretro.cfg ? 1 : 0,
        libretro.root_paths ? 1 : 0,
        static_cast<int>(libretro.active_context));

    if (!libretro.game_loaded || !libretro.emuenv || !libretro.cfg || !libretro.root_paths) {
        lr_log(RETRO_LOG_WARN, "perform_core_reset: prerequisites missing, skipping reset\n");
        return false;
    }

    stop_render_thread();
    request_guest_shutdown(*libretro.emuenv, "retro_reset");
    // A reset is a close and a load: the renderer goes the same way
    release_renderer(*libretro.emuenv);
    context_destroy();

    drop_emuenv();
    libretro.renderer_ready = false;
    libretro.app_started = false;
    libretro.pending_main_module_id = -1;

    // The content goes the same way too, so that what was chosen in Content
    // is applied and nothing of the run before is kept
    close_content();
    const GameInstallResult install_result = open_content();
    if (!install_result.success) {
        lr_log(RETRO_LOG_ERROR, "perform_core_reset: failed to prepare the content again\n");
        libretro.game_loaded = false;
        return false;
    }
    libretro.installed_title_id = install_result.title_id;
    libretro.installed_title = install_result.title;
    libretro.cfg->run_app_path = libretro.installed_title_id;

    libretro.emuenv = std::make_unique<EmuEnvState>();
    EmuEnvState &emuenv = *libretro.emuenv;

    if (!libretro_init_emuenv(emuenv, *libretro.root_paths)) {
        lr_log(RETRO_LOG_ERROR, "perform_core_reset: failed to reinitialize EmuEnvState\n");
        libretro.game_loaded = false;
        drop_emuenv();
        return false;
    }

    apply_config_changes();

    int32_t main_module_id = -1;
    const ExitCode load_err = libretro_load_app(main_module_id, emuenv);
    if (load_err != Success) {
        lr_log(RETRO_LOG_ERROR, "perform_core_reset: failed to reload app (error %d)\n", static_cast<int>(load_err));
        libretro.game_loaded = false;
        drop_emuenv();
        return false;
    }

    libretro.pending_main_module_id = main_module_id;
    libretro.app_started = false;

    context_reset();

    lr_log(RETRO_LOG_INFO,
        "perform_core_reset: complete (renderer_ready=%d, app_started=%d, pending_main_module_id=%d)\n",
        libretro.renderer_ready ? 1 : 0,
        libretro.app_started ? 1 : 0,
        libretro.pending_main_module_id);
    return true;
}

static const VkApplicationInfo *libretro_vk_get_application_info() {
    static const VkApplicationInfo info = {
        VK_STRUCTURE_TYPE_APPLICATION_INFO,
        nullptr,
        "Vita3K",
        0,
        "Vita3K",
        0,
        VK_MAKE_API_VERSION(0, 1, 1, 0),
    };
    return &info;
}

// RetroArch's device made by the core, with what memory mapping and the
// renderer's optional paths need (VK_KHR_buffer_device_address and the rest).
// A device RetroArch makes itself has none of them, and memory mapping on it
// called a null vkGetBufferDeviceAddress.
static bool libretro_vk_create_device(struct retro_vulkan_context *context, VkInstance instance, VkPhysicalDevice gpu,
    VkSurfaceKHR surface, PFN_vkGetInstanceProcAddr get_instance_proc_addr,
    const char **required_device_extensions, unsigned num_required_device_extensions,
    const char **required_device_layers, unsigned num_required_device_layers,
    const VkPhysicalDeviceFeatures *required_features) {
    LibretroVulkanDevice made;
    if (!libretro_create_vulkan_device(made, instance, gpu, surface, get_instance_proc_addr,
            required_device_extensions, num_required_device_extensions, required_features))
        return false;
    context->gpu = made.gpu;
    context->device = made.device;
    context->queue = made.queue;
    context->queue_family_index = made.queue_family_index;
    context->presentation_queue = made.queue;
    context->presentation_queue_family_index = made.queue_family_index;
    return true;
}

static bool try_set_hw_vulkan() {
    memset(&libretro.hw_render, 0, sizeof(libretro.hw_render));
    libretro.hw_render.context_type = RETRO_HW_CONTEXT_VULKAN;
    libretro.hw_render.version_major = VK_MAKE_API_VERSION(0, 1, 1, 0);
    libretro.hw_render.version_minor = 0;
    libretro.hw_render.context_reset = context_reset;
    libretro.hw_render.context_destroy = context_destroy;
    libretro.hw_render.cache_context = true;
    libretro.hw_render.bottom_left_origin = false;

    if (!libretro.environ_cb(RETRO_ENVIRONMENT_SET_HW_RENDER, &libretro.hw_render)) {
        lr_log(RETRO_LOG_WARN, "Frontend rejected Vulkan HW context\n");
        return false;
    }

    static const struct retro_hw_render_context_negotiation_interface_vulkan negotiation = {
        RETRO_HW_RENDER_CONTEXT_NEGOTIATION_INTERFACE_VULKAN,
        RETRO_HW_RENDER_CONTEXT_NEGOTIATION_INTERFACE_VULKAN_VERSION,
        libretro_vk_get_application_info,
        libretro_vk_create_device,
        nullptr,
    };
    libretro.environ_cb(RETRO_ENVIRONMENT_SET_HW_RENDER_CONTEXT_NEGOTIATION_INTERFACE, (void *)&negotiation);

    libretro.active_context = RETRO_HW_CONTEXT_VULKAN;
    return true;
}

static bool try_set_hw_opengl() {
    lr_trace("try_set_hw_opengl.enter", "requesting OpenGL Core 4.4");
    
    memset(&libretro.hw_render, 0, sizeof(libretro.hw_render));
    libretro.hw_render.context_type = RETRO_HW_CONTEXT_OPENGL_CORE;
    libretro.hw_render.version_major = 4;
    libretro.hw_render.version_minor = 4;
    libretro.hw_render.context_reset = context_reset;
    libretro.hw_render.context_destroy = context_destroy;
    libretro.hw_render.cache_context = true;
    libretro.hw_render.bottom_left_origin = true;
    libretro.hw_render.depth = false;
    libretro.hw_render.stencil = false;

    lr_trace("try_set_hw_opengl.setting_hw_render", "calling RETRO_ENVIRONMENT_SET_HW_RENDER");
    if (!libretro.environ_cb(RETRO_ENVIRONMENT_SET_HW_RENDER, &libretro.hw_render)) {
        lr_log(RETRO_LOG_WARN, "Frontend rejected OpenGL Core 4.4 HW context\n");
        lr_trace("try_set_hw_opengl.rejected", "OpenGL Core 4.4 rejected by frontend");
        return false;
    }

    libretro.active_context = RETRO_HW_CONTEXT_OPENGL_CORE;
    lr_trace("try_set_hw_opengl.success", "OpenGL Core 4.4 context accepted");
    return true;
}

static bool libretro_init_hw_render() {
    const char *backend_option = get_core_option_value("vita3k_backend_renderer", "Vulkan");
    const bool force_opengl = (strcmp(backend_option, "OpenGL") == 0);
    const bool force_vulkan = (strcmp(backend_option, "Vulkan") == 0);

    if (force_opengl) {
        if (try_set_hw_opengl()) return true;
        if (try_set_hw_vulkan()) return true;
    } else if (force_vulkan) {
        if (try_set_hw_vulkan()) return true;
        if (try_set_hw_opengl()) return true;
    }

    unsigned preferred = RETRO_HW_CONTEXT_NONE;
    if (!libretro.environ_cb(RETRO_ENVIRONMENT_GET_PREFERRED_HW_RENDER, &preferred))
        preferred = RETRO_HW_CONTEXT_VULKAN;

    bool is_gl_preferred = (preferred == RETRO_HW_CONTEXT_OPENGL_CORE
                         || preferred == RETRO_HW_CONTEXT_OPENGL
                         || preferred == RETRO_HW_CONTEXT_OPENGLES2
                         || preferred == RETRO_HW_CONTEXT_OPENGLES3
                         || preferred == RETRO_HW_CONTEXT_OPENGLES_VERSION);

    if (is_gl_preferred) {
        if (try_set_hw_opengl()) return true;
        if (try_set_hw_vulkan()) return true;
    } else {
        if (try_set_hw_vulkan()) return true;
        if (try_set_hw_opengl()) return true;
    }

    lr_log(RETRO_LOG_ERROR, "Failed to set any HW render context! Neither Vulkan nor OpenGL accepted.\n");
    return false;
}

RETRO_API void retro_set_environment(retro_environment_t cb) {
    libretro.environ_cb = cb;

    // Content behind a URI (saf://, the Play Store build) through the
    // frontend's VFS
    lr_vfs_init(cb);

    bool no_game = false;
    cb(RETRO_ENVIRONMENT_SET_SUPPORT_NO_GAME, &no_game);

    bool categories_supported = false;
    libretro_set_core_options(libretro.environ_cb, &categories_supported);
    retro_core_options_update_display_callback update_display{ update_trophy_display };
    cb(RETRO_ENVIRONMENT_SET_CORE_OPTIONS_UPDATE_DISPLAY_CALLBACK, &update_display);
    libretro_log_init();
}

RETRO_API void retro_set_video_refresh(retro_video_refresh_t cb) {
    libretro.video_cb = cb;
}

RETRO_API void retro_set_audio_sample(retro_audio_sample_t cb) {
    libretro.audio_sample_cb = cb;
}

RETRO_API void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb) {
    libretro.audio_batch_cb = cb;
}

RETRO_API void retro_set_input_poll(retro_input_poll_t cb) {
    libretro.input_poll_cb = cb;
}

RETRO_API void retro_set_input_state(retro_input_state_t cb) {
    libretro.input_state_cb = cb;
}

RETRO_API unsigned retro_api_version(void) {
    return RETRO_API_VERSION;
}

RETRO_API void retro_get_system_info(struct retro_system_info *info) {
    memset(info, 0, sizeof(*info));
    info->library_name = "Vita3K";
    // Upstream Vita3K's version and build number, as its builds are named
    // ("v0.2.1 4123"), and the upstream commit (upstream.version)
    static const std::string version = fmt::format("{} {} {}", app_version, app_number, app_hash);
    info->library_version = version.c_str();
    info->valid_extensions = "vpk|zip|pkg|bin|pup";
    info->need_fullpath = true;
    info->block_extract = true;
}

// The size of the frame handed over follows Internal Resolution Multiplier
// (1920x1088 at 2x), and the frontend has to be told: its integer scaling,
// screenshots and shaders read the size from the geometry, not from the
// frame (the bug NNshi found in cemu with resolution packs).
static unsigned s_reported_width = 0, s_reported_height = 0;

static void report_frame_size(unsigned width, unsigned height) {
    if (width == s_reported_width && height == s_reported_height)
        return;
    s_reported_width = width;
    s_reported_height = height;
    retro_game_geometry geometry{};
    geometry.base_width = width;
    geometry.base_height = height;
    geometry.max_width = 960 * 4;
    geometry.max_height = 544 * 4;
    geometry.aspect_ratio = 960.0f / 544.0f;
    libretro.environ_cb(RETRO_ENVIRONMENT_SET_GEOMETRY, &geometry);
    lr_log(RETRO_LOG_INFO, "output is now %ux%u\n", width, height);
}

RETRO_API void retro_get_system_av_info(struct retro_system_av_info *info) {
    memset(info, 0, sizeof(*info));
    float multiplier = libretro.cfg ? libretro.cfg->current_config.resolution_multiplier : 1.0f;
    if (multiplier < 1.0f || multiplier > 4.0f)
        multiplier = 1.0f;
    info->geometry.base_width = s_reported_width = static_cast<unsigned>(960 * multiplier);
    info->geometry.base_height = s_reported_height = static_cast<unsigned>(544 * multiplier);
    info->geometry.max_width = 960 * 4;
    info->geometry.max_height = 544 * 4;
    info->geometry.aspect_ratio = 960.0f / 544.0f;

    info->timing.fps = 60.0;
    info->timing.sample_rate = 48000.0;
}

#ifndef _WIN32
// The JIT (dynarmic's fault handler) gives the thread that first makes one -
// RetroArch's own - an alternate signal stack, and frees it when the core is
// unloaded without taking it off the thread. The next signal there was then
// delivered onto unmapped memory, and the kernel ended RetroArch with no
// crash report: the second game in the same process (sco8487). The thread's
// own stack is put back when the core closes.
static stack_t frontend_signal_stack;
static bool frontend_signal_stack_saved = false;
#endif

RETRO_API void retro_init(void) {
#ifndef _WIN32
    frontend_signal_stack_saved = sigaltstack(nullptr, &frontend_signal_stack) == 0;
#endif
    libretro_log_init();
    libretro_logging_init();
    lr_log(RETRO_LOG_INFO, "Vita3K libretro core %s %d (upstream %s), built from commit %s\n",
        app_version, app_number, app_hash, VITA3K_LIBRETRO_COMMIT);

    // SDL looks up the app's name when it makes its first thread, the guest's
    // main thread here. Without a name it asks for the executable's, which on
    // Android is the package name, read through Java: SDL's Java side is not
    // set up in a core, and that read crashed every game at start. A name
    // given as a hint is taken without asking.
    SDL_SetHint(SDL_HINT_APP_NAME, "Vita3K");

    libretro_init_paths();
#ifdef _WIN32
    lr_install_vectored_exception_handler();
#endif
    libretro_init_input_descriptors();
    libretro_setup_controller_info();

    lr_trace("retro_init", "system_dir=%s", libretro.system_dir.c_str());

    libretro.initialized = true;
}

RETRO_API void retro_deinit(void) {
    lr_log(RETRO_LOG_INFO, "retro_deinit()\n");
    lr_trace("retro_deinit.enter",
        "initialized=%d game_loaded=%d emuenv=%d app_started=%d",
        libretro.initialized ? 1 : 0,
        libretro.game_loaded ? 1 : 0,
        libretro.emuenv ? 1 : 0,
        libretro.app_started ? 1 : 0);

    if (libretro.emuenv) {
        stop_render_thread();
        request_guest_shutdown(*libretro.emuenv, "retro_deinit");
    }

    drop_emuenv();
    libretro.cfg.reset();
    libretro.root_paths.reset();
    libretro.initialized = false;
    libretro.game_loaded = false;
    libretro.app_started = false;
    libretro.pending_main_module_id = -1;
    libretro.reset_requested = false;

#ifdef _WIN32
    lr_remove_vectored_exception_handler();
#else
    if (frontend_signal_stack_saved) {
        stack_t current;
        if (sigaltstack(nullptr, &current) == 0 && current.ss_sp != frontend_signal_stack.ss_sp) {
            // sigaltstack refuses a stack marked as in use or disabled with
            // a size; only these fields are given back
            stack_t restore = {};
            restore.ss_sp = frontend_signal_stack.ss_sp;
            restore.ss_size = frontend_signal_stack.ss_size;
            restore.ss_flags = frontend_signal_stack.ss_flags & SS_DISABLE;
            if (sigaltstack(&restore, nullptr) != 0)
                lr_log(RETRO_LOG_WARN, "retro_deinit: the thread's signal stack could not be put back\n");
        }
        frontend_signal_stack_saved = false;
    }
#endif
}

static void RETRO_CALLCONV libretro_keyboard_event(bool down, unsigned keycode, uint32_t character, uint16_t modifiers);

RETRO_API bool retro_load_game(const struct retro_game_info *game) {
    if (!game || !game->path) {
        lr_log(RETRO_LOG_ERROR, "No game path provided\n");
        return false;
    }

    lr_log(RETRO_LOG_INFO, "retro_load_game: %s\n", game->path);

    // Keys for the name entry of Rename Active Account
    {
        retro_keyboard_callback keyboard{ libretro_keyboard_event };
        libretro.environ_cb(RETRO_ENVIRONMENT_SET_KEYBOARD_CALLBACK, &keyboard);
    }
    lr_trace("retro_load_game.begin", "path=%s", game->path);
    libretro.game_path = game->path;

    enum retro_pixel_format fmt = RETRO_PIXEL_FORMAT_XRGB8888;
    if (!libretro.environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &fmt)) {
        lr_log(RETRO_LOG_ERROR, "XRGB8888 pixel format not supported\n");
        return false;
    }

    if (!libretro_init_hw_render()) {
        lr_log(RETRO_LOG_ERROR, "retro_load_game: failed to initialize HW render context\n");
        lr_trace("retro_load_game.error", "libretro_init_hw_render failed");
        return false;
    }
    lr_trace("retro_load_game.hw_context", "active_context=%d", static_cast<int>(libretro.active_context));

    const fs::path pref_path = fs::path(libretro.system_dir);
    const fs::path system_dir = fs::path(libretro.system_dir);
    const fs::path game_path = fs_utils::utf8_to_path(libretro.game_path);
    fs::create_directories(pref_path);

    // A firmware package loaded as content is installed, and there is no game
    // to start; RetroArch then reports that nothing was loaded, after the
    // core's own message saying what was installed
    std::string extension = game_path.extension().string();
    std::transform(extension.begin(), extension.end(), extension.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    if (extension == ".pup") {
        install_firmware_content(pref_path, game_path);
        return false;
    }

    if (!check_firmware_installed(pref_path, system_dir)) {
        lr_log(RETRO_LOG_WARN, "Firmware not found — expect errors\n");
        lr_trace("retro_load_game.firmware", "firmware not found at %s", system_dir.generic_string().c_str());
    }

    GameInstallResult install_result = open_content();

    if (!install_result.success) {
        lr_log(RETRO_LOG_ERROR, "Game installation/verification failed.\n");
        lr_trace("retro_load_game.error", "ensure_game_installed failed for %s", game_path.generic_string().c_str());
        return false;
    }

    lr_trace("retro_load_game.install",
        "title_id=%s title=%s",
        install_result.title_id.c_str(),
        install_result.title.c_str());

    libretro.installed_title_id = install_result.title_id;
    libretro.installed_title = install_result.title;

    libretro.root_paths = std::make_unique<Root>();
    Root &root = *libretro.root_paths;

        root.set_vita_fs_path(pref_path);
    root.set_log_path(pref_path / "log");
    root.set_config_path(pref_path / "config");
    root.set_cache_path(pref_path / "cache");
    root.set_shared_path(pref_path);
    root.set_patch_path(pref_path / "patch");

    install_bundled_files(pref_path);
    root.set_static_assets_path(pref_path);

    app::init_paths(root);
    fs::create_directories(pref_path / "ux0" / "app");
    fs::create_directories(pref_path / "ux0" / "data");
    fs::create_directories(pref_path / "ux0" / "user" / "00" / "savedata");
    fs::create_directories(pref_path / "ux0" / "addcont");
    fs::create_directories(pref_path / "ux0" / "patch");

    libretro.cfg = std::make_unique<Config>();
    Config &cfg = *libretro.cfg;
    cfg.set_vita_fs_path(root.get_vita_fs_path());
    cfg.backend_renderer = (libretro.active_context == RETRO_HW_CONTEXT_VULKAN) ? "Vulkan" : "OpenGL";
    cfg.audio_backend = "Libretro";
    cfg.console = false;
    cfg.overwrite_config = false;
    cfg.run_app_path = libretro.installed_title_id;

    declare_module_options(pref_path);
    declare_adhoc_address_option();

    // Prime config from libretro core options before EmuEnv initialization so
    // restart-sensitive settings (CPU/modules/renderer/memory mapping) are
    // used during app::init/app::late_init and module loading.
    read_core_options();
    apply_config_changes();
    request_host_camera();

    libretro.emuenv = std::make_unique<EmuEnvState>();
    EmuEnvState &emuenv = *libretro.emuenv;

    if (!libretro_init_emuenv(emuenv, root)) {
        lr_log(RETRO_LOG_ERROR, "Failed to initialize emulator environment!\n");
        lr_trace("retro_load_game.error", "libretro_init_emuenv failed");
        drop_emuenv();
        return false;
    }

    // Apply live-changeable settings on initialized subsystems.
    apply_config_changes();

    int32_t main_module_id = -1;
    ExitCode load_err = libretro_load_app(main_module_id, emuenv);
    if (load_err != Success) {
        lr_log(RETRO_LOG_ERROR, "Failed to load game (error %d)!\n", (int)load_err);
        lr_trace("retro_load_game.error", "libretro_load_app failed code=%d", static_cast<int>(load_err));
        drop_emuenv();
        return false;
    }

    libretro.pending_main_module_id = main_module_id;
    libretro.app_started = false;
    libretro.reset_requested = false;
    
    libretro.game_loaded = true;

    lr_trace("retro_load_game.complete",
        "game_loaded=%d app_started=%d pending_main_module_id=%d",
        libretro.game_loaded ? 1 : 0,
        libretro.app_started ? 1 : 0,
        libretro.pending_main_module_id);

    return true;
}

RETRO_API bool retro_load_game_special(unsigned game_type, const struct retro_game_info *info, size_t num_info) {
    (void)game_type;
    (void)info;
    (void)num_info;
    return false;
}

RETRO_API void retro_unload_game(void) {
    lr_log(RETRO_LOG_INFO, "retro_unload_game()\n");
    lr_trace("retro_unload_game.enter", "game_loaded=%d emuenv=%d", libretro.game_loaded ? 1 : 0, libretro.emuenv ? 1 : 0);

    if (libretro.emuenv) {
        stop_render_thread();
        request_guest_shutdown(*libretro.emuenv, "retro_unload_game");
        release_renderer(*libretro.emuenv);
    }

    drop_emuenv();
    close_content();
    libretro.game_loaded = false;
    libretro.app_started = false;
    libretro.pending_main_module_id = -1;
    libretro.reset_requested = false;
    libretro.installed_title_id.clear();
    libretro.installed_title.clear();
}

// Rename Active Account: a name typed inside the core, since a core option
// cannot hold free text, as in the Cemu core (Shoegzer, #1). The name so far is
// shown as the frontend's status line. A pad picks it a character at a time;
// a keyboard types it, through the frontend's keyboard callback. The game gets
// no input while the entry is open.
static struct {
    bool active = false;
    std::string id;
    std::u32string text;
    std::recursive_mutex mutex; // the keyboard callback may come from another thread
    bool accept = false, cancel = false, changed = false;
    bool held[16]{};
    int repeat = 0, shown = 0;
} s_name_entry;

static constexpr size_t NAME_ENTRY_MAX = 16;
static const std::u32string NAME_ENTRY_CHARACTERS = U"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 -_.!?&+";

static std::string utf32_to_utf8(const std::u32string &text) {
    std::string out;
    for (const char32_t c : text) {
        if (c < 0x80)
            out += static_cast<char>(c);
        else if (c < 0x800) {
            out += static_cast<char>(0xC0 | (c >> 6));
            out += static_cast<char>(0x80 | (c & 0x3F));
        } else if (c < 0x10000) {
            out += static_cast<char>(0xE0 | (c >> 12));
            out += static_cast<char>(0x80 | ((c >> 6) & 0x3F));
            out += static_cast<char>(0x80 | (c & 0x3F));
        } else {
            out += static_cast<char>(0xF0 | (c >> 18));
            out += static_cast<char>(0x80 | ((c >> 12) & 0x3F));
            out += static_cast<char>(0x80 | ((c >> 6) & 0x3F));
            out += static_cast<char>(0x80 | (c & 0x3F));
        }
    }
    return out;
}

static std::u32string utf8_to_utf32(const std::string &text) {
    std::u32string out;
    for (size_t i = 0; i < text.size();) {
        const unsigned char c = static_cast<unsigned char>(text[i]);
        const int extra = c < 0x80 ? 0 : c < 0xE0 ? 1 : c < 0xF0 ? 2 : 3;
        char32_t code = extra == 0 ? c : extra == 1 ? (c & 0x1F) : extra == 2 ? (c & 0x0F) : (c & 0x07);
        for (int k = 1; k <= extra && i + k < text.size(); k++)
            code = (code << 6) | (static_cast<unsigned char>(text[i + k]) & 0x3F);
        out += code;
        i += extra + 1;
    }
    return out;
}

// A line that replaces the one before it: the frontend's status message, which
// has one place on screen, where notifications would pile up
static void lr_status(const std::string &text, unsigned duration_ms) {
    unsigned version = 0;
    if (!libretro.environ_cb || !libretro.environ_cb(RETRO_ENVIRONMENT_GET_MESSAGE_INTERFACE_VERSION, &version) || version < 1) {
        lr_message(text, duration_ms * 60 / 1000);
        return;
    }
    retro_message_ext msg{};
    msg.msg = text.c_str();
    msg.duration = duration_ms;
    msg.priority = 3;
    msg.level = RETRO_LOG_INFO;
    msg.target = RETRO_MESSAGE_TARGET_OSD;
    msg.type = RETRO_MESSAGE_TYPE_STATUS;
    msg.progress = -1;
    libretro.environ_cb(RETRO_ENVIRONMENT_SET_MESSAGE_EXT, &msg);
}

static void RETRO_CALLCONV libretro_keyboard_event(bool down, unsigned keycode, uint32_t character, uint16_t /*modifiers*/) {
    if (!down)
        return;
    std::lock_guard lock(s_name_entry.mutex);
    if (!s_name_entry.active)
        return;
    if (keycode == RETROK_BACKSPACE) {
        if (!s_name_entry.text.empty())
            s_name_entry.text.pop_back();
    } else if (keycode == RETROK_RETURN || keycode == RETROK_KP_ENTER)
        s_name_entry.accept = true;
    else if (keycode == RETROK_ESCAPE)
        s_name_entry.cancel = true;
    else if (character >= 32 && character != 127 && s_name_entry.text.size() < NAME_ENTRY_MAX)
        s_name_entry.text.push_back(static_cast<char32_t>(character));
    else
        return;
    s_name_entry.changed = true;
}

// Called after the input is polled: true while the entry is open, and then
// nothing of the input reaches the game
static bool libretro_update_name_entry(EmuEnvState &emuenv) {
    std::lock_guard lock(s_name_entry.mutex);
    const auto raw = [](unsigned id) {
        return libretro.input_state_cb && libretro.input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, id) != 0;
    };
    std::string id, name;
    if (!s_name_entry.active && libretro_accounts_take_rename_request(emuenv, id, name)) {
        s_name_entry.active = true;
        s_name_entry.id = id;
        s_name_entry.text = utf8_to_utf32(name);
        s_name_entry.accept = s_name_entry.cancel = false;
        s_name_entry.changed = true;
        s_name_entry.repeat = 0;
        // what is held as the menu closes is not a press
        for (unsigned i = 0; i < 16; i++)
            s_name_entry.held[i] = raw(i);
    }
    if (!s_name_entry.active)
        return false;

    bool pressed[16];
    for (unsigned i = 0; i < 16; i++) {
        const bool down = raw(i);
        pressed[i] = down && !s_name_entry.held[i];
        s_name_entry.held[i] = down;
    }
    // Up and Down repeat while held, after a third of a second
    const bool up = s_name_entry.held[RETRO_DEVICE_ID_JOYPAD_UP];
    const bool down = s_name_entry.held[RETRO_DEVICE_ID_JOYPAD_DOWN];
    bool step = pressed[RETRO_DEVICE_ID_JOYPAD_UP] || pressed[RETRO_DEVICE_ID_JOYPAD_DOWN];
    if (up != down) {
        if (++s_name_entry.repeat > 20 && s_name_entry.repeat % 4 == 0)
            step = true;
    } else
        s_name_entry.repeat = 0;
    if (step && up != down) {
        if (s_name_entry.text.empty())
            s_name_entry.text.push_back(NAME_ENTRY_CHARACTERS[0]);
        else {
            const size_t count = NAME_ENTRY_CHARACTERS.size();
            size_t at = NAME_ENTRY_CHARACTERS.find(s_name_entry.text.back());
            if (at == std::u32string::npos)
                at = 0;
            else
                at = (at + (down ? 1 : count - 1)) % count;
            s_name_entry.text.back() = NAME_ENTRY_CHARACTERS[at];
        }
        s_name_entry.changed = true;
    }
    if (pressed[RETRO_DEVICE_ID_JOYPAD_RIGHT] && s_name_entry.text.size() < NAME_ENTRY_MAX) {
        s_name_entry.text.push_back(s_name_entry.text.empty() ? NAME_ENTRY_CHARACTERS[0] : s_name_entry.text.back());
        s_name_entry.changed = true;
    }
    if (pressed[RETRO_DEVICE_ID_JOYPAD_LEFT] && !s_name_entry.text.empty()) {
        s_name_entry.text.pop_back();
        s_name_entry.changed = true;
    }
    if (pressed[RETRO_DEVICE_ID_JOYPAD_START])
        s_name_entry.accept = true;
    if (pressed[RETRO_DEVICE_ID_JOYPAD_SELECT])
        s_name_entry.cancel = true;

    if (s_name_entry.cancel) {
        s_name_entry.active = false;
        lr_status("Account not renamed", 3000);
        return true;
    }
    if (s_name_entry.accept) {
        s_name_entry.accept = false;
        std::u32string text = s_name_entry.text;
        while (!text.empty() && text.back() == U' ')
            text.pop_back();
        if (text.empty()) {
            lr_status("A name needs at least one character", 3000);
            return true;
        }
        s_name_entry.active = false;
        const std::string new_name = utf32_to_utf8(text);
        if (libretro_accounts_rename(emuenv, s_name_entry.id, new_name))
            lr_status(fmt::format("Account {} is now named {}", s_name_entry.id, new_name), 5000);
        else
            lr_status("Cannot rename: the account was not found", 4000);
        return true;
    }
    // Shown again before it runs out, so it stays up while the entry is open
    if (s_name_entry.changed || ++s_name_entry.shown >= 120) {
        s_name_entry.changed = false;
        s_name_entry.shown = 0;
        lr_status(fmt::format("Account name: {}_  (Start/Enter accepts, Select/Esc cancels)", utf32_to_utf8(s_name_entry.text)), 3000);
    }
    return true;
}

RETRO_API void retro_run(void) {
    if (!libretro.game_loaded || !libretro.emuenv)
        return;

    static std::atomic<uint64_t> run_counter{ 0 };
    const uint64_t run_index = run_counter.fetch_add(1, std::memory_order_relaxed) + 1;
    const bool trace_this_tick = (run_index <= 240) || ((run_index % 300) == 0);
    if (trace_this_tick) {
        lr_trace("retro_run.tick",
            "tick=%llu app_started=%d renderer_ready=%d active_context=%d render_thread=%d",
            static_cast<unsigned long long>(run_index),
            libretro.app_started ? 1 : 0,
            libretro.renderer_ready ? 1 : 0,
            static_cast<int>(libretro.active_context),
            libretro.render_thread ? 1 : 0);
    }

    // the trophy list, every few seconds of play
    if (libretro.app_started && run_index % 180 == 0)
        refresh_trophy_options(*libretro.emuenv);

    if (libretro.reset_requested.exchange(false)) {
        lr_log(RETRO_LOG_INFO, "retro_run: processing deferred reset request\n");
        if (!perform_core_reset()) {
            lr_log(RETRO_LOG_WARN, "retro_run: deferred reset failed\n");
            return;
        }
        if (!libretro.game_loaded || !libretro.emuenv)
            return;
    }

    // Check for core options updates
    bool updated = false;
    if (libretro.environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE_UPDATE, &updated) && updated) {
        read_core_options();
        apply_config_changes();
        libretro_accounts_options_changed(*libretro.emuenv);
    }

    EmuEnvState &emuenv = *libretro.emuenv;

    if (libretro.input_poll_cb)
        libretro.input_poll_cb();
    libretro_poll_input();
    if (libretro_update_name_entry(emuenv)) {
        auto &input = libretro_input_state();
        std::lock_guard lock(input.mutex);
        for (auto &port : input.ports)
            port = {};
        input.front_touch_count = 0;
        input.back_touch_count = 0;
        for (auto &point : input.front_touch)
            point.active = false;
        for (auto &point : input.back_touch)
            point.active = false;
    }

    if (libretro.app_started)
        libretro_vblank_tick(emuenv);

    if (libretro.active_context != RETRO_HW_CONTEXT_VULKAN
        && libretro.renderer_ready && emuenv.renderer) {
        emuenv.renderer->should_display = false;
        renderer::process_batches(*emuenv.renderer, emuenv.renderer->features, emuenv.mem, emuenv.cfg);
    }

    auto &vkp = libretro.vk_presentation;
    const auto *vulkan = vkp.vulkan;

    if (libretro.renderer_ready && libretro.active_context == RETRO_HW_CONTEXT_VULKAN
        && vulkan && vkp.num_images > 0) {
        if (!libretro_vk_validate_functions()) {
            lr_trace("retro_run.vk_abort", "missing required Vulkan functions at tick=%llu", static_cast<unsigned long long>(run_index));
            return;
        }

        uint32_t new_mask = vulkan->get_sync_index_mask(vulkan->handle);
        uint32_t new_count = 0;
        for (uint32_t i = 0; i < 32; i++)
            if (new_mask & (1u << i))
                new_count = i + 1;
        if (new_count != vkp.num_images && new_count > 0) {
            lr_trace("retro_run.vk_swapchain_resize", "old_num_images=%u new_num_images=%u", vkp.num_images, new_count);
            libretro_vk_destroy_presentation_resources();
            libretro_vk_create_presentation_resources();
        }

        // The images handed over take the size of the game's rendered
        // surface, which Internal Resolution Multiplier scales. They were
        // fixed at 960x544, so a 2x-4x render was shrunk back to 960x544 on
        // its way to the frontend and the multiplier showed nothing.
        {
            uint32_t surface_w, surface_h;
            {
                std::lock_guard<std::mutex> lock(libretro.rendered_frame_mutex);
                surface_w = libretro.vk_surface_width;
                surface_h = libretro.vk_surface_height;
            }
            if (surface_w && surface_h && surface_w <= 960 * 4 && surface_h <= 544 * 4
                && (surface_w != vkp.width || surface_h != vkp.height)) {
                lr_log(RETRO_LOG_INFO, "presentation images %ux%u -> %ux%u\n", vkp.width, vkp.height, surface_w, surface_h);
                libretro_vk_destroy_presentation_resources();
                vkp.width = surface_w;
                vkp.height = surface_h;
                libretro_vk_create_presentation_resources();
            }
        }

        vulkan->wait_sync_index(vulkan->handle);
        uint32_t index = vulkan->get_sync_index(vulkan->handle);
        if (index >= vkp.num_images)
            index = 0;

        if (trace_this_tick) {
            lr_trace("retro_run.vk_sync",
                "tick=%llu sync_index=%u num_images=%u width=%u height=%u",
                static_cast<unsigned long long>(run_index),
                index,
                vkp.num_images,
                vkp.width,
                vkp.height);
        }

        VkCommandBuffer cmd = vkp.cmd_buffers[index];
        // RetroArch's sync index does not tell when the core's own work for
        // it is done (the validation layer: the command buffer still in use
        // when reset); the core's fence for that index does
        if (vkp.fence_pending[index]) {
            vkfn.WaitForFences(vulkan->device, 1, &vkp.fences[index], VK_TRUE, UINT64_MAX);
            vkfn.ResetFences(vulkan->device, 1, &vkp.fences[index]);
            vkp.fence_pending[index] = false;
        }

        VkCommandBufferBeginInfo begin_info = { VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO };
        begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        vkfn.ResetCommandBuffer(cmd, 0);
        vkfn.BeginCommandBuffer(cmd, &begin_info);

        VkImage src_image = VK_NULL_HANDLE;
        uint32_t src_w = 0, src_h = 0, src_ox = 0, src_oy = 0;
        {
            std::lock_guard<std::mutex> lock(libretro.rendered_frame_mutex);
            if (libretro.has_new_frame && libretro.vk_surface_image != VK_NULL_HANDLE) {
                // the render thread does not write this one while it is ours
                s_present.reading = s_present.published;
                src_image = libretro.vk_surface_image;
                src_w = libretro.vk_surface_width;
                src_h = libretro.vk_surface_height;
                src_ox = libretro.vk_surface_offset_x;
                src_oy = libretro.vk_surface_offset_y;
            }
        }

        VkImageMemoryBarrier barrier = { VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER };
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        barrier.image = vkp.vk_images[index];
        barrier.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        // after RetroArch's reads of this image from its last use
        vkfn.CmdPipelineBarrier(cmd, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
            0, 0, nullptr, 0, nullptr, 1, &barrier);

        if (src_image != VK_NULL_HANDLE && src_w > 0 && src_h > 0) {
            if (trace_this_tick) {
                lr_trace("retro_run.vk_blit",
                    "tick=%llu src_image=%p src_w=%u src_h=%u src_ox=%u src_oy=%u",
                    static_cast<unsigned long long>(run_index),
                    src_image,
                    src_w,
                    src_h,
                    src_ox,
                    src_oy);
            }

            VkImageMemoryBarrier src_barrier = { VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER };
            src_barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            src_barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
            src_barrier.oldLayout = VK_IMAGE_LAYOUT_GENERAL;
            src_barrier.newLayout = VK_IMAGE_LAYOUT_GENERAL;
            src_barrier.image = src_image;
            src_barrier.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
            src_barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
            src_barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
            vkfn.CmdPipelineBarrier(cmd, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
                0, 0, nullptr, 0, nullptr, 1, &src_barrier);

            VkImageBlit blit_region = {};
            blit_region.srcSubresource = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1 };
            blit_region.srcOffsets[0] = { (int32_t)src_ox, (int32_t)src_oy, 0 };
            blit_region.srcOffsets[1] = { (int32_t)(src_ox + src_w), (int32_t)(src_oy + src_h), 1 };
            blit_region.dstSubresource = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1 };
            blit_region.dstOffsets[0] = { 0, 0, 0 };
            blit_region.dstOffsets[1] = { (int32_t)vkp.width, (int32_t)vkp.height, 1 };

            vkfn.CmdBlitImage(cmd, src_image, VK_IMAGE_LAYOUT_GENERAL,
                vkp.vk_images[index], VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                1, &blit_region, VK_FILTER_LINEAR);

        } else {
            VkClearColorValue black = { { 0.0f, 0.0f, 0.0f, 1.0f } };
            VkImageSubresourceRange range = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
            vkfn.CmdClearColorImage(cmd, vkp.vk_images[index], VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, &black, 1, &range);
        }

        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        vkfn.CmdPipelineBarrier(cmd, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
            0, 0, nullptr, 0, nullptr, 1, &barrier);

        vkfn.EndCommandBuffer(cmd);

        // Submitted here, ahead of RetroArch's frame on the same queue, whose
        // read of the image the barrier above orders after the blit
        VkSubmitInfo submit = { VK_STRUCTURE_TYPE_SUBMIT_INFO };
        submit.commandBufferCount = 1;
        submit.pCommandBuffers = &cmd;
        vulkan->lock_queue(vulkan->handle);
        vkfn.QueueSubmit(vulkan->queue, 1, &submit, vkp.fences[index]);
        vulkan->unlock_queue(vulkan->handle);
        vkp.fence_pending[index] = true;

        vkp.images[index].image_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        vulkan->set_image(vulkan->handle, &vkp.images[index], 0, nullptr, VK_QUEUE_FAMILY_IGNORED);
        report_frame_size(vkp.width, vkp.height);
        libretro.video_cb(RETRO_HW_FRAME_BUFFER_VALID, vkp.width, vkp.height, 0);
    } else if (libretro.renderer_ready
            && (libretro.active_context == RETRO_HW_CONTEXT_OPENGL_CORE
             || libretro.active_context == RETRO_HW_CONTEXT_OPENGL)) {
        GLuint fbo = (GLuint)libretro.hw_render.get_current_framebuffer();
        DisplayFrameInfo frame;
        {
            std::lock_guard<std::mutex> guard(emuenv.display.display_info_mutex);
            frame = emuenv.display.next_rendered_frame;
        }

        uint32_t width = frame.image_size.x > 0 ? static_cast<uint32_t>(frame.image_size.x) : 960;
        uint32_t height = frame.image_size.y > 0 ? static_cast<uint32_t>(frame.image_size.y) : 544;
        GLuint surface_tex = 0;
        float uvs[4] = { 0.0f, 0.0f, 1.0f, 1.0f };

        auto *gl_state = dynamic_cast<renderer::gl::GLState *>(emuenv.renderer.get());
        if (gl_state && frame.base) {
            SceFVector2 tex_size;
            surface_tex = gl_state->surface_cache.sourcing_color_surface_for_presentation(
                frame.base, frame.image_size.x, frame.image_size.y, frame.pitch,
                uvs, gl_state->res_multiplier, tex_size);
            if (surface_tex) {
                width = static_cast<uint32_t>(frame.image_size.x * gl_state->res_multiplier);
                height = static_cast<uint32_t>(frame.image_size.y * gl_state->res_multiplier);

                const GLint standard_swizzle[4] = { GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA };
                glBindTexture(GL_TEXTURE_2D, surface_tex);
                glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, standard_swizzle);
                glBindTexture(GL_TEXTURE_2D, 0);
            }
        }

        // A frame no surface was rendered into (the game wrote it with the
        // CPU, as some do for their first screen): uploaded from memory into a
        // texture of the core's and shown like a surface, as upstream's
        // render_frame does; it used to be shown as black
        if (!surface_tex && frame.base && frame.image_size.x > 0 && frame.image_size.y > 0
            && frame.pitch >= static_cast<uint32_t>(frame.image_size.x)) {
            static GLuint memory_tex = 0;
            if (!memory_tex)
                glGenTextures(1, &memory_tex);
            width = static_cast<uint32_t>(frame.image_size.x);
            height = static_cast<uint32_t>(frame.image_size.y);
            glBindTexture(GL_TEXTURE_2D, memory_tex);
            glPixelStorei(GL_UNPACK_ROW_LENGTH, static_cast<GLint>(frame.pitch));
            glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
            // ABGR8888 in memory: the bytes in R, G, B, A order
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, frame.base.get(emuenv.mem));
            glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glBindTexture(GL_TEXTURE_2D, 0);
            surface_tex = memory_tex;
            // memory is top-down, as the blit below takes it from the
            // surface's (0, 0); the whole texture is the frame
            uvs[0] = 0.0f;
            uvs[1] = 0.0f;
            uvs[2] = 1.0f;
            uvs[3] = 1.0f;
        }

        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glViewport(0, 0, width, height);

        if (surface_tex) {
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_BLEND);
            glDisable(GL_CULL_FACE);
            glDisable(GL_SCISSOR_TEST);
            glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

            static GLuint read_fbo = 0;
            if (!read_fbo)
                glGenFramebuffers(1, &read_fbo);

            glBindFramebuffer(GL_READ_FRAMEBUFFER, read_fbo);
            glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, surface_tex, 0);
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo);

            GLint src_y0 = static_cast<GLint>(uvs[1] * height / uvs[3]);
            GLint src_y1 = static_cast<GLint>(height);
            GLint src_x1 = static_cast<GLint>(width);

            glBlitFramebuffer(0, src_y0, src_x1, src_y1,
                              0, height, width, 0,
                              GL_COLOR_BUFFER_BIT, GL_LINEAR);

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        } else {
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        // Vita3K's overlays (the system dialogs, the trophy and shader
        // notices) over the frame, as upstream's render_frame draws them
        if (gl_state) {
            gl_state->update_overlays();
            if (gl_state->overlay_manager && gl_state->overlay_manager->has_visible())
                gl_state->overlay_renderer.render(*gl_state->overlay_manager, 0.0f, 0.0f,
                    static_cast<float>(width), static_cast<float>(height),
                    static_cast<float>(width), static_cast<float>(height), fbo);
        }

        report_frame_size(width, height);
        libretro.video_cb(RETRO_HW_FRAME_BUFFER_VALID, width, height, 0);
    } else {
        const int width = 960;
        const int height = 544;

        DisplayFrameInfo frame;
        {
            std::lock_guard<std::mutex> guard(emuenv.display.display_info_mutex);
            frame = emuenv.display.next_rendered_frame;
        }

        if (frame.base && frame.image_size.x > 0 && frame.image_size.y > 0) {
            const int fw = frame.image_size.x;
            const int fh = frame.image_size.y;
            const int pitch = frame.pitch > 0 ? frame.pitch : fw;
            const uint32_t *src = reinterpret_cast<const uint32_t *>(frame.base.get(emuenv.mem));

            if (src) {
                if (libretro.frame_buffer.size() != static_cast<size_t>(fw * fh))
                    libretro.frame_buffer.resize(fw * fh);

                // Convert ABGR8888 -> XRGB8888
                for (int y = 0; y < fh; y++) {
                    for (int x = 0; x < fw; x++) {
                        const uint32_t pixel = src[y * pitch + x];
                        const uint32_t r = (pixel >> 0) & 0xFF;
                        const uint32_t g = (pixel >> 8) & 0xFF;
                        const uint32_t b = (pixel >> 16) & 0xFF;
                        libretro.frame_buffer[y * fw + x] = (0xFF << 24) | (r << 16) | (g << 8) | b;
                    }
                }
                libretro.video_cb(libretro.frame_buffer.data(), fw, fh, fw * sizeof(uint32_t));
            } else {
                libretro.video_cb(nullptr, width, height, width * sizeof(uint32_t));
            }
        } else {
            if (libretro.frame_buffer.size() != static_cast<size_t>(width * height))
                libretro.frame_buffer.resize(width * height, 0);
            libretro.video_cb(libretro.frame_buffer.data(), width, height, width * sizeof(uint32_t));
        }
    }

    {
        static std::vector<int16_t> audio_buf;
        int num_frames = libretro_audio_drain(emuenv.audio, audio_buf);
        // Only what the game played: silence made up for a frame without
        // audio is time the game's audio did not take, heard as gaps and a
        // tempo that wanders (sco)
        if (num_frames > 0 && libretro.audio_batch_cb)
            libretro.audio_batch_cb(audio_buf.data(), num_frames);
    }
}

static void read_core_option(const char *key, const char *default_value, std::function<void(const char *)> apply_func) {
    if (!libretro.environ_cb || !apply_func)
        return;
    
    retro_variable variable = {};
    variable.key = key;
    if (libretro.environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &variable) && variable.value) {
        lr_log(RETRO_LOG_INFO, "Core option read: %s='%s'\n", key, variable.value);
        apply_func(variable.value);
    } else {
        // Use default value if variable not found
        lr_log(RETRO_LOG_INFO, "Core option read: %s missing, using default='%s'\n", key, default_value);
        apply_func(default_value);
    }
}

static void apply_config_changes() {
    if (!libretro.cfg)
        return;

    Config &cfg = *libretro.cfg;
    const bool have_emuenv = (libretro.emuenv != nullptr);
    EmuEnvState *emuenv = have_emuenv ? libretro.emuenv.get() : nullptr;

    const bool backend_changed = (cfg.backend_renderer != cfg.current_config.backend_renderer);
    const float resolution_delta = std::fabs(cfg.resolution_multiplier - cfg.current_config.resolution_multiplier);
    const bool resolution_changed = (resolution_delta > 0.001f);
    const bool memory_mapping_changed = (cfg.memory_mapping != cfg.current_config.memory_mapping);
    const bool high_accuracy_changed = (cfg.high_accuracy != cfg.current_config.high_accuracy);
    const bool modules_mode_changed = (cfg.modules_mode != cfg.current_config.modules_mode)
        || (cfg.lle_modules != cfg.current_config.lle_modules);
    const bool cpu_opt_changed = (cfg.cpu_opt != cfg.current_config.cpu_opt);

    // The Content options (game, update, DLC) apply when the content is started again
    const bool content_changed = content_options_changed();
    const bool restart_required = backend_changed || resolution_changed || memory_mapping_changed
        || high_accuracy_changed || modules_mode_changed || cpu_opt_changed || content_changed;

    if (restart_required && libretro.app_started) {
        lr_log(RETRO_LOG_INFO,
            "Restart check details: backend('%s'->'%s') res(%.3f->%.3f, delta=%.6f) mem_map('%s'->'%s') high_acc(%d->%d) modules(%d->%d) cpu_opt(%d->%d)\n",
            cfg.backend_renderer.c_str(),
            cfg.current_config.backend_renderer.c_str(),
            cfg.resolution_multiplier,
            cfg.current_config.resolution_multiplier,
            resolution_delta,
            cfg.memory_mapping.c_str(),
            cfg.current_config.memory_mapping.c_str(),
            cfg.high_accuracy ? 1 : 0,
            cfg.current_config.high_accuracy ? 1 : 0,
            cfg.modules_mode,
            cfg.current_config.modules_mode,
            cfg.cpu_opt ? 1 : 0,
            cfg.current_config.cpu_opt ? 1 : 0);
        lr_message("Vita3K: Some option changes require restarting content to fully apply.");
        lr_log(RETRO_LOG_WARN,
            "Core option change requires restart (backend=%d, res=%d, mem_map=%d, high_acc=%d, modules=%d, cpu_opt=%d)\n",
            backend_changed ? 1 : 0,
            resolution_changed ? 1 : 0,
            memory_mapping_changed ? 1 : 0,
            high_accuracy_changed ? 1 : 0,
            modules_mode_changed ? 1 : 0,
            cpu_opt_changed ? 1 : 0);
    }
    
    // Copy current_config values to main config
    cfg.cpu_opt = cfg.current_config.cpu_opt;
    cfg.modules_mode = cfg.current_config.modules_mode;
    cfg.lle_modules = cfg.current_config.lle_modules;
    cfg.audio_volume = cfg.current_config.audio_volume;
    cfg.ngs_enable = cfg.current_config.ngs_enable;
    cfg.pstv_mode = cfg.current_config.pstv_mode;
    cfg.sys_button = cfg.sys_button;
    cfg.fps_hack = cfg.current_config.fps_hack;
    cfg.file_loading_delay = cfg.current_config.file_loading_delay;
    cfg.psn_signed_in = cfg.current_config.psn_signed_in;
    
    // Renderer-specific config
    cfg.backend_renderer = cfg.current_config.backend_renderer;
    cfg.high_accuracy = cfg.current_config.high_accuracy;
    cfg.resolution_multiplier = cfg.current_config.resolution_multiplier;
    cfg.disable_surface_sync = cfg.current_config.disable_surface_sync;
    cfg.screen_filter = cfg.current_config.screen_filter;
    cfg.v_sync = cfg.current_config.v_sync;
    cfg.anisotropic_filtering = cfg.current_config.anisotropic_filtering;
    cfg.async_pipeline_compilation = cfg.current_config.async_pipeline_compilation;
    cfg.memory_mapping = cfg.current_config.memory_mapping;

    // Apply settings that can safely change while content is running.
    if (have_emuenv && emuenv->renderer) {
        emuenv->renderer->set_surface_sync_state(cfg.current_config.disable_surface_sync);
        emuenv->renderer->set_screen_filter(cfg.current_config.screen_filter);
        emuenv->renderer->set_anisotropic_filtering(cfg.current_config.anisotropic_filtering);
        emuenv->renderer->set_async_compilation(cfg.current_config.async_pipeline_compilation);
        emuenv->renderer->show_compile_shaders = cfg.show_compile_shaders;
        // update_overlays leaves the notice alone while the option is off, so
        // one on screen when it is turned off would stay there
        if (!cfg.show_compile_shaders && emuenv->renderer->overlay_manager)
            emuenv->renderer->overlay_manager->remove<overlay::shader_compile_notice>();

        // Resolution changes are restart-sensitive while ingame; apply immediately only before app start.
        if (!libretro.app_started)
            emuenv->renderer->res_multiplier = cfg.current_config.resolution_multiplier;
    }

    if (have_emuenv) {
        emuenv->display.fps_hack = cfg.current_config.fps_hack;
        emuenv->audio.set_global_volume(cfg.current_config.audio_volume / 100.0f);
    }
    
    // Log changes for debugging
    lr_log(RETRO_LOG_INFO, "Applied core options changes:\n");
    lr_log(RETRO_LOG_INFO, "  Backend: %s\n", cfg.backend_renderer.c_str());
    lr_log(RETRO_LOG_INFO, "  Resolution: %.1fx\n", cfg.resolution_multiplier);
    lr_log(RETRO_LOG_INFO, "  Screen Filter: %s\n", cfg.screen_filter.c_str());
    lr_log(RETRO_LOG_INFO, "  Surface Sync: %s\n", cfg.disable_surface_sync ? "disabled" : "enabled");
    lr_log(RETRO_LOG_INFO, "  FPS Hack: %s\n", cfg.fps_hack ? "enabled" : "disabled");
    lr_log(RETRO_LOG_INFO, "  Memory Mapping: %s\n", cfg.memory_mapping.c_str());
    lr_log(RETRO_LOG_INFO, "  CPU Opt: %s\n", cfg.cpu_opt ? "enabled" : "disabled");
    lr_log(RETRO_LOG_INFO, "  Audio Volume: %d%%\n", cfg.audio_volume);
}

static void read_core_options() {
    if (!libretro.cfg) return;
    
    // GPU Options
    read_core_option("vita3k_backend_renderer", "Vulkan", [](const char *value) {
        const std::string token = normalize_option_token(value);
        libretro.cfg->current_config.backend_renderer = (token == "opengl") ? "OpenGL" : "Vulkan";
    });
    
    read_core_option("vita3k_resolution_multiplier", "1", [](const char *value) {
        libretro.cfg->current_config.resolution_multiplier = parse_float_option(value, 1.0f);
    });
    
    read_core_option("vita3k_screen_filter", "Bilinear", [](const char *value) {
        libretro.cfg->current_config.screen_filter = value;
    });
    
    read_core_option("vita3k_anisotropic_filtering", "1", [](const char *value) {
        libretro.cfg->current_config.anisotropic_filtering = parse_int_option(value, 1);
    });
    
    read_core_option("vita3k_v_sync", "enabled", [](const char *value) {
        libretro.cfg->current_config.v_sync = parse_enabled_option(value, true);
    });
    
    read_core_option("vita3k_async_pipeline", "enabled", [](const char *value) {
        libretro.cfg->current_config.async_pipeline_compilation = parse_enabled_option(value, true);
    });
    
    // The notice of shaders being compiled in the lower left corner (sco8487)
    read_core_option("vita3k_compile_overlay", "enabled", [](const char *value) {
        libretro.cfg->show_compile_shaders = parse_enabled_option(value, true);
    });

    read_core_option("vita3k_surface_sync", "enabled", [](const char *value) {
        // Inverted logic: disable_surface_sync = !surface_sync_enabled
        libretro.cfg->current_config.disable_surface_sync = !parse_enabled_option(value, true);
    });
    
    read_core_option("vita3k_high_accuracy", "disabled", [](const char *value) {
        libretro.cfg->current_config.high_accuracy = parse_enabled_option(value, false);
    });
    
    read_core_option("vita3k_memory_mapping", "double-buffer", [](const char *value) {
        libretro.cfg->current_config.memory_mapping = canonical_memory_mapping_option(value);
    });
    
    // System Options
    read_core_option("vita3k_pstv_mode", "disabled", [](const char *value) {
        libretro.cfg->current_config.pstv_mode = parse_enabled_option(value, false);
    });
    
    read_core_option("vita3k_sys_lang", "1", [](const char *value) {
        const int lang = std::clamp(parse_int_option(value, SCE_SYSTEM_PARAM_LANG_ENGLISH_US), 0, static_cast<int>(SCE_SYSTEM_PARAM_LANG_TURKISH));
        libretro.cfg->sys_lang = lang;
        libretro.cfg->current_config.sys_lang = lang;
    });

    read_core_option("vita3k_sys_date_format", "2", [](const char *value) {
        const int format = std::clamp(parse_int_option(value, SCE_SYSTEM_PARAM_DATE_FORMAT_MMDDYYYY), 0, static_cast<int>(SCE_SYSTEM_PARAM_DATE_FORMAT_MMDDYYYY));
        libretro.cfg->sys_date_format = format;
        libretro.cfg->current_config.sys_date_format = format;
    });

    read_core_option("vita3k_sys_time_format", "0", [](const char *value) {
        const int format = std::clamp(parse_int_option(value, SCE_SYSTEM_PARAM_TIME_FORMAT_12HOUR), 0, static_cast<int>(SCE_SYSTEM_PARAM_TIME_FORMAT_24HOUR));
        libretro.cfg->sys_time_format = format;
        libretro.cfg->current_config.sys_time_format = format;
    });

    read_core_option("vita3k_sys_button", "1", [](const char *value) {
        libretro.cfg->sys_button = parse_int_option(value, 1);
    });
    
    read_core_option("vita3k_modules_mode", "0", [](const char *value) {
        int mode = parse_int_option(value, 0);
        if (mode < ModulesMode::AUTOMATIC)
            mode = ModulesMode::AUTOMATIC;
        if (mode > ModulesMode::MANUAL)
            mode = ModulesMode::MANUAL;
        libretro.cfg->current_config.modules_mode = mode;
    });

    // The modules turned on under Modules, shown there only when they are used
    auto &lle_modules = libretro.cfg->current_config.lle_modules;
    lle_modules.clear();
    const bool manual_modules = libretro.cfg->current_config.modules_mode != static_cast<int>(ModulesMode::AUTOMATIC);
    for (const std::string &name : s_module_names) {
        const std::string key = MODULE_KEY_PREFIX + name;
        if (std::string_view(get_core_option_value(key.c_str(), "disabled")) == "enabled")
            lle_modules.push_back(name);
        retro_core_option_display display{ key.c_str(), manual_modules };
        libretro.environ_cb(RETRO_ENVIRONMENT_SET_CORE_OPTIONS_DISPLAY, &display);
    }
    
    read_core_option("vita3k_fps_hack", "disabled", [](const char *value) {
        libretro.cfg->current_config.fps_hack = parse_enabled_option(value, false);
    });
    
    read_core_option("vita3k_file_loading_delay", "0", [](const char *value) {
        int delay = parse_int_option(value, 0);
        if (delay < 0)
            delay = 0;
        if (delay > 30)
            delay = 30;
        libretro.cfg->current_config.file_loading_delay = delay;
    });
    
    // Audio Options
    read_core_option("vita3k_audio_volume", "100", [](const char *value) {
        int volume = parse_int_option(value, 100);
        if (volume < 0)
            volume = 0;
        if (volume > 100)
            volume = 100;
        libretro.cfg->current_config.audio_volume = volume;
    });
    
    read_core_option("vita3k_ngs_enable", "enabled", [](const char *value) {
        libretro.cfg->current_config.ngs_enable = parse_enabled_option(value, true);
    });
    
    // CPU Options
    read_core_option("vita3k_cpu_opt", "enabled", [](const char *value) {
        libretro.cfg->current_config.cpu_opt = parse_enabled_option(value, true);
    });
    
    // Network Options
    read_core_option("vita3k_http_enable", "enabled", [](const char *value) {
        libretro.cfg->http_enable = parse_enabled_option(value, true);
    });
    read_core_option("vita3k_http_timeout_attempts", "50", [](const char *value) {
        libretro.cfg->http_timeout_attempts = std::clamp(parse_int_option(value, 50), 0, 100);
    });
    read_core_option("vita3k_http_timeout_sleep", "100", [](const char *value) {
        libretro.cfg->http_timeout_sleep_ms = std::clamp(parse_int_option(value, 100), 50, 3000);
    });
    read_core_option("vita3k_http_read_end_attempts", "10", [](const char *value) {
        libretro.cfg->http_read_end_attempts = std::clamp(parse_int_option(value, 10), 0, 100);
    });
    read_core_option("vita3k_http_read_end_sleep", "250", [](const char *value) {
        libretro.cfg->http_read_end_sleep_ms = std::clamp(parse_int_option(value, 250), 50, 3000);
    });
    read_core_option("vita3k_adhoc_addr", "0", [](const char *value) {
        libretro.cfg->adhoc_addr = std::max(parse_int_option(value, 0), 0);
    });

    // The cameras, for the next time the game opens one (SceCamera reads them
    // from the running emulator's config then)
    for (const bool front : { true, false }) {
        const char *side = front ? "front" : "back";
        const std::string source = get_core_option_value(fmt::format("vita3k_{}_camera", side).c_str(), "host");
        const int type = source == "color" ? CameraType::SolidColor : source == "image" ? CameraType::Image : CameraType::WebCamera;
        const uint32_t color = static_cast<uint32_t>(std::strtoul(get_core_option_value(fmt::format("vita3k_{}_camera_color", side).c_str(), "0"), nullptr, 10));
        std::string image;
        for (const char *extension : { ".png", ".jpg", ".jpeg" }) {
            const fs::path path = fs::path(libretro.system_dir) / "camera" / (std::string(side) + extension);
            std::error_code ec;
            if (fs::exists(path, ec)) {
                image = fs_utils::path_to_utf8(path);
                break;
            }
        }
        for (Config *cfg : { libretro.cfg.get(), libretro.emuenv ? &libretro.emuenv->cfg : nullptr }) {
            if (!cfg)
                continue;
            (front ? cfg->front_camera_type : cfg->back_camera_type) = type;
            (front ? cfg->front_camera_color : cfg->back_camera_color) = color;
            (front ? cfg->front_camera_image : cfg->back_camera_image) = image;
        }
    }

    read_core_option("vita3k_psn_signed_in", "disabled", [](const char *value) {
        libretro.cfg->current_config.psn_signed_in = parse_enabled_option(value, false);
    });
}

RETRO_API size_t retro_serialize_size(void) {
    return 0; // Save states not supported
}

RETRO_API bool retro_serialize(void *data, size_t size) {
    (void)data;
    (void)size;
    return false;
}

RETRO_API bool retro_unserialize(const void *data, size_t size) {
    (void)data;
    (void)size;
    return false;
}

RETRO_API void retro_reset(void) {
    lr_log(RETRO_LOG_INFO,
        "retro_reset requested (game_loaded=%d, emuenv=%d) -> scheduling deferred reset\n",
        libretro.game_loaded ? 1 : 0,
        libretro.emuenv ? 1 : 0);
    libretro.reset_requested = true;
}

RETRO_API void retro_cheat_reset(void) {}

RETRO_API void retro_cheat_set(unsigned index, bool enabled, const char *code) {
    (void)index;
    (void)enabled;
    (void)code;
}

RETRO_API unsigned retro_get_region(void) {
    return RETRO_REGION_NTSC;
}

RETRO_API void *retro_get_memory_data(unsigned id) {
    (void)id;
    return nullptr;
}

RETRO_API size_t retro_get_memory_size(unsigned id) {
    (void)id;
    return 0;
}

RETRO_API void retro_set_controller_port_device(unsigned port, unsigned device) {
    const char *name = "Unknown";
    switch (device & RETRO_DEVICE_MASK) {
    case RETRO_DEVICE_NONE: name = "None"; break;
    case RETRO_DEVICE_JOYPAD: name = "Joypad"; break;
    case RETRO_DEVICE_ANALOG: name = "Analog"; break;
    case RETRO_DEVICE_POINTER: name = "Pointer"; break;
    }
    lr_log(RETRO_LOG_INFO, "Set controller port %u device %u (%s)\n", port, device, name);
}
