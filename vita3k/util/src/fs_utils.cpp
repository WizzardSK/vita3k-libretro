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

#include <cstdio>
#include <cstring>
#include <util/fs.h>
#include <util/string_utils.h>

#include <SDL3/SDL_iostream.h>

#include <cstdio>
#include <cstring>

namespace fs_utils {

fs::path construct_file_name(const fs::path &base_path, const fs::path &folder_path, const fs::path &file_name, const fs::path &extension) {
    fs::path full_file_path{ base_path / folder_path / file_name };
    if (!extension.empty())
        full_file_path.replace_extension(extension);

    return full_file_path.generic_path();
}

std::string path_to_utf8(const fs::path &path) {
    if constexpr (sizeof(fs::path::value_type) == sizeof(wchar_t)) {
        return string_utils::wide_to_utf(path.wstring());
    } else {
        return path.string();
    }
}

fs::path utf8_to_path(const std::string &str) {
    if constexpr (sizeof(fs::path::value_type) == sizeof(wchar_t)) {
        return fs::path{ string_utils::utf_to_wide(str) };
    } else {
        return fs::path{ str };
    }
}

fs::path path_concat(const fs::path &path1, const fs::path &path2) {
    return fs::path{ path1.native() + path2.native() };
}

void dump_data(const fs::path &path, const void *data, const std::streamsize size) {
    fs::ofstream of{ path, fs::ofstream::binary };
    if (!of.fail()) {
        of.write(static_cast<const char *>(data), size);
        of.close();
    }
}
template <typename T>
static bool read_data(const fs::path &path, std::vector<T> &data) {
    data.clear();
#ifdef BUILD_LIBRETRO
    // Plain stdio in the core: on Android SDL_IOFromFile takes a file that
    // fopen cannot open to the app's internal storage through JNI, which a
    // core has none of set up - a missing built-in shader in system/vita3k
    // brought RetroArch down with SIGTRAP instead of failing (sco8487)
    FILE *f = FOPEN(path.c_str(), "rb");
    if (!f)
        return false;
    char chunk[65536];
    size_t n;
    std::vector<char> bytes;
    while ((n = fread(chunk, 1, sizeof(chunk), f)) > 0)
        bytes.insert(bytes.end(), chunk, chunk + n);
    fclose(f);
    if (bytes.empty() || bytes.size() % sizeof(T))
        return false;
    data.resize(bytes.size() / sizeof(T));
    memcpy(data.data(), bytes.data(), bytes.size());
    return true;
#endif
    SDL_IOStream *file = SDL_IOFromFile(fs_utils::path_to_utf8(path).c_str(), "rb");
    if (!file) {
        return false;
    }

    // Get the size of the file
    const Sint64 size = SDL_GetIOSize(file);
    if (size <= 0) {
        SDL_CloseIO(file);
        return false;
    }

    // Resize the vector to fit the file content
    data.resize(size);

    // Read the content of the file
    if (SDL_ReadIO(file, data.data(), size) != size) {
        SDL_CloseIO(file);
        data.clear();
        return false;
    }

    SDL_CloseIO(file);
    return true;
}

bool read_data(const fs::path &path, std::vector<uint8_t> &data) { return read_data<uint8_t>(path, data); }
bool read_data(const fs::path &path, std::vector<int8_t> &data) { return read_data<int8_t>(path, data); }
bool read_data(const fs::path &path, std::vector<char> &data) { return read_data<char>(path, data); }

bool copy_directory_contents(const fs::path &src_path, const fs::path &dst_path, const fs::copy_options options) {
    try {
        if (!fs::is_directory(src_path))
            return false;

        fs::create_directories(dst_path);

        for (const auto &src : fs::recursive_directory_iterator(src_path)) {
            const auto relative_path = fs::relative(src.path(), src_path);
            const auto output_path = dst_path / relative_path;

            if (fs::is_directory(src)) {
                fs::create_directories(output_path);
            } else if (fs::is_regular_file(src)) {
                fs::create_directories(output_path.parent_path());
                fs::copy_file(src.path(), output_path, options);
            }
        }

        return true;
    } catch (const std::exception &) {
        return false;
    }
}

} // namespace fs_utils

#if defined(BUILD_LIBRETRO) && !defined(_WIN32)
FILE *(*libretro_fopen_hook)(const char *filename, const char *mode) = nullptr;

FILE *libretro_fopen(const char *filename, const char *mode) {
    if (libretro_fopen_hook && std::strstr(filename, "://"))
        return libretro_fopen_hook(filename, mode);
    return fopen(filename, mode);
}
#endif
