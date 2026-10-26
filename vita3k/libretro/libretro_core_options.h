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

// The English texts are edited here; the translations in
// libretro_core_options_intl.h come from Crowdin (intl/).

#ifndef LIBRETRO_CORE_OPTIONS_H__
#define LIBRETRO_CORE_OPTIONS_H__

#include <stdlib.h>
#include <string.h>

#include "libretro.h"

#ifndef HAVE_NO_LANGEXTRA
#include "libretro_core_options_intl.h"
#endif

/*
 ********************************
 * VERSION: 2.0
 ********************************
 *
 * - 2.0: Add support for core options v2 interface
 * - 1.3: Move translations to libretro_core_options_intl.h
 *        - libretro_core_options_intl.h includes BOM and utf-8
 *          fix for MSVC 2010-2013
 *        - Added HAVE_NO_LANGEXTRA flag to disable translations
 *          on platforms/compilers without BOM support
 * - 1.2: Use core options v1 interface when
 *        RETRO_ENVIRONMENT_GET_CORE_OPTIONS_VERSION is >= 1
 *        (previously required RETRO_ENVIRONMENT_GET_CORE_OPTIONS_VERSION == 1)
 * - 1.1: Support generation of core options v0 retro_core_option_value
 *        arrays containing options with a single value
 * - 1.0: First commit
*/

#ifdef __cplusplus
extern "C" {
#endif

/*
 ********************************
 * Core Option Definitions
 ********************************
*/

/* RETRO_LANGUAGE_ENGLISH */

/* Default language:
 * - All other languages must include the same keys and values
 * - Will be used as a fallback in the event that frontend language
 *   is not available
 * - Will be used as a fallback for any missing entries in
 *   frontend language definition
 * - Translations live in libretro_core_options_intl.h, which is
 *   generated from Crowdin - edit only the English texts here
 */

struct retro_core_option_v2_category option_cats_us[] = {
    { "gpu", "GPU", "Graphics rendering options." },
    { "cpu", "CPU", "CPU emulation options." },
    { "system", "System", "System emulation options." },
    { "audio", "Audio", "Audio output options." },
    { "network", "Network", "Network options." },
    { "install", "Content", "Manage data for a given title, as well as any updates and downloadable content." },
    { "remove", "Remove Content", "Selects titles with installed data and caches to delete when the core closes or resets. It does not remove original media, saves, or trophies." },
    { "camera", "Camera", "What the Vita's front and back cameras see." },
    { "accounts", "Accounts", "The Vita's accounts (users) in ux0/user, each with its own saves and trophies." },
    { "trophies", "Trophies", "The current title's trophies." },
    { "modules", "Modules", "The firmware's modules (vs0/sys/external) to load when Modules Mode (in System) is Auto & Manual or Manual." },
    { NULL, NULL, NULL },
};

struct retro_core_option_v2_definition option_defs_us[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        "Backend Renderer",
        NULL,
        "Select the graphics backend. Vulkan is recommended.",
        NULL,
        "gpu",
        {
            { "Vulkan", "Vulkan" },
            { "OpenGL", "OpenGL" },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        "Internal Resolution Multiplier",
        NULL,
        "Multiplier for the internal rendering resolution (960x544 base).",
        NULL,
        "gpu",
        {
            { "1", "1x (960x544)" },
            { "2", "2x (1920x1088)" },
            { "3", "3x (2880x1632)" },
            { "4", "4x (3840x2176)" },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        "Screen Filter",
        NULL,
        "Post-processing filter applied to the rendered frame.",
        NULL,
        "gpu",
        {
            { "Bilinear", "Bilinear" },
            { "Nearest", "Nearest" },
            { "Bicubic", "Bicubic" },
            { "FXAA", "FXAA" },
            { "FSR", "FSR" },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        "Anisotropic Filtering",
        NULL,
        "Level of anisotropic texture filtering.",
        NULL,
        "gpu",
        {
            { "1", "1x (Off)" },
            { "2", "2x" },
            { "4", "4x" },
            { "8", "8x" },
            { "16", "16x" },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        "V-Sync",
        NULL,
        "Enable or disable vertical sync.",
        NULL,
        "gpu",
        {
            { "enabled", NULL },
            { "disabled", NULL },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_async_pipeline",
        "Async Pipeline Compilation",
        NULL,
        "Compile shader pipelines asynchronously to reduce stuttering.",
        NULL,
        "gpu",
        {
            { "enabled", NULL },
            { "disabled", NULL },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_compile_overlay",
        "Shader Compilation Overlay",
        NULL,
        NULL,
        NULL,
        "gpu",
        {
            { "enabled", NULL },
            { "disabled", NULL },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_memory_mapping",
        "Memory Mapping",
        NULL,
        "GPU memory mapping method. Higher methods improve performance but require GPU support.",
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", "Double Buffer" },
            { "external-host", "External Host" },
            { "page-table", "Page Table" },
            { "native-buffer", "Native Buffer" },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        "High Accuracy Rendering",
        NULL,
        "Enable more accurate but slower rendering techniques.",
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "enabled", NULL },
            { NULL, NULL },
        },
        "disabled"
    },
    // ── CPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_cpu_opt",
        "CPU Optimizations (Dynarmic JIT)",
        NULL,
        "Enable Dynarmic JIT for faster CPU emulation.",
        NULL,
        "cpu",
        {
            { "enabled", NULL },
            { "disabled", NULL },
            { NULL, NULL },
        },
        "enabled"
    },
    // ── System ───────────────────────────────────────────────────────────
    {
        "vita3k_pkg_mode",
        "Run Mode",
        NULL,
        "How a title, its updates and downloadable content (DLC) run. Enables updates and DLC in a title's directory by default. They can also load from elsewhere, which installs them whatever the Run Mode.\n\n"
        "Direct: Runs directly from the original media.\n"
        "Direct with Cache: Same as Direct, but the core caches reads to local storage. This helps performance in certain cases, like when accessing media on a high-latency network share.\n"
        "Installed: Installs the original media when first loaded, and runs it from local storage.",
        NULL,
        "install",
        {
            { "run", "Direct" },
            { "cache", "Direct with Cache" },
            { "install", "Installed" },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_trophy_show",
        "Display: Earn Status",
        NULL,
        "Controls which trophies are displayed by whether or not they have been earned.",
        NULL,
        "trophies",
        {
            { "all", "All" },
            { "earned", "Earned" },
            { "unearned", "Not Earned" },
            { NULL, NULL },
        },
        "all"
    },
    {
        "vita3k_trophy_grade",
        "Display: Grade",
        NULL,
        "Controls which trophies are displayed by their grade (Platinum, Gold, Silver or Bronze).",
        NULL,
        "trophies",
        {
            { "all", "All" },
            { "platinum", "Platinum" },
            { "gold", "Gold" },
            { "silver", "Silver" },
            { "bronze", "Bronze" },
            { NULL, NULL },
        },
        "all"
    },
    {
        "vita3k_trophy_hidden",
        "Display: Hidden",
        NULL,
        "Controls the display of hidden trophies.",
        NULL,
        "trophies",
        {
            { "disabled", NULL },
            { "enabled", NULL },
            { NULL, NULL },
        },
        "disabled"
    },
    {
        "vita3k_trophy_sort",
        "Sort Method",
        NULL,
        "Controls how trophies are sorted.",
        NULL,
        "trophies",
        {
            { "type", "By Grade" },
            { "name", "By Name" },
            { "date", "By Earn Date" },
            { NULL, NULL },
        },
        "type"
    },
    {
        "vita3k_content_subdirs",
        "Include Subdirectories",
        NULL,
        "ON: Loads updates and DLC in the title's directory and subdirectories.\n"
        "OFF: Loads updates and DLC only in the title's directory.",
        NULL,
        "install",
        {
            { "disabled", NULL },
            { "enabled", NULL },
            { NULL, NULL },
        },
        "disabled"
    },
    {
        "vita3k_pstv_mode",
        "PS TV Mode",
        NULL,
        "Emulate a PlayStation TV instead of a PS Vita.",
        NULL,
        "system",
        {
            { "disabled", NULL },
            { "enabled", NULL },
            { NULL, NULL },
        },
        "disabled"
    },
    {
        "vita3k_modules_mode",
        "Modules Mode",
        NULL,
        "How system modules are loaded. Automatic: the core's own implementation, and the firmware's modules the core knows it needs. Auto & Manual: those, and the ones turned on under Modules. Manual: only the ones turned on under Modules. Automatic is recommended.",
        NULL,
        "system",
        {
            { "0", "Automatic" },
            { "1", "Auto & Manual" },
            { "2", "Manual" },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        "FPS Hack (30 to 60)",
        NULL,
        "Attempt to run 30fps-locked games at 60fps. May cause issues.",
        NULL,
        "system",
        {
            { "disabled", NULL },
            { "enabled", NULL },
            { NULL, NULL },
        },
        "disabled"
    },
    {
        "vita3k_sys_button",
        "Confirm Button",
        NULL,
        "Which button is used for confirm actions.",
        NULL,
        "system",
        {
            { "0", "Circle" },
            { "1", "Cross" },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_sys_lang",
        "System Language",
        NULL,
        "The console's language, which games use for their text and the system dialogs show. Applies the next time the game is started.",
        NULL,
        "system",
        {
            { "0", "Japanese" },
            { "1", "English (United States)" },
            { "2", "French" },
            { "3", "Spanish" },
            { "4", "German" },
            { "5", "Italian" },
            { "6", "Dutch" },
            { "7", "Portuguese (Portugal)" },
            { "8", "Russian" },
            { "9", "Korean" },
            { "10", "Chinese (Traditional)" },
            { "11", "Chinese (Simplified)" },
            { "12", "Finnish" },
            { "13", "Swedish" },
            { "14", "Danish" },
            { "15", "Norwegian" },
            { "16", "Polish" },
            { "17", "Portuguese (Brazil)" },
            { "18", "English (United Kingdom)" },
            { "19", "Turkish" },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_sys_date_format",
        "Date Format",
        NULL,
        "How the console writes dates, for games and the system dialogs (save data lists, for one). The date and time themselves are the host's. Applies the next time the game is started.",
        NULL,
        "system",
        {
            { "0", "YYYY/MM/DD" },
            { "1", "DD/MM/YYYY" },
            { "2", "MM/DD/YYYY" },
            { NULL, NULL },
        },
        "2"
    },
    {
        "vita3k_sys_time_format",
        "Time Format",
        NULL,
        "Whether the console shows the time in 12 or 24 hours, for games and the system dialogs. Applies the next time the game is started.",
        NULL,
        "system",
        {
            { "0", "12-Hour" },
            { "1", "24-Hour" },
            { NULL, NULL },
        },
        "0"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        "Audio Volume",
        NULL,
        "Master audio volume level.",
        NULL,
        "audio",
        {
            { "0", "0%" },
            { "10", "10%" },
            { "20", "20%" },
            { "30", "30%" },
            { "40", "40%" },
            { "50", "50%" },
            { "60", "60%" },
            { "70", "70%" },
            { "80", "80%" },
            { "90", "90%" },
            { "100", "100%" },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        "NGS Audio Engine",
        NULL,
        "Enable the NGS audio engine for enhanced audio.",
        NULL,
        "audio",
        {
            { "enabled", NULL },
            { "disabled", NULL },
            { NULL, NULL },
        },
        "enabled"
    },
    // ── Network ──────────────────────────────────────────────────────────
    {
        "vita3k_psn_signed_in",
        "PSN Signed In",
        NULL,
        "Pretend to be signed in to PSN. Required by some games.",
        NULL,
        "network",
        {
            { "disabled", NULL },
            { "enabled", NULL },
            { NULL, NULL },
        },
        "disabled"
    },
    {
        "vita3k_http_enable",
        "HTTP",
        NULL,
        "Enable HTTP networking support for apps that use it. Applies the next time the game is started.",
        NULL,
        "network",
        {
            { "enabled", NULL },
            { "disabled", NULL },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_http_timeout_attempts",
        "HTTP Timeout Attempts",
        NULL,
        "How many times to retry connecting when the server doesn't respond. Could be useful with a very unstable or very slow connection. Applies the next time the game is started.",
        NULL,
        "network",
        {
            { "0", NULL },
            { "5", NULL },
            { "10", NULL },
            { "15", NULL },
            { "20", NULL },
            { "25", NULL },
            { "30", NULL },
            { "35", NULL },
            { "40", NULL },
            { "45", NULL },
            { "50", NULL },
            { "55", NULL },
            { "60", NULL },
            { "65", NULL },
            { "70", NULL },
            { "75", NULL },
            { "80", NULL },
            { "85", NULL },
            { "90", NULL },
            { "95", NULL },
            { "100", NULL },
            { NULL, NULL },
        },
        "50"
    },
    {
        "vita3k_http_timeout_sleep",
        "HTTP Timeout Sleep",
        NULL,
        "How long to wait between connection retries. Could be useful with a very unstable or very slow connection. Applies the next time the game is started.",
        NULL,
        "network",
        {
            { "50", "50 ms" },
            { "100", "100 ms" },
            { "150", "150 ms" },
            { "200", "200 ms" },
            { "250", "250 ms" },
            { "300", "300 ms" },
            { "400", "400 ms" },
            { "500", "500 ms" },
            { "750", "750 ms" },
            { "1000", "1000 ms" },
            { "1500", "1500 ms" },
            { "2000", "2000 ms" },
            { "2500", "2500 ms" },
            { "3000", "3000 ms" },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_http_read_end_attempts",
        "HTTP Read End Attempts",
        NULL,
        "How many retries to attempt when there is no more data to read. Lower can improve performance, but can make games unstable with a bad enough connection. Applies the next time the game is started.",
        NULL,
        "network",
        {
            { "0", NULL },
            { "5", NULL },
            { "10", NULL },
            { "15", NULL },
            { "20", NULL },
            { "25", NULL },
            { "30", NULL },
            { "35", NULL },
            { "40", NULL },
            { "45", NULL },
            { "50", NULL },
            { "55", NULL },
            { "60", NULL },
            { "65", NULL },
            { "70", NULL },
            { "75", NULL },
            { "80", NULL },
            { "85", NULL },
            { "90", NULL },
            { "95", NULL },
            { "100", NULL },
            { NULL, NULL },
        },
        "10"
    },
    {
        "vita3k_http_read_end_sleep",
        "HTTP Read End Sleep",
        NULL,
        "How long to wait between read attempt retries. Lower can improve performance, but can make games unstable with a bad enough connection. Applies the next time the game is started.",
        NULL,
        "network",
        {
            { "50", "50 ms" },
            { "100", "100 ms" },
            { "150", "150 ms" },
            { "200", "200 ms" },
            { "250", "250 ms" },
            { "300", "300 ms" },
            { "400", "400 ms" },
            { "500", "500 ms" },
            { "750", "750 ms" },
            { "1000", "1000 ms" },
            { "1500", "1500 ms" },
            { "2000", "2000 ms" },
            { "2500", "2500 ms" },
            { "3000", "3000 ms" },
            { NULL, NULL },
        },
        "250"
    },
    {
        "vita3k_front_camera",
        "Front Camera",
        NULL,
        "What the Vita's front camera sees. Host Camera: RetroArch's camera (Settings > Privacy > Camera Access has to be on, and a camera driver there for this platform). Image: system/vita3k/camera/front.png or front.jpg. Solid Color: the Front Camera Color. When a source is not available the next one is taken. Applies the next time the game opens the camera.",
        NULL,
        "camera",
        {
            { "host", "Host Camera" },
            { "image", "Image" },
            { "color", "Solid Color" },
            { NULL, NULL },
        },
        "host"
    },
    {
        "vita3k_front_camera_color",
        "Front Camera Color",
        NULL,
        "The colour the front camera shows with Solid Color.",
        NULL,
        "camera",
        {
            { "0", "Black" },
            { "16777215", "White" },
            { "8421504", "Gray" },
            { "255", "Red" },
            { "65280", "Green" },
            { "16711680", "Blue" },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_back_camera",
        "Back Camera",
        NULL,
        "What the Vita's back camera sees. Host Camera: RetroArch's camera (Settings > Privacy > Camera Access has to be on, and a camera driver there for this platform). Image: system/vita3k/camera/back.png or back.jpg. Solid Color: the Back Camera Color. When a source is not available the next one is taken. Applies the next time the game opens the camera.",
        NULL,
        "camera",
        {
            { "host", "Host Camera" },
            { "image", "Image" },
            { "color", "Solid Color" },
            { NULL, NULL },
        },
        "host"
    },
    {
        "vita3k_back_camera_color",
        "Back Camera Color",
        NULL,
        "The colour the back camera shows with Solid Color.",
        NULL,
        "camera",
        {
            { "0", "Black" },
            { "16777215", "White" },
            { "8421504", "Gray" },
            { "255", "Red" },
            { "65280", "Green" },
            { "16711680", "Blue" },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_surface_sync",
        "Surface Sync",
        NULL,
        "GPU memory optimization. May improve performance by 20-40%.",
        NULL,
        "gpu",
        {
            { "enabled", "Enabled (more accurate)" },
            { "disabled", "Disabled (faster)" },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        "File Loading Delay",
        NULL,
        "Delay in milliseconds for file loading. Helps with timing-sensitive games.",
        NULL,
        "system",
        {
            { "0", "0 ms" },
            { "5", "5 ms" },
            { "10", "10 ms" },
            { "15", "15 ms" },
            { "20", "20 ms" },
            { "25", "25 ms" },
            { "30", "30 ms" },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};

struct retro_core_options_v2 options_us = {
   option_cats_us,
   option_defs_us
};

/*
 ********************************
 * Language Mapping
 ********************************
*/

#ifndef HAVE_NO_LANGEXTRA
struct retro_core_options_v2 *options_intl[RETRO_LANGUAGE_LAST] = {
   &options_us,       /* RETRO_LANGUAGE_ENGLISH */
   &options_ja,       /* RETRO_LANGUAGE_JAPANESE */
   &options_fr,       /* RETRO_LANGUAGE_FRENCH */
   &options_es,       /* RETRO_LANGUAGE_SPANISH */
   &options_de,       /* RETRO_LANGUAGE_GERMAN */
   &options_it,       /* RETRO_LANGUAGE_ITALIAN */
   &options_nl,       /* RETRO_LANGUAGE_DUTCH */
   &options_pt_br,    /* RETRO_LANGUAGE_PORTUGUESE_BRAZIL */
   &options_pt_pt,    /* RETRO_LANGUAGE_PORTUGUESE_PORTUGAL */
   &options_ru,       /* RETRO_LANGUAGE_RUSSIAN */
   &options_ko,       /* RETRO_LANGUAGE_KOREAN */
   &options_cht,      /* RETRO_LANGUAGE_CHINESE_TRADITIONAL */
   &options_chs,      /* RETRO_LANGUAGE_CHINESE_SIMPLIFIED */
   &options_eo,       /* RETRO_LANGUAGE_ESPERANTO */
   &options_pl,       /* RETRO_LANGUAGE_POLISH */
   &options_vn,       /* RETRO_LANGUAGE_VIETNAMESE */
   &options_ar,       /* RETRO_LANGUAGE_ARABIC */
   &options_el,       /* RETRO_LANGUAGE_GREEK */
   &options_tr,       /* RETRO_LANGUAGE_TURKISH */
   &options_sk,       /* RETRO_LANGUAGE_SLOVAK */
   &options_fa,       /* RETRO_LANGUAGE_PERSIAN */
   &options_he,       /* RETRO_LANGUAGE_HEBREW */
   &options_ast,      /* RETRO_LANGUAGE_ASTURIAN */
   &options_fi,       /* RETRO_LANGUAGE_FINNISH */
   &options_id,       /* RETRO_LANGUAGE_INDONESIAN */
   &options_sv,       /* RETRO_LANGUAGE_SWEDISH */
   &options_uk,       /* RETRO_LANGUAGE_UKRAINIAN */
   &options_cs,       /* RETRO_LANGUAGE_CZECH */
   &options_val,      /* RETRO_LANGUAGE_CATALAN_VALENCIA */
   &options_ca,       /* RETRO_LANGUAGE_CATALAN */
   &options_en,       /* RETRO_LANGUAGE_BRITISH_ENGLISH */
   &options_hu,       /* RETRO_LANGUAGE_HUNGARIAN */
   &options_be,       /* RETRO_LANGUAGE_BELARUSIAN */
   &options_gl,       /* RETRO_LANGUAGE_GALICIAN */
   &options_no,       /* RETRO_LANGUAGE_NORWEGIAN */
   &options_ga,       /* RETRO_LANGUAGE_IRISH */
};
#endif

/*
 ********************************
 * Functions
 ********************************
*/

/* Handles configuration/setting of core options.
 * Should be called as early as possible - ideally inside
 * retro_set_environment(), and no later than retro_load_game()
 * > We place the function body in the header to avoid the
 *   necessity of adding more .c files (i.e. want this to
 *   be as painless as possible for core devs)
 */

static inline void libretro_set_core_options(retro_environment_t environ_cb,
      bool *categories_supported)
{
   unsigned version  = 0;
#ifndef HAVE_NO_LANGEXTRA
   unsigned language = 0;
#endif

   if (!environ_cb || !categories_supported)
      return;

   *categories_supported = false;

   if (!environ_cb(RETRO_ENVIRONMENT_GET_CORE_OPTIONS_VERSION, &version))
      version = 0;

   if (version >= 2)
   {
#ifndef HAVE_NO_LANGEXTRA
      struct retro_core_options_v2_intl core_options_intl;

      core_options_intl.us    = &options_us;
      core_options_intl.local = NULL;

      if (environ_cb(RETRO_ENVIRONMENT_GET_LANGUAGE, &language) &&
          (language < RETRO_LANGUAGE_LAST) && (language != RETRO_LANGUAGE_ENGLISH))
         core_options_intl.local = options_intl[language];

      *categories_supported = environ_cb(RETRO_ENVIRONMENT_SET_CORE_OPTIONS_V2_INTL,
            &core_options_intl);
#else
      *categories_supported = environ_cb(RETRO_ENVIRONMENT_SET_CORE_OPTIONS_V2,
            &options_us);
#endif
   }
   else
   {
      size_t i, j;
      size_t option_index              = 0;
      size_t num_options               = 0;
      struct retro_core_option_definition
            *option_v1_defs_us         = NULL;
#ifndef HAVE_NO_LANGEXTRA
      size_t num_options_intl          = 0;
      struct retro_core_option_v2_definition
            *option_defs_intl          = NULL;
      struct retro_core_option_definition
            *option_v1_defs_intl       = NULL;
      struct retro_core_options_intl
            core_options_v1_intl;
#endif
      struct retro_variable *variables = NULL;
      char **values_buf                = NULL;

      /* Determine total number of options */
      while (true)
      {
         if (option_defs_us[num_options].key)
            num_options++;
         else
            break;
      }

      if (version >= 1)
      {
         /* Allocate US array */
         option_v1_defs_us = (struct retro_core_option_definition *)
               calloc(num_options + 1, sizeof(struct retro_core_option_definition));

         /* Copy parameters from option_defs_us array */
         for (i = 0; i < num_options; i++)
         {
            struct retro_core_option_v2_definition *option_def_us = &option_defs_us[i];
            struct retro_core_option_value *option_values         = option_def_us->values;
            struct retro_core_option_definition *option_v1_def_us = &option_v1_defs_us[i];
            struct retro_core_option_value *option_v1_values      = option_v1_def_us->values;

            option_v1_def_us->key           = option_def_us->key;
            option_v1_def_us->desc          = option_def_us->desc;
            option_v1_def_us->info          = option_def_us->info;
            option_v1_def_us->default_value = option_def_us->default_value;

            /* Values must be copied individually... */
            while (option_values->value)
            {
               option_v1_values->value = option_values->value;
               option_v1_values->label = option_values->label;

               option_values++;
               option_v1_values++;
            }
         }

#ifndef HAVE_NO_LANGEXTRA
         if (environ_cb(RETRO_ENVIRONMENT_GET_LANGUAGE, &language) &&
             (language < RETRO_LANGUAGE_LAST) && (language != RETRO_LANGUAGE_ENGLISH) &&
             options_intl[language])
            option_defs_intl = options_intl[language]->definitions;

         if (option_defs_intl)
         {
            /* Determine number of intl options */
            while (true)
            {
               if (option_defs_intl[num_options_intl].key)
                  num_options_intl++;
               else
                  break;
            }

            /* Allocate intl array */
            option_v1_defs_intl = (struct retro_core_option_definition *)
                  calloc(num_options_intl + 1, sizeof(struct retro_core_option_definition));

            /* Copy parameters from option_defs_intl array */
            for (i = 0; i < num_options_intl; i++)
            {
               struct retro_core_option_v2_definition *option_def_intl = &option_defs_intl[i];
               struct retro_core_option_value *option_values           = option_def_intl->values;
               struct retro_core_option_definition *option_v1_def_intl = &option_v1_defs_intl[i];
               struct retro_core_option_value *option_v1_values        = option_v1_def_intl->values;

               option_v1_def_intl->key           = option_def_intl->key;
               option_v1_def_intl->desc          = option_def_intl->desc;
               option_v1_def_intl->info          = option_def_intl->info;
               option_v1_def_intl->default_value = option_def_intl->default_value;

               /* Values must be copied individually... */
               while (option_values->value)
               {
                  option_v1_values->value = option_values->value;
                  option_v1_values->label = option_values->label;

                  option_values++;
                  option_v1_values++;
               }
            }
         }

         core_options_v1_intl.us    = option_v1_defs_us;
         core_options_v1_intl.local = option_v1_defs_intl;

         environ_cb(RETRO_ENVIRONMENT_SET_CORE_OPTIONS_INTL, &core_options_v1_intl);
#else
         environ_cb(RETRO_ENVIRONMENT_SET_CORE_OPTIONS, option_v1_defs_us);
#endif
      }
      else
      {
         /* Allocate arrays */
         variables  = (struct retro_variable *)calloc(num_options + 1,
               sizeof(struct retro_variable));
         values_buf = (char **)calloc(num_options, sizeof(char *));

         if (!variables || !values_buf)
            goto error;

         /* Copy parameters from option_defs_us array */
         for (i = 0; i < num_options; i++)
         {
            const char *key                        = option_defs_us[i].key;
            const char *desc                       = option_defs_us[i].desc;
            const char *default_value              = option_defs_us[i].default_value;
            struct retro_core_option_value *values = option_defs_us[i].values;
            size_t buf_len                         = 3;
            size_t default_index                   = 0;

            values_buf[i] = NULL;

            if (desc)
            {
               size_t num_values = 0;

               /* Determine number of values */
               while (true)
               {
                  if (values[num_values].value)
                  {
                     /* Check if this is the default value */
                     if (default_value)
                        if (strcmp(values[num_values].value, default_value) == 0)
                           default_index = num_values;

                     buf_len += strlen(values[num_values].value);
                     num_values++;
                  }
                  else
                     break;
               }

               /* Build values string */
               if (num_values > 0)
               {
                  buf_len += num_values - 1;
                  buf_len += strlen(desc);

                  values_buf[i] = (char *)calloc(buf_len, sizeof(char));
                  if (!values_buf[i])
                     goto error;

                  strcpy(values_buf[i], desc);
                  strcat(values_buf[i], "; ");

                  /* Default value goes first */
                  strcat(values_buf[i], values[default_index].value);

                  /* Add remaining values */
                  for (j = 0; j < num_values; j++)
                  {
                     if (j != default_index)
                     {
                        strcat(values_buf[i], "|");
                        strcat(values_buf[i], values[j].value);
                     }
                  }
               }
            }

            variables[option_index].key   = key;
            variables[option_index].value = values_buf[i];
            option_index++;
         }

         /* Set variables */
         environ_cb(RETRO_ENVIRONMENT_SET_VARIABLES, variables);
      }

error:
      /* Clean up */

      if (option_v1_defs_us)
      {
         free(option_v1_defs_us);
         option_v1_defs_us = NULL;
      }

#ifndef HAVE_NO_LANGEXTRA
      if (option_v1_defs_intl)
      {
         free(option_v1_defs_intl);
         option_v1_defs_intl = NULL;
      }
#endif

      if (values_buf)
      {
         for (i = 0; i < num_options; i++)
         {
            if (values_buf[i])
            {
               free(values_buf[i]);
               values_buf[i] = NULL;
            }
         }

         free(values_buf);
         values_buf = NULL;
      }

      if (variables)
      {
         free(variables);
         variables = NULL;
      }
   }
}

#ifdef __cplusplus
}
#endif

#endif
