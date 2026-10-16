# Vita3K libretro core

A [libretro](https://www.libretro.com/) core of [Vita3K](https://github.com/Vita3K/Vita3K), the experimental PlayStation Vita emulator, for RetroArch and other libretro frontends. It is built on upstream Vita3K and on [danprice142's libretro port](https://github.com/danprice142/Vita3K-libretro). The core is currently on Vita3K v0.2.1 build 4123, commit a5aa96572 of 5 October 2026.

This repository is the core only: the standalone Vita3K (its Qt interface, updater and Android app) is not part of it. For that, and for compatibility lists, see [Vita3K](https://vita3k.org/).

## Downloads

The core is built by libretro's buildbot for Linux (x86_64, aarch64) and Android (arm64, x86_64), and is installed from RetroArch: Online Updater > Core Downloader. Every push to the `libretro` branch is also built in [Actions](https://github.com/WizzardSK/vita3k-libretro/actions/workflows/libretro.yml), Windows x86_64 included; the builds are the artifacts of a run, and downloading them needs a GitHub login.

## Installation

Each build from Actions has two folders:

- `cores/` - the core (`vita3k_libretro.so`, `vita3k_libretro.dll` or `vita3k_libretro_android.so`), for RetroArch's cores directory.
- `system/vita3k/` - the emulator's data, built-in shaders and the icons of its system dialogs, for RetroArch's system directory.

The PS Vita firmware is required. Download it from PlayStation's website and put it in `system/vita3k/`. The three packages are told apart by their file names, in any case:

- the system firmware - any `.pup` without `preinst` or `font` in its name (`PSP2UPDAT.PUP`, `PSVUPDAT.PUP`, `firmware.pup`)
- the preinstalled package - a `.pup` with `preinst` in its name (`preinst.pup`, `PSP2UPDAT_PREINST.PUP`)
- the fonts, optional - a `.pup` with `font` in its name (`font.pup`, `PSP2UPDAT_FONT.PUP`)

All three download under the same name, so rename the preinstalled package and the fonts as you save them.

The core installs them the first time it starts.

A `.pup` can also be loaded from RetroArch like a game, under any name: the core installs it, says which parts of the firmware are still missing, and starts nothing. Load each of the three that way and then a game.

## Content

A game is loaded as a `.vpk` or `.zip`, as a game folder, or through the folder's `eboot.bin`. It is installed into `system/vita3k/` the first time it is started, and started from there afterwards.

A game, update or DLC can also be loaded as a `.pkg`, with its license next to it: `work.bin`, `<pkg name>.rif`, or the zRIF in `<pkg name>.zrif`. System > Game PKG says whether a game's PKG is run without installing (the default: it starts in seconds and its files are decrypted from the PKG as the game reads them) or installed into `ux0/app`. Updates and DLC are installed.

## Requirements

The core renders with Vulkan (1.1 or later) on RetroArch's own device, or with OpenGL. Set RetroArch's video driver to `vulkan` (or `glcore`).

## Controls

The pad is the Vita's buttons and sticks. Games that use the gyroscope and accelerometer (Gravity Rush, for one) get them from RetroArch's sensor interface wherever RetroArch has sensors to give: on Android devices and with controllers whose driver reports them. Elsewhere they get no motion.

## Core options

- **GPU**: renderer, internal resolution, screen filter (bilinear, nearest, bicubic, FXAA, FSR), anisotropic filtering, asynchronous pipeline compilation, the shader compile overlay, memory mapping, high-accuracy rendering, surface sync, V-Sync, FPS hack.
- **CPU**: CPU optimizations.
- **System**: PS TV mode, modules mode, confirm button, file loading delay.
- **Audio**: volume, NGS audio engine.
- **Network**: PSN signed in.

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
