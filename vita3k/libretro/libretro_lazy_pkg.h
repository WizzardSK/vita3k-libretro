#pragma once

#include <util/fs.h>

#include <cstdint>
#include <string>
#include <vector>

// A game run without installing it, out of its PKG, VPK/ZIP or folder (the
// source). Its files are laid out in ux0/app/<title id>: the PFS metadata in
// full, the executables and small files decrypted into their place, every other
// file a placeholder of its size with no data (a hole). The PFS mount tells the
// files apart by their first sectors, read out of the source into memory. A
// placeholder opened to read is served out of the source a block at a time,
// decrypted as it is read (open_file_hook), and nothing of it is written; one
// opened to write, read whole (vfs::host_file_hook) or with one hash over all of
// it (an icv file) is decrypted into its place first. With Persistent Cache the
// blocks read are also kept for the next run. unmount() removes the lot.
namespace lazy_pkg {

// How an error starts when the drive has no room (a run without installing, with or
// without Persistent Cache, or an install): the content is then not run another way
inline constexpr const char *NO_ROOM = "not enough free space:";

// Lays out the PKG's files in app_dir and mounts its PFS with the license.
// False, with the reason in error, if the package cannot be run this way; the
// caller then installs it as usual.
bool mount(const fs::path &pkg_path, const fs::path &app_dir, const std::string &zrif, std::string &error);
// A game folder (extracted, or a NoNpDrm dump with its work.bin) run the same way, read
// where it lies; zrif only for an encrypted one
bool mount_folder(const fs::path &dir, const fs::path &app_dir, const std::string &zrif, std::string &error);
// A VPK/ZIP run the same way, from the game's folder in it (prefix: "" or
// ending in '/'); zrif only for an encrypted (NoNpDrm) game
bool mount_archive(const fs::path &archive_path, const std::string &prefix, const fs::path &app_dir,
    const std::string &zrif, std::string &error);

// Persistent Cache: the blocks decrypted while a game runs are also written
// under cache_root/<title id>, and read from there the next time, across
// sessions; empty for none (Run Without Installing). Set before mount().
void set_cache_root(const fs::path &cache_root);
// Whether one is set: Persistent Cache rather than keeping nothing
bool has_cache_root();
// The space a file takes on the disk: of a sparse file, only its parts written
std::uint64_t disk_size(const fs::path &file);

// Whether files in dir can have holes: parts of the right size that take no
// disk space until written. Run Without Installing and Persistent Cache lay a
// game out as such files; where they cannot have holes (FAT32, exFAT) every
// file takes its full size, and the two save nothing over an install
// (sco8487). Tried with a file written and removed there, and the answer
// kept in dir/libretro_pkg/holes until dir is on another file system.
bool holes_supported(const fs::path &dir);

// A PKG installed in dir (ux0/app, ux0/patch or ux0/addcont), each file read
// out of it, decrypted and written once, where upstream's install_pkg writes
// the package out encrypted and decrypts that into a second copy. Written
// encrypted is only the PFS metadata (sce_pfs), deleted at the end; an icv
// file is decrypted whole in memory. False, with the reason in error, and
// nothing left.
bool install(const fs::path &pkg_path, const fs::path &dir, const std::string &zrif, std::string &error);

// pkg_sfo, pkg_info, mount_update and mount_dlc take a VPK/ZIP or a folder as
// well as a PKG
bool is_archive(const fs::path &path);
// The content's param.sfo
bool pkg_sfo(const fs::path &pkg_path, std::vector<std::uint8_t> &sfo);

// What a PKG is, from its param.sfo: title ID, category ("gd" a game, "gp"
// an update, "ac" DLC) and version
struct PkgInfo {
    std::string title_id;
    std::string category;
    std::string version;
    std::string content_id;
    std::string title;
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
