# Vita3K libretro core

A [libretro](https://www.libretro.com/) core of [Vita3K](https://github.com/Vita3K/Vita3K), the experimental PlayStation Vita emulator, for RetroArch and other libretro frontends. It is built on current upstream Vita3K and on [danprice142's libretro port](https://github.com/danprice142/Vita3K-libretro).

This repository is the core only: the standalone Vita3K (its Qt interface, updater and Android app) is not part of it. For that, and for compatibility lists, see [Vita3K](https://vita3k.org/).

## Downloads

Test builds for Linux x86_64 and aarch64, Windows x86_64 and Android arm64 and x86_64 are on the [releases page](https://github.com/WizzardSK/vita3k-libretro/releases). Every push to the `libretro` branch also builds them in [Actions](https://github.com/WizzardSK/vita3k-libretro/actions/workflows/libretro.yml).

## Installation

Each release zip has two folders:

- `cores/` - the core (`vita3k_libretro.so`, `vita3k_libretro.dll` or `vita3k_libretro_android.so`), for RetroArch's cores directory.
- `system/vita3k/` - the emulator's data and built-in shaders, for RetroArch's system directory.

The PS Vita firmware is required. Download it from PlayStation's website and put it in `system/vita3k/`:

- `PSP2UPDAT.PUP` - the system firmware
- `PSP2UPDAT_PREINST.PUP` (or `preinst_fresh.pup`) - the preinstalled package
- `PSP2UPDAT_FONT.PUP` (or `font_fresh.pup`) - the fonts, optional

The core installs them the first time it starts.

## Content

A game is loaded as a `.vpk` or `.zip`, as a game folder, or through the folder's `eboot.bin`. It is installed into `system/vita3k/` the first time it is started, and started from there afterwards.

## Requirements

The core renders with Vulkan (1.1 or later) on RetroArch's own device, or with OpenGL. Set RetroArch's video driver to `vulkan` (or `glcore`).

## Core options

- **GPU**: renderer, internal resolution, screen filter (bilinear, nearest, bicubic, FXAA, FSR), anisotropic filtering, asynchronous pipeline compilation, memory mapping, high-accuracy rendering, surface sync, V-Sync, FPS hack.
- **CPU**: CPU optimizations.
- **System**: PS TV mode, modules mode, confirm button, file loading delay, touchpad cursor.
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

Upstream Vita3K is merged in as it is. `upstream.version` holds the build number and commit of the upstream the core is built on, which is the core's version ("v0.2.1 4123"); update it with every merge (`git rev-list --count` and `git rev-parse --short=9` of the merged upstream commit), along with `display_version` in `vita3k_libretro.info`. One rule for the merge itself: the paths in `.upstream-excluded` (the standalone app's parts) were deleted on purpose and stay deleted. Right after merging, run `git rm -r -q --ignore-unmatch --pathspec-from-file=.upstream-excluded`, and never resolve a conflict on one of those paths by restoring the file.

## License

GPLv2, as Vita3K.
