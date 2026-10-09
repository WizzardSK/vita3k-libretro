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

bool read_file(VitaIoDevice device, FileBuffer &buf, const fs::path &vita_fs_path, const fs::path &vfs_file_path);
bool read_app_file(FileBuffer &buf, const fs::path &vita_fs_path, const std::string &app_path, const fs::path &vfs_file_path);
SceSize get_directory_used_size(const VitaIoDevice device, const std::string &vfs_path, const fs::path &vita_fs_path);
} // namespace vfs
