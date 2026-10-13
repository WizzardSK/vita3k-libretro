// Vita3K libretro core
// Copyright (C) 2026 Vita3K team
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.

#include "libretro_vfs.h"

#include <cctype>
#include <cstdio>
#include <cstring>

#if !defined(_WIN32)
#include <sys/types.h>
#endif

static const retro_vfs_interface *s_vfs = nullptr;
static unsigned s_vfs_version = 0;

bool lr_vfs_is_uri(const std::string &path) {
    // RFC 3986 scheme: a letter, then letters, digits, + - or .; then ://
    if (path.empty() || !std::isalpha(static_cast<unsigned char>(path[0])))
        return false;
    for (size_t i = 1; i < path.size(); i++) {
        const char c = path[i];
        if (c == ':')
            return path.compare(i, 3, "://") == 0;
        if (!std::isalnum(static_cast<unsigned char>(c)) && c != '+' && c != '-' && c != '.')
            return false;
    }
    return false;
}

#if !defined(_WIN32)
// FILE* over a VFS file handle, so code that reads with fread/fseek/ftell
// works on a URI. The position after a seek is taken from tell(): the
// frontend's seek() returns 0 rather than the new position.
namespace {
struct VfsCookie {
    retro_vfs_file_handle *handle;
};

std::int64_t vfs_read(void *c, char *buf, size_t size) {
    return s_vfs->read(static_cast<VfsCookie *>(c)->handle, buf, size);
}

std::int64_t vfs_write(void *c, const char *buf, size_t size) {
    return s_vfs->write(static_cast<VfsCookie *>(c)->handle, buf, size);
}

std::int64_t vfs_seek(void *c, std::int64_t offset, int whence) {
    retro_vfs_file_handle *handle = static_cast<VfsCookie *>(c)->handle;
    const int seek_position = whence == SEEK_SET ? RETRO_VFS_SEEK_POSITION_START
        : whence == SEEK_CUR                   ? RETRO_VFS_SEEK_POSITION_CURRENT
                                               : RETRO_VFS_SEEK_POSITION_END;
    if (s_vfs->seek(handle, offset, seek_position) < 0)
        return -1;
    return s_vfs->tell(handle);
}

int vfs_close(void *c) {
    VfsCookie *cookie = static_cast<VfsCookie *>(c);
    const int result = s_vfs->close(cookie->handle);
    delete cookie;
    return result;
}

#if defined(__APPLE__)
int apple_read(void *c, char *buf, int size) { return static_cast<int>(vfs_read(c, buf, size)); }
int apple_write(void *c, const char *buf, int size) { return static_cast<int>(vfs_write(c, buf, size)); }
fpos_t apple_seek(void *c, fpos_t offset, int whence) { return vfs_seek(c, offset, whence); }
#elif defined(__ANDROID__)
// bionic has fopencookie only from API 32; funopen64 from 24
int bionic_read(void *c, char *buf, int size) { return static_cast<int>(vfs_read(c, buf, size)); }
int bionic_write(void *c, const char *buf, int size) { return static_cast<int>(vfs_write(c, buf, size)); }
off64_t bionic_seek(void *c, off64_t offset, int whence) { return vfs_seek(c, offset, whence); }
#else
ssize_t cookie_read(void *c, char *buf, size_t size) { return vfs_read(c, buf, size); }
ssize_t cookie_write(void *c, const char *buf, size_t size) { return vfs_write(c, buf, size); }
int cookie_seek(void *c, off64_t *offset, int whence) {
    const std::int64_t position = vfs_seek(c, *offset, whence);
    if (position < 0)
        return -1;
    *offset = position;
    return 0;
}
#endif
} // namespace

static FILE *lr_vfs_fopen(const char *path, const char *mode) {
    if (!s_vfs)
        return nullptr;
    unsigned access = RETRO_VFS_FILE_ACCESS_READ;
    if (std::strchr(mode, 'w'))
        access = RETRO_VFS_FILE_ACCESS_WRITE;
    else if (std::strchr(mode, 'a'))
        access = RETRO_VFS_FILE_ACCESS_WRITE | RETRO_VFS_FILE_ACCESS_UPDATE_EXISTING;
    if (std::strchr(mode, '+'))
        access = RETRO_VFS_FILE_ACCESS_READ_WRITE | (std::strchr(mode, 'r') ? RETRO_VFS_FILE_ACCESS_UPDATE_EXISTING : 0);
    retro_vfs_file_handle *handle = s_vfs->open(path, access, RETRO_VFS_FILE_ACCESS_HINT_NONE);
    if (!handle)
        return nullptr;
    VfsCookie *cookie = new VfsCookie{ handle };
#if defined(__APPLE__)
    FILE *file = funopen(cookie, apple_read, apple_write, apple_seek, vfs_close);
#elif defined(__ANDROID__)
    FILE *file = funopen64(cookie, bionic_read, bionic_write, bionic_seek, vfs_close);
#else
    cookie_io_functions_t io{ cookie_read, cookie_write, cookie_seek, vfs_close };
    FILE *file = fopencookie(cookie, mode, io);
#endif
    if (!file)
        vfs_close(cookie);
    return file;
}

// util/fs.h: FOPEN asks this for a URI
extern FILE *(*libretro_fopen_hook)(const char *path, const char *mode);
#endif

void lr_vfs_init(retro_environment_t cb) {
    retro_vfs_interface_info info{ 3, nullptr };
    if (cb(RETRO_ENVIRONMENT_GET_VFS_INTERFACE, &info) && info.iface) {
        s_vfs = info.iface;
        s_vfs_version = info.required_interface_version;
#if !defined(_WIN32)
        libretro_fopen_hook = lr_vfs_fopen;
#endif
    }
}

bool lr_vfs_stat(const std::string &path, bool *is_directory, std::uint64_t *size) {
    if (!s_vfs || s_vfs_version < 3)
        return false;
    int32_t file_size = 0;
    const int flags = s_vfs->stat(path.c_str(), &file_size);
    if (!(flags & RETRO_VFS_STAT_IS_VALID))
        return false;
    if (is_directory)
        *is_directory = (flags & RETRO_VFS_STAT_IS_DIRECTORY) != 0;
    if (size) {
        // stat reports 32 bits; for anything larger the size comes from the file
        *size = static_cast<std::uint32_t>(file_size);
        if (!(flags & RETRO_VFS_STAT_IS_DIRECTORY)) {
            if (retro_vfs_file_handle *handle = s_vfs->open(path.c_str(), RETRO_VFS_FILE_ACCESS_READ, RETRO_VFS_FILE_ACCESS_HINT_NONE)) {
                const std::int64_t real = s_vfs->size(handle);
                if (real >= 0)
                    *size = static_cast<std::uint64_t>(real);
                s_vfs->close(handle);
            }
        }
    }
    return true;
}

std::vector<std::string> lr_vfs_list(const std::string &dir) {
    std::vector<std::string> entries;
    if (!s_vfs || s_vfs_version < 3)
        return entries;
    retro_vfs_dir_handle *handle = s_vfs->opendir(dir.c_str(), true);
    if (!handle)
        return entries;
    const std::string base = !dir.empty() && dir.back() == '/' ? dir : dir + "/";
    while (s_vfs->readdir(handle)) {
        const char *name = s_vfs->dirent_get_name(handle);
        if (!name || !std::strcmp(name, ".") || !std::strcmp(name, ".."))
            continue;
        entries.push_back(base + name);
    }
    s_vfs->closedir(handle);
    return entries;
}

bool lr_vfs_read_file(const std::string &path, std::string &out) {
    if (!s_vfs)
        return false;
    retro_vfs_file_handle *handle = s_vfs->open(path.c_str(), RETRO_VFS_FILE_ACCESS_READ, RETRO_VFS_FILE_ACCESS_HINT_NONE);
    if (!handle)
        return false;
    const std::int64_t size = s_vfs->size(handle);
    bool ok = size >= 0;
    if (ok) {
        out.resize(static_cast<size_t>(size));
        ok = size == 0 || s_vfs->read(handle, out.data(), static_cast<std::uint64_t>(size)) == size;
    }
    s_vfs->close(handle);
    return ok;
}
