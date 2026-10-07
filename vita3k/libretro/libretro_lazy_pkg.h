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

// Removes what mount() laid out, and stops decrypting on open
void unmount();

bool mounted();

} // namespace lazy_pkg
