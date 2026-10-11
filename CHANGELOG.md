# Changelog of the libretro core

What changed in the libretro core of this fork, newest first. Changes that come with a merge of upstream Vita3K are in upstream's own history; a merge is noted here with the upstream version it brought in.

## Unreleased

- The core option texts can be translated through libretro's Crowdin project: the options header is on the standard template, with the `intl/` scripts and the upload and sync workflows. All texts are English until the first sync.
- Internal Resolution Multiplier reaches RetroArch: the images handed over take the size the picture was rendered at (they were fixed at 960x544, shrinking a 2x to 4x render back), and RetroArch is told the size when it changes.
- Audio: RetroArch gets one frame's worth per call, and the game's audio waits once about 64 ms is queued.
- Closing content and Reset stop GXM before the guest threads and join its display thread, clean the renderer up before it is freed and stop the audio ports first, as upstream's shutdown does.
- A NoNpDrm game in a `.zip` installs decrypted.
- Android: RetroArch no longer crashes over a missing built-in shader; the core reads its data files itself instead of through SDL, which sent a file it could not open to Java.

## Test build 2 - 2026-10-05, rebuilt on 6 and 7 October

- Merged up to upstream Vita3K v0.2.1 build 4123 (a5aa96572), from upstream of February, with its new renderer and overlay code. The core reports upstream's version.
- The repository holds the core only: the standalone app's Qt interface, updater and Android app are not part of it.
- PKG install: a game's PKG, its update or DLC is installed with upstream's installer. A game's PKG needs its license next to it (`<name>.zrif`, `<name>.rif`, `work.bin` or `<CONTENT_ID>.rif`) or already in `ux0/license`; a license can also keep its PSN name, and every 512-byte `.bin` near the PKG is checked for the content ID.
- New option System > Game PKG, by default Run Without Installing: the game runs straight from its PKG, each file decrypted the first time the game reads it. Install keeps the full install; updates and DLC are still installed.
- Vulkan on RetroArch's device: the core makes the device itself, with what memory mapping needs, takes RetroArch's queue lock for every submit, and copies each frame for RetroArch on the render thread. This fixed the lost GPU device with memory mapping. Memory Mapping is Double Buffer by default, as upstream, and Page Table works.
- Audio: a game's audio ports are mixed instead of played one after another, each converted to 48 kHz, and no silence is made up. Before, sound warbled and ran at the wrong tempo.
- Android: games no longer crash at start. SDL asked Android's Java side for the app's package name, which a core does not have.
- PKG installs no longer stop at 80%.
- macOS cores for Apple Silicon and Intel, with Vulkan through RetroArch's MoltenVK.
- Linux cores are built on Ubuntu 24.04 (glibc 2.39).
- The core info file is in each zip.

## Test build 1 - 2026-10-05

- The first builds of the core from CI: Linux x86_64 and aarch64, Windows x86_64, Android arm64 and x86_64.
- A recipe for libretro's buildbot and a core info file.

## February 2026

- libretro support, by danprice142: the original port this fork builds on.
