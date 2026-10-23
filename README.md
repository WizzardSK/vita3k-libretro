# Vita3K libretro core

A [libretro](https://www.libretro.com/) core of [Vita3K](https://github.com/Vita3K/Vita3K), the experimental PlayStation Vita emulator, for RetroArch and other libretro frontends. It is built on upstream Vita3K and on [danprice142's libretro port](https://github.com/danprice142/Vita3K-libretro). The core is currently on Vita3K v0.2.1 build 4123, commit a5aa96572 of 5 October 2026.

This repository is the core only: the standalone Vita3K (its Qt interface, updater and Android app) is not part of it. For that, and for compatibility lists, see [Vita3K](https://vita3k.org/).

## Downloads

The core is built by libretro's buildbot for Linux (x86_64, aarch64) and Android (arm64, x86_64), and is installed from RetroArch: Online Updater > Core Downloader. Every push to the `libretro` branch is also built in [Actions](https://github.com/WizzardSK/vita3k-libretro/actions/workflows/libretro.yml), Windows x86_64 included; the builds are the artifacts of a run, and downloading them needs a GitHub login.

## Installation

Each build from Actions has two folders:

- `cores/` - the core (`vita3k_libretro.so`, `vita3k_libretro.dll` or `vita3k_libretro_android.so`), for RetroArch's cores directory.
- `info/` - its core info file, for RetroArch's info directory.

The emulator's data, built-in shaders and the icons of its system dialogs are inside the core: it unpacks them into `system/vita3k/` the first time it starts, and again after an update of the core.

The PS Vita firmware is required. Download it from PlayStation's website and put it in `system/vita3k/`. The three packages are told apart by their file names, in any case:

- the system firmware - any `.pup` without `preinst` or `font` in its name (`PSP2UPDAT.PUP`, `PSVUPDAT.PUP`, `firmware.pup`)
- the preinstalled package - a `.pup` with `preinst` in its name (`preinst.pup`, `PSP2UPDAT_PREINST.PUP`)
- the fonts, optional - a `.pup` with `font` in its name (`font.pup`, `PSP2UPDAT_FONT.PUP`)

All three download under the same name, so rename the preinstalled package and the fonts as you save them.

Then turn on Core Options > System > Install Firmware: when the menu is closed, the core installs every part it finds there, over what is installed, so a newer system firmware `.pup` updates it. Core options are there only while content runs: with no firmware yet, a game still loads (it waits on a black screen, and the core says which part is missing), so turn the option on then and close and load the game again once it is done. Nothing is installed at a start by itself.

A `.pup` can also be loaded from RetroArch like a game, under any name: the core installs it, says which parts of the firmware are still missing, and starts nothing. Load each of the three that way and then a game.

## Content

A game is loaded as a `.pkg`, `.vpk` or `.zip`, as a game folder, or through the folder's `eboot.bin`. With Run Method set to Direct or Direct with Cache (the default is the first), the game is read where it lies as it goes, whichever of these it is; with Installed it is installed into `system/vita3k/` the first time it is started, and started from there afterwards. Where the system folder is on a file system without sparse files (FAT32, exFAT), Run Method offers Installed only. A game's updates and DLC (PKG, VPK or ZIP) beside it, or inside its folder, are listed in the core options under Content (with Include Subdirectories, also in every directory below), and Remove Data, when turned on, deletes what the core wrote for the running title as it is closed or reset (its install, update and DLC, persistent cache and shader cache; saves stay). A DLC turned off, or an installed update another version or None is chosen over, is set aside in `ux0/libretro_pkg/off` and comes back when chosen again. Where things go: an installed game in `ux0/app/<title ID>`, its update in `ux0/patch/<title ID>`, its DLC in `ux0/addcont/<title ID>`, and Direct with Cache's persistent cache in `system/vita3k/cache/pkg`. The core options' Trophies category lists the running game's trophies, which are kept in `ux0/user/<account>/trophy`, and a trophy earned while playing is announced over the picture with its icon, as in the standalone.

A game, update or DLC can also be loaded as a `.pkg`, with its license next to it: `work.bin`, `<pkg name>.rif`, or the zRIF in `<pkg name>.zrif`. Run Method says whether it is run directly (it starts in seconds and its files are decrypted from the PKG as the game reads them) or installed into `ux0/app`; an update or DLC loaded on its own is installed (Installed in Content, whatever the Run Method).

## Requirements

The core renders with Vulkan (1.1 or later) on RetroArch's own device, or with OpenGL. Set RetroArch's video driver to `vulkan` (or `glcore`).

## Controls

The pad is the Vita's buttons and sticks. Games that use the gyroscope and accelerometer (Gravity Rush, for one) get them from RetroArch's sensor interface wherever RetroArch has sensors to give: on Android devices and with controllers whose driver reports them. Elsewhere they get no motion.

## Core options

- **GPU**: renderer, internal resolution, screen filter (bilinear, nearest, bicubic, FXAA, FSR), anisotropic filtering, asynchronous pipeline compilation, the shader compile overlay, memory mapping, high-accuracy rendering, surface sync, V-Sync, FPS hack.
- **CPU**: CPU optimizations.
- **System**: PS TV mode, modules mode, confirm button, system language, date format, time format, file loading delay. The date and time are the host's, as in standalone Vita3K.
- **Modules**: the firmware's modules (`vs0/sys/external`), each on or off, loaded when Modules Mode (in System) is Auto & Manual or Manual; listed only then. Saved per game with RetroArch's game options, as upstream keeps them per game.
- **Audio**: volume, NGS audio engine.
- **Camera**: what the front and back cameras see: RetroArch's camera (Host Camera; it needs Settings > Privacy > Camera Access on, and a camera driver for the platform), an image (`system/vita3k/camera/front.png` or `back.png`, also `.jpg`), or a solid colour.
- **Network**: PSN signed in, HTTP (on or off, timeout and read-end attempts and sleeps), the adhoc address among the host's network interfaces.
- **Accounts**: the account a game starts as (Active Account), Create Account, Rename Active Account (a name entry by pad or keyboard, shown as RetroArch's notification) and Remove Account. Each account (`ux0/user/<id>`) has its own saves and trophies. Their names are in `system/vita3k/account_name.txt`, one `<id> = <name>` line each, which the core writes at each start; change a name there and the account has it the next time a game starts.

## Building

The core is built with CMake, as Vita3K is. The [workflow](.github/workflows/libretro.yml) shows the full setup for each platform; on Linux:

```sh
git clone --recursive -b libretro https://github.com/WizzardSK/vita3k-libretro.git
cd vita3k-libretro
cmake --preset linux-ninja-clang -DBUILD_LIBRETRO=ON -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
  -DCMAKE_LINKER_TYPE=LLD -DCMAKE_SHARED_LINKER_FLAGS=-Wl,-Bsymbolic -DVITA3K_FORCE_CUSTOM_BOOST=ON
cmake --build build/linux-ninja-clang --config Release --target vita3k_libretro
```

`.gitlab-ci.yml` is the recipe for libretro's buildbot.

## Updating from upstream

Upstream Vita3K is merged in as it is. `upstream.version` holds the build number and commit of the upstream the core is built on, which is the core's version ("v0.2.1 4123"); update it with every merge (`git rev-list --count` and `git rev-parse --short=9` of the merged upstream commit), along with `display_version` in `vita3k_libretro.info` and the version named at the top of this file. One rule for the merge itself: the paths in `.upstream-excluded` (the standalone app's parts) were deleted on purpose and stay deleted. Right after merging, run `git rm -r -q --ignore-unmatch --pathspec-from-file=.upstream-excluded`, and never resolve a conflict on one of those paths by restoring the file.

## License

GPLv2, as Vita3K.
