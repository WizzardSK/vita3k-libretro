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

#include <util/fs.h>
#include <util/types.h>

#include <functional>
#include <string>
#include <vector>

enum class VitaIoDevice : int;

namespace vfs {

using FileBuffer = std::vector<SceUInt8>;

// Called with the host path of a file about to be opened or read, if set. The
// libretro core runs a PKG without installing it: its files are placeholders
// until first read, and this is where one is decrypted.
extern std::function<void(const fs::path &)> host_file_hook;
// Called as a file is opened through the IO functions (open_file), with its
// SCE_O_* flags; host_file_hook is for whole-file reads (read_file)
extern std::function<void(const fs::path &, int)> host_open_hook;
// Given every host path a guest path is turned into, if set, and returns the one
// to use: the libretro core lays an installed game's update, kept in
// ux0/patch/<title>, over its files this way
extern std::function<fs::path(const fs::path &)> host_path_hook;
// Given the host path of a directory being opened, if set: the names the core
// lays over it (an update's files the game's folder has not), listed after the
// directory's own
extern std::function<std::vector<std::string>(const fs::path &)> host_dir_hook;
// What the user makes, kept outside the Vita's storage: the libretro core
// keeps it in RetroArch's save directory, laid out as in the storage in this
// folder (user_data_root / "ux0/user/..."). The paths, relative to the
// storage: the accounts with their saves and trophies and the play times
// (ux0/user), the photo album (ux0/picture) and the registry
// (vd0/registry/system.dreg). Empty (the default): in the storage, as upstream.
extern fs::path user_data_root;
extern const std::vector<fs::path> user_data_paths;
// A host path in the storage under one of user_data_paths, moved to
// user_data_root; any other path as it is
fs::path user_data_redirect(const fs::path &vita_fs_path, const fs::path &host);
// The host path of a path relative to the storage, wherever it is kept
fs::path user_data_path(const fs::path &vita_fs_path, const fs::path &relative);
// The host folder of an account's "savedata" or "trophy", wherever it is kept
fs::path user_data_dir(const fs::path &vita_fs_path, const std::string &user_id, const std::string &kind);

bool read_file(VitaIoDevice device, FileBuffer &buf, const fs::path &vita_fs_path, const fs::path &vfs_file_path);
bool read_app_file(FileBuffer &buf, const fs::path &vita_fs_path, const std::string &app_path, const fs::path &vfs_file_path);
SceSize get_directory_used_size(const VitaIoDevice device, const std::string &vfs_path, const fs::path &vita_fs_path);
} // namespace vfs
