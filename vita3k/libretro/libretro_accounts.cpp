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

#include "libretro_accounts.h"
#include "libretro_log.h"

#include <app/functions.h>
#include <app/state.h>
#include <config/state.h>
#include <emuenv/state.h>
#include <io/state.h>
#include <util/fs.h>
#include <util/log.h>

#include <fmt/format.h>

#include <fstream>
#include <sstream>

static ContentOptionsHandler s_declare;
static std::function<std::string(const std::string &)> s_get;
static std::function<void(const std::string &, const std::string &)> s_set;

// The user the running game was started as: Remove Account does not offer it
static std::string s_running_id;

static constexpr const char *ACTIVE_KEY = "vita3k_account_active";
static constexpr const char *CREATE_KEY = "vita3k_account_create";
static constexpr const char *REMOVE_KEY = "vita3k_account_remove";
static constexpr const char *RENAME_KEY = "vita3k_account_rename";

// Rename Active Account turned on, waiting for the name entry to take it
static bool s_rename_requested = false;
static constexpr const char *REMOVE_NONE = "none";

// The console's limit for a user name, in characters
static constexpr size_t NAME_MAX_CHARS = 16;

void set_account_option_callbacks(ContentOptionsHandler declare,
    std::function<std::string(const std::string &)> get,
    std::function<void(const std::string &, const std::string &)> set) {
    s_declare = std::move(declare);
    s_get = std::move(get);
    s_set = std::move(set);
}

static fs::path names_file(const EmuEnvState &emuenv) {
    return emuenv.vita_fs_path / "account_name.txt";
}

static std::string trim(const std::string &text) {
    const size_t begin = text.find_first_not_of(" \t\r\n");
    if (begin == std::string::npos)
        return {};
    const size_t end = text.find_last_not_of(" \t\r\n");
    return text.substr(begin, end - begin + 1);
}

// The first NAME_MAX_CHARS characters of a UTF-8 name, cut between characters
static std::string limit_name(const std::string &name) {
    size_t chars = 0;
    for (size_t i = 0; i < name.size(); i++) {
        if ((static_cast<unsigned char>(name[i]) & 0xC0) != 0x80) {
            if (chars == NAME_MAX_CHARS)
                return name.substr(0, i);
            chars++;
        }
    }
    return name;
}

static std::string label_of(const app::User &user) {
    return fmt::format("{} ({})", user.name, user.id);
}

// account_name.txt: a comment, then "<id> = <name>" for each user there is
static void write_names_file(const EmuEnvState &emuenv) {
    std::ofstream out(names_file(emuenv).string(), std::ios::trunc);
    out << "# Account names. One line per account: <id> = <name>, the name up to " << NAME_MAX_CHARS << " characters.\n";
    out << "# Change a name here and the account has it the next time a game starts.\n";
    out << "# This file is written again at each start with the accounts there are.\n";
    for (const auto &[id, user] : emuenv.app.user_list.users)
        out << id << " = " << user.name << "\n";
}

// The names in account_name.txt given to the users they name
static void apply_names_file(EmuEnvState &emuenv) {
    std::ifstream in(names_file(emuenv).string());
    if (!in)
        return;
    std::string line;
    while (std::getline(in, line)) {
        line = trim(line);
        if (line.empty() || line.front() == '#')
            continue;
        const size_t equals = line.find('=');
        if (equals == std::string::npos)
            continue;
        const std::string id = trim(line.substr(0, equals));
        const std::string name = limit_name(trim(line.substr(equals + 1)));
        auto it = emuenv.app.user_list.users.find(id);
        if (it == emuenv.app.user_list.users.end() || name.empty() || it->second.name == name)
            continue;
        it->second.name = name;
        app::save_user(emuenv, id);
        LOG_INFO("Account {} named {} from account_name.txt", id, name);
    }
}

static std::vector<ContentOption> account_options(const EmuEnvState &emuenv) {
    const auto &users = emuenv.app.user_list.users;
    std::vector<ContentOption> options;

    ContentOption active;
    active.key = ACTIVE_KEY;
    active.category = "accounts";
    active.label = "Active Account";
    active.info = "The account a game starts as, with its own saves and trophies. A change applies the next time the game is started or reset, as on the console the user is chosen before a game runs.";
    for (const auto &[id, user] : users)
        active.values.emplace_back(id, label_of(user));
    active.default_value = users.empty() ? std::string("00") : users.begin()->first;
    options.push_back(std::move(active));

    ContentOption create;
    create.key = CREATE_KEY;
    create.category = "accounts";
    create.label = "Create Account";
    create.info = "Creates an account when this menu is exited, named Player 2, Player 3 and so on, and makes it the Active Account. It appears in the lists once the menu has been exited and opened again.";
    create.values = { { "disabled", "OFF" }, { "enabled", "ON" } };
    create.default_value = "disabled";
    options.push_back(std::move(create));

    ContentOption rename;
    rename.key = RENAME_KEY;
    rename.category = "accounts";
    rename.label = "Rename Active Account";
    rename.info = "Opens the name entry for the Active Account when this menu is exited, and returns to OFF. The name so far is shown as a notification over the game, so the frontend's on-screen notifications have to be on.\n\nWith a pad: Up and Down change the last character, Right adds one, Left removes one, Start accepts, Select cancels.\n\nWith a keyboard: type, Backspace removes, Enter accepts, Escape cancels.\n\nUp to 16 characters. The game gets no input while the entry is open. Names can also be changed in system/vita3k/account_name.txt.";
    rename.values = { { "disabled", "OFF" }, { "enabled", "ON" } };
    rename.default_value = "disabled";
    options.push_back(std::move(rename));

    ContentOption remove;
    remove.key = REMOVE_KEY;
    remove.category = "accounts";
    remove.label = "Remove Account";
    remove.info = "Removes the selected account (ux0/user/<id>) when this menu is exited. The option shows Nothing again on return to the menu.\n\nThe Active Account cannot be removed, nor can the account the running game was started with until that game is closed.\n\nWARNING: removing an account also permanently deletes its saves and trophies in every game. Back them up first.";
    remove.values.emplace_back(REMOVE_NONE, "Nothing");
    const std::string active_id = s_get ? s_get(ACTIVE_KEY) : std::string{};
    for (const auto &[id, user] : users) {
        if (id != active_id && id != s_running_id)
            remove.values.emplace_back(id, label_of(user));
    }
    remove.default_value = REMOVE_NONE;
    options.push_back(std::move(remove));

    return options;
}

static void declare(const EmuEnvState &emuenv) {
    if (s_declare)
        s_declare(account_options(emuenv));
}

void libretro_accounts_start(EmuEnvState &emuenv) {
    app::load_users(emuenv);
    auto &users = emuenv.app.user_list.users;

    // The first start: user 00, whose folder earlier builds of the core used
    // without a user.xml, as upstream's first user is made
    if (users.empty())
        app::create_user(emuenv, "Vita3K");

    apply_names_file(emuenv);

    // Declared once so that Active Account has its values at the frontend
    // before it is read
    declare(emuenv);
    std::string id = s_get ? s_get(ACTIVE_KEY) : std::string{};
    if (!users.contains(id))
        id = users.begin()->first;

    app::activate_user(emuenv, id);
    emuenv.cfg.user_id = id;
    s_running_id = id;
    LOG_INFO("Account {} ({}) active", id, emuenv.io.user_name);

    write_names_file(emuenv);
    declare(emuenv);
}

void libretro_accounts_options_changed(EmuEnvState &emuenv) {
    if (!s_get || !s_set)
        return;
    auto &users = emuenv.app.user_list.users;
    bool changed = false;

    if (s_get(CREATE_KEY) == "enabled") {
        const std::string id = app::create_user(emuenv, fmt::format("Player {}", users.size() + 1));
        LOG_INFO("Account {} created", id);
        s_set(CREATE_KEY, "disabled");
        s_set(ACTIVE_KEY, id);
        changed = true;
    }

    const std::string remove_id = s_get(REMOVE_KEY);
    if (!remove_id.empty() && remove_id != REMOVE_NONE) {
        if (users.contains(remove_id) && remove_id != s_get(ACTIVE_KEY) && remove_id != s_running_id) {
            app::delete_user(emuenv, remove_id);
            LOG_INFO("Account {} removed", remove_id);
        }
        s_set(REMOVE_KEY, REMOVE_NONE);
        changed = true;
    }

    if (s_get(RENAME_KEY) == "enabled") {
        s_set(RENAME_KEY, "disabled");
        s_rename_requested = true;
    }

    if (changed) {
        write_names_file(emuenv);
        declare(emuenv);
    }
}

bool libretro_accounts_take_rename_request(const EmuEnvState &emuenv, std::string &id, std::string &name) {
    if (!s_rename_requested)
        return false;
    s_rename_requested = false;
    const auto &users = emuenv.app.user_list.users;
    id = s_get ? s_get(ACTIVE_KEY) : std::string{};
    if (!users.contains(id))
        id = s_running_id;
    const auto it = users.find(id);
    if (it == users.end())
        return false;
    name = it->second.name;
    return true;
}

bool libretro_accounts_rename(EmuEnvState &emuenv, const std::string &id, const std::string &name) {
    auto it = emuenv.app.user_list.users.find(id);
    if (it == emuenv.app.user_list.users.end())
        return false;
    it->second.name = limit_name(name);
    app::save_user(emuenv, id);
    // the running game's user: its name as the game asks for it from now on
    if (id == s_running_id)
        emuenv.io.user_name = it->second.name;
    LOG_INFO("Account {} renamed {}", id, it->second.name);
    write_names_file(emuenv);
    declare(emuenv);
    return true;
}
