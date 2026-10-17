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

#include "libretro_installer.h"

#include <functional>
#include <map>
#include <string>
#include <vector>

struct EmuEnvState;

// The Vita's users (ux0/user/<id>/user.xml, upstream's accounts) in the core
// options, under Accounts: the one a game starts with, one created, one
// removed, and their names from system/vita3k/account_name.txt.

// How the options reach the frontend, set by the core's frontend glue: the
// account options declared beside the core's own (answering with each key's
// value), and a key's value read and set there
void set_account_option_callbacks(ContentOptionsHandler declare,
    std::function<std::string(const std::string &)> get,
    std::function<void(const std::string &, const std::string &)> set);

// At a game's start, before its user data is used: the users read, one made
// when there is none, the names from account_name.txt applied, the user chosen
// in Active Account activated, and the options declared
void libretro_accounts_start(EmuEnvState &emuenv);

// After the frontend's options changed: Create Account and Remove Account
// carried out, and Rename Active Account turned into a request for the name
// entry
void libretro_accounts_options_changed(EmuEnvState &emuenv);

// Rename Active Account asked for since the last call: the active account's
// id and its name now, for the name entry to start from
bool libretro_accounts_take_rename_request(const EmuEnvState &emuenv, std::string &id, std::string &name);

// The name entry's result: the account renamed (up to 16 characters), saved,
// and account_name.txt and the options written again. False when the account
// is gone.
bool libretro_accounts_rename(EmuEnvState &emuenv, const std::string &id, const std::string &name);
