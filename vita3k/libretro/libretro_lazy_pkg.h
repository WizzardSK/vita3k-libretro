#pragma once

#include <util/fs.h>

#include <string>

// A game's PKG run without installing it. The package's files are laid out in
// ux0/app/<title id> as placeholders - the PFS metadata, the executables and
// small files in full, every other file only as long as the PFS mount needs to
// identify it, the rest of it sparse - and each one is decrypted the first time
// the game opens it (vfs::host_file_hook). So a game starts in seconds, and
// only what it reads is ever written out. unmount() removes the lot.
namespace lazy_pkg {

// Lays out the PKG's files in app_dir and mounts its PFS with the license.
// False, with the reason in error, if the package cannot be run this way; the
// caller then installs it as usual.
bool mount(const fs::path &pkg_path, const fs::path &app_dir, const std::string &zrif, std::string &error);

// Persistent Cache: the blocks decrypted while a game runs are also written
// under cache_root/<title id>, and read from there the next time, across
// sessions; empty for none (Run Without Installing). Set before mount().
void set_cache_root(const fs::path &cache_root);

// What a PKG is, from its param.sfo: title ID, category ("gd" a game, "gp"
// an update, "ac" DLC) and version
struct PkgInfo {
    std::string title_id;
    std::string category;
    std::string version;
    std::string content_id;
};
bool pkg_info(const fs::path &pkg_path, PkgInfo &info);

// An update's PKG laid over the mounted game: its files are read out of it
// (decrypted as they are read, with the game's license) in place of the
// game's, nothing installed
bool mount_update(const fs::path &pkg_path, const std::string &zrif, std::string &error);

// A DLC's PKG laid out in ux0/addcont/<title id>/<DLC id> the same way, read
// out of its PKG with its own license; not if that DLC is installed already
bool mount_dlc(const fs::path &pkg_path, const std::string &content_id, const std::string &zrif, std::string &error);

// Removes what mount() laid out, and stops decrypting on open
void unmount();

bool mounted();

} // namespace lazy_pkg
