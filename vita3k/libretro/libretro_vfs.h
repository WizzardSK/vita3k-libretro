// Vita3K libretro core
// Copyright (C) 2026 Vita3K team
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#pragma once

// Content through the frontend's VFS: a path RetroArch hands over as a URI
// (saf://..., the Android Storage Access Framework of the Play Store build)
// cannot be opened, stat'ed or listed natively. These go through RetroArch's
// VFS for such paths; FOPEN does too (util/fs.h), so the archive and PKG
// readers work on them unchanged. Ordinary paths are left to the OS.

#include "libretro.h"

#include <cstdint>
#include <string>
#include <vector>

// Asks the frontend for its VFS (retro_set_environment).
void lr_vfs_init(retro_environment_t cb);

// A path of the form scheme://..., which only the frontend can open.
bool lr_vfs_is_uri(const std::string &path);

// Whether path exists, and if so whether it is a directory and its size.
bool lr_vfs_stat(const std::string &path, bool *is_directory, std::uint64_t *size);

// The entries of a directory, as full paths (without . and ..).
std::vector<std::string> lr_vfs_list(const std::string &dir);

// The whole file.
bool lr_vfs_read_file(const std::string &path, std::string &out);
