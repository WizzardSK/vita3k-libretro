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

#include <cctype>
#include <util/string_utils.h>

#include <SDL3/SDL_iostream.h>

#include <cstdio>
#include <cstring>
#include <chrono>

namespace fs_utils {

fs::path construct_file_name(const fs::path &base_path, const fs::path &folder_path, const fs::path &file_name, const fs::path &extension) {
    // std's operator/ replaces on a rooted rhs and adds a separator for an empty one, unlike Boost
    fs::path full_file_path{ base_path };
    for (const auto &part : { folder_path.relative_path(), file_name.relative_path() }) {
        if (!part.empty())
            full_file_path /= part;
    }
    if (!extension.empty())
        full_file_path.replace_extension(extension);

    return generic_path(full_file_path);
}

fs::path generic_path(const fs::path &path) {
    return path.generic_string<fs::path::value_type>();
}

std::time_t to_time_t(const fs::file_time_type time) {
    // MSVC's file_clock only has to_utc, and libc++ lacks clock_cast
#ifdef _MSVC_STL_VERSION
    const auto sys_time = std::chrono::clock_cast<std::chrono::system_clock>(time);
#else
    const auto sys_time = fs::file_time_type::clock::to_sys(time);
#endif
    return std::chrono::system_clock::to_time_t(std::chrono::time_point_cast<std::chrono::system_clock::duration>(sys_time));
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

bool dump_data(const fs::path &path, const void *data, const std::streamsize size) {
    std::ofstream of{ path, std::ofstream::binary };
    if (of.fail())
        return false;
    of.write(static_cast<const char *>(data), size);
    of.close();
    return !of.fail();
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

// A URI: scheme:// - or scheme:/, as boost's path leaves one with its two
// slashes merged (libretro_vfs.cpp puts them back)
static bool libretro_is_uri(const char *filename) {
    const char *colon = std::strstr(filename, ":/");
    if (!colon || colon - filename < 2 || !std::isalpha(static_cast<unsigned char>(filename[0])))
        return false;
    for (const char *c = filename + 1; c < colon; c++)
        if (!std::isalnum(static_cast<unsigned char>(*c)) && *c != '+' && *c != '-' && *c != '.')
            return false;
    return true;
}

FILE *libretro_fopen(const char *filename, const char *mode) {
    if (libretro_fopen_hook && libretro_is_uri(filename))
        return libretro_fopen_hook(filename, mode);
    return fopen(filename, mode);
}
#endif
