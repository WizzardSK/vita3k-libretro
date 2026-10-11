#ifndef LIBRETRO_CORE_OPTIONS_INTL_H__
#define LIBRETRO_CORE_OPTIONS_INTL_H__

#if defined(_MSC_VER) && (_MSC_VER >= 1500 && _MSC_VER < 1900)
/* https://support.microsoft.com/en-us/kb/980263 */
#pragma execution_character_set("utf-8")
#pragma warning(disable:4566)
#endif

#include "libretro.h"

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
/* RETRO_LANGUAGE_AR */

#define CATEGORY_GPU_LABEL_AR NULL
#define CATEGORY_GPU_INFO_0_AR NULL
#define CATEGORY_CPU_LABEL_AR NULL
#define CATEGORY_CPU_INFO_0_AR NULL
#define CATEGORY_SYSTEM_LABEL_AR NULL
#define CATEGORY_SYSTEM_INFO_0_AR NULL
#define CATEGORY_AUDIO_LABEL_AR NULL
#define CATEGORY_AUDIO_INFO_0_AR NULL
#define CATEGORY_NETWORK_LABEL_AR NULL
#define CATEGORY_NETWORK_INFO_0_AR NULL
#define VITA3K_BACKEND_RENDERER_LABEL_AR NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_AR NULL
#define OPTION_VAL_VULKAN_AR NULL
#define OPTION_VAL_OPENGL_AR NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_AR NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_AR NULL
#define OPTION_VAL_1_AR NULL
#define OPTION_VAL_2_AR NULL
#define OPTION_VAL_3_AR NULL
#define OPTION_VAL_4_AR NULL
#define VITA3K_SCREEN_FILTER_LABEL_AR NULL
#define VITA3K_SCREEN_FILTER_INFO_0_AR NULL
#define OPTION_VAL_BILINEAR_AR NULL
#define OPTION_VAL_NEAREST_AR NULL
#define OPTION_VAL_BICUBIC_AR NULL
#define OPTION_VAL_FXAA_AR NULL
#define OPTION_VAL_FSR_AR NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_AR NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_AR NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_AR NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_AR NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_AR NULL
#define OPTION_VAL_8_AR NULL
#define OPTION_VAL_16_AR NULL
#define VITA3K_V_SYNC_LABEL_AR NULL
#define VITA3K_V_SYNC_INFO_0_AR NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_AR NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_AR NULL
#define VITA3K_MEMORY_MAPPING_LABEL_AR NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_AR NULL
#define OPTION_VAL_DOUBLE_BUFFER_AR NULL
#define OPTION_VAL_EXTERNAL_HOST_AR NULL
#define OPTION_VAL_PAGE_TABLE_AR NULL
#define OPTION_VAL_NATIVE_BUFFER_AR NULL
#define VITA3K_HIGH_ACCURACY_LABEL_AR NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_AR NULL
#define VITA3K_CPU_OPT_LABEL_AR NULL
#define VITA3K_CPU_OPT_INFO_0_AR NULL
#define VITA3K_PKG_MODE_LABEL_AR NULL
#define VITA3K_PKG_MODE_INFO_0_AR NULL
#define OPTION_VAL_RUN_AR NULL
#define OPTION_VAL_INSTALL_AR NULL
#define VITA3K_PSTV_MODE_LABEL_AR NULL
#define VITA3K_PSTV_MODE_INFO_0_AR NULL
#define VITA3K_MODULES_MODE_LABEL_AR NULL
#define VITA3K_MODULES_MODE_INFO_0_AR NULL
#define OPTION_VAL_0_AR NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_AR NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_AR NULL
#define VITA3K_FPS_HACK_LABEL_AR NULL
#define VITA3K_FPS_HACK_INFO_0_AR NULL
#define VITA3K_SYS_BUTTON_LABEL_AR NULL
#define VITA3K_SYS_BUTTON_INFO_0_AR NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_AR NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_AR NULL
#define VITA3K_AUDIO_VOLUME_LABEL_AR NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_AR NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_AR NULL
#define OPTION_VAL_10_AR NULL
#define OPTION_VAL_20_AR NULL
#define OPTION_VAL_30_AR NULL
#define OPTION_VAL_40_AR NULL
#define OPTION_VAL_50_AR NULL
#define OPTION_VAL_60_AR NULL
#define OPTION_VAL_70_AR NULL
#define OPTION_VAL_80_AR NULL
#define OPTION_VAL_90_AR NULL
#define OPTION_VAL_100_AR NULL
#define VITA3K_NGS_ENABLE_LABEL_AR NULL
#define VITA3K_NGS_ENABLE_INFO_0_AR NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_AR NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_AR NULL
#define VITA3K_SURFACE_SYNC_LABEL_AR NULL
#define VITA3K_SURFACE_SYNC_INFO_0_AR NULL
#define OPTION_VAL_ENABLED_AR NULL
#define OPTION_VAL_DISABLED_AR NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_AR NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_AR NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_AR NULL
#define OPTION_VAL_5_AR NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_AR NULL
#define OPTION_VAL_15_AR NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_AR NULL
#define OPTION_VAL_25_AR NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_AR NULL

struct retro_core_option_v2_category option_cats_ar[] = {
    { "gpu", CATEGORY_GPU_LABEL_AR, CATEGORY_GPU_INFO_0_AR },
    { "cpu", CATEGORY_CPU_LABEL_AR, CATEGORY_CPU_INFO_0_AR },
    { "system", CATEGORY_SYSTEM_LABEL_AR, CATEGORY_SYSTEM_INFO_0_AR },
    { "audio", CATEGORY_AUDIO_LABEL_AR, CATEGORY_AUDIO_INFO_0_AR },
    { "network", CATEGORY_NETWORK_LABEL_AR, CATEGORY_NETWORK_INFO_0_AR },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_ar[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_AR,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_AR,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_AR },
            { "OpenGL", OPTION_VAL_OPENGL_AR },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_AR,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_AR,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_AR },
            { "2", OPTION_VAL_2_AR },
            { "3", OPTION_VAL_3_AR },
            { "4", OPTION_VAL_4_AR },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_AR,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_AR,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_AR },
            { "Nearest", OPTION_VAL_NEAREST_AR },
            { "Bicubic", OPTION_VAL_BICUBIC_AR },
            { "FXAA", OPTION_VAL_FXAA_AR },
            { "FSR", OPTION_VAL_FSR_AR },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_AR,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_AR,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_AR },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_AR },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_AR },
            { "8", OPTION_VAL_8_AR },
            { "16", OPTION_VAL_16_AR },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_AR,
        NULL,
        VITA3K_V_SYNC_INFO_0_AR,
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
        VITA3K_ASYNC_PIPELINE_LABEL_AR,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_AR,
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
        VITA3K_MEMORY_MAPPING_LABEL_AR,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_AR,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_AR },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_AR },
            { "page-table", OPTION_VAL_PAGE_TABLE_AR },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_AR },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_AR,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_AR,
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
        VITA3K_CPU_OPT_LABEL_AR,
        NULL,
        VITA3K_CPU_OPT_INFO_0_AR,
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
        VITA3K_PKG_MODE_LABEL_AR,
        NULL,
        VITA3K_PKG_MODE_INFO_0_AR,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_AR },
            { "install", OPTION_VAL_INSTALL_AR },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_AR,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_AR,
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
        VITA3K_MODULES_MODE_LABEL_AR,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_AR,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_AR },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_AR },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_AR },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_AR,
        NULL,
        VITA3K_FPS_HACK_INFO_0_AR,
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
        VITA3K_SYS_BUTTON_LABEL_AR,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_AR,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_AR },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_AR },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_AR,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_AR,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_AR },
            { "10", OPTION_VAL_10_AR },
            { "20", OPTION_VAL_20_AR },
            { "30", OPTION_VAL_30_AR },
            { "40", OPTION_VAL_40_AR },
            { "50", OPTION_VAL_50_AR },
            { "60", OPTION_VAL_60_AR },
            { "70", OPTION_VAL_70_AR },
            { "80", OPTION_VAL_80_AR },
            { "90", OPTION_VAL_90_AR },
            { "100", OPTION_VAL_100_AR },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_AR,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_AR,
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
        VITA3K_PSN_SIGNED_IN_LABEL_AR,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_AR,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_AR,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_AR,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_AR },
            { "disabled", OPTION_VAL_DISABLED_AR },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_AR,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_AR,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_AR },
            { "5", OPTION_VAL_5_AR },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_AR },
            { "15", OPTION_VAL_15_AR },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_AR },
            { "25", OPTION_VAL_25_AR },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_AR },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_ar = {
   option_cats_ar,
   option_defs_ar
};

/* RETRO_LANGUAGE_AST */

#define CATEGORY_GPU_LABEL_AST NULL
#define CATEGORY_GPU_INFO_0_AST NULL
#define CATEGORY_CPU_LABEL_AST NULL
#define CATEGORY_CPU_INFO_0_AST NULL
#define CATEGORY_SYSTEM_LABEL_AST NULL
#define CATEGORY_SYSTEM_INFO_0_AST NULL
#define CATEGORY_AUDIO_LABEL_AST NULL
#define CATEGORY_AUDIO_INFO_0_AST NULL
#define CATEGORY_NETWORK_LABEL_AST NULL
#define CATEGORY_NETWORK_INFO_0_AST NULL
#define VITA3K_BACKEND_RENDERER_LABEL_AST NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_AST NULL
#define OPTION_VAL_VULKAN_AST NULL
#define OPTION_VAL_OPENGL_AST NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_AST NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_AST NULL
#define OPTION_VAL_1_AST NULL
#define OPTION_VAL_2_AST NULL
#define OPTION_VAL_3_AST NULL
#define OPTION_VAL_4_AST NULL
#define VITA3K_SCREEN_FILTER_LABEL_AST NULL
#define VITA3K_SCREEN_FILTER_INFO_0_AST NULL
#define OPTION_VAL_BILINEAR_AST NULL
#define OPTION_VAL_NEAREST_AST NULL
#define OPTION_VAL_BICUBIC_AST NULL
#define OPTION_VAL_FXAA_AST NULL
#define OPTION_VAL_FSR_AST NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_AST NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_AST NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_AST NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_AST NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_AST NULL
#define OPTION_VAL_8_AST NULL
#define OPTION_VAL_16_AST NULL
#define VITA3K_V_SYNC_LABEL_AST NULL
#define VITA3K_V_SYNC_INFO_0_AST NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_AST NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_AST NULL
#define VITA3K_MEMORY_MAPPING_LABEL_AST NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_AST NULL
#define OPTION_VAL_DOUBLE_BUFFER_AST NULL
#define OPTION_VAL_EXTERNAL_HOST_AST NULL
#define OPTION_VAL_PAGE_TABLE_AST NULL
#define OPTION_VAL_NATIVE_BUFFER_AST NULL
#define VITA3K_HIGH_ACCURACY_LABEL_AST NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_AST NULL
#define VITA3K_CPU_OPT_LABEL_AST NULL
#define VITA3K_CPU_OPT_INFO_0_AST NULL
#define VITA3K_PKG_MODE_LABEL_AST NULL
#define VITA3K_PKG_MODE_INFO_0_AST NULL
#define OPTION_VAL_RUN_AST NULL
#define OPTION_VAL_INSTALL_AST NULL
#define VITA3K_PSTV_MODE_LABEL_AST NULL
#define VITA3K_PSTV_MODE_INFO_0_AST NULL
#define VITA3K_MODULES_MODE_LABEL_AST NULL
#define VITA3K_MODULES_MODE_INFO_0_AST NULL
#define OPTION_VAL_0_AST NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_AST NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_AST NULL
#define VITA3K_FPS_HACK_LABEL_AST NULL
#define VITA3K_FPS_HACK_INFO_0_AST NULL
#define VITA3K_SYS_BUTTON_LABEL_AST NULL
#define VITA3K_SYS_BUTTON_INFO_0_AST NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_AST NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_AST NULL
#define VITA3K_AUDIO_VOLUME_LABEL_AST NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_AST NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_AST NULL
#define OPTION_VAL_10_AST NULL
#define OPTION_VAL_20_AST NULL
#define OPTION_VAL_30_AST NULL
#define OPTION_VAL_40_AST NULL
#define OPTION_VAL_50_AST NULL
#define OPTION_VAL_60_AST NULL
#define OPTION_VAL_70_AST NULL
#define OPTION_VAL_80_AST NULL
#define OPTION_VAL_90_AST NULL
#define OPTION_VAL_100_AST NULL
#define VITA3K_NGS_ENABLE_LABEL_AST NULL
#define VITA3K_NGS_ENABLE_INFO_0_AST NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_AST NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_AST NULL
#define VITA3K_SURFACE_SYNC_LABEL_AST NULL
#define VITA3K_SURFACE_SYNC_INFO_0_AST NULL
#define OPTION_VAL_ENABLED_AST NULL
#define OPTION_VAL_DISABLED_AST NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_AST NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_AST NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_AST NULL
#define OPTION_VAL_5_AST NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_AST NULL
#define OPTION_VAL_15_AST NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_AST NULL
#define OPTION_VAL_25_AST NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_AST NULL

struct retro_core_option_v2_category option_cats_ast[] = {
    { "gpu", CATEGORY_GPU_LABEL_AST, CATEGORY_GPU_INFO_0_AST },
    { "cpu", CATEGORY_CPU_LABEL_AST, CATEGORY_CPU_INFO_0_AST },
    { "system", CATEGORY_SYSTEM_LABEL_AST, CATEGORY_SYSTEM_INFO_0_AST },
    { "audio", CATEGORY_AUDIO_LABEL_AST, CATEGORY_AUDIO_INFO_0_AST },
    { "network", CATEGORY_NETWORK_LABEL_AST, CATEGORY_NETWORK_INFO_0_AST },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_ast[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_AST,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_AST,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_AST },
            { "OpenGL", OPTION_VAL_OPENGL_AST },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_AST,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_AST,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_AST },
            { "2", OPTION_VAL_2_AST },
            { "3", OPTION_VAL_3_AST },
            { "4", OPTION_VAL_4_AST },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_AST,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_AST,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_AST },
            { "Nearest", OPTION_VAL_NEAREST_AST },
            { "Bicubic", OPTION_VAL_BICUBIC_AST },
            { "FXAA", OPTION_VAL_FXAA_AST },
            { "FSR", OPTION_VAL_FSR_AST },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_AST,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_AST,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_AST },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_AST },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_AST },
            { "8", OPTION_VAL_8_AST },
            { "16", OPTION_VAL_16_AST },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_AST,
        NULL,
        VITA3K_V_SYNC_INFO_0_AST,
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
        VITA3K_ASYNC_PIPELINE_LABEL_AST,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_AST,
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
        VITA3K_MEMORY_MAPPING_LABEL_AST,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_AST,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_AST },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_AST },
            { "page-table", OPTION_VAL_PAGE_TABLE_AST },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_AST },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_AST,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_AST,
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
        VITA3K_CPU_OPT_LABEL_AST,
        NULL,
        VITA3K_CPU_OPT_INFO_0_AST,
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
        VITA3K_PKG_MODE_LABEL_AST,
        NULL,
        VITA3K_PKG_MODE_INFO_0_AST,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_AST },
            { "install", OPTION_VAL_INSTALL_AST },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_AST,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_AST,
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
        VITA3K_MODULES_MODE_LABEL_AST,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_AST,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_AST },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_AST },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_AST },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_AST,
        NULL,
        VITA3K_FPS_HACK_INFO_0_AST,
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
        VITA3K_SYS_BUTTON_LABEL_AST,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_AST,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_AST },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_AST },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_AST,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_AST,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_AST },
            { "10", OPTION_VAL_10_AST },
            { "20", OPTION_VAL_20_AST },
            { "30", OPTION_VAL_30_AST },
            { "40", OPTION_VAL_40_AST },
            { "50", OPTION_VAL_50_AST },
            { "60", OPTION_VAL_60_AST },
            { "70", OPTION_VAL_70_AST },
            { "80", OPTION_VAL_80_AST },
            { "90", OPTION_VAL_90_AST },
            { "100", OPTION_VAL_100_AST },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_AST,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_AST,
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
        VITA3K_PSN_SIGNED_IN_LABEL_AST,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_AST,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_AST,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_AST,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_AST },
            { "disabled", OPTION_VAL_DISABLED_AST },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_AST,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_AST,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_AST },
            { "5", OPTION_VAL_5_AST },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_AST },
            { "15", OPTION_VAL_15_AST },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_AST },
            { "25", OPTION_VAL_25_AST },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_AST },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_ast = {
   option_cats_ast,
   option_defs_ast
};

/* RETRO_LANGUAGE_BE */

#define CATEGORY_GPU_LABEL_BE NULL
#define CATEGORY_GPU_INFO_0_BE NULL
#define CATEGORY_CPU_LABEL_BE NULL
#define CATEGORY_CPU_INFO_0_BE NULL
#define CATEGORY_SYSTEM_LABEL_BE NULL
#define CATEGORY_SYSTEM_INFO_0_BE NULL
#define CATEGORY_AUDIO_LABEL_BE NULL
#define CATEGORY_AUDIO_INFO_0_BE NULL
#define CATEGORY_NETWORK_LABEL_BE NULL
#define CATEGORY_NETWORK_INFO_0_BE NULL
#define VITA3K_BACKEND_RENDERER_LABEL_BE NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_BE NULL
#define OPTION_VAL_VULKAN_BE NULL
#define OPTION_VAL_OPENGL_BE NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_BE NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_BE NULL
#define OPTION_VAL_1_BE NULL
#define OPTION_VAL_2_BE NULL
#define OPTION_VAL_3_BE NULL
#define OPTION_VAL_4_BE NULL
#define VITA3K_SCREEN_FILTER_LABEL_BE NULL
#define VITA3K_SCREEN_FILTER_INFO_0_BE NULL
#define OPTION_VAL_BILINEAR_BE NULL
#define OPTION_VAL_NEAREST_BE NULL
#define OPTION_VAL_BICUBIC_BE NULL
#define OPTION_VAL_FXAA_BE NULL
#define OPTION_VAL_FSR_BE NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_BE NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_BE NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_BE NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_BE NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_BE NULL
#define OPTION_VAL_8_BE NULL
#define OPTION_VAL_16_BE NULL
#define VITA3K_V_SYNC_LABEL_BE NULL
#define VITA3K_V_SYNC_INFO_0_BE NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_BE NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_BE NULL
#define VITA3K_MEMORY_MAPPING_LABEL_BE NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_BE NULL
#define OPTION_VAL_DOUBLE_BUFFER_BE NULL
#define OPTION_VAL_EXTERNAL_HOST_BE NULL
#define OPTION_VAL_PAGE_TABLE_BE NULL
#define OPTION_VAL_NATIVE_BUFFER_BE NULL
#define VITA3K_HIGH_ACCURACY_LABEL_BE NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_BE NULL
#define VITA3K_CPU_OPT_LABEL_BE NULL
#define VITA3K_CPU_OPT_INFO_0_BE NULL
#define VITA3K_PKG_MODE_LABEL_BE NULL
#define VITA3K_PKG_MODE_INFO_0_BE NULL
#define OPTION_VAL_RUN_BE NULL
#define OPTION_VAL_INSTALL_BE NULL
#define VITA3K_PSTV_MODE_LABEL_BE NULL
#define VITA3K_PSTV_MODE_INFO_0_BE NULL
#define VITA3K_MODULES_MODE_LABEL_BE NULL
#define VITA3K_MODULES_MODE_INFO_0_BE NULL
#define OPTION_VAL_0_BE NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_BE NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_BE NULL
#define VITA3K_FPS_HACK_LABEL_BE NULL
#define VITA3K_FPS_HACK_INFO_0_BE NULL
#define VITA3K_SYS_BUTTON_LABEL_BE NULL
#define VITA3K_SYS_BUTTON_INFO_0_BE NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_BE NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_BE NULL
#define VITA3K_AUDIO_VOLUME_LABEL_BE NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_BE NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_BE NULL
#define OPTION_VAL_10_BE NULL
#define OPTION_VAL_20_BE NULL
#define OPTION_VAL_30_BE NULL
#define OPTION_VAL_40_BE NULL
#define OPTION_VAL_50_BE NULL
#define OPTION_VAL_60_BE NULL
#define OPTION_VAL_70_BE NULL
#define OPTION_VAL_80_BE NULL
#define OPTION_VAL_90_BE NULL
#define OPTION_VAL_100_BE NULL
#define VITA3K_NGS_ENABLE_LABEL_BE NULL
#define VITA3K_NGS_ENABLE_INFO_0_BE NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_BE NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_BE NULL
#define VITA3K_SURFACE_SYNC_LABEL_BE NULL
#define VITA3K_SURFACE_SYNC_INFO_0_BE NULL
#define OPTION_VAL_ENABLED_BE NULL
#define OPTION_VAL_DISABLED_BE NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_BE NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_BE NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_BE NULL
#define OPTION_VAL_5_BE NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_BE NULL
#define OPTION_VAL_15_BE NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_BE NULL
#define OPTION_VAL_25_BE NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_BE NULL

struct retro_core_option_v2_category option_cats_be[] = {
    { "gpu", CATEGORY_GPU_LABEL_BE, CATEGORY_GPU_INFO_0_BE },
    { "cpu", CATEGORY_CPU_LABEL_BE, CATEGORY_CPU_INFO_0_BE },
    { "system", CATEGORY_SYSTEM_LABEL_BE, CATEGORY_SYSTEM_INFO_0_BE },
    { "audio", CATEGORY_AUDIO_LABEL_BE, CATEGORY_AUDIO_INFO_0_BE },
    { "network", CATEGORY_NETWORK_LABEL_BE, CATEGORY_NETWORK_INFO_0_BE },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_be[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_BE,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_BE,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_BE },
            { "OpenGL", OPTION_VAL_OPENGL_BE },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_BE,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_BE,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_BE },
            { "2", OPTION_VAL_2_BE },
            { "3", OPTION_VAL_3_BE },
            { "4", OPTION_VAL_4_BE },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_BE,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_BE,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_BE },
            { "Nearest", OPTION_VAL_NEAREST_BE },
            { "Bicubic", OPTION_VAL_BICUBIC_BE },
            { "FXAA", OPTION_VAL_FXAA_BE },
            { "FSR", OPTION_VAL_FSR_BE },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_BE,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_BE,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_BE },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_BE },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_BE },
            { "8", OPTION_VAL_8_BE },
            { "16", OPTION_VAL_16_BE },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_BE,
        NULL,
        VITA3K_V_SYNC_INFO_0_BE,
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
        VITA3K_ASYNC_PIPELINE_LABEL_BE,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_BE,
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
        VITA3K_MEMORY_MAPPING_LABEL_BE,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_BE,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_BE },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_BE },
            { "page-table", OPTION_VAL_PAGE_TABLE_BE },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_BE },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_BE,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_BE,
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
        VITA3K_CPU_OPT_LABEL_BE,
        NULL,
        VITA3K_CPU_OPT_INFO_0_BE,
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
        VITA3K_PKG_MODE_LABEL_BE,
        NULL,
        VITA3K_PKG_MODE_INFO_0_BE,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_BE },
            { "install", OPTION_VAL_INSTALL_BE },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_BE,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_BE,
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
        VITA3K_MODULES_MODE_LABEL_BE,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_BE,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_BE },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_BE },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_BE },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_BE,
        NULL,
        VITA3K_FPS_HACK_INFO_0_BE,
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
        VITA3K_SYS_BUTTON_LABEL_BE,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_BE,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_BE },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_BE },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_BE,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_BE,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_BE },
            { "10", OPTION_VAL_10_BE },
            { "20", OPTION_VAL_20_BE },
            { "30", OPTION_VAL_30_BE },
            { "40", OPTION_VAL_40_BE },
            { "50", OPTION_VAL_50_BE },
            { "60", OPTION_VAL_60_BE },
            { "70", OPTION_VAL_70_BE },
            { "80", OPTION_VAL_80_BE },
            { "90", OPTION_VAL_90_BE },
            { "100", OPTION_VAL_100_BE },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_BE,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_BE,
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
        VITA3K_PSN_SIGNED_IN_LABEL_BE,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_BE,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_BE,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_BE,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_BE },
            { "disabled", OPTION_VAL_DISABLED_BE },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_BE,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_BE,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_BE },
            { "5", OPTION_VAL_5_BE },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_BE },
            { "15", OPTION_VAL_15_BE },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_BE },
            { "25", OPTION_VAL_25_BE },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_BE },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_be = {
   option_cats_be,
   option_defs_be
};

/* RETRO_LANGUAGE_CA */

#define CATEGORY_GPU_LABEL_CA NULL
#define CATEGORY_GPU_INFO_0_CA NULL
#define CATEGORY_CPU_LABEL_CA NULL
#define CATEGORY_CPU_INFO_0_CA NULL
#define CATEGORY_SYSTEM_LABEL_CA NULL
#define CATEGORY_SYSTEM_INFO_0_CA NULL
#define CATEGORY_AUDIO_LABEL_CA NULL
#define CATEGORY_AUDIO_INFO_0_CA NULL
#define CATEGORY_NETWORK_LABEL_CA NULL
#define CATEGORY_NETWORK_INFO_0_CA NULL
#define VITA3K_BACKEND_RENDERER_LABEL_CA NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_CA NULL
#define OPTION_VAL_VULKAN_CA NULL
#define OPTION_VAL_OPENGL_CA NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_CA NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_CA NULL
#define OPTION_VAL_1_CA NULL
#define OPTION_VAL_2_CA NULL
#define OPTION_VAL_3_CA NULL
#define OPTION_VAL_4_CA NULL
#define VITA3K_SCREEN_FILTER_LABEL_CA NULL
#define VITA3K_SCREEN_FILTER_INFO_0_CA NULL
#define OPTION_VAL_BILINEAR_CA NULL
#define OPTION_VAL_NEAREST_CA NULL
#define OPTION_VAL_BICUBIC_CA NULL
#define OPTION_VAL_FXAA_CA NULL
#define OPTION_VAL_FSR_CA NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_CA NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_CA NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_CA NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_CA NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_CA NULL
#define OPTION_VAL_8_CA NULL
#define OPTION_VAL_16_CA NULL
#define VITA3K_V_SYNC_LABEL_CA NULL
#define VITA3K_V_SYNC_INFO_0_CA NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_CA NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_CA NULL
#define VITA3K_MEMORY_MAPPING_LABEL_CA NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_CA NULL
#define OPTION_VAL_DOUBLE_BUFFER_CA NULL
#define OPTION_VAL_EXTERNAL_HOST_CA NULL
#define OPTION_VAL_PAGE_TABLE_CA NULL
#define OPTION_VAL_NATIVE_BUFFER_CA NULL
#define VITA3K_HIGH_ACCURACY_LABEL_CA NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_CA NULL
#define VITA3K_CPU_OPT_LABEL_CA NULL
#define VITA3K_CPU_OPT_INFO_0_CA NULL
#define VITA3K_PKG_MODE_LABEL_CA NULL
#define VITA3K_PKG_MODE_INFO_0_CA NULL
#define OPTION_VAL_RUN_CA NULL
#define OPTION_VAL_INSTALL_CA NULL
#define VITA3K_PSTV_MODE_LABEL_CA NULL
#define VITA3K_PSTV_MODE_INFO_0_CA NULL
#define VITA3K_MODULES_MODE_LABEL_CA NULL
#define VITA3K_MODULES_MODE_INFO_0_CA NULL
#define OPTION_VAL_0_CA NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_CA NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_CA NULL
#define VITA3K_FPS_HACK_LABEL_CA NULL
#define VITA3K_FPS_HACK_INFO_0_CA NULL
#define VITA3K_SYS_BUTTON_LABEL_CA NULL
#define VITA3K_SYS_BUTTON_INFO_0_CA NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_CA NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_CA NULL
#define VITA3K_AUDIO_VOLUME_LABEL_CA NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_CA NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_CA NULL
#define OPTION_VAL_10_CA NULL
#define OPTION_VAL_20_CA NULL
#define OPTION_VAL_30_CA NULL
#define OPTION_VAL_40_CA NULL
#define OPTION_VAL_50_CA NULL
#define OPTION_VAL_60_CA NULL
#define OPTION_VAL_70_CA NULL
#define OPTION_VAL_80_CA NULL
#define OPTION_VAL_90_CA NULL
#define OPTION_VAL_100_CA NULL
#define VITA3K_NGS_ENABLE_LABEL_CA NULL
#define VITA3K_NGS_ENABLE_INFO_0_CA NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_CA NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_CA NULL
#define VITA3K_SURFACE_SYNC_LABEL_CA NULL
#define VITA3K_SURFACE_SYNC_INFO_0_CA NULL
#define OPTION_VAL_ENABLED_CA NULL
#define OPTION_VAL_DISABLED_CA NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_CA NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_CA NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_CA NULL
#define OPTION_VAL_5_CA NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_CA NULL
#define OPTION_VAL_15_CA NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_CA NULL
#define OPTION_VAL_25_CA NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_CA NULL

struct retro_core_option_v2_category option_cats_ca[] = {
    { "gpu", CATEGORY_GPU_LABEL_CA, CATEGORY_GPU_INFO_0_CA },
    { "cpu", CATEGORY_CPU_LABEL_CA, CATEGORY_CPU_INFO_0_CA },
    { "system", CATEGORY_SYSTEM_LABEL_CA, CATEGORY_SYSTEM_INFO_0_CA },
    { "audio", CATEGORY_AUDIO_LABEL_CA, CATEGORY_AUDIO_INFO_0_CA },
    { "network", CATEGORY_NETWORK_LABEL_CA, CATEGORY_NETWORK_INFO_0_CA },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_ca[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_CA,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_CA,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_CA },
            { "OpenGL", OPTION_VAL_OPENGL_CA },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_CA,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_CA,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_CA },
            { "2", OPTION_VAL_2_CA },
            { "3", OPTION_VAL_3_CA },
            { "4", OPTION_VAL_4_CA },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_CA,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_CA,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_CA },
            { "Nearest", OPTION_VAL_NEAREST_CA },
            { "Bicubic", OPTION_VAL_BICUBIC_CA },
            { "FXAA", OPTION_VAL_FXAA_CA },
            { "FSR", OPTION_VAL_FSR_CA },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_CA,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_CA,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_CA },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_CA },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_CA },
            { "8", OPTION_VAL_8_CA },
            { "16", OPTION_VAL_16_CA },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_CA,
        NULL,
        VITA3K_V_SYNC_INFO_0_CA,
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
        VITA3K_ASYNC_PIPELINE_LABEL_CA,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_CA,
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
        VITA3K_MEMORY_MAPPING_LABEL_CA,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_CA,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_CA },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_CA },
            { "page-table", OPTION_VAL_PAGE_TABLE_CA },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_CA },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_CA,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_CA,
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
        VITA3K_CPU_OPT_LABEL_CA,
        NULL,
        VITA3K_CPU_OPT_INFO_0_CA,
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
        VITA3K_PKG_MODE_LABEL_CA,
        NULL,
        VITA3K_PKG_MODE_INFO_0_CA,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_CA },
            { "install", OPTION_VAL_INSTALL_CA },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_CA,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_CA,
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
        VITA3K_MODULES_MODE_LABEL_CA,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_CA,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_CA },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_CA },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_CA },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_CA,
        NULL,
        VITA3K_FPS_HACK_INFO_0_CA,
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
        VITA3K_SYS_BUTTON_LABEL_CA,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_CA,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_CA },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_CA },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_CA,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_CA,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_CA },
            { "10", OPTION_VAL_10_CA },
            { "20", OPTION_VAL_20_CA },
            { "30", OPTION_VAL_30_CA },
            { "40", OPTION_VAL_40_CA },
            { "50", OPTION_VAL_50_CA },
            { "60", OPTION_VAL_60_CA },
            { "70", OPTION_VAL_70_CA },
            { "80", OPTION_VAL_80_CA },
            { "90", OPTION_VAL_90_CA },
            { "100", OPTION_VAL_100_CA },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_CA,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_CA,
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
        VITA3K_PSN_SIGNED_IN_LABEL_CA,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_CA,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_CA,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_CA,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_CA },
            { "disabled", OPTION_VAL_DISABLED_CA },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_CA,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_CA,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_CA },
            { "5", OPTION_VAL_5_CA },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_CA },
            { "15", OPTION_VAL_15_CA },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_CA },
            { "25", OPTION_VAL_25_CA },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_CA },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_ca = {
   option_cats_ca,
   option_defs_ca
};

/* RETRO_LANGUAGE_CHS */

#define CATEGORY_GPU_LABEL_CHS NULL
#define CATEGORY_GPU_INFO_0_CHS NULL
#define CATEGORY_CPU_LABEL_CHS NULL
#define CATEGORY_CPU_INFO_0_CHS NULL
#define CATEGORY_SYSTEM_LABEL_CHS NULL
#define CATEGORY_SYSTEM_INFO_0_CHS NULL
#define CATEGORY_AUDIO_LABEL_CHS NULL
#define CATEGORY_AUDIO_INFO_0_CHS NULL
#define CATEGORY_NETWORK_LABEL_CHS NULL
#define CATEGORY_NETWORK_INFO_0_CHS NULL
#define VITA3K_BACKEND_RENDERER_LABEL_CHS NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_CHS NULL
#define OPTION_VAL_VULKAN_CHS NULL
#define OPTION_VAL_OPENGL_CHS NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_CHS NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_CHS NULL
#define OPTION_VAL_1_CHS NULL
#define OPTION_VAL_2_CHS NULL
#define OPTION_VAL_3_CHS NULL
#define OPTION_VAL_4_CHS NULL
#define VITA3K_SCREEN_FILTER_LABEL_CHS NULL
#define VITA3K_SCREEN_FILTER_INFO_0_CHS NULL
#define OPTION_VAL_BILINEAR_CHS NULL
#define OPTION_VAL_NEAREST_CHS NULL
#define OPTION_VAL_BICUBIC_CHS NULL
#define OPTION_VAL_FXAA_CHS NULL
#define OPTION_VAL_FSR_CHS NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_CHS NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_CHS NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_CHS NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_CHS NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_CHS NULL
#define OPTION_VAL_8_CHS NULL
#define OPTION_VAL_16_CHS NULL
#define VITA3K_V_SYNC_LABEL_CHS NULL
#define VITA3K_V_SYNC_INFO_0_CHS NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_CHS NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_CHS NULL
#define VITA3K_MEMORY_MAPPING_LABEL_CHS NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_CHS NULL
#define OPTION_VAL_DOUBLE_BUFFER_CHS NULL
#define OPTION_VAL_EXTERNAL_HOST_CHS NULL
#define OPTION_VAL_PAGE_TABLE_CHS NULL
#define OPTION_VAL_NATIVE_BUFFER_CHS NULL
#define VITA3K_HIGH_ACCURACY_LABEL_CHS NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_CHS NULL
#define VITA3K_CPU_OPT_LABEL_CHS NULL
#define VITA3K_CPU_OPT_INFO_0_CHS NULL
#define VITA3K_PKG_MODE_LABEL_CHS NULL
#define VITA3K_PKG_MODE_INFO_0_CHS NULL
#define OPTION_VAL_RUN_CHS NULL
#define OPTION_VAL_INSTALL_CHS NULL
#define VITA3K_PSTV_MODE_LABEL_CHS NULL
#define VITA3K_PSTV_MODE_INFO_0_CHS NULL
#define VITA3K_MODULES_MODE_LABEL_CHS NULL
#define VITA3K_MODULES_MODE_INFO_0_CHS NULL
#define OPTION_VAL_0_CHS NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_CHS NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_CHS NULL
#define VITA3K_FPS_HACK_LABEL_CHS NULL
#define VITA3K_FPS_HACK_INFO_0_CHS NULL
#define VITA3K_SYS_BUTTON_LABEL_CHS NULL
#define VITA3K_SYS_BUTTON_INFO_0_CHS NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_CHS NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_CHS NULL
#define VITA3K_AUDIO_VOLUME_LABEL_CHS NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_CHS NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_CHS NULL
#define OPTION_VAL_10_CHS NULL
#define OPTION_VAL_20_CHS NULL
#define OPTION_VAL_30_CHS NULL
#define OPTION_VAL_40_CHS NULL
#define OPTION_VAL_50_CHS NULL
#define OPTION_VAL_60_CHS NULL
#define OPTION_VAL_70_CHS NULL
#define OPTION_VAL_80_CHS NULL
#define OPTION_VAL_90_CHS NULL
#define OPTION_VAL_100_CHS NULL
#define VITA3K_NGS_ENABLE_LABEL_CHS NULL
#define VITA3K_NGS_ENABLE_INFO_0_CHS NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_CHS NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_CHS NULL
#define VITA3K_SURFACE_SYNC_LABEL_CHS NULL
#define VITA3K_SURFACE_SYNC_INFO_0_CHS NULL
#define OPTION_VAL_ENABLED_CHS NULL
#define OPTION_VAL_DISABLED_CHS NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_CHS NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_CHS NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_CHS NULL
#define OPTION_VAL_5_CHS NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_CHS NULL
#define OPTION_VAL_15_CHS NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_CHS NULL
#define OPTION_VAL_25_CHS NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_CHS NULL

struct retro_core_option_v2_category option_cats_chs[] = {
    { "gpu", CATEGORY_GPU_LABEL_CHS, CATEGORY_GPU_INFO_0_CHS },
    { "cpu", CATEGORY_CPU_LABEL_CHS, CATEGORY_CPU_INFO_0_CHS },
    { "system", CATEGORY_SYSTEM_LABEL_CHS, CATEGORY_SYSTEM_INFO_0_CHS },
    { "audio", CATEGORY_AUDIO_LABEL_CHS, CATEGORY_AUDIO_INFO_0_CHS },
    { "network", CATEGORY_NETWORK_LABEL_CHS, CATEGORY_NETWORK_INFO_0_CHS },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_chs[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_CHS,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_CHS,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_CHS },
            { "OpenGL", OPTION_VAL_OPENGL_CHS },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_CHS,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_CHS,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_CHS },
            { "2", OPTION_VAL_2_CHS },
            { "3", OPTION_VAL_3_CHS },
            { "4", OPTION_VAL_4_CHS },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_CHS,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_CHS,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_CHS },
            { "Nearest", OPTION_VAL_NEAREST_CHS },
            { "Bicubic", OPTION_VAL_BICUBIC_CHS },
            { "FXAA", OPTION_VAL_FXAA_CHS },
            { "FSR", OPTION_VAL_FSR_CHS },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_CHS,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_CHS,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_CHS },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_CHS },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_CHS },
            { "8", OPTION_VAL_8_CHS },
            { "16", OPTION_VAL_16_CHS },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_CHS,
        NULL,
        VITA3K_V_SYNC_INFO_0_CHS,
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
        VITA3K_ASYNC_PIPELINE_LABEL_CHS,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_CHS,
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
        VITA3K_MEMORY_MAPPING_LABEL_CHS,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_CHS,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_CHS },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_CHS },
            { "page-table", OPTION_VAL_PAGE_TABLE_CHS },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_CHS },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_CHS,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_CHS,
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
        VITA3K_CPU_OPT_LABEL_CHS,
        NULL,
        VITA3K_CPU_OPT_INFO_0_CHS,
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
        VITA3K_PKG_MODE_LABEL_CHS,
        NULL,
        VITA3K_PKG_MODE_INFO_0_CHS,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_CHS },
            { "install", OPTION_VAL_INSTALL_CHS },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_CHS,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_CHS,
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
        VITA3K_MODULES_MODE_LABEL_CHS,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_CHS,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_CHS },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_CHS },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_CHS },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_CHS,
        NULL,
        VITA3K_FPS_HACK_INFO_0_CHS,
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
        VITA3K_SYS_BUTTON_LABEL_CHS,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_CHS,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_CHS },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_CHS },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_CHS,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_CHS,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_CHS },
            { "10", OPTION_VAL_10_CHS },
            { "20", OPTION_VAL_20_CHS },
            { "30", OPTION_VAL_30_CHS },
            { "40", OPTION_VAL_40_CHS },
            { "50", OPTION_VAL_50_CHS },
            { "60", OPTION_VAL_60_CHS },
            { "70", OPTION_VAL_70_CHS },
            { "80", OPTION_VAL_80_CHS },
            { "90", OPTION_VAL_90_CHS },
            { "100", OPTION_VAL_100_CHS },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_CHS,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_CHS,
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
        VITA3K_PSN_SIGNED_IN_LABEL_CHS,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_CHS,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_CHS,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_CHS,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_CHS },
            { "disabled", OPTION_VAL_DISABLED_CHS },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_CHS,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_CHS,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_CHS },
            { "5", OPTION_VAL_5_CHS },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_CHS },
            { "15", OPTION_VAL_15_CHS },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_CHS },
            { "25", OPTION_VAL_25_CHS },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_CHS },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_chs = {
   option_cats_chs,
   option_defs_chs
};

/* RETRO_LANGUAGE_CHT */

#define CATEGORY_GPU_LABEL_CHT NULL
#define CATEGORY_GPU_INFO_0_CHT NULL
#define CATEGORY_CPU_LABEL_CHT NULL
#define CATEGORY_CPU_INFO_0_CHT NULL
#define CATEGORY_SYSTEM_LABEL_CHT NULL
#define CATEGORY_SYSTEM_INFO_0_CHT NULL
#define CATEGORY_AUDIO_LABEL_CHT NULL
#define CATEGORY_AUDIO_INFO_0_CHT NULL
#define CATEGORY_NETWORK_LABEL_CHT NULL
#define CATEGORY_NETWORK_INFO_0_CHT NULL
#define VITA3K_BACKEND_RENDERER_LABEL_CHT NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_CHT NULL
#define OPTION_VAL_VULKAN_CHT NULL
#define OPTION_VAL_OPENGL_CHT NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_CHT NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_CHT NULL
#define OPTION_VAL_1_CHT NULL
#define OPTION_VAL_2_CHT NULL
#define OPTION_VAL_3_CHT NULL
#define OPTION_VAL_4_CHT NULL
#define VITA3K_SCREEN_FILTER_LABEL_CHT NULL
#define VITA3K_SCREEN_FILTER_INFO_0_CHT NULL
#define OPTION_VAL_BILINEAR_CHT NULL
#define OPTION_VAL_NEAREST_CHT NULL
#define OPTION_VAL_BICUBIC_CHT NULL
#define OPTION_VAL_FXAA_CHT NULL
#define OPTION_VAL_FSR_CHT NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_CHT NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_CHT NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_CHT NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_CHT NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_CHT NULL
#define OPTION_VAL_8_CHT NULL
#define OPTION_VAL_16_CHT NULL
#define VITA3K_V_SYNC_LABEL_CHT NULL
#define VITA3K_V_SYNC_INFO_0_CHT NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_CHT NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_CHT NULL
#define VITA3K_MEMORY_MAPPING_LABEL_CHT NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_CHT NULL
#define OPTION_VAL_DOUBLE_BUFFER_CHT NULL
#define OPTION_VAL_EXTERNAL_HOST_CHT NULL
#define OPTION_VAL_PAGE_TABLE_CHT NULL
#define OPTION_VAL_NATIVE_BUFFER_CHT NULL
#define VITA3K_HIGH_ACCURACY_LABEL_CHT NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_CHT NULL
#define VITA3K_CPU_OPT_LABEL_CHT NULL
#define VITA3K_CPU_OPT_INFO_0_CHT NULL
#define VITA3K_PKG_MODE_LABEL_CHT NULL
#define VITA3K_PKG_MODE_INFO_0_CHT NULL
#define OPTION_VAL_RUN_CHT NULL
#define OPTION_VAL_INSTALL_CHT NULL
#define VITA3K_PSTV_MODE_LABEL_CHT NULL
#define VITA3K_PSTV_MODE_INFO_0_CHT NULL
#define VITA3K_MODULES_MODE_LABEL_CHT NULL
#define VITA3K_MODULES_MODE_INFO_0_CHT NULL
#define OPTION_VAL_0_CHT NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_CHT NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_CHT NULL
#define VITA3K_FPS_HACK_LABEL_CHT NULL
#define VITA3K_FPS_HACK_INFO_0_CHT NULL
#define VITA3K_SYS_BUTTON_LABEL_CHT NULL
#define VITA3K_SYS_BUTTON_INFO_0_CHT NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_CHT NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_CHT NULL
#define VITA3K_AUDIO_VOLUME_LABEL_CHT NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_CHT NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_CHT NULL
#define OPTION_VAL_10_CHT NULL
#define OPTION_VAL_20_CHT NULL
#define OPTION_VAL_30_CHT NULL
#define OPTION_VAL_40_CHT NULL
#define OPTION_VAL_50_CHT NULL
#define OPTION_VAL_60_CHT NULL
#define OPTION_VAL_70_CHT NULL
#define OPTION_VAL_80_CHT NULL
#define OPTION_VAL_90_CHT NULL
#define OPTION_VAL_100_CHT NULL
#define VITA3K_NGS_ENABLE_LABEL_CHT NULL
#define VITA3K_NGS_ENABLE_INFO_0_CHT NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_CHT NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_CHT NULL
#define VITA3K_SURFACE_SYNC_LABEL_CHT NULL
#define VITA3K_SURFACE_SYNC_INFO_0_CHT NULL
#define OPTION_VAL_ENABLED_CHT NULL
#define OPTION_VAL_DISABLED_CHT NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_CHT NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_CHT NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_CHT NULL
#define OPTION_VAL_5_CHT NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_CHT NULL
#define OPTION_VAL_15_CHT NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_CHT NULL
#define OPTION_VAL_25_CHT NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_CHT NULL

struct retro_core_option_v2_category option_cats_cht[] = {
    { "gpu", CATEGORY_GPU_LABEL_CHT, CATEGORY_GPU_INFO_0_CHT },
    { "cpu", CATEGORY_CPU_LABEL_CHT, CATEGORY_CPU_INFO_0_CHT },
    { "system", CATEGORY_SYSTEM_LABEL_CHT, CATEGORY_SYSTEM_INFO_0_CHT },
    { "audio", CATEGORY_AUDIO_LABEL_CHT, CATEGORY_AUDIO_INFO_0_CHT },
    { "network", CATEGORY_NETWORK_LABEL_CHT, CATEGORY_NETWORK_INFO_0_CHT },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_cht[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_CHT,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_CHT,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_CHT },
            { "OpenGL", OPTION_VAL_OPENGL_CHT },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_CHT,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_CHT,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_CHT },
            { "2", OPTION_VAL_2_CHT },
            { "3", OPTION_VAL_3_CHT },
            { "4", OPTION_VAL_4_CHT },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_CHT,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_CHT,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_CHT },
            { "Nearest", OPTION_VAL_NEAREST_CHT },
            { "Bicubic", OPTION_VAL_BICUBIC_CHT },
            { "FXAA", OPTION_VAL_FXAA_CHT },
            { "FSR", OPTION_VAL_FSR_CHT },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_CHT,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_CHT,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_CHT },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_CHT },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_CHT },
            { "8", OPTION_VAL_8_CHT },
            { "16", OPTION_VAL_16_CHT },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_CHT,
        NULL,
        VITA3K_V_SYNC_INFO_0_CHT,
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
        VITA3K_ASYNC_PIPELINE_LABEL_CHT,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_CHT,
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
        VITA3K_MEMORY_MAPPING_LABEL_CHT,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_CHT,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_CHT },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_CHT },
            { "page-table", OPTION_VAL_PAGE_TABLE_CHT },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_CHT },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_CHT,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_CHT,
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
        VITA3K_CPU_OPT_LABEL_CHT,
        NULL,
        VITA3K_CPU_OPT_INFO_0_CHT,
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
        VITA3K_PKG_MODE_LABEL_CHT,
        NULL,
        VITA3K_PKG_MODE_INFO_0_CHT,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_CHT },
            { "install", OPTION_VAL_INSTALL_CHT },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_CHT,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_CHT,
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
        VITA3K_MODULES_MODE_LABEL_CHT,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_CHT,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_CHT },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_CHT },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_CHT },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_CHT,
        NULL,
        VITA3K_FPS_HACK_INFO_0_CHT,
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
        VITA3K_SYS_BUTTON_LABEL_CHT,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_CHT,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_CHT },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_CHT },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_CHT,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_CHT,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_CHT },
            { "10", OPTION_VAL_10_CHT },
            { "20", OPTION_VAL_20_CHT },
            { "30", OPTION_VAL_30_CHT },
            { "40", OPTION_VAL_40_CHT },
            { "50", OPTION_VAL_50_CHT },
            { "60", OPTION_VAL_60_CHT },
            { "70", OPTION_VAL_70_CHT },
            { "80", OPTION_VAL_80_CHT },
            { "90", OPTION_VAL_90_CHT },
            { "100", OPTION_VAL_100_CHT },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_CHT,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_CHT,
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
        VITA3K_PSN_SIGNED_IN_LABEL_CHT,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_CHT,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_CHT,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_CHT,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_CHT },
            { "disabled", OPTION_VAL_DISABLED_CHT },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_CHT,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_CHT,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_CHT },
            { "5", OPTION_VAL_5_CHT },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_CHT },
            { "15", OPTION_VAL_15_CHT },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_CHT },
            { "25", OPTION_VAL_25_CHT },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_CHT },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_cht = {
   option_cats_cht,
   option_defs_cht
};

/* RETRO_LANGUAGE_CS */

#define CATEGORY_GPU_LABEL_CS NULL
#define CATEGORY_GPU_INFO_0_CS NULL
#define CATEGORY_CPU_LABEL_CS NULL
#define CATEGORY_CPU_INFO_0_CS NULL
#define CATEGORY_SYSTEM_LABEL_CS NULL
#define CATEGORY_SYSTEM_INFO_0_CS NULL
#define CATEGORY_AUDIO_LABEL_CS NULL
#define CATEGORY_AUDIO_INFO_0_CS NULL
#define CATEGORY_NETWORK_LABEL_CS NULL
#define CATEGORY_NETWORK_INFO_0_CS NULL
#define VITA3K_BACKEND_RENDERER_LABEL_CS NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_CS NULL
#define OPTION_VAL_VULKAN_CS NULL
#define OPTION_VAL_OPENGL_CS NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_CS NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_CS NULL
#define OPTION_VAL_1_CS NULL
#define OPTION_VAL_2_CS NULL
#define OPTION_VAL_3_CS NULL
#define OPTION_VAL_4_CS NULL
#define VITA3K_SCREEN_FILTER_LABEL_CS NULL
#define VITA3K_SCREEN_FILTER_INFO_0_CS NULL
#define OPTION_VAL_BILINEAR_CS NULL
#define OPTION_VAL_NEAREST_CS NULL
#define OPTION_VAL_BICUBIC_CS NULL
#define OPTION_VAL_FXAA_CS NULL
#define OPTION_VAL_FSR_CS NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_CS NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_CS NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_CS NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_CS NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_CS NULL
#define OPTION_VAL_8_CS NULL
#define OPTION_VAL_16_CS NULL
#define VITA3K_V_SYNC_LABEL_CS NULL
#define VITA3K_V_SYNC_INFO_0_CS NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_CS NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_CS NULL
#define VITA3K_MEMORY_MAPPING_LABEL_CS NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_CS NULL
#define OPTION_VAL_DOUBLE_BUFFER_CS NULL
#define OPTION_VAL_EXTERNAL_HOST_CS NULL
#define OPTION_VAL_PAGE_TABLE_CS NULL
#define OPTION_VAL_NATIVE_BUFFER_CS NULL
#define VITA3K_HIGH_ACCURACY_LABEL_CS NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_CS NULL
#define VITA3K_CPU_OPT_LABEL_CS NULL
#define VITA3K_CPU_OPT_INFO_0_CS NULL
#define VITA3K_PKG_MODE_LABEL_CS NULL
#define VITA3K_PKG_MODE_INFO_0_CS NULL
#define OPTION_VAL_RUN_CS NULL
#define OPTION_VAL_INSTALL_CS NULL
#define VITA3K_PSTV_MODE_LABEL_CS NULL
#define VITA3K_PSTV_MODE_INFO_0_CS NULL
#define VITA3K_MODULES_MODE_LABEL_CS NULL
#define VITA3K_MODULES_MODE_INFO_0_CS NULL
#define OPTION_VAL_0_CS NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_CS NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_CS NULL
#define VITA3K_FPS_HACK_LABEL_CS NULL
#define VITA3K_FPS_HACK_INFO_0_CS NULL
#define VITA3K_SYS_BUTTON_LABEL_CS NULL
#define VITA3K_SYS_BUTTON_INFO_0_CS NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_CS NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_CS NULL
#define VITA3K_AUDIO_VOLUME_LABEL_CS NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_CS NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_CS NULL
#define OPTION_VAL_10_CS NULL
#define OPTION_VAL_20_CS NULL
#define OPTION_VAL_30_CS NULL
#define OPTION_VAL_40_CS NULL
#define OPTION_VAL_50_CS NULL
#define OPTION_VAL_60_CS NULL
#define OPTION_VAL_70_CS NULL
#define OPTION_VAL_80_CS NULL
#define OPTION_VAL_90_CS NULL
#define OPTION_VAL_100_CS NULL
#define VITA3K_NGS_ENABLE_LABEL_CS NULL
#define VITA3K_NGS_ENABLE_INFO_0_CS NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_CS NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_CS NULL
#define VITA3K_SURFACE_SYNC_LABEL_CS NULL
#define VITA3K_SURFACE_SYNC_INFO_0_CS NULL
#define OPTION_VAL_ENABLED_CS NULL
#define OPTION_VAL_DISABLED_CS NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_CS NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_CS NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_CS NULL
#define OPTION_VAL_5_CS NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_CS NULL
#define OPTION_VAL_15_CS NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_CS NULL
#define OPTION_VAL_25_CS NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_CS NULL

struct retro_core_option_v2_category option_cats_cs[] = {
    { "gpu", CATEGORY_GPU_LABEL_CS, CATEGORY_GPU_INFO_0_CS },
    { "cpu", CATEGORY_CPU_LABEL_CS, CATEGORY_CPU_INFO_0_CS },
    { "system", CATEGORY_SYSTEM_LABEL_CS, CATEGORY_SYSTEM_INFO_0_CS },
    { "audio", CATEGORY_AUDIO_LABEL_CS, CATEGORY_AUDIO_INFO_0_CS },
    { "network", CATEGORY_NETWORK_LABEL_CS, CATEGORY_NETWORK_INFO_0_CS },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_cs[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_CS,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_CS,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_CS },
            { "OpenGL", OPTION_VAL_OPENGL_CS },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_CS,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_CS,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_CS },
            { "2", OPTION_VAL_2_CS },
            { "3", OPTION_VAL_3_CS },
            { "4", OPTION_VAL_4_CS },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_CS,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_CS,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_CS },
            { "Nearest", OPTION_VAL_NEAREST_CS },
            { "Bicubic", OPTION_VAL_BICUBIC_CS },
            { "FXAA", OPTION_VAL_FXAA_CS },
            { "FSR", OPTION_VAL_FSR_CS },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_CS,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_CS,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_CS },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_CS },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_CS },
            { "8", OPTION_VAL_8_CS },
            { "16", OPTION_VAL_16_CS },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_CS,
        NULL,
        VITA3K_V_SYNC_INFO_0_CS,
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
        VITA3K_ASYNC_PIPELINE_LABEL_CS,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_CS,
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
        VITA3K_MEMORY_MAPPING_LABEL_CS,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_CS,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_CS },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_CS },
            { "page-table", OPTION_VAL_PAGE_TABLE_CS },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_CS },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_CS,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_CS,
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
        VITA3K_CPU_OPT_LABEL_CS,
        NULL,
        VITA3K_CPU_OPT_INFO_0_CS,
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
        VITA3K_PKG_MODE_LABEL_CS,
        NULL,
        VITA3K_PKG_MODE_INFO_0_CS,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_CS },
            { "install", OPTION_VAL_INSTALL_CS },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_CS,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_CS,
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
        VITA3K_MODULES_MODE_LABEL_CS,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_CS,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_CS },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_CS },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_CS },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_CS,
        NULL,
        VITA3K_FPS_HACK_INFO_0_CS,
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
        VITA3K_SYS_BUTTON_LABEL_CS,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_CS,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_CS },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_CS },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_CS,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_CS,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_CS },
            { "10", OPTION_VAL_10_CS },
            { "20", OPTION_VAL_20_CS },
            { "30", OPTION_VAL_30_CS },
            { "40", OPTION_VAL_40_CS },
            { "50", OPTION_VAL_50_CS },
            { "60", OPTION_VAL_60_CS },
            { "70", OPTION_VAL_70_CS },
            { "80", OPTION_VAL_80_CS },
            { "90", OPTION_VAL_90_CS },
            { "100", OPTION_VAL_100_CS },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_CS,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_CS,
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
        VITA3K_PSN_SIGNED_IN_LABEL_CS,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_CS,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_CS,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_CS,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_CS },
            { "disabled", OPTION_VAL_DISABLED_CS },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_CS,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_CS,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_CS },
            { "5", OPTION_VAL_5_CS },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_CS },
            { "15", OPTION_VAL_15_CS },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_CS },
            { "25", OPTION_VAL_25_CS },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_CS },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_cs = {
   option_cats_cs,
   option_defs_cs
};

/* RETRO_LANGUAGE_DE */

#define CATEGORY_GPU_LABEL_DE NULL
#define CATEGORY_GPU_INFO_0_DE NULL
#define CATEGORY_CPU_LABEL_DE NULL
#define CATEGORY_CPU_INFO_0_DE NULL
#define CATEGORY_SYSTEM_LABEL_DE NULL
#define CATEGORY_SYSTEM_INFO_0_DE NULL
#define CATEGORY_AUDIO_LABEL_DE NULL
#define CATEGORY_AUDIO_INFO_0_DE NULL
#define CATEGORY_NETWORK_LABEL_DE NULL
#define CATEGORY_NETWORK_INFO_0_DE NULL
#define VITA3K_BACKEND_RENDERER_LABEL_DE NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_DE NULL
#define OPTION_VAL_VULKAN_DE NULL
#define OPTION_VAL_OPENGL_DE NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_DE NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_DE NULL
#define OPTION_VAL_1_DE NULL
#define OPTION_VAL_2_DE NULL
#define OPTION_VAL_3_DE NULL
#define OPTION_VAL_4_DE NULL
#define VITA3K_SCREEN_FILTER_LABEL_DE NULL
#define VITA3K_SCREEN_FILTER_INFO_0_DE NULL
#define OPTION_VAL_BILINEAR_DE NULL
#define OPTION_VAL_NEAREST_DE NULL
#define OPTION_VAL_BICUBIC_DE NULL
#define OPTION_VAL_FXAA_DE NULL
#define OPTION_VAL_FSR_DE NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_DE NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_DE NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_DE NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_DE NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_DE NULL
#define OPTION_VAL_8_DE NULL
#define OPTION_VAL_16_DE NULL
#define VITA3K_V_SYNC_LABEL_DE NULL
#define VITA3K_V_SYNC_INFO_0_DE NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_DE NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_DE NULL
#define VITA3K_MEMORY_MAPPING_LABEL_DE NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_DE NULL
#define OPTION_VAL_DOUBLE_BUFFER_DE NULL
#define OPTION_VAL_EXTERNAL_HOST_DE NULL
#define OPTION_VAL_PAGE_TABLE_DE NULL
#define OPTION_VAL_NATIVE_BUFFER_DE NULL
#define VITA3K_HIGH_ACCURACY_LABEL_DE NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_DE NULL
#define VITA3K_CPU_OPT_LABEL_DE NULL
#define VITA3K_CPU_OPT_INFO_0_DE NULL
#define VITA3K_PKG_MODE_LABEL_DE NULL
#define VITA3K_PKG_MODE_INFO_0_DE NULL
#define OPTION_VAL_RUN_DE NULL
#define OPTION_VAL_INSTALL_DE NULL
#define VITA3K_PSTV_MODE_LABEL_DE NULL
#define VITA3K_PSTV_MODE_INFO_0_DE NULL
#define VITA3K_MODULES_MODE_LABEL_DE NULL
#define VITA3K_MODULES_MODE_INFO_0_DE NULL
#define OPTION_VAL_0_DE NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_DE NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_DE NULL
#define VITA3K_FPS_HACK_LABEL_DE NULL
#define VITA3K_FPS_HACK_INFO_0_DE NULL
#define VITA3K_SYS_BUTTON_LABEL_DE NULL
#define VITA3K_SYS_BUTTON_INFO_0_DE NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_DE NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_DE NULL
#define VITA3K_AUDIO_VOLUME_LABEL_DE NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_DE NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_DE NULL
#define OPTION_VAL_10_DE NULL
#define OPTION_VAL_20_DE NULL
#define OPTION_VAL_30_DE NULL
#define OPTION_VAL_40_DE NULL
#define OPTION_VAL_50_DE NULL
#define OPTION_VAL_60_DE NULL
#define OPTION_VAL_70_DE NULL
#define OPTION_VAL_80_DE NULL
#define OPTION_VAL_90_DE NULL
#define OPTION_VAL_100_DE NULL
#define VITA3K_NGS_ENABLE_LABEL_DE NULL
#define VITA3K_NGS_ENABLE_INFO_0_DE NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_DE NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_DE NULL
#define VITA3K_SURFACE_SYNC_LABEL_DE NULL
#define VITA3K_SURFACE_SYNC_INFO_0_DE NULL
#define OPTION_VAL_ENABLED_DE NULL
#define OPTION_VAL_DISABLED_DE NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_DE NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_DE NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_DE NULL
#define OPTION_VAL_5_DE NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_DE NULL
#define OPTION_VAL_15_DE NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_DE NULL
#define OPTION_VAL_25_DE NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_DE NULL

struct retro_core_option_v2_category option_cats_de[] = {
    { "gpu", CATEGORY_GPU_LABEL_DE, CATEGORY_GPU_INFO_0_DE },
    { "cpu", CATEGORY_CPU_LABEL_DE, CATEGORY_CPU_INFO_0_DE },
    { "system", CATEGORY_SYSTEM_LABEL_DE, CATEGORY_SYSTEM_INFO_0_DE },
    { "audio", CATEGORY_AUDIO_LABEL_DE, CATEGORY_AUDIO_INFO_0_DE },
    { "network", CATEGORY_NETWORK_LABEL_DE, CATEGORY_NETWORK_INFO_0_DE },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_de[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_DE,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_DE,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_DE },
            { "OpenGL", OPTION_VAL_OPENGL_DE },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_DE,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_DE,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_DE },
            { "2", OPTION_VAL_2_DE },
            { "3", OPTION_VAL_3_DE },
            { "4", OPTION_VAL_4_DE },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_DE,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_DE,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_DE },
            { "Nearest", OPTION_VAL_NEAREST_DE },
            { "Bicubic", OPTION_VAL_BICUBIC_DE },
            { "FXAA", OPTION_VAL_FXAA_DE },
            { "FSR", OPTION_VAL_FSR_DE },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_DE,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_DE,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_DE },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_DE },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_DE },
            { "8", OPTION_VAL_8_DE },
            { "16", OPTION_VAL_16_DE },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_DE,
        NULL,
        VITA3K_V_SYNC_INFO_0_DE,
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
        VITA3K_ASYNC_PIPELINE_LABEL_DE,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_DE,
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
        VITA3K_MEMORY_MAPPING_LABEL_DE,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_DE,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_DE },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_DE },
            { "page-table", OPTION_VAL_PAGE_TABLE_DE },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_DE },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_DE,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_DE,
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
        VITA3K_CPU_OPT_LABEL_DE,
        NULL,
        VITA3K_CPU_OPT_INFO_0_DE,
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
        VITA3K_PKG_MODE_LABEL_DE,
        NULL,
        VITA3K_PKG_MODE_INFO_0_DE,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_DE },
            { "install", OPTION_VAL_INSTALL_DE },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_DE,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_DE,
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
        VITA3K_MODULES_MODE_LABEL_DE,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_DE,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_DE },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_DE },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_DE },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_DE,
        NULL,
        VITA3K_FPS_HACK_INFO_0_DE,
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
        VITA3K_SYS_BUTTON_LABEL_DE,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_DE,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_DE },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_DE },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_DE,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_DE,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_DE },
            { "10", OPTION_VAL_10_DE },
            { "20", OPTION_VAL_20_DE },
            { "30", OPTION_VAL_30_DE },
            { "40", OPTION_VAL_40_DE },
            { "50", OPTION_VAL_50_DE },
            { "60", OPTION_VAL_60_DE },
            { "70", OPTION_VAL_70_DE },
            { "80", OPTION_VAL_80_DE },
            { "90", OPTION_VAL_90_DE },
            { "100", OPTION_VAL_100_DE },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_DE,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_DE,
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
        VITA3K_PSN_SIGNED_IN_LABEL_DE,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_DE,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_DE,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_DE,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_DE },
            { "disabled", OPTION_VAL_DISABLED_DE },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_DE,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_DE,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_DE },
            { "5", OPTION_VAL_5_DE },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_DE },
            { "15", OPTION_VAL_15_DE },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_DE },
            { "25", OPTION_VAL_25_DE },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_DE },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_de = {
   option_cats_de,
   option_defs_de
};

/* RETRO_LANGUAGE_EL */

#define CATEGORY_GPU_LABEL_EL NULL
#define CATEGORY_GPU_INFO_0_EL NULL
#define CATEGORY_CPU_LABEL_EL NULL
#define CATEGORY_CPU_INFO_0_EL NULL
#define CATEGORY_SYSTEM_LABEL_EL NULL
#define CATEGORY_SYSTEM_INFO_0_EL NULL
#define CATEGORY_AUDIO_LABEL_EL NULL
#define CATEGORY_AUDIO_INFO_0_EL NULL
#define CATEGORY_NETWORK_LABEL_EL NULL
#define CATEGORY_NETWORK_INFO_0_EL NULL
#define VITA3K_BACKEND_RENDERER_LABEL_EL NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_EL NULL
#define OPTION_VAL_VULKAN_EL NULL
#define OPTION_VAL_OPENGL_EL NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_EL NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_EL NULL
#define OPTION_VAL_1_EL NULL
#define OPTION_VAL_2_EL NULL
#define OPTION_VAL_3_EL NULL
#define OPTION_VAL_4_EL NULL
#define VITA3K_SCREEN_FILTER_LABEL_EL NULL
#define VITA3K_SCREEN_FILTER_INFO_0_EL NULL
#define OPTION_VAL_BILINEAR_EL NULL
#define OPTION_VAL_NEAREST_EL NULL
#define OPTION_VAL_BICUBIC_EL NULL
#define OPTION_VAL_FXAA_EL NULL
#define OPTION_VAL_FSR_EL NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_EL NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_EL NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_EL NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_EL NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_EL NULL
#define OPTION_VAL_8_EL NULL
#define OPTION_VAL_16_EL NULL
#define VITA3K_V_SYNC_LABEL_EL NULL
#define VITA3K_V_SYNC_INFO_0_EL NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_EL NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_EL NULL
#define VITA3K_MEMORY_MAPPING_LABEL_EL NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_EL NULL
#define OPTION_VAL_DOUBLE_BUFFER_EL NULL
#define OPTION_VAL_EXTERNAL_HOST_EL NULL
#define OPTION_VAL_PAGE_TABLE_EL NULL
#define OPTION_VAL_NATIVE_BUFFER_EL NULL
#define VITA3K_HIGH_ACCURACY_LABEL_EL NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_EL NULL
#define VITA3K_CPU_OPT_LABEL_EL NULL
#define VITA3K_CPU_OPT_INFO_0_EL NULL
#define VITA3K_PKG_MODE_LABEL_EL NULL
#define VITA3K_PKG_MODE_INFO_0_EL NULL
#define OPTION_VAL_RUN_EL NULL
#define OPTION_VAL_INSTALL_EL NULL
#define VITA3K_PSTV_MODE_LABEL_EL NULL
#define VITA3K_PSTV_MODE_INFO_0_EL NULL
#define VITA3K_MODULES_MODE_LABEL_EL NULL
#define VITA3K_MODULES_MODE_INFO_0_EL NULL
#define OPTION_VAL_0_EL NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_EL NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_EL NULL
#define VITA3K_FPS_HACK_LABEL_EL NULL
#define VITA3K_FPS_HACK_INFO_0_EL NULL
#define VITA3K_SYS_BUTTON_LABEL_EL NULL
#define VITA3K_SYS_BUTTON_INFO_0_EL NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_EL NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_EL NULL
#define VITA3K_AUDIO_VOLUME_LABEL_EL NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_EL NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_EL NULL
#define OPTION_VAL_10_EL NULL
#define OPTION_VAL_20_EL NULL
#define OPTION_VAL_30_EL NULL
#define OPTION_VAL_40_EL NULL
#define OPTION_VAL_50_EL NULL
#define OPTION_VAL_60_EL NULL
#define OPTION_VAL_70_EL NULL
#define OPTION_VAL_80_EL NULL
#define OPTION_VAL_90_EL NULL
#define OPTION_VAL_100_EL NULL
#define VITA3K_NGS_ENABLE_LABEL_EL NULL
#define VITA3K_NGS_ENABLE_INFO_0_EL NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_EL NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_EL NULL
#define VITA3K_SURFACE_SYNC_LABEL_EL NULL
#define VITA3K_SURFACE_SYNC_INFO_0_EL NULL
#define OPTION_VAL_ENABLED_EL NULL
#define OPTION_VAL_DISABLED_EL NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_EL NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_EL NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_EL NULL
#define OPTION_VAL_5_EL NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_EL NULL
#define OPTION_VAL_15_EL NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_EL NULL
#define OPTION_VAL_25_EL NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_EL NULL

struct retro_core_option_v2_category option_cats_el[] = {
    { "gpu", CATEGORY_GPU_LABEL_EL, CATEGORY_GPU_INFO_0_EL },
    { "cpu", CATEGORY_CPU_LABEL_EL, CATEGORY_CPU_INFO_0_EL },
    { "system", CATEGORY_SYSTEM_LABEL_EL, CATEGORY_SYSTEM_INFO_0_EL },
    { "audio", CATEGORY_AUDIO_LABEL_EL, CATEGORY_AUDIO_INFO_0_EL },
    { "network", CATEGORY_NETWORK_LABEL_EL, CATEGORY_NETWORK_INFO_0_EL },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_el[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_EL,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_EL,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_EL },
            { "OpenGL", OPTION_VAL_OPENGL_EL },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_EL,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_EL,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_EL },
            { "2", OPTION_VAL_2_EL },
            { "3", OPTION_VAL_3_EL },
            { "4", OPTION_VAL_4_EL },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_EL,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_EL,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_EL },
            { "Nearest", OPTION_VAL_NEAREST_EL },
            { "Bicubic", OPTION_VAL_BICUBIC_EL },
            { "FXAA", OPTION_VAL_FXAA_EL },
            { "FSR", OPTION_VAL_FSR_EL },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_EL,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_EL,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_EL },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_EL },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_EL },
            { "8", OPTION_VAL_8_EL },
            { "16", OPTION_VAL_16_EL },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_EL,
        NULL,
        VITA3K_V_SYNC_INFO_0_EL,
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
        VITA3K_ASYNC_PIPELINE_LABEL_EL,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_EL,
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
        VITA3K_MEMORY_MAPPING_LABEL_EL,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_EL,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_EL },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_EL },
            { "page-table", OPTION_VAL_PAGE_TABLE_EL },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_EL },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_EL,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_EL,
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
        VITA3K_CPU_OPT_LABEL_EL,
        NULL,
        VITA3K_CPU_OPT_INFO_0_EL,
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
        VITA3K_PKG_MODE_LABEL_EL,
        NULL,
        VITA3K_PKG_MODE_INFO_0_EL,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_EL },
            { "install", OPTION_VAL_INSTALL_EL },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_EL,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_EL,
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
        VITA3K_MODULES_MODE_LABEL_EL,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_EL,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_EL },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_EL },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_EL },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_EL,
        NULL,
        VITA3K_FPS_HACK_INFO_0_EL,
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
        VITA3K_SYS_BUTTON_LABEL_EL,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_EL,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_EL },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_EL },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_EL,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_EL,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_EL },
            { "10", OPTION_VAL_10_EL },
            { "20", OPTION_VAL_20_EL },
            { "30", OPTION_VAL_30_EL },
            { "40", OPTION_VAL_40_EL },
            { "50", OPTION_VAL_50_EL },
            { "60", OPTION_VAL_60_EL },
            { "70", OPTION_VAL_70_EL },
            { "80", OPTION_VAL_80_EL },
            { "90", OPTION_VAL_90_EL },
            { "100", OPTION_VAL_100_EL },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_EL,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_EL,
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
        VITA3K_PSN_SIGNED_IN_LABEL_EL,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_EL,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_EL,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_EL,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_EL },
            { "disabled", OPTION_VAL_DISABLED_EL },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_EL,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_EL,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_EL },
            { "5", OPTION_VAL_5_EL },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_EL },
            { "15", OPTION_VAL_15_EL },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_EL },
            { "25", OPTION_VAL_25_EL },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_EL },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_el = {
   option_cats_el,
   option_defs_el
};

/* RETRO_LANGUAGE_EN */

#define CATEGORY_GPU_LABEL_EN NULL
#define CATEGORY_GPU_INFO_0_EN NULL
#define CATEGORY_CPU_LABEL_EN NULL
#define CATEGORY_CPU_INFO_0_EN NULL
#define CATEGORY_SYSTEM_LABEL_EN NULL
#define CATEGORY_SYSTEM_INFO_0_EN NULL
#define CATEGORY_AUDIO_LABEL_EN NULL
#define CATEGORY_AUDIO_INFO_0_EN NULL
#define CATEGORY_NETWORK_LABEL_EN NULL
#define CATEGORY_NETWORK_INFO_0_EN NULL
#define VITA3K_BACKEND_RENDERER_LABEL_EN NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_EN NULL
#define OPTION_VAL_VULKAN_EN NULL
#define OPTION_VAL_OPENGL_EN NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_EN NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_EN NULL
#define OPTION_VAL_1_EN NULL
#define OPTION_VAL_2_EN NULL
#define OPTION_VAL_3_EN NULL
#define OPTION_VAL_4_EN NULL
#define VITA3K_SCREEN_FILTER_LABEL_EN NULL
#define VITA3K_SCREEN_FILTER_INFO_0_EN NULL
#define OPTION_VAL_BILINEAR_EN NULL
#define OPTION_VAL_NEAREST_EN NULL
#define OPTION_VAL_BICUBIC_EN NULL
#define OPTION_VAL_FXAA_EN NULL
#define OPTION_VAL_FSR_EN NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_EN NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_EN NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_EN NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_EN NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_EN NULL
#define OPTION_VAL_8_EN NULL
#define OPTION_VAL_16_EN NULL
#define VITA3K_V_SYNC_LABEL_EN NULL
#define VITA3K_V_SYNC_INFO_0_EN NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_EN NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_EN NULL
#define VITA3K_MEMORY_MAPPING_LABEL_EN NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_EN NULL
#define OPTION_VAL_DOUBLE_BUFFER_EN NULL
#define OPTION_VAL_EXTERNAL_HOST_EN NULL
#define OPTION_VAL_PAGE_TABLE_EN NULL
#define OPTION_VAL_NATIVE_BUFFER_EN NULL
#define VITA3K_HIGH_ACCURACY_LABEL_EN NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_EN NULL
#define VITA3K_CPU_OPT_LABEL_EN NULL
#define VITA3K_CPU_OPT_INFO_0_EN NULL
#define VITA3K_PKG_MODE_LABEL_EN NULL
#define VITA3K_PKG_MODE_INFO_0_EN NULL
#define OPTION_VAL_RUN_EN NULL
#define OPTION_VAL_INSTALL_EN NULL
#define VITA3K_PSTV_MODE_LABEL_EN NULL
#define VITA3K_PSTV_MODE_INFO_0_EN NULL
#define VITA3K_MODULES_MODE_LABEL_EN NULL
#define VITA3K_MODULES_MODE_INFO_0_EN NULL
#define OPTION_VAL_0_EN NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_EN NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_EN NULL
#define VITA3K_FPS_HACK_LABEL_EN NULL
#define VITA3K_FPS_HACK_INFO_0_EN NULL
#define VITA3K_SYS_BUTTON_LABEL_EN NULL
#define VITA3K_SYS_BUTTON_INFO_0_EN NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_EN NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_EN NULL
#define VITA3K_AUDIO_VOLUME_LABEL_EN NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_EN NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_EN NULL
#define OPTION_VAL_10_EN NULL
#define OPTION_VAL_20_EN NULL
#define OPTION_VAL_30_EN NULL
#define OPTION_VAL_40_EN NULL
#define OPTION_VAL_50_EN NULL
#define OPTION_VAL_60_EN NULL
#define OPTION_VAL_70_EN NULL
#define OPTION_VAL_80_EN NULL
#define OPTION_VAL_90_EN NULL
#define OPTION_VAL_100_EN NULL
#define VITA3K_NGS_ENABLE_LABEL_EN NULL
#define VITA3K_NGS_ENABLE_INFO_0_EN NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_EN NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_EN NULL
#define VITA3K_SURFACE_SYNC_LABEL_EN NULL
#define VITA3K_SURFACE_SYNC_INFO_0_EN NULL
#define OPTION_VAL_ENABLED_EN NULL
#define OPTION_VAL_DISABLED_EN NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_EN NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_EN NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_EN NULL
#define OPTION_VAL_5_EN NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_EN NULL
#define OPTION_VAL_15_EN NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_EN NULL
#define OPTION_VAL_25_EN NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_EN NULL

struct retro_core_option_v2_category option_cats_en[] = {
    { "gpu", CATEGORY_GPU_LABEL_EN, CATEGORY_GPU_INFO_0_EN },
    { "cpu", CATEGORY_CPU_LABEL_EN, CATEGORY_CPU_INFO_0_EN },
    { "system", CATEGORY_SYSTEM_LABEL_EN, CATEGORY_SYSTEM_INFO_0_EN },
    { "audio", CATEGORY_AUDIO_LABEL_EN, CATEGORY_AUDIO_INFO_0_EN },
    { "network", CATEGORY_NETWORK_LABEL_EN, CATEGORY_NETWORK_INFO_0_EN },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_en[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_EN,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_EN,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_EN },
            { "OpenGL", OPTION_VAL_OPENGL_EN },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_EN,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_EN,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_EN },
            { "2", OPTION_VAL_2_EN },
            { "3", OPTION_VAL_3_EN },
            { "4", OPTION_VAL_4_EN },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_EN,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_EN,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_EN },
            { "Nearest", OPTION_VAL_NEAREST_EN },
            { "Bicubic", OPTION_VAL_BICUBIC_EN },
            { "FXAA", OPTION_VAL_FXAA_EN },
            { "FSR", OPTION_VAL_FSR_EN },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_EN,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_EN,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_EN },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_EN },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_EN },
            { "8", OPTION_VAL_8_EN },
            { "16", OPTION_VAL_16_EN },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_EN,
        NULL,
        VITA3K_V_SYNC_INFO_0_EN,
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
        VITA3K_ASYNC_PIPELINE_LABEL_EN,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_EN,
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
        VITA3K_MEMORY_MAPPING_LABEL_EN,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_EN,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_EN },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_EN },
            { "page-table", OPTION_VAL_PAGE_TABLE_EN },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_EN },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_EN,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_EN,
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
        VITA3K_CPU_OPT_LABEL_EN,
        NULL,
        VITA3K_CPU_OPT_INFO_0_EN,
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
        VITA3K_PKG_MODE_LABEL_EN,
        NULL,
        VITA3K_PKG_MODE_INFO_0_EN,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_EN },
            { "install", OPTION_VAL_INSTALL_EN },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_EN,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_EN,
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
        VITA3K_MODULES_MODE_LABEL_EN,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_EN,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_EN },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_EN },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_EN },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_EN,
        NULL,
        VITA3K_FPS_HACK_INFO_0_EN,
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
        VITA3K_SYS_BUTTON_LABEL_EN,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_EN,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_EN },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_EN },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_EN,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_EN,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_EN },
            { "10", OPTION_VAL_10_EN },
            { "20", OPTION_VAL_20_EN },
            { "30", OPTION_VAL_30_EN },
            { "40", OPTION_VAL_40_EN },
            { "50", OPTION_VAL_50_EN },
            { "60", OPTION_VAL_60_EN },
            { "70", OPTION_VAL_70_EN },
            { "80", OPTION_VAL_80_EN },
            { "90", OPTION_VAL_90_EN },
            { "100", OPTION_VAL_100_EN },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_EN,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_EN,
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
        VITA3K_PSN_SIGNED_IN_LABEL_EN,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_EN,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_EN,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_EN,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_EN },
            { "disabled", OPTION_VAL_DISABLED_EN },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_EN,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_EN,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_EN },
            { "5", OPTION_VAL_5_EN },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_EN },
            { "15", OPTION_VAL_15_EN },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_EN },
            { "25", OPTION_VAL_25_EN },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_EN },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_en = {
   option_cats_en,
   option_defs_en
};

/* RETRO_LANGUAGE_EO */

#define CATEGORY_GPU_LABEL_EO NULL
#define CATEGORY_GPU_INFO_0_EO NULL
#define CATEGORY_CPU_LABEL_EO NULL
#define CATEGORY_CPU_INFO_0_EO NULL
#define CATEGORY_SYSTEM_LABEL_EO NULL
#define CATEGORY_SYSTEM_INFO_0_EO NULL
#define CATEGORY_AUDIO_LABEL_EO NULL
#define CATEGORY_AUDIO_INFO_0_EO NULL
#define CATEGORY_NETWORK_LABEL_EO NULL
#define CATEGORY_NETWORK_INFO_0_EO NULL
#define VITA3K_BACKEND_RENDERER_LABEL_EO NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_EO NULL
#define OPTION_VAL_VULKAN_EO NULL
#define OPTION_VAL_OPENGL_EO NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_EO NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_EO NULL
#define OPTION_VAL_1_EO NULL
#define OPTION_VAL_2_EO NULL
#define OPTION_VAL_3_EO NULL
#define OPTION_VAL_4_EO NULL
#define VITA3K_SCREEN_FILTER_LABEL_EO NULL
#define VITA3K_SCREEN_FILTER_INFO_0_EO NULL
#define OPTION_VAL_BILINEAR_EO NULL
#define OPTION_VAL_NEAREST_EO NULL
#define OPTION_VAL_BICUBIC_EO NULL
#define OPTION_VAL_FXAA_EO NULL
#define OPTION_VAL_FSR_EO NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_EO NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_EO NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_EO NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_EO NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_EO NULL
#define OPTION_VAL_8_EO NULL
#define OPTION_VAL_16_EO NULL
#define VITA3K_V_SYNC_LABEL_EO NULL
#define VITA3K_V_SYNC_INFO_0_EO NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_EO NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_EO NULL
#define VITA3K_MEMORY_MAPPING_LABEL_EO NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_EO NULL
#define OPTION_VAL_DOUBLE_BUFFER_EO NULL
#define OPTION_VAL_EXTERNAL_HOST_EO NULL
#define OPTION_VAL_PAGE_TABLE_EO NULL
#define OPTION_VAL_NATIVE_BUFFER_EO NULL
#define VITA3K_HIGH_ACCURACY_LABEL_EO NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_EO NULL
#define VITA3K_CPU_OPT_LABEL_EO NULL
#define VITA3K_CPU_OPT_INFO_0_EO NULL
#define VITA3K_PKG_MODE_LABEL_EO NULL
#define VITA3K_PKG_MODE_INFO_0_EO NULL
#define OPTION_VAL_RUN_EO NULL
#define OPTION_VAL_INSTALL_EO NULL
#define VITA3K_PSTV_MODE_LABEL_EO NULL
#define VITA3K_PSTV_MODE_INFO_0_EO NULL
#define VITA3K_MODULES_MODE_LABEL_EO NULL
#define VITA3K_MODULES_MODE_INFO_0_EO NULL
#define OPTION_VAL_0_EO NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_EO NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_EO NULL
#define VITA3K_FPS_HACK_LABEL_EO NULL
#define VITA3K_FPS_HACK_INFO_0_EO NULL
#define VITA3K_SYS_BUTTON_LABEL_EO NULL
#define VITA3K_SYS_BUTTON_INFO_0_EO NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_EO NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_EO NULL
#define VITA3K_AUDIO_VOLUME_LABEL_EO NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_EO NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_EO NULL
#define OPTION_VAL_10_EO NULL
#define OPTION_VAL_20_EO NULL
#define OPTION_VAL_30_EO NULL
#define OPTION_VAL_40_EO NULL
#define OPTION_VAL_50_EO NULL
#define OPTION_VAL_60_EO NULL
#define OPTION_VAL_70_EO NULL
#define OPTION_VAL_80_EO NULL
#define OPTION_VAL_90_EO NULL
#define OPTION_VAL_100_EO NULL
#define VITA3K_NGS_ENABLE_LABEL_EO NULL
#define VITA3K_NGS_ENABLE_INFO_0_EO NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_EO NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_EO NULL
#define VITA3K_SURFACE_SYNC_LABEL_EO NULL
#define VITA3K_SURFACE_SYNC_INFO_0_EO NULL
#define OPTION_VAL_ENABLED_EO NULL
#define OPTION_VAL_DISABLED_EO NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_EO NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_EO NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_EO NULL
#define OPTION_VAL_5_EO NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_EO NULL
#define OPTION_VAL_15_EO NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_EO NULL
#define OPTION_VAL_25_EO NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_EO NULL

struct retro_core_option_v2_category option_cats_eo[] = {
    { "gpu", CATEGORY_GPU_LABEL_EO, CATEGORY_GPU_INFO_0_EO },
    { "cpu", CATEGORY_CPU_LABEL_EO, CATEGORY_CPU_INFO_0_EO },
    { "system", CATEGORY_SYSTEM_LABEL_EO, CATEGORY_SYSTEM_INFO_0_EO },
    { "audio", CATEGORY_AUDIO_LABEL_EO, CATEGORY_AUDIO_INFO_0_EO },
    { "network", CATEGORY_NETWORK_LABEL_EO, CATEGORY_NETWORK_INFO_0_EO },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_eo[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_EO,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_EO,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_EO },
            { "OpenGL", OPTION_VAL_OPENGL_EO },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_EO,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_EO,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_EO },
            { "2", OPTION_VAL_2_EO },
            { "3", OPTION_VAL_3_EO },
            { "4", OPTION_VAL_4_EO },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_EO,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_EO,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_EO },
            { "Nearest", OPTION_VAL_NEAREST_EO },
            { "Bicubic", OPTION_VAL_BICUBIC_EO },
            { "FXAA", OPTION_VAL_FXAA_EO },
            { "FSR", OPTION_VAL_FSR_EO },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_EO,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_EO,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_EO },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_EO },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_EO },
            { "8", OPTION_VAL_8_EO },
            { "16", OPTION_VAL_16_EO },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_EO,
        NULL,
        VITA3K_V_SYNC_INFO_0_EO,
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
        VITA3K_ASYNC_PIPELINE_LABEL_EO,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_EO,
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
        VITA3K_MEMORY_MAPPING_LABEL_EO,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_EO,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_EO },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_EO },
            { "page-table", OPTION_VAL_PAGE_TABLE_EO },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_EO },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_EO,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_EO,
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
        VITA3K_CPU_OPT_LABEL_EO,
        NULL,
        VITA3K_CPU_OPT_INFO_0_EO,
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
        VITA3K_PKG_MODE_LABEL_EO,
        NULL,
        VITA3K_PKG_MODE_INFO_0_EO,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_EO },
            { "install", OPTION_VAL_INSTALL_EO },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_EO,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_EO,
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
        VITA3K_MODULES_MODE_LABEL_EO,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_EO,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_EO },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_EO },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_EO },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_EO,
        NULL,
        VITA3K_FPS_HACK_INFO_0_EO,
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
        VITA3K_SYS_BUTTON_LABEL_EO,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_EO,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_EO },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_EO },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_EO,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_EO,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_EO },
            { "10", OPTION_VAL_10_EO },
            { "20", OPTION_VAL_20_EO },
            { "30", OPTION_VAL_30_EO },
            { "40", OPTION_VAL_40_EO },
            { "50", OPTION_VAL_50_EO },
            { "60", OPTION_VAL_60_EO },
            { "70", OPTION_VAL_70_EO },
            { "80", OPTION_VAL_80_EO },
            { "90", OPTION_VAL_90_EO },
            { "100", OPTION_VAL_100_EO },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_EO,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_EO,
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
        VITA3K_PSN_SIGNED_IN_LABEL_EO,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_EO,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_EO,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_EO,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_EO },
            { "disabled", OPTION_VAL_DISABLED_EO },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_EO,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_EO,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_EO },
            { "5", OPTION_VAL_5_EO },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_EO },
            { "15", OPTION_VAL_15_EO },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_EO },
            { "25", OPTION_VAL_25_EO },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_EO },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_eo = {
   option_cats_eo,
   option_defs_eo
};

/* RETRO_LANGUAGE_ES */

#define CATEGORY_GPU_LABEL_ES NULL
#define CATEGORY_GPU_INFO_0_ES NULL
#define CATEGORY_CPU_LABEL_ES NULL
#define CATEGORY_CPU_INFO_0_ES NULL
#define CATEGORY_SYSTEM_LABEL_ES NULL
#define CATEGORY_SYSTEM_INFO_0_ES NULL
#define CATEGORY_AUDIO_LABEL_ES NULL
#define CATEGORY_AUDIO_INFO_0_ES NULL
#define CATEGORY_NETWORK_LABEL_ES NULL
#define CATEGORY_NETWORK_INFO_0_ES NULL
#define VITA3K_BACKEND_RENDERER_LABEL_ES NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_ES NULL
#define OPTION_VAL_VULKAN_ES NULL
#define OPTION_VAL_OPENGL_ES NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_ES NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_ES NULL
#define OPTION_VAL_1_ES NULL
#define OPTION_VAL_2_ES NULL
#define OPTION_VAL_3_ES NULL
#define OPTION_VAL_4_ES NULL
#define VITA3K_SCREEN_FILTER_LABEL_ES NULL
#define VITA3K_SCREEN_FILTER_INFO_0_ES NULL
#define OPTION_VAL_BILINEAR_ES NULL
#define OPTION_VAL_NEAREST_ES NULL
#define OPTION_VAL_BICUBIC_ES NULL
#define OPTION_VAL_FXAA_ES NULL
#define OPTION_VAL_FSR_ES NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_ES NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_ES NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_ES NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_ES NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_ES NULL
#define OPTION_VAL_8_ES NULL
#define OPTION_VAL_16_ES NULL
#define VITA3K_V_SYNC_LABEL_ES NULL
#define VITA3K_V_SYNC_INFO_0_ES NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_ES NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_ES NULL
#define VITA3K_MEMORY_MAPPING_LABEL_ES NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_ES NULL
#define OPTION_VAL_DOUBLE_BUFFER_ES NULL
#define OPTION_VAL_EXTERNAL_HOST_ES NULL
#define OPTION_VAL_PAGE_TABLE_ES NULL
#define OPTION_VAL_NATIVE_BUFFER_ES NULL
#define VITA3K_HIGH_ACCURACY_LABEL_ES NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_ES NULL
#define VITA3K_CPU_OPT_LABEL_ES NULL
#define VITA3K_CPU_OPT_INFO_0_ES NULL
#define VITA3K_PKG_MODE_LABEL_ES NULL
#define VITA3K_PKG_MODE_INFO_0_ES NULL
#define OPTION_VAL_RUN_ES NULL
#define OPTION_VAL_INSTALL_ES NULL
#define VITA3K_PSTV_MODE_LABEL_ES NULL
#define VITA3K_PSTV_MODE_INFO_0_ES NULL
#define VITA3K_MODULES_MODE_LABEL_ES NULL
#define VITA3K_MODULES_MODE_INFO_0_ES NULL
#define OPTION_VAL_0_ES NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_ES NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_ES NULL
#define VITA3K_FPS_HACK_LABEL_ES NULL
#define VITA3K_FPS_HACK_INFO_0_ES NULL
#define VITA3K_SYS_BUTTON_LABEL_ES NULL
#define VITA3K_SYS_BUTTON_INFO_0_ES NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_ES NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_ES NULL
#define VITA3K_AUDIO_VOLUME_LABEL_ES NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_ES NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_ES NULL
#define OPTION_VAL_10_ES NULL
#define OPTION_VAL_20_ES NULL
#define OPTION_VAL_30_ES NULL
#define OPTION_VAL_40_ES NULL
#define OPTION_VAL_50_ES NULL
#define OPTION_VAL_60_ES NULL
#define OPTION_VAL_70_ES NULL
#define OPTION_VAL_80_ES NULL
#define OPTION_VAL_90_ES NULL
#define OPTION_VAL_100_ES NULL
#define VITA3K_NGS_ENABLE_LABEL_ES NULL
#define VITA3K_NGS_ENABLE_INFO_0_ES NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_ES NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_ES NULL
#define VITA3K_SURFACE_SYNC_LABEL_ES NULL
#define VITA3K_SURFACE_SYNC_INFO_0_ES NULL
#define OPTION_VAL_ENABLED_ES NULL
#define OPTION_VAL_DISABLED_ES NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_ES NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_ES NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_ES NULL
#define OPTION_VAL_5_ES NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_ES NULL
#define OPTION_VAL_15_ES NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_ES NULL
#define OPTION_VAL_25_ES NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_ES NULL

struct retro_core_option_v2_category option_cats_es[] = {
    { "gpu", CATEGORY_GPU_LABEL_ES, CATEGORY_GPU_INFO_0_ES },
    { "cpu", CATEGORY_CPU_LABEL_ES, CATEGORY_CPU_INFO_0_ES },
    { "system", CATEGORY_SYSTEM_LABEL_ES, CATEGORY_SYSTEM_INFO_0_ES },
    { "audio", CATEGORY_AUDIO_LABEL_ES, CATEGORY_AUDIO_INFO_0_ES },
    { "network", CATEGORY_NETWORK_LABEL_ES, CATEGORY_NETWORK_INFO_0_ES },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_es[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_ES,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_ES,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_ES },
            { "OpenGL", OPTION_VAL_OPENGL_ES },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_ES,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_ES,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_ES },
            { "2", OPTION_VAL_2_ES },
            { "3", OPTION_VAL_3_ES },
            { "4", OPTION_VAL_4_ES },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_ES,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_ES,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_ES },
            { "Nearest", OPTION_VAL_NEAREST_ES },
            { "Bicubic", OPTION_VAL_BICUBIC_ES },
            { "FXAA", OPTION_VAL_FXAA_ES },
            { "FSR", OPTION_VAL_FSR_ES },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_ES,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_ES,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_ES },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_ES },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_ES },
            { "8", OPTION_VAL_8_ES },
            { "16", OPTION_VAL_16_ES },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_ES,
        NULL,
        VITA3K_V_SYNC_INFO_0_ES,
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
        VITA3K_ASYNC_PIPELINE_LABEL_ES,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_ES,
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
        VITA3K_MEMORY_MAPPING_LABEL_ES,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_ES,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_ES },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_ES },
            { "page-table", OPTION_VAL_PAGE_TABLE_ES },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_ES },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_ES,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_ES,
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
        VITA3K_CPU_OPT_LABEL_ES,
        NULL,
        VITA3K_CPU_OPT_INFO_0_ES,
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
        VITA3K_PKG_MODE_LABEL_ES,
        NULL,
        VITA3K_PKG_MODE_INFO_0_ES,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_ES },
            { "install", OPTION_VAL_INSTALL_ES },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_ES,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_ES,
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
        VITA3K_MODULES_MODE_LABEL_ES,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_ES,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_ES },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_ES },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_ES },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_ES,
        NULL,
        VITA3K_FPS_HACK_INFO_0_ES,
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
        VITA3K_SYS_BUTTON_LABEL_ES,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_ES,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_ES },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_ES },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_ES,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_ES,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_ES },
            { "10", OPTION_VAL_10_ES },
            { "20", OPTION_VAL_20_ES },
            { "30", OPTION_VAL_30_ES },
            { "40", OPTION_VAL_40_ES },
            { "50", OPTION_VAL_50_ES },
            { "60", OPTION_VAL_60_ES },
            { "70", OPTION_VAL_70_ES },
            { "80", OPTION_VAL_80_ES },
            { "90", OPTION_VAL_90_ES },
            { "100", OPTION_VAL_100_ES },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_ES,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_ES,
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
        VITA3K_PSN_SIGNED_IN_LABEL_ES,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_ES,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_ES,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_ES,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_ES },
            { "disabled", OPTION_VAL_DISABLED_ES },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_ES,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_ES,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_ES },
            { "5", OPTION_VAL_5_ES },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_ES },
            { "15", OPTION_VAL_15_ES },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_ES },
            { "25", OPTION_VAL_25_ES },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_ES },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_es = {
   option_cats_es,
   option_defs_es
};

/* RETRO_LANGUAGE_FA */

#define CATEGORY_GPU_LABEL_FA NULL
#define CATEGORY_GPU_INFO_0_FA NULL
#define CATEGORY_CPU_LABEL_FA NULL
#define CATEGORY_CPU_INFO_0_FA NULL
#define CATEGORY_SYSTEM_LABEL_FA NULL
#define CATEGORY_SYSTEM_INFO_0_FA NULL
#define CATEGORY_AUDIO_LABEL_FA NULL
#define CATEGORY_AUDIO_INFO_0_FA NULL
#define CATEGORY_NETWORK_LABEL_FA NULL
#define CATEGORY_NETWORK_INFO_0_FA NULL
#define VITA3K_BACKEND_RENDERER_LABEL_FA NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_FA NULL
#define OPTION_VAL_VULKAN_FA NULL
#define OPTION_VAL_OPENGL_FA NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_FA NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_FA NULL
#define OPTION_VAL_1_FA NULL
#define OPTION_VAL_2_FA NULL
#define OPTION_VAL_3_FA NULL
#define OPTION_VAL_4_FA NULL
#define VITA3K_SCREEN_FILTER_LABEL_FA NULL
#define VITA3K_SCREEN_FILTER_INFO_0_FA NULL
#define OPTION_VAL_BILINEAR_FA NULL
#define OPTION_VAL_NEAREST_FA NULL
#define OPTION_VAL_BICUBIC_FA NULL
#define OPTION_VAL_FXAA_FA NULL
#define OPTION_VAL_FSR_FA NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_FA NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_FA NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_FA NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_FA NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_FA NULL
#define OPTION_VAL_8_FA NULL
#define OPTION_VAL_16_FA NULL
#define VITA3K_V_SYNC_LABEL_FA NULL
#define VITA3K_V_SYNC_INFO_0_FA NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_FA NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_FA NULL
#define VITA3K_MEMORY_MAPPING_LABEL_FA NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_FA NULL
#define OPTION_VAL_DOUBLE_BUFFER_FA NULL
#define OPTION_VAL_EXTERNAL_HOST_FA NULL
#define OPTION_VAL_PAGE_TABLE_FA NULL
#define OPTION_VAL_NATIVE_BUFFER_FA NULL
#define VITA3K_HIGH_ACCURACY_LABEL_FA NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_FA NULL
#define VITA3K_CPU_OPT_LABEL_FA NULL
#define VITA3K_CPU_OPT_INFO_0_FA NULL
#define VITA3K_PKG_MODE_LABEL_FA NULL
#define VITA3K_PKG_MODE_INFO_0_FA NULL
#define OPTION_VAL_RUN_FA NULL
#define OPTION_VAL_INSTALL_FA NULL
#define VITA3K_PSTV_MODE_LABEL_FA NULL
#define VITA3K_PSTV_MODE_INFO_0_FA NULL
#define VITA3K_MODULES_MODE_LABEL_FA NULL
#define VITA3K_MODULES_MODE_INFO_0_FA NULL
#define OPTION_VAL_0_FA NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_FA NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_FA NULL
#define VITA3K_FPS_HACK_LABEL_FA NULL
#define VITA3K_FPS_HACK_INFO_0_FA NULL
#define VITA3K_SYS_BUTTON_LABEL_FA NULL
#define VITA3K_SYS_BUTTON_INFO_0_FA NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_FA NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_FA NULL
#define VITA3K_AUDIO_VOLUME_LABEL_FA NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_FA NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_FA NULL
#define OPTION_VAL_10_FA NULL
#define OPTION_VAL_20_FA NULL
#define OPTION_VAL_30_FA NULL
#define OPTION_VAL_40_FA NULL
#define OPTION_VAL_50_FA NULL
#define OPTION_VAL_60_FA NULL
#define OPTION_VAL_70_FA NULL
#define OPTION_VAL_80_FA NULL
#define OPTION_VAL_90_FA NULL
#define OPTION_VAL_100_FA NULL
#define VITA3K_NGS_ENABLE_LABEL_FA NULL
#define VITA3K_NGS_ENABLE_INFO_0_FA NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_FA NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_FA NULL
#define VITA3K_SURFACE_SYNC_LABEL_FA NULL
#define VITA3K_SURFACE_SYNC_INFO_0_FA NULL
#define OPTION_VAL_ENABLED_FA NULL
#define OPTION_VAL_DISABLED_FA NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_FA NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_FA NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_FA NULL
#define OPTION_VAL_5_FA NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_FA NULL
#define OPTION_VAL_15_FA NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_FA NULL
#define OPTION_VAL_25_FA NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_FA NULL

struct retro_core_option_v2_category option_cats_fa[] = {
    { "gpu", CATEGORY_GPU_LABEL_FA, CATEGORY_GPU_INFO_0_FA },
    { "cpu", CATEGORY_CPU_LABEL_FA, CATEGORY_CPU_INFO_0_FA },
    { "system", CATEGORY_SYSTEM_LABEL_FA, CATEGORY_SYSTEM_INFO_0_FA },
    { "audio", CATEGORY_AUDIO_LABEL_FA, CATEGORY_AUDIO_INFO_0_FA },
    { "network", CATEGORY_NETWORK_LABEL_FA, CATEGORY_NETWORK_INFO_0_FA },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_fa[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_FA,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_FA,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_FA },
            { "OpenGL", OPTION_VAL_OPENGL_FA },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_FA,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_FA,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_FA },
            { "2", OPTION_VAL_2_FA },
            { "3", OPTION_VAL_3_FA },
            { "4", OPTION_VAL_4_FA },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_FA,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_FA,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_FA },
            { "Nearest", OPTION_VAL_NEAREST_FA },
            { "Bicubic", OPTION_VAL_BICUBIC_FA },
            { "FXAA", OPTION_VAL_FXAA_FA },
            { "FSR", OPTION_VAL_FSR_FA },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_FA,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_FA,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_FA },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_FA },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_FA },
            { "8", OPTION_VAL_8_FA },
            { "16", OPTION_VAL_16_FA },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_FA,
        NULL,
        VITA3K_V_SYNC_INFO_0_FA,
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
        VITA3K_ASYNC_PIPELINE_LABEL_FA,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_FA,
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
        VITA3K_MEMORY_MAPPING_LABEL_FA,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_FA,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_FA },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_FA },
            { "page-table", OPTION_VAL_PAGE_TABLE_FA },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_FA },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_FA,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_FA,
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
        VITA3K_CPU_OPT_LABEL_FA,
        NULL,
        VITA3K_CPU_OPT_INFO_0_FA,
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
        VITA3K_PKG_MODE_LABEL_FA,
        NULL,
        VITA3K_PKG_MODE_INFO_0_FA,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_FA },
            { "install", OPTION_VAL_INSTALL_FA },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_FA,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_FA,
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
        VITA3K_MODULES_MODE_LABEL_FA,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_FA,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_FA },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_FA },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_FA },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_FA,
        NULL,
        VITA3K_FPS_HACK_INFO_0_FA,
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
        VITA3K_SYS_BUTTON_LABEL_FA,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_FA,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_FA },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_FA },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_FA,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_FA,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_FA },
            { "10", OPTION_VAL_10_FA },
            { "20", OPTION_VAL_20_FA },
            { "30", OPTION_VAL_30_FA },
            { "40", OPTION_VAL_40_FA },
            { "50", OPTION_VAL_50_FA },
            { "60", OPTION_VAL_60_FA },
            { "70", OPTION_VAL_70_FA },
            { "80", OPTION_VAL_80_FA },
            { "90", OPTION_VAL_90_FA },
            { "100", OPTION_VAL_100_FA },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_FA,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_FA,
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
        VITA3K_PSN_SIGNED_IN_LABEL_FA,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_FA,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_FA,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_FA,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_FA },
            { "disabled", OPTION_VAL_DISABLED_FA },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_FA,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_FA,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_FA },
            { "5", OPTION_VAL_5_FA },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_FA },
            { "15", OPTION_VAL_15_FA },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_FA },
            { "25", OPTION_VAL_25_FA },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_FA },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_fa = {
   option_cats_fa,
   option_defs_fa
};

/* RETRO_LANGUAGE_FI */

#define CATEGORY_GPU_LABEL_FI NULL
#define CATEGORY_GPU_INFO_0_FI NULL
#define CATEGORY_CPU_LABEL_FI NULL
#define CATEGORY_CPU_INFO_0_FI NULL
#define CATEGORY_SYSTEM_LABEL_FI NULL
#define CATEGORY_SYSTEM_INFO_0_FI NULL
#define CATEGORY_AUDIO_LABEL_FI NULL
#define CATEGORY_AUDIO_INFO_0_FI NULL
#define CATEGORY_NETWORK_LABEL_FI NULL
#define CATEGORY_NETWORK_INFO_0_FI NULL
#define VITA3K_BACKEND_RENDERER_LABEL_FI NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_FI NULL
#define OPTION_VAL_VULKAN_FI NULL
#define OPTION_VAL_OPENGL_FI NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_FI NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_FI NULL
#define OPTION_VAL_1_FI NULL
#define OPTION_VAL_2_FI NULL
#define OPTION_VAL_3_FI NULL
#define OPTION_VAL_4_FI NULL
#define VITA3K_SCREEN_FILTER_LABEL_FI NULL
#define VITA3K_SCREEN_FILTER_INFO_0_FI NULL
#define OPTION_VAL_BILINEAR_FI NULL
#define OPTION_VAL_NEAREST_FI NULL
#define OPTION_VAL_BICUBIC_FI NULL
#define OPTION_VAL_FXAA_FI NULL
#define OPTION_VAL_FSR_FI NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_FI NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_FI NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_FI NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_FI NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_FI NULL
#define OPTION_VAL_8_FI NULL
#define OPTION_VAL_16_FI NULL
#define VITA3K_V_SYNC_LABEL_FI NULL
#define VITA3K_V_SYNC_INFO_0_FI NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_FI NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_FI NULL
#define VITA3K_MEMORY_MAPPING_LABEL_FI NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_FI NULL
#define OPTION_VAL_DOUBLE_BUFFER_FI NULL
#define OPTION_VAL_EXTERNAL_HOST_FI NULL
#define OPTION_VAL_PAGE_TABLE_FI NULL
#define OPTION_VAL_NATIVE_BUFFER_FI NULL
#define VITA3K_HIGH_ACCURACY_LABEL_FI NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_FI NULL
#define VITA3K_CPU_OPT_LABEL_FI NULL
#define VITA3K_CPU_OPT_INFO_0_FI NULL
#define VITA3K_PKG_MODE_LABEL_FI NULL
#define VITA3K_PKG_MODE_INFO_0_FI NULL
#define OPTION_VAL_RUN_FI NULL
#define OPTION_VAL_INSTALL_FI NULL
#define VITA3K_PSTV_MODE_LABEL_FI NULL
#define VITA3K_PSTV_MODE_INFO_0_FI NULL
#define VITA3K_MODULES_MODE_LABEL_FI NULL
#define VITA3K_MODULES_MODE_INFO_0_FI NULL
#define OPTION_VAL_0_FI NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_FI NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_FI NULL
#define VITA3K_FPS_HACK_LABEL_FI NULL
#define VITA3K_FPS_HACK_INFO_0_FI NULL
#define VITA3K_SYS_BUTTON_LABEL_FI NULL
#define VITA3K_SYS_BUTTON_INFO_0_FI NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_FI NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_FI NULL
#define VITA3K_AUDIO_VOLUME_LABEL_FI NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_FI NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_FI NULL
#define OPTION_VAL_10_FI NULL
#define OPTION_VAL_20_FI NULL
#define OPTION_VAL_30_FI NULL
#define OPTION_VAL_40_FI NULL
#define OPTION_VAL_50_FI NULL
#define OPTION_VAL_60_FI NULL
#define OPTION_VAL_70_FI NULL
#define OPTION_VAL_80_FI NULL
#define OPTION_VAL_90_FI NULL
#define OPTION_VAL_100_FI NULL
#define VITA3K_NGS_ENABLE_LABEL_FI NULL
#define VITA3K_NGS_ENABLE_INFO_0_FI NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_FI NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_FI NULL
#define VITA3K_SURFACE_SYNC_LABEL_FI NULL
#define VITA3K_SURFACE_SYNC_INFO_0_FI NULL
#define OPTION_VAL_ENABLED_FI NULL
#define OPTION_VAL_DISABLED_FI NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_FI NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_FI NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_FI NULL
#define OPTION_VAL_5_FI NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_FI NULL
#define OPTION_VAL_15_FI NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_FI NULL
#define OPTION_VAL_25_FI NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_FI NULL

struct retro_core_option_v2_category option_cats_fi[] = {
    { "gpu", CATEGORY_GPU_LABEL_FI, CATEGORY_GPU_INFO_0_FI },
    { "cpu", CATEGORY_CPU_LABEL_FI, CATEGORY_CPU_INFO_0_FI },
    { "system", CATEGORY_SYSTEM_LABEL_FI, CATEGORY_SYSTEM_INFO_0_FI },
    { "audio", CATEGORY_AUDIO_LABEL_FI, CATEGORY_AUDIO_INFO_0_FI },
    { "network", CATEGORY_NETWORK_LABEL_FI, CATEGORY_NETWORK_INFO_0_FI },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_fi[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_FI,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_FI,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_FI },
            { "OpenGL", OPTION_VAL_OPENGL_FI },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_FI,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_FI,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_FI },
            { "2", OPTION_VAL_2_FI },
            { "3", OPTION_VAL_3_FI },
            { "4", OPTION_VAL_4_FI },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_FI,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_FI,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_FI },
            { "Nearest", OPTION_VAL_NEAREST_FI },
            { "Bicubic", OPTION_VAL_BICUBIC_FI },
            { "FXAA", OPTION_VAL_FXAA_FI },
            { "FSR", OPTION_VAL_FSR_FI },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_FI,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_FI,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_FI },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_FI },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_FI },
            { "8", OPTION_VAL_8_FI },
            { "16", OPTION_VAL_16_FI },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_FI,
        NULL,
        VITA3K_V_SYNC_INFO_0_FI,
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
        VITA3K_ASYNC_PIPELINE_LABEL_FI,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_FI,
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
        VITA3K_MEMORY_MAPPING_LABEL_FI,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_FI,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_FI },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_FI },
            { "page-table", OPTION_VAL_PAGE_TABLE_FI },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_FI },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_FI,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_FI,
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
        VITA3K_CPU_OPT_LABEL_FI,
        NULL,
        VITA3K_CPU_OPT_INFO_0_FI,
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
        VITA3K_PKG_MODE_LABEL_FI,
        NULL,
        VITA3K_PKG_MODE_INFO_0_FI,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_FI },
            { "install", OPTION_VAL_INSTALL_FI },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_FI,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_FI,
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
        VITA3K_MODULES_MODE_LABEL_FI,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_FI,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_FI },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_FI },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_FI },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_FI,
        NULL,
        VITA3K_FPS_HACK_INFO_0_FI,
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
        VITA3K_SYS_BUTTON_LABEL_FI,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_FI,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_FI },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_FI },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_FI,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_FI,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_FI },
            { "10", OPTION_VAL_10_FI },
            { "20", OPTION_VAL_20_FI },
            { "30", OPTION_VAL_30_FI },
            { "40", OPTION_VAL_40_FI },
            { "50", OPTION_VAL_50_FI },
            { "60", OPTION_VAL_60_FI },
            { "70", OPTION_VAL_70_FI },
            { "80", OPTION_VAL_80_FI },
            { "90", OPTION_VAL_90_FI },
            { "100", OPTION_VAL_100_FI },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_FI,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_FI,
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
        VITA3K_PSN_SIGNED_IN_LABEL_FI,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_FI,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_FI,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_FI,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_FI },
            { "disabled", OPTION_VAL_DISABLED_FI },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_FI,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_FI,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_FI },
            { "5", OPTION_VAL_5_FI },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_FI },
            { "15", OPTION_VAL_15_FI },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_FI },
            { "25", OPTION_VAL_25_FI },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_FI },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_fi = {
   option_cats_fi,
   option_defs_fi
};

/* RETRO_LANGUAGE_FR */

#define CATEGORY_GPU_LABEL_FR NULL
#define CATEGORY_GPU_INFO_0_FR NULL
#define CATEGORY_CPU_LABEL_FR NULL
#define CATEGORY_CPU_INFO_0_FR NULL
#define CATEGORY_SYSTEM_LABEL_FR NULL
#define CATEGORY_SYSTEM_INFO_0_FR NULL
#define CATEGORY_AUDIO_LABEL_FR NULL
#define CATEGORY_AUDIO_INFO_0_FR NULL
#define CATEGORY_NETWORK_LABEL_FR NULL
#define CATEGORY_NETWORK_INFO_0_FR NULL
#define VITA3K_BACKEND_RENDERER_LABEL_FR NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_FR NULL
#define OPTION_VAL_VULKAN_FR NULL
#define OPTION_VAL_OPENGL_FR NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_FR NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_FR NULL
#define OPTION_VAL_1_FR NULL
#define OPTION_VAL_2_FR NULL
#define OPTION_VAL_3_FR NULL
#define OPTION_VAL_4_FR NULL
#define VITA3K_SCREEN_FILTER_LABEL_FR NULL
#define VITA3K_SCREEN_FILTER_INFO_0_FR NULL
#define OPTION_VAL_BILINEAR_FR NULL
#define OPTION_VAL_NEAREST_FR NULL
#define OPTION_VAL_BICUBIC_FR NULL
#define OPTION_VAL_FXAA_FR NULL
#define OPTION_VAL_FSR_FR NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_FR NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_FR NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_FR NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_FR NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_FR NULL
#define OPTION_VAL_8_FR NULL
#define OPTION_VAL_16_FR NULL
#define VITA3K_V_SYNC_LABEL_FR NULL
#define VITA3K_V_SYNC_INFO_0_FR NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_FR NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_FR NULL
#define VITA3K_MEMORY_MAPPING_LABEL_FR NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_FR NULL
#define OPTION_VAL_DOUBLE_BUFFER_FR NULL
#define OPTION_VAL_EXTERNAL_HOST_FR NULL
#define OPTION_VAL_PAGE_TABLE_FR NULL
#define OPTION_VAL_NATIVE_BUFFER_FR NULL
#define VITA3K_HIGH_ACCURACY_LABEL_FR NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_FR NULL
#define VITA3K_CPU_OPT_LABEL_FR NULL
#define VITA3K_CPU_OPT_INFO_0_FR NULL
#define VITA3K_PKG_MODE_LABEL_FR NULL
#define VITA3K_PKG_MODE_INFO_0_FR NULL
#define OPTION_VAL_RUN_FR NULL
#define OPTION_VAL_INSTALL_FR NULL
#define VITA3K_PSTV_MODE_LABEL_FR NULL
#define VITA3K_PSTV_MODE_INFO_0_FR NULL
#define VITA3K_MODULES_MODE_LABEL_FR NULL
#define VITA3K_MODULES_MODE_INFO_0_FR NULL
#define OPTION_VAL_0_FR NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_FR NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_FR NULL
#define VITA3K_FPS_HACK_LABEL_FR NULL
#define VITA3K_FPS_HACK_INFO_0_FR NULL
#define VITA3K_SYS_BUTTON_LABEL_FR NULL
#define VITA3K_SYS_BUTTON_INFO_0_FR NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_FR NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_FR NULL
#define VITA3K_AUDIO_VOLUME_LABEL_FR NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_FR NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_FR NULL
#define OPTION_VAL_10_FR NULL
#define OPTION_VAL_20_FR NULL
#define OPTION_VAL_30_FR NULL
#define OPTION_VAL_40_FR NULL
#define OPTION_VAL_50_FR NULL
#define OPTION_VAL_60_FR NULL
#define OPTION_VAL_70_FR NULL
#define OPTION_VAL_80_FR NULL
#define OPTION_VAL_90_FR NULL
#define OPTION_VAL_100_FR NULL
#define VITA3K_NGS_ENABLE_LABEL_FR NULL
#define VITA3K_NGS_ENABLE_INFO_0_FR NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_FR NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_FR NULL
#define VITA3K_SURFACE_SYNC_LABEL_FR NULL
#define VITA3K_SURFACE_SYNC_INFO_0_FR NULL
#define OPTION_VAL_ENABLED_FR NULL
#define OPTION_VAL_DISABLED_FR NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_FR NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_FR NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_FR NULL
#define OPTION_VAL_5_FR NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_FR NULL
#define OPTION_VAL_15_FR NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_FR NULL
#define OPTION_VAL_25_FR NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_FR NULL

struct retro_core_option_v2_category option_cats_fr[] = {
    { "gpu", CATEGORY_GPU_LABEL_FR, CATEGORY_GPU_INFO_0_FR },
    { "cpu", CATEGORY_CPU_LABEL_FR, CATEGORY_CPU_INFO_0_FR },
    { "system", CATEGORY_SYSTEM_LABEL_FR, CATEGORY_SYSTEM_INFO_0_FR },
    { "audio", CATEGORY_AUDIO_LABEL_FR, CATEGORY_AUDIO_INFO_0_FR },
    { "network", CATEGORY_NETWORK_LABEL_FR, CATEGORY_NETWORK_INFO_0_FR },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_fr[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_FR,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_FR,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_FR },
            { "OpenGL", OPTION_VAL_OPENGL_FR },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_FR,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_FR,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_FR },
            { "2", OPTION_VAL_2_FR },
            { "3", OPTION_VAL_3_FR },
            { "4", OPTION_VAL_4_FR },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_FR,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_FR,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_FR },
            { "Nearest", OPTION_VAL_NEAREST_FR },
            { "Bicubic", OPTION_VAL_BICUBIC_FR },
            { "FXAA", OPTION_VAL_FXAA_FR },
            { "FSR", OPTION_VAL_FSR_FR },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_FR,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_FR,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_FR },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_FR },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_FR },
            { "8", OPTION_VAL_8_FR },
            { "16", OPTION_VAL_16_FR },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_FR,
        NULL,
        VITA3K_V_SYNC_INFO_0_FR,
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
        VITA3K_ASYNC_PIPELINE_LABEL_FR,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_FR,
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
        VITA3K_MEMORY_MAPPING_LABEL_FR,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_FR,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_FR },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_FR },
            { "page-table", OPTION_VAL_PAGE_TABLE_FR },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_FR },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_FR,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_FR,
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
        VITA3K_CPU_OPT_LABEL_FR,
        NULL,
        VITA3K_CPU_OPT_INFO_0_FR,
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
        VITA3K_PKG_MODE_LABEL_FR,
        NULL,
        VITA3K_PKG_MODE_INFO_0_FR,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_FR },
            { "install", OPTION_VAL_INSTALL_FR },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_FR,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_FR,
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
        VITA3K_MODULES_MODE_LABEL_FR,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_FR,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_FR },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_FR },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_FR },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_FR,
        NULL,
        VITA3K_FPS_HACK_INFO_0_FR,
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
        VITA3K_SYS_BUTTON_LABEL_FR,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_FR,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_FR },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_FR },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_FR,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_FR,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_FR },
            { "10", OPTION_VAL_10_FR },
            { "20", OPTION_VAL_20_FR },
            { "30", OPTION_VAL_30_FR },
            { "40", OPTION_VAL_40_FR },
            { "50", OPTION_VAL_50_FR },
            { "60", OPTION_VAL_60_FR },
            { "70", OPTION_VAL_70_FR },
            { "80", OPTION_VAL_80_FR },
            { "90", OPTION_VAL_90_FR },
            { "100", OPTION_VAL_100_FR },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_FR,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_FR,
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
        VITA3K_PSN_SIGNED_IN_LABEL_FR,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_FR,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_FR,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_FR,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_FR },
            { "disabled", OPTION_VAL_DISABLED_FR },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_FR,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_FR,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_FR },
            { "5", OPTION_VAL_5_FR },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_FR },
            { "15", OPTION_VAL_15_FR },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_FR },
            { "25", OPTION_VAL_25_FR },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_FR },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_fr = {
   option_cats_fr,
   option_defs_fr
};

/* RETRO_LANGUAGE_GA */

#define CATEGORY_GPU_LABEL_GA NULL
#define CATEGORY_GPU_INFO_0_GA NULL
#define CATEGORY_CPU_LABEL_GA NULL
#define CATEGORY_CPU_INFO_0_GA NULL
#define CATEGORY_SYSTEM_LABEL_GA NULL
#define CATEGORY_SYSTEM_INFO_0_GA NULL
#define CATEGORY_AUDIO_LABEL_GA NULL
#define CATEGORY_AUDIO_INFO_0_GA NULL
#define CATEGORY_NETWORK_LABEL_GA NULL
#define CATEGORY_NETWORK_INFO_0_GA NULL
#define VITA3K_BACKEND_RENDERER_LABEL_GA NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_GA NULL
#define OPTION_VAL_VULKAN_GA NULL
#define OPTION_VAL_OPENGL_GA NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_GA NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_GA NULL
#define OPTION_VAL_1_GA NULL
#define OPTION_VAL_2_GA NULL
#define OPTION_VAL_3_GA NULL
#define OPTION_VAL_4_GA NULL
#define VITA3K_SCREEN_FILTER_LABEL_GA NULL
#define VITA3K_SCREEN_FILTER_INFO_0_GA NULL
#define OPTION_VAL_BILINEAR_GA NULL
#define OPTION_VAL_NEAREST_GA NULL
#define OPTION_VAL_BICUBIC_GA NULL
#define OPTION_VAL_FXAA_GA NULL
#define OPTION_VAL_FSR_GA NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_GA NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_GA NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_GA NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_GA NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_GA NULL
#define OPTION_VAL_8_GA NULL
#define OPTION_VAL_16_GA NULL
#define VITA3K_V_SYNC_LABEL_GA NULL
#define VITA3K_V_SYNC_INFO_0_GA NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_GA NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_GA NULL
#define VITA3K_MEMORY_MAPPING_LABEL_GA NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_GA NULL
#define OPTION_VAL_DOUBLE_BUFFER_GA NULL
#define OPTION_VAL_EXTERNAL_HOST_GA NULL
#define OPTION_VAL_PAGE_TABLE_GA NULL
#define OPTION_VAL_NATIVE_BUFFER_GA NULL
#define VITA3K_HIGH_ACCURACY_LABEL_GA NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_GA NULL
#define VITA3K_CPU_OPT_LABEL_GA NULL
#define VITA3K_CPU_OPT_INFO_0_GA NULL
#define VITA3K_PKG_MODE_LABEL_GA NULL
#define VITA3K_PKG_MODE_INFO_0_GA NULL
#define OPTION_VAL_RUN_GA NULL
#define OPTION_VAL_INSTALL_GA NULL
#define VITA3K_PSTV_MODE_LABEL_GA NULL
#define VITA3K_PSTV_MODE_INFO_0_GA NULL
#define VITA3K_MODULES_MODE_LABEL_GA NULL
#define VITA3K_MODULES_MODE_INFO_0_GA NULL
#define OPTION_VAL_0_GA NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_GA NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_GA NULL
#define VITA3K_FPS_HACK_LABEL_GA NULL
#define VITA3K_FPS_HACK_INFO_0_GA NULL
#define VITA3K_SYS_BUTTON_LABEL_GA NULL
#define VITA3K_SYS_BUTTON_INFO_0_GA NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_GA NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_GA NULL
#define VITA3K_AUDIO_VOLUME_LABEL_GA NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_GA NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_GA NULL
#define OPTION_VAL_10_GA NULL
#define OPTION_VAL_20_GA NULL
#define OPTION_VAL_30_GA NULL
#define OPTION_VAL_40_GA NULL
#define OPTION_VAL_50_GA NULL
#define OPTION_VAL_60_GA NULL
#define OPTION_VAL_70_GA NULL
#define OPTION_VAL_80_GA NULL
#define OPTION_VAL_90_GA NULL
#define OPTION_VAL_100_GA NULL
#define VITA3K_NGS_ENABLE_LABEL_GA NULL
#define VITA3K_NGS_ENABLE_INFO_0_GA NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_GA NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_GA NULL
#define VITA3K_SURFACE_SYNC_LABEL_GA NULL
#define VITA3K_SURFACE_SYNC_INFO_0_GA NULL
#define OPTION_VAL_ENABLED_GA NULL
#define OPTION_VAL_DISABLED_GA NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_GA NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_GA NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_GA NULL
#define OPTION_VAL_5_GA NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_GA NULL
#define OPTION_VAL_15_GA NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_GA NULL
#define OPTION_VAL_25_GA NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_GA NULL

struct retro_core_option_v2_category option_cats_ga[] = {
    { "gpu", CATEGORY_GPU_LABEL_GA, CATEGORY_GPU_INFO_0_GA },
    { "cpu", CATEGORY_CPU_LABEL_GA, CATEGORY_CPU_INFO_0_GA },
    { "system", CATEGORY_SYSTEM_LABEL_GA, CATEGORY_SYSTEM_INFO_0_GA },
    { "audio", CATEGORY_AUDIO_LABEL_GA, CATEGORY_AUDIO_INFO_0_GA },
    { "network", CATEGORY_NETWORK_LABEL_GA, CATEGORY_NETWORK_INFO_0_GA },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_ga[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_GA,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_GA,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_GA },
            { "OpenGL", OPTION_VAL_OPENGL_GA },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_GA,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_GA,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_GA },
            { "2", OPTION_VAL_2_GA },
            { "3", OPTION_VAL_3_GA },
            { "4", OPTION_VAL_4_GA },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_GA,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_GA,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_GA },
            { "Nearest", OPTION_VAL_NEAREST_GA },
            { "Bicubic", OPTION_VAL_BICUBIC_GA },
            { "FXAA", OPTION_VAL_FXAA_GA },
            { "FSR", OPTION_VAL_FSR_GA },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_GA,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_GA,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_GA },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_GA },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_GA },
            { "8", OPTION_VAL_8_GA },
            { "16", OPTION_VAL_16_GA },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_GA,
        NULL,
        VITA3K_V_SYNC_INFO_0_GA,
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
        VITA3K_ASYNC_PIPELINE_LABEL_GA,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_GA,
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
        VITA3K_MEMORY_MAPPING_LABEL_GA,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_GA,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_GA },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_GA },
            { "page-table", OPTION_VAL_PAGE_TABLE_GA },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_GA },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_GA,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_GA,
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
        VITA3K_CPU_OPT_LABEL_GA,
        NULL,
        VITA3K_CPU_OPT_INFO_0_GA,
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
        VITA3K_PKG_MODE_LABEL_GA,
        NULL,
        VITA3K_PKG_MODE_INFO_0_GA,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_GA },
            { "install", OPTION_VAL_INSTALL_GA },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_GA,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_GA,
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
        VITA3K_MODULES_MODE_LABEL_GA,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_GA,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_GA },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_GA },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_GA },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_GA,
        NULL,
        VITA3K_FPS_HACK_INFO_0_GA,
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
        VITA3K_SYS_BUTTON_LABEL_GA,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_GA,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_GA },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_GA },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_GA,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_GA,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_GA },
            { "10", OPTION_VAL_10_GA },
            { "20", OPTION_VAL_20_GA },
            { "30", OPTION_VAL_30_GA },
            { "40", OPTION_VAL_40_GA },
            { "50", OPTION_VAL_50_GA },
            { "60", OPTION_VAL_60_GA },
            { "70", OPTION_VAL_70_GA },
            { "80", OPTION_VAL_80_GA },
            { "90", OPTION_VAL_90_GA },
            { "100", OPTION_VAL_100_GA },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_GA,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_GA,
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
        VITA3K_PSN_SIGNED_IN_LABEL_GA,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_GA,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_GA,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_GA,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_GA },
            { "disabled", OPTION_VAL_DISABLED_GA },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_GA,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_GA,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_GA },
            { "5", OPTION_VAL_5_GA },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_GA },
            { "15", OPTION_VAL_15_GA },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_GA },
            { "25", OPTION_VAL_25_GA },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_GA },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_ga = {
   option_cats_ga,
   option_defs_ga
};

/* RETRO_LANGUAGE_GL */

#define CATEGORY_GPU_LABEL_GL NULL
#define CATEGORY_GPU_INFO_0_GL NULL
#define CATEGORY_CPU_LABEL_GL NULL
#define CATEGORY_CPU_INFO_0_GL NULL
#define CATEGORY_SYSTEM_LABEL_GL NULL
#define CATEGORY_SYSTEM_INFO_0_GL NULL
#define CATEGORY_AUDIO_LABEL_GL NULL
#define CATEGORY_AUDIO_INFO_0_GL NULL
#define CATEGORY_NETWORK_LABEL_GL NULL
#define CATEGORY_NETWORK_INFO_0_GL NULL
#define VITA3K_BACKEND_RENDERER_LABEL_GL NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_GL NULL
#define OPTION_VAL_VULKAN_GL NULL
#define OPTION_VAL_OPENGL_GL NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_GL NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_GL NULL
#define OPTION_VAL_1_GL NULL
#define OPTION_VAL_2_GL NULL
#define OPTION_VAL_3_GL NULL
#define OPTION_VAL_4_GL NULL
#define VITA3K_SCREEN_FILTER_LABEL_GL NULL
#define VITA3K_SCREEN_FILTER_INFO_0_GL NULL
#define OPTION_VAL_BILINEAR_GL NULL
#define OPTION_VAL_NEAREST_GL NULL
#define OPTION_VAL_BICUBIC_GL NULL
#define OPTION_VAL_FXAA_GL NULL
#define OPTION_VAL_FSR_GL NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_GL NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_GL NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_GL NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_GL NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_GL NULL
#define OPTION_VAL_8_GL NULL
#define OPTION_VAL_16_GL NULL
#define VITA3K_V_SYNC_LABEL_GL NULL
#define VITA3K_V_SYNC_INFO_0_GL NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_GL NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_GL NULL
#define VITA3K_MEMORY_MAPPING_LABEL_GL NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_GL NULL
#define OPTION_VAL_DOUBLE_BUFFER_GL NULL
#define OPTION_VAL_EXTERNAL_HOST_GL NULL
#define OPTION_VAL_PAGE_TABLE_GL NULL
#define OPTION_VAL_NATIVE_BUFFER_GL NULL
#define VITA3K_HIGH_ACCURACY_LABEL_GL NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_GL NULL
#define VITA3K_CPU_OPT_LABEL_GL NULL
#define VITA3K_CPU_OPT_INFO_0_GL NULL
#define VITA3K_PKG_MODE_LABEL_GL NULL
#define VITA3K_PKG_MODE_INFO_0_GL NULL
#define OPTION_VAL_RUN_GL NULL
#define OPTION_VAL_INSTALL_GL NULL
#define VITA3K_PSTV_MODE_LABEL_GL NULL
#define VITA3K_PSTV_MODE_INFO_0_GL NULL
#define VITA3K_MODULES_MODE_LABEL_GL NULL
#define VITA3K_MODULES_MODE_INFO_0_GL NULL
#define OPTION_VAL_0_GL NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_GL NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_GL NULL
#define VITA3K_FPS_HACK_LABEL_GL NULL
#define VITA3K_FPS_HACK_INFO_0_GL NULL
#define VITA3K_SYS_BUTTON_LABEL_GL NULL
#define VITA3K_SYS_BUTTON_INFO_0_GL NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_GL NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_GL NULL
#define VITA3K_AUDIO_VOLUME_LABEL_GL NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_GL NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_GL NULL
#define OPTION_VAL_10_GL NULL
#define OPTION_VAL_20_GL NULL
#define OPTION_VAL_30_GL NULL
#define OPTION_VAL_40_GL NULL
#define OPTION_VAL_50_GL NULL
#define OPTION_VAL_60_GL NULL
#define OPTION_VAL_70_GL NULL
#define OPTION_VAL_80_GL NULL
#define OPTION_VAL_90_GL NULL
#define OPTION_VAL_100_GL NULL
#define VITA3K_NGS_ENABLE_LABEL_GL NULL
#define VITA3K_NGS_ENABLE_INFO_0_GL NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_GL NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_GL NULL
#define VITA3K_SURFACE_SYNC_LABEL_GL NULL
#define VITA3K_SURFACE_SYNC_INFO_0_GL NULL
#define OPTION_VAL_ENABLED_GL NULL
#define OPTION_VAL_DISABLED_GL NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_GL NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_GL NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_GL NULL
#define OPTION_VAL_5_GL NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_GL NULL
#define OPTION_VAL_15_GL NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_GL NULL
#define OPTION_VAL_25_GL NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_GL NULL

struct retro_core_option_v2_category option_cats_gl[] = {
    { "gpu", CATEGORY_GPU_LABEL_GL, CATEGORY_GPU_INFO_0_GL },
    { "cpu", CATEGORY_CPU_LABEL_GL, CATEGORY_CPU_INFO_0_GL },
    { "system", CATEGORY_SYSTEM_LABEL_GL, CATEGORY_SYSTEM_INFO_0_GL },
    { "audio", CATEGORY_AUDIO_LABEL_GL, CATEGORY_AUDIO_INFO_0_GL },
    { "network", CATEGORY_NETWORK_LABEL_GL, CATEGORY_NETWORK_INFO_0_GL },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_gl[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_GL,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_GL,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_GL },
            { "OpenGL", OPTION_VAL_OPENGL_GL },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_GL,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_GL,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_GL },
            { "2", OPTION_VAL_2_GL },
            { "3", OPTION_VAL_3_GL },
            { "4", OPTION_VAL_4_GL },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_GL,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_GL,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_GL },
            { "Nearest", OPTION_VAL_NEAREST_GL },
            { "Bicubic", OPTION_VAL_BICUBIC_GL },
            { "FXAA", OPTION_VAL_FXAA_GL },
            { "FSR", OPTION_VAL_FSR_GL },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_GL,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_GL,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_GL },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_GL },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_GL },
            { "8", OPTION_VAL_8_GL },
            { "16", OPTION_VAL_16_GL },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_GL,
        NULL,
        VITA3K_V_SYNC_INFO_0_GL,
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
        VITA3K_ASYNC_PIPELINE_LABEL_GL,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_GL,
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
        VITA3K_MEMORY_MAPPING_LABEL_GL,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_GL,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_GL },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_GL },
            { "page-table", OPTION_VAL_PAGE_TABLE_GL },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_GL },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_GL,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_GL,
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
        VITA3K_CPU_OPT_LABEL_GL,
        NULL,
        VITA3K_CPU_OPT_INFO_0_GL,
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
        VITA3K_PKG_MODE_LABEL_GL,
        NULL,
        VITA3K_PKG_MODE_INFO_0_GL,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_GL },
            { "install", OPTION_VAL_INSTALL_GL },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_GL,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_GL,
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
        VITA3K_MODULES_MODE_LABEL_GL,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_GL,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_GL },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_GL },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_GL },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_GL,
        NULL,
        VITA3K_FPS_HACK_INFO_0_GL,
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
        VITA3K_SYS_BUTTON_LABEL_GL,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_GL,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_GL },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_GL },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_GL,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_GL,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_GL },
            { "10", OPTION_VAL_10_GL },
            { "20", OPTION_VAL_20_GL },
            { "30", OPTION_VAL_30_GL },
            { "40", OPTION_VAL_40_GL },
            { "50", OPTION_VAL_50_GL },
            { "60", OPTION_VAL_60_GL },
            { "70", OPTION_VAL_70_GL },
            { "80", OPTION_VAL_80_GL },
            { "90", OPTION_VAL_90_GL },
            { "100", OPTION_VAL_100_GL },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_GL,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_GL,
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
        VITA3K_PSN_SIGNED_IN_LABEL_GL,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_GL,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_GL,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_GL,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_GL },
            { "disabled", OPTION_VAL_DISABLED_GL },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_GL,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_GL,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_GL },
            { "5", OPTION_VAL_5_GL },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_GL },
            { "15", OPTION_VAL_15_GL },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_GL },
            { "25", OPTION_VAL_25_GL },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_GL },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_gl = {
   option_cats_gl,
   option_defs_gl
};

/* RETRO_LANGUAGE_HE */

#define CATEGORY_GPU_LABEL_HE NULL
#define CATEGORY_GPU_INFO_0_HE NULL
#define CATEGORY_CPU_LABEL_HE NULL
#define CATEGORY_CPU_INFO_0_HE NULL
#define CATEGORY_SYSTEM_LABEL_HE NULL
#define CATEGORY_SYSTEM_INFO_0_HE NULL
#define CATEGORY_AUDIO_LABEL_HE NULL
#define CATEGORY_AUDIO_INFO_0_HE NULL
#define CATEGORY_NETWORK_LABEL_HE NULL
#define CATEGORY_NETWORK_INFO_0_HE NULL
#define VITA3K_BACKEND_RENDERER_LABEL_HE NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_HE NULL
#define OPTION_VAL_VULKAN_HE NULL
#define OPTION_VAL_OPENGL_HE NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_HE NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_HE NULL
#define OPTION_VAL_1_HE NULL
#define OPTION_VAL_2_HE NULL
#define OPTION_VAL_3_HE NULL
#define OPTION_VAL_4_HE NULL
#define VITA3K_SCREEN_FILTER_LABEL_HE NULL
#define VITA3K_SCREEN_FILTER_INFO_0_HE NULL
#define OPTION_VAL_BILINEAR_HE NULL
#define OPTION_VAL_NEAREST_HE NULL
#define OPTION_VAL_BICUBIC_HE NULL
#define OPTION_VAL_FXAA_HE NULL
#define OPTION_VAL_FSR_HE NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_HE NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_HE NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_HE NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_HE NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_HE NULL
#define OPTION_VAL_8_HE NULL
#define OPTION_VAL_16_HE NULL
#define VITA3K_V_SYNC_LABEL_HE NULL
#define VITA3K_V_SYNC_INFO_0_HE NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_HE NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_HE NULL
#define VITA3K_MEMORY_MAPPING_LABEL_HE NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_HE NULL
#define OPTION_VAL_DOUBLE_BUFFER_HE NULL
#define OPTION_VAL_EXTERNAL_HOST_HE NULL
#define OPTION_VAL_PAGE_TABLE_HE NULL
#define OPTION_VAL_NATIVE_BUFFER_HE NULL
#define VITA3K_HIGH_ACCURACY_LABEL_HE NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_HE NULL
#define VITA3K_CPU_OPT_LABEL_HE NULL
#define VITA3K_CPU_OPT_INFO_0_HE NULL
#define VITA3K_PKG_MODE_LABEL_HE NULL
#define VITA3K_PKG_MODE_INFO_0_HE NULL
#define OPTION_VAL_RUN_HE NULL
#define OPTION_VAL_INSTALL_HE NULL
#define VITA3K_PSTV_MODE_LABEL_HE NULL
#define VITA3K_PSTV_MODE_INFO_0_HE NULL
#define VITA3K_MODULES_MODE_LABEL_HE NULL
#define VITA3K_MODULES_MODE_INFO_0_HE NULL
#define OPTION_VAL_0_HE NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_HE NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_HE NULL
#define VITA3K_FPS_HACK_LABEL_HE NULL
#define VITA3K_FPS_HACK_INFO_0_HE NULL
#define VITA3K_SYS_BUTTON_LABEL_HE NULL
#define VITA3K_SYS_BUTTON_INFO_0_HE NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_HE NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_HE NULL
#define VITA3K_AUDIO_VOLUME_LABEL_HE NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_HE NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_HE NULL
#define OPTION_VAL_10_HE NULL
#define OPTION_VAL_20_HE NULL
#define OPTION_VAL_30_HE NULL
#define OPTION_VAL_40_HE NULL
#define OPTION_VAL_50_HE NULL
#define OPTION_VAL_60_HE NULL
#define OPTION_VAL_70_HE NULL
#define OPTION_VAL_80_HE NULL
#define OPTION_VAL_90_HE NULL
#define OPTION_VAL_100_HE NULL
#define VITA3K_NGS_ENABLE_LABEL_HE NULL
#define VITA3K_NGS_ENABLE_INFO_0_HE NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_HE NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_HE NULL
#define VITA3K_SURFACE_SYNC_LABEL_HE NULL
#define VITA3K_SURFACE_SYNC_INFO_0_HE NULL
#define OPTION_VAL_ENABLED_HE NULL
#define OPTION_VAL_DISABLED_HE NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_HE NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_HE NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_HE NULL
#define OPTION_VAL_5_HE NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_HE NULL
#define OPTION_VAL_15_HE NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_HE NULL
#define OPTION_VAL_25_HE NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_HE NULL

struct retro_core_option_v2_category option_cats_he[] = {
    { "gpu", CATEGORY_GPU_LABEL_HE, CATEGORY_GPU_INFO_0_HE },
    { "cpu", CATEGORY_CPU_LABEL_HE, CATEGORY_CPU_INFO_0_HE },
    { "system", CATEGORY_SYSTEM_LABEL_HE, CATEGORY_SYSTEM_INFO_0_HE },
    { "audio", CATEGORY_AUDIO_LABEL_HE, CATEGORY_AUDIO_INFO_0_HE },
    { "network", CATEGORY_NETWORK_LABEL_HE, CATEGORY_NETWORK_INFO_0_HE },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_he[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_HE,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_HE,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_HE },
            { "OpenGL", OPTION_VAL_OPENGL_HE },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_HE,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_HE,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_HE },
            { "2", OPTION_VAL_2_HE },
            { "3", OPTION_VAL_3_HE },
            { "4", OPTION_VAL_4_HE },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_HE,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_HE,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_HE },
            { "Nearest", OPTION_VAL_NEAREST_HE },
            { "Bicubic", OPTION_VAL_BICUBIC_HE },
            { "FXAA", OPTION_VAL_FXAA_HE },
            { "FSR", OPTION_VAL_FSR_HE },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_HE,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_HE,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_HE },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_HE },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_HE },
            { "8", OPTION_VAL_8_HE },
            { "16", OPTION_VAL_16_HE },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_HE,
        NULL,
        VITA3K_V_SYNC_INFO_0_HE,
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
        VITA3K_ASYNC_PIPELINE_LABEL_HE,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_HE,
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
        VITA3K_MEMORY_MAPPING_LABEL_HE,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_HE,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_HE },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_HE },
            { "page-table", OPTION_VAL_PAGE_TABLE_HE },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_HE },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_HE,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_HE,
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
        VITA3K_CPU_OPT_LABEL_HE,
        NULL,
        VITA3K_CPU_OPT_INFO_0_HE,
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
        VITA3K_PKG_MODE_LABEL_HE,
        NULL,
        VITA3K_PKG_MODE_INFO_0_HE,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_HE },
            { "install", OPTION_VAL_INSTALL_HE },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_HE,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_HE,
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
        VITA3K_MODULES_MODE_LABEL_HE,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_HE,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_HE },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_HE },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_HE },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_HE,
        NULL,
        VITA3K_FPS_HACK_INFO_0_HE,
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
        VITA3K_SYS_BUTTON_LABEL_HE,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_HE,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_HE },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_HE },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_HE,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_HE,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_HE },
            { "10", OPTION_VAL_10_HE },
            { "20", OPTION_VAL_20_HE },
            { "30", OPTION_VAL_30_HE },
            { "40", OPTION_VAL_40_HE },
            { "50", OPTION_VAL_50_HE },
            { "60", OPTION_VAL_60_HE },
            { "70", OPTION_VAL_70_HE },
            { "80", OPTION_VAL_80_HE },
            { "90", OPTION_VAL_90_HE },
            { "100", OPTION_VAL_100_HE },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_HE,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_HE,
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
        VITA3K_PSN_SIGNED_IN_LABEL_HE,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_HE,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_HE,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_HE,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_HE },
            { "disabled", OPTION_VAL_DISABLED_HE },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_HE,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_HE,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_HE },
            { "5", OPTION_VAL_5_HE },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_HE },
            { "15", OPTION_VAL_15_HE },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_HE },
            { "25", OPTION_VAL_25_HE },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_HE },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_he = {
   option_cats_he,
   option_defs_he
};

/* RETRO_LANGUAGE_HU */

#define CATEGORY_GPU_LABEL_HU NULL
#define CATEGORY_GPU_INFO_0_HU NULL
#define CATEGORY_CPU_LABEL_HU NULL
#define CATEGORY_CPU_INFO_0_HU NULL
#define CATEGORY_SYSTEM_LABEL_HU NULL
#define CATEGORY_SYSTEM_INFO_0_HU NULL
#define CATEGORY_AUDIO_LABEL_HU NULL
#define CATEGORY_AUDIO_INFO_0_HU NULL
#define CATEGORY_NETWORK_LABEL_HU NULL
#define CATEGORY_NETWORK_INFO_0_HU NULL
#define VITA3K_BACKEND_RENDERER_LABEL_HU NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_HU NULL
#define OPTION_VAL_VULKAN_HU NULL
#define OPTION_VAL_OPENGL_HU NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_HU NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_HU NULL
#define OPTION_VAL_1_HU NULL
#define OPTION_VAL_2_HU NULL
#define OPTION_VAL_3_HU NULL
#define OPTION_VAL_4_HU NULL
#define VITA3K_SCREEN_FILTER_LABEL_HU NULL
#define VITA3K_SCREEN_FILTER_INFO_0_HU NULL
#define OPTION_VAL_BILINEAR_HU NULL
#define OPTION_VAL_NEAREST_HU NULL
#define OPTION_VAL_BICUBIC_HU NULL
#define OPTION_VAL_FXAA_HU NULL
#define OPTION_VAL_FSR_HU NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_HU NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_HU NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_HU NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_HU NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_HU NULL
#define OPTION_VAL_8_HU NULL
#define OPTION_VAL_16_HU NULL
#define VITA3K_V_SYNC_LABEL_HU NULL
#define VITA3K_V_SYNC_INFO_0_HU NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_HU NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_HU NULL
#define VITA3K_MEMORY_MAPPING_LABEL_HU NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_HU NULL
#define OPTION_VAL_DOUBLE_BUFFER_HU NULL
#define OPTION_VAL_EXTERNAL_HOST_HU NULL
#define OPTION_VAL_PAGE_TABLE_HU NULL
#define OPTION_VAL_NATIVE_BUFFER_HU NULL
#define VITA3K_HIGH_ACCURACY_LABEL_HU NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_HU NULL
#define VITA3K_CPU_OPT_LABEL_HU NULL
#define VITA3K_CPU_OPT_INFO_0_HU NULL
#define VITA3K_PKG_MODE_LABEL_HU NULL
#define VITA3K_PKG_MODE_INFO_0_HU NULL
#define OPTION_VAL_RUN_HU NULL
#define OPTION_VAL_INSTALL_HU NULL
#define VITA3K_PSTV_MODE_LABEL_HU NULL
#define VITA3K_PSTV_MODE_INFO_0_HU NULL
#define VITA3K_MODULES_MODE_LABEL_HU NULL
#define VITA3K_MODULES_MODE_INFO_0_HU NULL
#define OPTION_VAL_0_HU NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_HU NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_HU NULL
#define VITA3K_FPS_HACK_LABEL_HU NULL
#define VITA3K_FPS_HACK_INFO_0_HU NULL
#define VITA3K_SYS_BUTTON_LABEL_HU NULL
#define VITA3K_SYS_BUTTON_INFO_0_HU NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_HU NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_HU NULL
#define VITA3K_AUDIO_VOLUME_LABEL_HU NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_HU NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_HU NULL
#define OPTION_VAL_10_HU NULL
#define OPTION_VAL_20_HU NULL
#define OPTION_VAL_30_HU NULL
#define OPTION_VAL_40_HU NULL
#define OPTION_VAL_50_HU NULL
#define OPTION_VAL_60_HU NULL
#define OPTION_VAL_70_HU NULL
#define OPTION_VAL_80_HU NULL
#define OPTION_VAL_90_HU NULL
#define OPTION_VAL_100_HU NULL
#define VITA3K_NGS_ENABLE_LABEL_HU NULL
#define VITA3K_NGS_ENABLE_INFO_0_HU NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_HU NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_HU NULL
#define VITA3K_SURFACE_SYNC_LABEL_HU NULL
#define VITA3K_SURFACE_SYNC_INFO_0_HU NULL
#define OPTION_VAL_ENABLED_HU NULL
#define OPTION_VAL_DISABLED_HU NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_HU NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_HU NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_HU NULL
#define OPTION_VAL_5_HU NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_HU NULL
#define OPTION_VAL_15_HU NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_HU NULL
#define OPTION_VAL_25_HU NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_HU NULL

struct retro_core_option_v2_category option_cats_hu[] = {
    { "gpu", CATEGORY_GPU_LABEL_HU, CATEGORY_GPU_INFO_0_HU },
    { "cpu", CATEGORY_CPU_LABEL_HU, CATEGORY_CPU_INFO_0_HU },
    { "system", CATEGORY_SYSTEM_LABEL_HU, CATEGORY_SYSTEM_INFO_0_HU },
    { "audio", CATEGORY_AUDIO_LABEL_HU, CATEGORY_AUDIO_INFO_0_HU },
    { "network", CATEGORY_NETWORK_LABEL_HU, CATEGORY_NETWORK_INFO_0_HU },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_hu[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_HU,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_HU,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_HU },
            { "OpenGL", OPTION_VAL_OPENGL_HU },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_HU,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_HU,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_HU },
            { "2", OPTION_VAL_2_HU },
            { "3", OPTION_VAL_3_HU },
            { "4", OPTION_VAL_4_HU },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_HU,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_HU,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_HU },
            { "Nearest", OPTION_VAL_NEAREST_HU },
            { "Bicubic", OPTION_VAL_BICUBIC_HU },
            { "FXAA", OPTION_VAL_FXAA_HU },
            { "FSR", OPTION_VAL_FSR_HU },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_HU,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_HU,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_HU },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_HU },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_HU },
            { "8", OPTION_VAL_8_HU },
            { "16", OPTION_VAL_16_HU },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_HU,
        NULL,
        VITA3K_V_SYNC_INFO_0_HU,
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
        VITA3K_ASYNC_PIPELINE_LABEL_HU,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_HU,
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
        VITA3K_MEMORY_MAPPING_LABEL_HU,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_HU,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_HU },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_HU },
            { "page-table", OPTION_VAL_PAGE_TABLE_HU },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_HU },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_HU,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_HU,
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
        VITA3K_CPU_OPT_LABEL_HU,
        NULL,
        VITA3K_CPU_OPT_INFO_0_HU,
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
        VITA3K_PKG_MODE_LABEL_HU,
        NULL,
        VITA3K_PKG_MODE_INFO_0_HU,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_HU },
            { "install", OPTION_VAL_INSTALL_HU },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_HU,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_HU,
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
        VITA3K_MODULES_MODE_LABEL_HU,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_HU,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_HU },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_HU },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_HU },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_HU,
        NULL,
        VITA3K_FPS_HACK_INFO_0_HU,
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
        VITA3K_SYS_BUTTON_LABEL_HU,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_HU,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_HU },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_HU },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_HU,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_HU,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_HU },
            { "10", OPTION_VAL_10_HU },
            { "20", OPTION_VAL_20_HU },
            { "30", OPTION_VAL_30_HU },
            { "40", OPTION_VAL_40_HU },
            { "50", OPTION_VAL_50_HU },
            { "60", OPTION_VAL_60_HU },
            { "70", OPTION_VAL_70_HU },
            { "80", OPTION_VAL_80_HU },
            { "90", OPTION_VAL_90_HU },
            { "100", OPTION_VAL_100_HU },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_HU,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_HU,
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
        VITA3K_PSN_SIGNED_IN_LABEL_HU,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_HU,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_HU,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_HU,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_HU },
            { "disabled", OPTION_VAL_DISABLED_HU },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_HU,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_HU,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_HU },
            { "5", OPTION_VAL_5_HU },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_HU },
            { "15", OPTION_VAL_15_HU },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_HU },
            { "25", OPTION_VAL_25_HU },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_HU },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_hu = {
   option_cats_hu,
   option_defs_hu
};

/* RETRO_LANGUAGE_ID */

#define CATEGORY_GPU_LABEL_ID NULL
#define CATEGORY_GPU_INFO_0_ID NULL
#define CATEGORY_CPU_LABEL_ID NULL
#define CATEGORY_CPU_INFO_0_ID NULL
#define CATEGORY_SYSTEM_LABEL_ID NULL
#define CATEGORY_SYSTEM_INFO_0_ID NULL
#define CATEGORY_AUDIO_LABEL_ID NULL
#define CATEGORY_AUDIO_INFO_0_ID NULL
#define CATEGORY_NETWORK_LABEL_ID NULL
#define CATEGORY_NETWORK_INFO_0_ID NULL
#define VITA3K_BACKEND_RENDERER_LABEL_ID NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_ID NULL
#define OPTION_VAL_VULKAN_ID NULL
#define OPTION_VAL_OPENGL_ID NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_ID NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_ID NULL
#define OPTION_VAL_1_ID NULL
#define OPTION_VAL_2_ID NULL
#define OPTION_VAL_3_ID NULL
#define OPTION_VAL_4_ID NULL
#define VITA3K_SCREEN_FILTER_LABEL_ID NULL
#define VITA3K_SCREEN_FILTER_INFO_0_ID NULL
#define OPTION_VAL_BILINEAR_ID NULL
#define OPTION_VAL_NEAREST_ID NULL
#define OPTION_VAL_BICUBIC_ID NULL
#define OPTION_VAL_FXAA_ID NULL
#define OPTION_VAL_FSR_ID NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_ID NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_ID NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_ID NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_ID NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_ID NULL
#define OPTION_VAL_8_ID NULL
#define OPTION_VAL_16_ID NULL
#define VITA3K_V_SYNC_LABEL_ID NULL
#define VITA3K_V_SYNC_INFO_0_ID NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_ID NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_ID NULL
#define VITA3K_MEMORY_MAPPING_LABEL_ID NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_ID NULL
#define OPTION_VAL_DOUBLE_BUFFER_ID NULL
#define OPTION_VAL_EXTERNAL_HOST_ID NULL
#define OPTION_VAL_PAGE_TABLE_ID NULL
#define OPTION_VAL_NATIVE_BUFFER_ID NULL
#define VITA3K_HIGH_ACCURACY_LABEL_ID NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_ID NULL
#define VITA3K_CPU_OPT_LABEL_ID NULL
#define VITA3K_CPU_OPT_INFO_0_ID NULL
#define VITA3K_PKG_MODE_LABEL_ID NULL
#define VITA3K_PKG_MODE_INFO_0_ID NULL
#define OPTION_VAL_RUN_ID NULL
#define OPTION_VAL_INSTALL_ID NULL
#define VITA3K_PSTV_MODE_LABEL_ID NULL
#define VITA3K_PSTV_MODE_INFO_0_ID NULL
#define VITA3K_MODULES_MODE_LABEL_ID NULL
#define VITA3K_MODULES_MODE_INFO_0_ID NULL
#define OPTION_VAL_0_ID NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_ID NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_ID NULL
#define VITA3K_FPS_HACK_LABEL_ID NULL
#define VITA3K_FPS_HACK_INFO_0_ID NULL
#define VITA3K_SYS_BUTTON_LABEL_ID NULL
#define VITA3K_SYS_BUTTON_INFO_0_ID NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_ID NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_ID NULL
#define VITA3K_AUDIO_VOLUME_LABEL_ID NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_ID NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_ID NULL
#define OPTION_VAL_10_ID NULL
#define OPTION_VAL_20_ID NULL
#define OPTION_VAL_30_ID NULL
#define OPTION_VAL_40_ID NULL
#define OPTION_VAL_50_ID NULL
#define OPTION_VAL_60_ID NULL
#define OPTION_VAL_70_ID NULL
#define OPTION_VAL_80_ID NULL
#define OPTION_VAL_90_ID NULL
#define OPTION_VAL_100_ID NULL
#define VITA3K_NGS_ENABLE_LABEL_ID NULL
#define VITA3K_NGS_ENABLE_INFO_0_ID NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_ID NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_ID NULL
#define VITA3K_SURFACE_SYNC_LABEL_ID NULL
#define VITA3K_SURFACE_SYNC_INFO_0_ID NULL
#define OPTION_VAL_ENABLED_ID NULL
#define OPTION_VAL_DISABLED_ID NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_ID NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_ID NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_ID NULL
#define OPTION_VAL_5_ID NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_ID NULL
#define OPTION_VAL_15_ID NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_ID NULL
#define OPTION_VAL_25_ID NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_ID NULL

struct retro_core_option_v2_category option_cats_id[] = {
    { "gpu", CATEGORY_GPU_LABEL_ID, CATEGORY_GPU_INFO_0_ID },
    { "cpu", CATEGORY_CPU_LABEL_ID, CATEGORY_CPU_INFO_0_ID },
    { "system", CATEGORY_SYSTEM_LABEL_ID, CATEGORY_SYSTEM_INFO_0_ID },
    { "audio", CATEGORY_AUDIO_LABEL_ID, CATEGORY_AUDIO_INFO_0_ID },
    { "network", CATEGORY_NETWORK_LABEL_ID, CATEGORY_NETWORK_INFO_0_ID },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_id[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_ID,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_ID,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_ID },
            { "OpenGL", OPTION_VAL_OPENGL_ID },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_ID,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_ID,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_ID },
            { "2", OPTION_VAL_2_ID },
            { "3", OPTION_VAL_3_ID },
            { "4", OPTION_VAL_4_ID },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_ID,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_ID,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_ID },
            { "Nearest", OPTION_VAL_NEAREST_ID },
            { "Bicubic", OPTION_VAL_BICUBIC_ID },
            { "FXAA", OPTION_VAL_FXAA_ID },
            { "FSR", OPTION_VAL_FSR_ID },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_ID,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_ID,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_ID },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_ID },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_ID },
            { "8", OPTION_VAL_8_ID },
            { "16", OPTION_VAL_16_ID },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_ID,
        NULL,
        VITA3K_V_SYNC_INFO_0_ID,
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
        VITA3K_ASYNC_PIPELINE_LABEL_ID,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_ID,
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
        VITA3K_MEMORY_MAPPING_LABEL_ID,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_ID,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_ID },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_ID },
            { "page-table", OPTION_VAL_PAGE_TABLE_ID },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_ID },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_ID,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_ID,
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
        VITA3K_CPU_OPT_LABEL_ID,
        NULL,
        VITA3K_CPU_OPT_INFO_0_ID,
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
        VITA3K_PKG_MODE_LABEL_ID,
        NULL,
        VITA3K_PKG_MODE_INFO_0_ID,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_ID },
            { "install", OPTION_VAL_INSTALL_ID },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_ID,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_ID,
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
        VITA3K_MODULES_MODE_LABEL_ID,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_ID,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_ID },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_ID },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_ID },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_ID,
        NULL,
        VITA3K_FPS_HACK_INFO_0_ID,
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
        VITA3K_SYS_BUTTON_LABEL_ID,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_ID,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_ID },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_ID },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_ID,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_ID,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_ID },
            { "10", OPTION_VAL_10_ID },
            { "20", OPTION_VAL_20_ID },
            { "30", OPTION_VAL_30_ID },
            { "40", OPTION_VAL_40_ID },
            { "50", OPTION_VAL_50_ID },
            { "60", OPTION_VAL_60_ID },
            { "70", OPTION_VAL_70_ID },
            { "80", OPTION_VAL_80_ID },
            { "90", OPTION_VAL_90_ID },
            { "100", OPTION_VAL_100_ID },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_ID,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_ID,
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
        VITA3K_PSN_SIGNED_IN_LABEL_ID,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_ID,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_ID,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_ID,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_ID },
            { "disabled", OPTION_VAL_DISABLED_ID },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_ID,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_ID,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_ID },
            { "5", OPTION_VAL_5_ID },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_ID },
            { "15", OPTION_VAL_15_ID },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_ID },
            { "25", OPTION_VAL_25_ID },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_ID },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_id = {
   option_cats_id,
   option_defs_id
};

/* RETRO_LANGUAGE_IT */

#define CATEGORY_GPU_LABEL_IT NULL
#define CATEGORY_GPU_INFO_0_IT NULL
#define CATEGORY_CPU_LABEL_IT NULL
#define CATEGORY_CPU_INFO_0_IT NULL
#define CATEGORY_SYSTEM_LABEL_IT NULL
#define CATEGORY_SYSTEM_INFO_0_IT NULL
#define CATEGORY_AUDIO_LABEL_IT NULL
#define CATEGORY_AUDIO_INFO_0_IT NULL
#define CATEGORY_NETWORK_LABEL_IT NULL
#define CATEGORY_NETWORK_INFO_0_IT NULL
#define VITA3K_BACKEND_RENDERER_LABEL_IT NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_IT NULL
#define OPTION_VAL_VULKAN_IT NULL
#define OPTION_VAL_OPENGL_IT NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_IT NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_IT NULL
#define OPTION_VAL_1_IT NULL
#define OPTION_VAL_2_IT NULL
#define OPTION_VAL_3_IT NULL
#define OPTION_VAL_4_IT NULL
#define VITA3K_SCREEN_FILTER_LABEL_IT NULL
#define VITA3K_SCREEN_FILTER_INFO_0_IT NULL
#define OPTION_VAL_BILINEAR_IT NULL
#define OPTION_VAL_NEAREST_IT NULL
#define OPTION_VAL_BICUBIC_IT NULL
#define OPTION_VAL_FXAA_IT NULL
#define OPTION_VAL_FSR_IT NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_IT NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_IT NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_IT NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_IT NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_IT NULL
#define OPTION_VAL_8_IT NULL
#define OPTION_VAL_16_IT NULL
#define VITA3K_V_SYNC_LABEL_IT NULL
#define VITA3K_V_SYNC_INFO_0_IT NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_IT NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_IT NULL
#define VITA3K_MEMORY_MAPPING_LABEL_IT NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_IT NULL
#define OPTION_VAL_DOUBLE_BUFFER_IT NULL
#define OPTION_VAL_EXTERNAL_HOST_IT NULL
#define OPTION_VAL_PAGE_TABLE_IT NULL
#define OPTION_VAL_NATIVE_BUFFER_IT NULL
#define VITA3K_HIGH_ACCURACY_LABEL_IT NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_IT NULL
#define VITA3K_CPU_OPT_LABEL_IT NULL
#define VITA3K_CPU_OPT_INFO_0_IT NULL
#define VITA3K_PKG_MODE_LABEL_IT NULL
#define VITA3K_PKG_MODE_INFO_0_IT NULL
#define OPTION_VAL_RUN_IT NULL
#define OPTION_VAL_INSTALL_IT NULL
#define VITA3K_PSTV_MODE_LABEL_IT NULL
#define VITA3K_PSTV_MODE_INFO_0_IT NULL
#define VITA3K_MODULES_MODE_LABEL_IT NULL
#define VITA3K_MODULES_MODE_INFO_0_IT NULL
#define OPTION_VAL_0_IT NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_IT NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_IT NULL
#define VITA3K_FPS_HACK_LABEL_IT NULL
#define VITA3K_FPS_HACK_INFO_0_IT NULL
#define VITA3K_SYS_BUTTON_LABEL_IT NULL
#define VITA3K_SYS_BUTTON_INFO_0_IT NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_IT NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_IT NULL
#define VITA3K_AUDIO_VOLUME_LABEL_IT NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_IT NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_IT NULL
#define OPTION_VAL_10_IT NULL
#define OPTION_VAL_20_IT NULL
#define OPTION_VAL_30_IT NULL
#define OPTION_VAL_40_IT NULL
#define OPTION_VAL_50_IT NULL
#define OPTION_VAL_60_IT NULL
#define OPTION_VAL_70_IT NULL
#define OPTION_VAL_80_IT NULL
#define OPTION_VAL_90_IT NULL
#define OPTION_VAL_100_IT NULL
#define VITA3K_NGS_ENABLE_LABEL_IT NULL
#define VITA3K_NGS_ENABLE_INFO_0_IT NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_IT NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_IT NULL
#define VITA3K_SURFACE_SYNC_LABEL_IT NULL
#define VITA3K_SURFACE_SYNC_INFO_0_IT NULL
#define OPTION_VAL_ENABLED_IT NULL
#define OPTION_VAL_DISABLED_IT NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_IT NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_IT NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_IT NULL
#define OPTION_VAL_5_IT NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_IT NULL
#define OPTION_VAL_15_IT NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_IT NULL
#define OPTION_VAL_25_IT NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_IT NULL

struct retro_core_option_v2_category option_cats_it[] = {
    { "gpu", CATEGORY_GPU_LABEL_IT, CATEGORY_GPU_INFO_0_IT },
    { "cpu", CATEGORY_CPU_LABEL_IT, CATEGORY_CPU_INFO_0_IT },
    { "system", CATEGORY_SYSTEM_LABEL_IT, CATEGORY_SYSTEM_INFO_0_IT },
    { "audio", CATEGORY_AUDIO_LABEL_IT, CATEGORY_AUDIO_INFO_0_IT },
    { "network", CATEGORY_NETWORK_LABEL_IT, CATEGORY_NETWORK_INFO_0_IT },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_it[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_IT,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_IT,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_IT },
            { "OpenGL", OPTION_VAL_OPENGL_IT },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_IT,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_IT,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_IT },
            { "2", OPTION_VAL_2_IT },
            { "3", OPTION_VAL_3_IT },
            { "4", OPTION_VAL_4_IT },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_IT,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_IT,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_IT },
            { "Nearest", OPTION_VAL_NEAREST_IT },
            { "Bicubic", OPTION_VAL_BICUBIC_IT },
            { "FXAA", OPTION_VAL_FXAA_IT },
            { "FSR", OPTION_VAL_FSR_IT },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_IT,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_IT,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_IT },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_IT },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_IT },
            { "8", OPTION_VAL_8_IT },
            { "16", OPTION_VAL_16_IT },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_IT,
        NULL,
        VITA3K_V_SYNC_INFO_0_IT,
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
        VITA3K_ASYNC_PIPELINE_LABEL_IT,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_IT,
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
        VITA3K_MEMORY_MAPPING_LABEL_IT,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_IT,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_IT },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_IT },
            { "page-table", OPTION_VAL_PAGE_TABLE_IT },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_IT },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_IT,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_IT,
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
        VITA3K_CPU_OPT_LABEL_IT,
        NULL,
        VITA3K_CPU_OPT_INFO_0_IT,
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
        VITA3K_PKG_MODE_LABEL_IT,
        NULL,
        VITA3K_PKG_MODE_INFO_0_IT,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_IT },
            { "install", OPTION_VAL_INSTALL_IT },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_IT,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_IT,
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
        VITA3K_MODULES_MODE_LABEL_IT,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_IT,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_IT },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_IT },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_IT },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_IT,
        NULL,
        VITA3K_FPS_HACK_INFO_0_IT,
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
        VITA3K_SYS_BUTTON_LABEL_IT,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_IT,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_IT },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_IT },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_IT,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_IT,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_IT },
            { "10", OPTION_VAL_10_IT },
            { "20", OPTION_VAL_20_IT },
            { "30", OPTION_VAL_30_IT },
            { "40", OPTION_VAL_40_IT },
            { "50", OPTION_VAL_50_IT },
            { "60", OPTION_VAL_60_IT },
            { "70", OPTION_VAL_70_IT },
            { "80", OPTION_VAL_80_IT },
            { "90", OPTION_VAL_90_IT },
            { "100", OPTION_VAL_100_IT },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_IT,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_IT,
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
        VITA3K_PSN_SIGNED_IN_LABEL_IT,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_IT,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_IT,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_IT,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_IT },
            { "disabled", OPTION_VAL_DISABLED_IT },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_IT,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_IT,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_IT },
            { "5", OPTION_VAL_5_IT },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_IT },
            { "15", OPTION_VAL_15_IT },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_IT },
            { "25", OPTION_VAL_25_IT },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_IT },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_it = {
   option_cats_it,
   option_defs_it
};

/* RETRO_LANGUAGE_JA */

#define CATEGORY_GPU_LABEL_JA NULL
#define CATEGORY_GPU_INFO_0_JA NULL
#define CATEGORY_CPU_LABEL_JA NULL
#define CATEGORY_CPU_INFO_0_JA NULL
#define CATEGORY_SYSTEM_LABEL_JA NULL
#define CATEGORY_SYSTEM_INFO_0_JA NULL
#define CATEGORY_AUDIO_LABEL_JA NULL
#define CATEGORY_AUDIO_INFO_0_JA NULL
#define CATEGORY_NETWORK_LABEL_JA NULL
#define CATEGORY_NETWORK_INFO_0_JA NULL
#define VITA3K_BACKEND_RENDERER_LABEL_JA NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_JA NULL
#define OPTION_VAL_VULKAN_JA NULL
#define OPTION_VAL_OPENGL_JA NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_JA NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_JA NULL
#define OPTION_VAL_1_JA NULL
#define OPTION_VAL_2_JA NULL
#define OPTION_VAL_3_JA NULL
#define OPTION_VAL_4_JA NULL
#define VITA3K_SCREEN_FILTER_LABEL_JA NULL
#define VITA3K_SCREEN_FILTER_INFO_0_JA NULL
#define OPTION_VAL_BILINEAR_JA NULL
#define OPTION_VAL_NEAREST_JA NULL
#define OPTION_VAL_BICUBIC_JA NULL
#define OPTION_VAL_FXAA_JA NULL
#define OPTION_VAL_FSR_JA NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_JA NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_JA NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_JA NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_JA NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_JA NULL
#define OPTION_VAL_8_JA NULL
#define OPTION_VAL_16_JA NULL
#define VITA3K_V_SYNC_LABEL_JA NULL
#define VITA3K_V_SYNC_INFO_0_JA NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_JA NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_JA NULL
#define VITA3K_MEMORY_MAPPING_LABEL_JA NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_JA NULL
#define OPTION_VAL_DOUBLE_BUFFER_JA NULL
#define OPTION_VAL_EXTERNAL_HOST_JA NULL
#define OPTION_VAL_PAGE_TABLE_JA NULL
#define OPTION_VAL_NATIVE_BUFFER_JA NULL
#define VITA3K_HIGH_ACCURACY_LABEL_JA NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_JA NULL
#define VITA3K_CPU_OPT_LABEL_JA NULL
#define VITA3K_CPU_OPT_INFO_0_JA NULL
#define VITA3K_PKG_MODE_LABEL_JA NULL
#define VITA3K_PKG_MODE_INFO_0_JA NULL
#define OPTION_VAL_RUN_JA NULL
#define OPTION_VAL_INSTALL_JA NULL
#define VITA3K_PSTV_MODE_LABEL_JA NULL
#define VITA3K_PSTV_MODE_INFO_0_JA NULL
#define VITA3K_MODULES_MODE_LABEL_JA NULL
#define VITA3K_MODULES_MODE_INFO_0_JA NULL
#define OPTION_VAL_0_JA NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_JA NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_JA NULL
#define VITA3K_FPS_HACK_LABEL_JA NULL
#define VITA3K_FPS_HACK_INFO_0_JA NULL
#define VITA3K_SYS_BUTTON_LABEL_JA NULL
#define VITA3K_SYS_BUTTON_INFO_0_JA NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_JA NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_JA NULL
#define VITA3K_AUDIO_VOLUME_LABEL_JA NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_JA NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_JA NULL
#define OPTION_VAL_10_JA NULL
#define OPTION_VAL_20_JA NULL
#define OPTION_VAL_30_JA NULL
#define OPTION_VAL_40_JA NULL
#define OPTION_VAL_50_JA NULL
#define OPTION_VAL_60_JA NULL
#define OPTION_VAL_70_JA NULL
#define OPTION_VAL_80_JA NULL
#define OPTION_VAL_90_JA NULL
#define OPTION_VAL_100_JA NULL
#define VITA3K_NGS_ENABLE_LABEL_JA NULL
#define VITA3K_NGS_ENABLE_INFO_0_JA NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_JA NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_JA NULL
#define VITA3K_SURFACE_SYNC_LABEL_JA NULL
#define VITA3K_SURFACE_SYNC_INFO_0_JA NULL
#define OPTION_VAL_ENABLED_JA NULL
#define OPTION_VAL_DISABLED_JA NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_JA NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_JA NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_JA NULL
#define OPTION_VAL_5_JA NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_JA NULL
#define OPTION_VAL_15_JA NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_JA NULL
#define OPTION_VAL_25_JA NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_JA NULL

struct retro_core_option_v2_category option_cats_ja[] = {
    { "gpu", CATEGORY_GPU_LABEL_JA, CATEGORY_GPU_INFO_0_JA },
    { "cpu", CATEGORY_CPU_LABEL_JA, CATEGORY_CPU_INFO_0_JA },
    { "system", CATEGORY_SYSTEM_LABEL_JA, CATEGORY_SYSTEM_INFO_0_JA },
    { "audio", CATEGORY_AUDIO_LABEL_JA, CATEGORY_AUDIO_INFO_0_JA },
    { "network", CATEGORY_NETWORK_LABEL_JA, CATEGORY_NETWORK_INFO_0_JA },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_ja[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_JA,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_JA,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_JA },
            { "OpenGL", OPTION_VAL_OPENGL_JA },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_JA,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_JA,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_JA },
            { "2", OPTION_VAL_2_JA },
            { "3", OPTION_VAL_3_JA },
            { "4", OPTION_VAL_4_JA },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_JA,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_JA,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_JA },
            { "Nearest", OPTION_VAL_NEAREST_JA },
            { "Bicubic", OPTION_VAL_BICUBIC_JA },
            { "FXAA", OPTION_VAL_FXAA_JA },
            { "FSR", OPTION_VAL_FSR_JA },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_JA,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_JA,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_JA },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_JA },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_JA },
            { "8", OPTION_VAL_8_JA },
            { "16", OPTION_VAL_16_JA },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_JA,
        NULL,
        VITA3K_V_SYNC_INFO_0_JA,
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
        VITA3K_ASYNC_PIPELINE_LABEL_JA,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_JA,
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
        VITA3K_MEMORY_MAPPING_LABEL_JA,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_JA,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_JA },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_JA },
            { "page-table", OPTION_VAL_PAGE_TABLE_JA },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_JA },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_JA,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_JA,
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
        VITA3K_CPU_OPT_LABEL_JA,
        NULL,
        VITA3K_CPU_OPT_INFO_0_JA,
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
        VITA3K_PKG_MODE_LABEL_JA,
        NULL,
        VITA3K_PKG_MODE_INFO_0_JA,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_JA },
            { "install", OPTION_VAL_INSTALL_JA },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_JA,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_JA,
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
        VITA3K_MODULES_MODE_LABEL_JA,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_JA,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_JA },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_JA },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_JA },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_JA,
        NULL,
        VITA3K_FPS_HACK_INFO_0_JA,
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
        VITA3K_SYS_BUTTON_LABEL_JA,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_JA,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_JA },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_JA },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_JA,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_JA,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_JA },
            { "10", OPTION_VAL_10_JA },
            { "20", OPTION_VAL_20_JA },
            { "30", OPTION_VAL_30_JA },
            { "40", OPTION_VAL_40_JA },
            { "50", OPTION_VAL_50_JA },
            { "60", OPTION_VAL_60_JA },
            { "70", OPTION_VAL_70_JA },
            { "80", OPTION_VAL_80_JA },
            { "90", OPTION_VAL_90_JA },
            { "100", OPTION_VAL_100_JA },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_JA,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_JA,
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
        VITA3K_PSN_SIGNED_IN_LABEL_JA,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_JA,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_JA,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_JA,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_JA },
            { "disabled", OPTION_VAL_DISABLED_JA },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_JA,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_JA,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_JA },
            { "5", OPTION_VAL_5_JA },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_JA },
            { "15", OPTION_VAL_15_JA },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_JA },
            { "25", OPTION_VAL_25_JA },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_JA },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_ja = {
   option_cats_ja,
   option_defs_ja
};

/* RETRO_LANGUAGE_KO */

#define CATEGORY_GPU_LABEL_KO NULL
#define CATEGORY_GPU_INFO_0_KO NULL
#define CATEGORY_CPU_LABEL_KO NULL
#define CATEGORY_CPU_INFO_0_KO NULL
#define CATEGORY_SYSTEM_LABEL_KO NULL
#define CATEGORY_SYSTEM_INFO_0_KO NULL
#define CATEGORY_AUDIO_LABEL_KO NULL
#define CATEGORY_AUDIO_INFO_0_KO NULL
#define CATEGORY_NETWORK_LABEL_KO NULL
#define CATEGORY_NETWORK_INFO_0_KO NULL
#define VITA3K_BACKEND_RENDERER_LABEL_KO NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_KO NULL
#define OPTION_VAL_VULKAN_KO NULL
#define OPTION_VAL_OPENGL_KO NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_KO NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_KO NULL
#define OPTION_VAL_1_KO NULL
#define OPTION_VAL_2_KO NULL
#define OPTION_VAL_3_KO NULL
#define OPTION_VAL_4_KO NULL
#define VITA3K_SCREEN_FILTER_LABEL_KO NULL
#define VITA3K_SCREEN_FILTER_INFO_0_KO NULL
#define OPTION_VAL_BILINEAR_KO NULL
#define OPTION_VAL_NEAREST_KO NULL
#define OPTION_VAL_BICUBIC_KO NULL
#define OPTION_VAL_FXAA_KO NULL
#define OPTION_VAL_FSR_KO NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_KO NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_KO NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_KO NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_KO NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_KO NULL
#define OPTION_VAL_8_KO NULL
#define OPTION_VAL_16_KO NULL
#define VITA3K_V_SYNC_LABEL_KO NULL
#define VITA3K_V_SYNC_INFO_0_KO NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_KO NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_KO NULL
#define VITA3K_MEMORY_MAPPING_LABEL_KO NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_KO NULL
#define OPTION_VAL_DOUBLE_BUFFER_KO NULL
#define OPTION_VAL_EXTERNAL_HOST_KO NULL
#define OPTION_VAL_PAGE_TABLE_KO NULL
#define OPTION_VAL_NATIVE_BUFFER_KO NULL
#define VITA3K_HIGH_ACCURACY_LABEL_KO NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_KO NULL
#define VITA3K_CPU_OPT_LABEL_KO NULL
#define VITA3K_CPU_OPT_INFO_0_KO NULL
#define VITA3K_PKG_MODE_LABEL_KO NULL
#define VITA3K_PKG_MODE_INFO_0_KO NULL
#define OPTION_VAL_RUN_KO NULL
#define OPTION_VAL_INSTALL_KO NULL
#define VITA3K_PSTV_MODE_LABEL_KO NULL
#define VITA3K_PSTV_MODE_INFO_0_KO NULL
#define VITA3K_MODULES_MODE_LABEL_KO NULL
#define VITA3K_MODULES_MODE_INFO_0_KO NULL
#define OPTION_VAL_0_KO NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_KO NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_KO NULL
#define VITA3K_FPS_HACK_LABEL_KO NULL
#define VITA3K_FPS_HACK_INFO_0_KO NULL
#define VITA3K_SYS_BUTTON_LABEL_KO NULL
#define VITA3K_SYS_BUTTON_INFO_0_KO NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_KO NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_KO NULL
#define VITA3K_AUDIO_VOLUME_LABEL_KO NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_KO NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_KO NULL
#define OPTION_VAL_10_KO NULL
#define OPTION_VAL_20_KO NULL
#define OPTION_VAL_30_KO NULL
#define OPTION_VAL_40_KO NULL
#define OPTION_VAL_50_KO NULL
#define OPTION_VAL_60_KO NULL
#define OPTION_VAL_70_KO NULL
#define OPTION_VAL_80_KO NULL
#define OPTION_VAL_90_KO NULL
#define OPTION_VAL_100_KO NULL
#define VITA3K_NGS_ENABLE_LABEL_KO NULL
#define VITA3K_NGS_ENABLE_INFO_0_KO NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_KO NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_KO NULL
#define VITA3K_SURFACE_SYNC_LABEL_KO NULL
#define VITA3K_SURFACE_SYNC_INFO_0_KO NULL
#define OPTION_VAL_ENABLED_KO NULL
#define OPTION_VAL_DISABLED_KO NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_KO NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_KO NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_KO NULL
#define OPTION_VAL_5_KO NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_KO NULL
#define OPTION_VAL_15_KO NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_KO NULL
#define OPTION_VAL_25_KO NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_KO NULL

struct retro_core_option_v2_category option_cats_ko[] = {
    { "gpu", CATEGORY_GPU_LABEL_KO, CATEGORY_GPU_INFO_0_KO },
    { "cpu", CATEGORY_CPU_LABEL_KO, CATEGORY_CPU_INFO_0_KO },
    { "system", CATEGORY_SYSTEM_LABEL_KO, CATEGORY_SYSTEM_INFO_0_KO },
    { "audio", CATEGORY_AUDIO_LABEL_KO, CATEGORY_AUDIO_INFO_0_KO },
    { "network", CATEGORY_NETWORK_LABEL_KO, CATEGORY_NETWORK_INFO_0_KO },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_ko[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_KO,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_KO,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_KO },
            { "OpenGL", OPTION_VAL_OPENGL_KO },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_KO,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_KO,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_KO },
            { "2", OPTION_VAL_2_KO },
            { "3", OPTION_VAL_3_KO },
            { "4", OPTION_VAL_4_KO },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_KO,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_KO,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_KO },
            { "Nearest", OPTION_VAL_NEAREST_KO },
            { "Bicubic", OPTION_VAL_BICUBIC_KO },
            { "FXAA", OPTION_VAL_FXAA_KO },
            { "FSR", OPTION_VAL_FSR_KO },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_KO,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_KO,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_KO },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_KO },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_KO },
            { "8", OPTION_VAL_8_KO },
            { "16", OPTION_VAL_16_KO },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_KO,
        NULL,
        VITA3K_V_SYNC_INFO_0_KO,
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
        VITA3K_ASYNC_PIPELINE_LABEL_KO,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_KO,
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
        VITA3K_MEMORY_MAPPING_LABEL_KO,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_KO,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_KO },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_KO },
            { "page-table", OPTION_VAL_PAGE_TABLE_KO },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_KO },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_KO,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_KO,
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
        VITA3K_CPU_OPT_LABEL_KO,
        NULL,
        VITA3K_CPU_OPT_INFO_0_KO,
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
        VITA3K_PKG_MODE_LABEL_KO,
        NULL,
        VITA3K_PKG_MODE_INFO_0_KO,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_KO },
            { "install", OPTION_VAL_INSTALL_KO },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_KO,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_KO,
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
        VITA3K_MODULES_MODE_LABEL_KO,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_KO,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_KO },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_KO },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_KO },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_KO,
        NULL,
        VITA3K_FPS_HACK_INFO_0_KO,
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
        VITA3K_SYS_BUTTON_LABEL_KO,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_KO,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_KO },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_KO },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_KO,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_KO,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_KO },
            { "10", OPTION_VAL_10_KO },
            { "20", OPTION_VAL_20_KO },
            { "30", OPTION_VAL_30_KO },
            { "40", OPTION_VAL_40_KO },
            { "50", OPTION_VAL_50_KO },
            { "60", OPTION_VAL_60_KO },
            { "70", OPTION_VAL_70_KO },
            { "80", OPTION_VAL_80_KO },
            { "90", OPTION_VAL_90_KO },
            { "100", OPTION_VAL_100_KO },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_KO,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_KO,
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
        VITA3K_PSN_SIGNED_IN_LABEL_KO,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_KO,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_KO,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_KO,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_KO },
            { "disabled", OPTION_VAL_DISABLED_KO },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_KO,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_KO,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_KO },
            { "5", OPTION_VAL_5_KO },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_KO },
            { "15", OPTION_VAL_15_KO },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_KO },
            { "25", OPTION_VAL_25_KO },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_KO },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_ko = {
   option_cats_ko,
   option_defs_ko
};

/* RETRO_LANGUAGE_NL */

#define CATEGORY_GPU_LABEL_NL NULL
#define CATEGORY_GPU_INFO_0_NL NULL
#define CATEGORY_CPU_LABEL_NL NULL
#define CATEGORY_CPU_INFO_0_NL NULL
#define CATEGORY_SYSTEM_LABEL_NL NULL
#define CATEGORY_SYSTEM_INFO_0_NL NULL
#define CATEGORY_AUDIO_LABEL_NL NULL
#define CATEGORY_AUDIO_INFO_0_NL NULL
#define CATEGORY_NETWORK_LABEL_NL NULL
#define CATEGORY_NETWORK_INFO_0_NL NULL
#define VITA3K_BACKEND_RENDERER_LABEL_NL NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_NL NULL
#define OPTION_VAL_VULKAN_NL NULL
#define OPTION_VAL_OPENGL_NL NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_NL NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_NL NULL
#define OPTION_VAL_1_NL NULL
#define OPTION_VAL_2_NL NULL
#define OPTION_VAL_3_NL NULL
#define OPTION_VAL_4_NL NULL
#define VITA3K_SCREEN_FILTER_LABEL_NL NULL
#define VITA3K_SCREEN_FILTER_INFO_0_NL NULL
#define OPTION_VAL_BILINEAR_NL NULL
#define OPTION_VAL_NEAREST_NL NULL
#define OPTION_VAL_BICUBIC_NL NULL
#define OPTION_VAL_FXAA_NL NULL
#define OPTION_VAL_FSR_NL NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_NL NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_NL NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_NL NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_NL NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_NL NULL
#define OPTION_VAL_8_NL NULL
#define OPTION_VAL_16_NL NULL
#define VITA3K_V_SYNC_LABEL_NL NULL
#define VITA3K_V_SYNC_INFO_0_NL NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_NL NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_NL NULL
#define VITA3K_MEMORY_MAPPING_LABEL_NL NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_NL NULL
#define OPTION_VAL_DOUBLE_BUFFER_NL NULL
#define OPTION_VAL_EXTERNAL_HOST_NL NULL
#define OPTION_VAL_PAGE_TABLE_NL NULL
#define OPTION_VAL_NATIVE_BUFFER_NL NULL
#define VITA3K_HIGH_ACCURACY_LABEL_NL NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_NL NULL
#define VITA3K_CPU_OPT_LABEL_NL NULL
#define VITA3K_CPU_OPT_INFO_0_NL NULL
#define VITA3K_PKG_MODE_LABEL_NL NULL
#define VITA3K_PKG_MODE_INFO_0_NL NULL
#define OPTION_VAL_RUN_NL NULL
#define OPTION_VAL_INSTALL_NL NULL
#define VITA3K_PSTV_MODE_LABEL_NL NULL
#define VITA3K_PSTV_MODE_INFO_0_NL NULL
#define VITA3K_MODULES_MODE_LABEL_NL NULL
#define VITA3K_MODULES_MODE_INFO_0_NL NULL
#define OPTION_VAL_0_NL NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_NL NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_NL NULL
#define VITA3K_FPS_HACK_LABEL_NL NULL
#define VITA3K_FPS_HACK_INFO_0_NL NULL
#define VITA3K_SYS_BUTTON_LABEL_NL NULL
#define VITA3K_SYS_BUTTON_INFO_0_NL NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_NL NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_NL NULL
#define VITA3K_AUDIO_VOLUME_LABEL_NL NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_NL NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_NL NULL
#define OPTION_VAL_10_NL NULL
#define OPTION_VAL_20_NL NULL
#define OPTION_VAL_30_NL NULL
#define OPTION_VAL_40_NL NULL
#define OPTION_VAL_50_NL NULL
#define OPTION_VAL_60_NL NULL
#define OPTION_VAL_70_NL NULL
#define OPTION_VAL_80_NL NULL
#define OPTION_VAL_90_NL NULL
#define OPTION_VAL_100_NL NULL
#define VITA3K_NGS_ENABLE_LABEL_NL NULL
#define VITA3K_NGS_ENABLE_INFO_0_NL NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_NL NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_NL NULL
#define VITA3K_SURFACE_SYNC_LABEL_NL NULL
#define VITA3K_SURFACE_SYNC_INFO_0_NL NULL
#define OPTION_VAL_ENABLED_NL NULL
#define OPTION_VAL_DISABLED_NL NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_NL NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_NL NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_NL NULL
#define OPTION_VAL_5_NL NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_NL NULL
#define OPTION_VAL_15_NL NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_NL NULL
#define OPTION_VAL_25_NL NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_NL NULL

struct retro_core_option_v2_category option_cats_nl[] = {
    { "gpu", CATEGORY_GPU_LABEL_NL, CATEGORY_GPU_INFO_0_NL },
    { "cpu", CATEGORY_CPU_LABEL_NL, CATEGORY_CPU_INFO_0_NL },
    { "system", CATEGORY_SYSTEM_LABEL_NL, CATEGORY_SYSTEM_INFO_0_NL },
    { "audio", CATEGORY_AUDIO_LABEL_NL, CATEGORY_AUDIO_INFO_0_NL },
    { "network", CATEGORY_NETWORK_LABEL_NL, CATEGORY_NETWORK_INFO_0_NL },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_nl[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_NL,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_NL,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_NL },
            { "OpenGL", OPTION_VAL_OPENGL_NL },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_NL,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_NL,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_NL },
            { "2", OPTION_VAL_2_NL },
            { "3", OPTION_VAL_3_NL },
            { "4", OPTION_VAL_4_NL },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_NL,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_NL,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_NL },
            { "Nearest", OPTION_VAL_NEAREST_NL },
            { "Bicubic", OPTION_VAL_BICUBIC_NL },
            { "FXAA", OPTION_VAL_FXAA_NL },
            { "FSR", OPTION_VAL_FSR_NL },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_NL,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_NL,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_NL },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_NL },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_NL },
            { "8", OPTION_VAL_8_NL },
            { "16", OPTION_VAL_16_NL },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_NL,
        NULL,
        VITA3K_V_SYNC_INFO_0_NL,
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
        VITA3K_ASYNC_PIPELINE_LABEL_NL,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_NL,
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
        VITA3K_MEMORY_MAPPING_LABEL_NL,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_NL,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_NL },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_NL },
            { "page-table", OPTION_VAL_PAGE_TABLE_NL },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_NL },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_NL,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_NL,
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
        VITA3K_CPU_OPT_LABEL_NL,
        NULL,
        VITA3K_CPU_OPT_INFO_0_NL,
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
        VITA3K_PKG_MODE_LABEL_NL,
        NULL,
        VITA3K_PKG_MODE_INFO_0_NL,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_NL },
            { "install", OPTION_VAL_INSTALL_NL },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_NL,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_NL,
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
        VITA3K_MODULES_MODE_LABEL_NL,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_NL,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_NL },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_NL },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_NL },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_NL,
        NULL,
        VITA3K_FPS_HACK_INFO_0_NL,
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
        VITA3K_SYS_BUTTON_LABEL_NL,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_NL,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_NL },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_NL },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_NL,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_NL,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_NL },
            { "10", OPTION_VAL_10_NL },
            { "20", OPTION_VAL_20_NL },
            { "30", OPTION_VAL_30_NL },
            { "40", OPTION_VAL_40_NL },
            { "50", OPTION_VAL_50_NL },
            { "60", OPTION_VAL_60_NL },
            { "70", OPTION_VAL_70_NL },
            { "80", OPTION_VAL_80_NL },
            { "90", OPTION_VAL_90_NL },
            { "100", OPTION_VAL_100_NL },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_NL,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_NL,
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
        VITA3K_PSN_SIGNED_IN_LABEL_NL,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_NL,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_NL,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_NL,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_NL },
            { "disabled", OPTION_VAL_DISABLED_NL },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_NL,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_NL,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_NL },
            { "5", OPTION_VAL_5_NL },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_NL },
            { "15", OPTION_VAL_15_NL },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_NL },
            { "25", OPTION_VAL_25_NL },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_NL },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_nl = {
   option_cats_nl,
   option_defs_nl
};

/* RETRO_LANGUAGE_NO */

#define CATEGORY_GPU_LABEL_NO NULL
#define CATEGORY_GPU_INFO_0_NO NULL
#define CATEGORY_CPU_LABEL_NO NULL
#define CATEGORY_CPU_INFO_0_NO NULL
#define CATEGORY_SYSTEM_LABEL_NO NULL
#define CATEGORY_SYSTEM_INFO_0_NO NULL
#define CATEGORY_AUDIO_LABEL_NO NULL
#define CATEGORY_AUDIO_INFO_0_NO NULL
#define CATEGORY_NETWORK_LABEL_NO NULL
#define CATEGORY_NETWORK_INFO_0_NO NULL
#define VITA3K_BACKEND_RENDERER_LABEL_NO NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_NO NULL
#define OPTION_VAL_VULKAN_NO NULL
#define OPTION_VAL_OPENGL_NO NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_NO NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_NO NULL
#define OPTION_VAL_1_NO NULL
#define OPTION_VAL_2_NO NULL
#define OPTION_VAL_3_NO NULL
#define OPTION_VAL_4_NO NULL
#define VITA3K_SCREEN_FILTER_LABEL_NO NULL
#define VITA3K_SCREEN_FILTER_INFO_0_NO NULL
#define OPTION_VAL_BILINEAR_NO NULL
#define OPTION_VAL_NEAREST_NO NULL
#define OPTION_VAL_BICUBIC_NO NULL
#define OPTION_VAL_FXAA_NO NULL
#define OPTION_VAL_FSR_NO NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_NO NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_NO NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_NO NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_NO NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_NO NULL
#define OPTION_VAL_8_NO NULL
#define OPTION_VAL_16_NO NULL
#define VITA3K_V_SYNC_LABEL_NO NULL
#define VITA3K_V_SYNC_INFO_0_NO NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_NO NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_NO NULL
#define VITA3K_MEMORY_MAPPING_LABEL_NO NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_NO NULL
#define OPTION_VAL_DOUBLE_BUFFER_NO NULL
#define OPTION_VAL_EXTERNAL_HOST_NO NULL
#define OPTION_VAL_PAGE_TABLE_NO NULL
#define OPTION_VAL_NATIVE_BUFFER_NO NULL
#define VITA3K_HIGH_ACCURACY_LABEL_NO NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_NO NULL
#define VITA3K_CPU_OPT_LABEL_NO NULL
#define VITA3K_CPU_OPT_INFO_0_NO NULL
#define VITA3K_PKG_MODE_LABEL_NO NULL
#define VITA3K_PKG_MODE_INFO_0_NO NULL
#define OPTION_VAL_RUN_NO NULL
#define OPTION_VAL_INSTALL_NO NULL
#define VITA3K_PSTV_MODE_LABEL_NO NULL
#define VITA3K_PSTV_MODE_INFO_0_NO NULL
#define VITA3K_MODULES_MODE_LABEL_NO NULL
#define VITA3K_MODULES_MODE_INFO_0_NO NULL
#define OPTION_VAL_0_NO NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_NO NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_NO NULL
#define VITA3K_FPS_HACK_LABEL_NO NULL
#define VITA3K_FPS_HACK_INFO_0_NO NULL
#define VITA3K_SYS_BUTTON_LABEL_NO NULL
#define VITA3K_SYS_BUTTON_INFO_0_NO NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_NO NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_NO NULL
#define VITA3K_AUDIO_VOLUME_LABEL_NO NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_NO NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_NO NULL
#define OPTION_VAL_10_NO NULL
#define OPTION_VAL_20_NO NULL
#define OPTION_VAL_30_NO NULL
#define OPTION_VAL_40_NO NULL
#define OPTION_VAL_50_NO NULL
#define OPTION_VAL_60_NO NULL
#define OPTION_VAL_70_NO NULL
#define OPTION_VAL_80_NO NULL
#define OPTION_VAL_90_NO NULL
#define OPTION_VAL_100_NO NULL
#define VITA3K_NGS_ENABLE_LABEL_NO NULL
#define VITA3K_NGS_ENABLE_INFO_0_NO NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_NO NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_NO NULL
#define VITA3K_SURFACE_SYNC_LABEL_NO NULL
#define VITA3K_SURFACE_SYNC_INFO_0_NO NULL
#define OPTION_VAL_ENABLED_NO NULL
#define OPTION_VAL_DISABLED_NO NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_NO NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_NO NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_NO NULL
#define OPTION_VAL_5_NO NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_NO NULL
#define OPTION_VAL_15_NO NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_NO NULL
#define OPTION_VAL_25_NO NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_NO NULL

struct retro_core_option_v2_category option_cats_no[] = {
    { "gpu", CATEGORY_GPU_LABEL_NO, CATEGORY_GPU_INFO_0_NO },
    { "cpu", CATEGORY_CPU_LABEL_NO, CATEGORY_CPU_INFO_0_NO },
    { "system", CATEGORY_SYSTEM_LABEL_NO, CATEGORY_SYSTEM_INFO_0_NO },
    { "audio", CATEGORY_AUDIO_LABEL_NO, CATEGORY_AUDIO_INFO_0_NO },
    { "network", CATEGORY_NETWORK_LABEL_NO, CATEGORY_NETWORK_INFO_0_NO },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_no[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_NO,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_NO,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_NO },
            { "OpenGL", OPTION_VAL_OPENGL_NO },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_NO,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_NO,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_NO },
            { "2", OPTION_VAL_2_NO },
            { "3", OPTION_VAL_3_NO },
            { "4", OPTION_VAL_4_NO },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_NO,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_NO,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_NO },
            { "Nearest", OPTION_VAL_NEAREST_NO },
            { "Bicubic", OPTION_VAL_BICUBIC_NO },
            { "FXAA", OPTION_VAL_FXAA_NO },
            { "FSR", OPTION_VAL_FSR_NO },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_NO,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_NO,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_NO },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_NO },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_NO },
            { "8", OPTION_VAL_8_NO },
            { "16", OPTION_VAL_16_NO },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_NO,
        NULL,
        VITA3K_V_SYNC_INFO_0_NO,
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
        VITA3K_ASYNC_PIPELINE_LABEL_NO,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_NO,
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
        VITA3K_MEMORY_MAPPING_LABEL_NO,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_NO,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_NO },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_NO },
            { "page-table", OPTION_VAL_PAGE_TABLE_NO },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_NO },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_NO,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_NO,
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
        VITA3K_CPU_OPT_LABEL_NO,
        NULL,
        VITA3K_CPU_OPT_INFO_0_NO,
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
        VITA3K_PKG_MODE_LABEL_NO,
        NULL,
        VITA3K_PKG_MODE_INFO_0_NO,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_NO },
            { "install", OPTION_VAL_INSTALL_NO },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_NO,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_NO,
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
        VITA3K_MODULES_MODE_LABEL_NO,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_NO,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_NO },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_NO },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_NO },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_NO,
        NULL,
        VITA3K_FPS_HACK_INFO_0_NO,
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
        VITA3K_SYS_BUTTON_LABEL_NO,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_NO,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_NO },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_NO },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_NO,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_NO,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_NO },
            { "10", OPTION_VAL_10_NO },
            { "20", OPTION_VAL_20_NO },
            { "30", OPTION_VAL_30_NO },
            { "40", OPTION_VAL_40_NO },
            { "50", OPTION_VAL_50_NO },
            { "60", OPTION_VAL_60_NO },
            { "70", OPTION_VAL_70_NO },
            { "80", OPTION_VAL_80_NO },
            { "90", OPTION_VAL_90_NO },
            { "100", OPTION_VAL_100_NO },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_NO,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_NO,
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
        VITA3K_PSN_SIGNED_IN_LABEL_NO,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_NO,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_NO,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_NO,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_NO },
            { "disabled", OPTION_VAL_DISABLED_NO },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_NO,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_NO,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_NO },
            { "5", OPTION_VAL_5_NO },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_NO },
            { "15", OPTION_VAL_15_NO },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_NO },
            { "25", OPTION_VAL_25_NO },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_NO },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_no = {
   option_cats_no,
   option_defs_no
};

/* RETRO_LANGUAGE_PL */

#define CATEGORY_GPU_LABEL_PL NULL
#define CATEGORY_GPU_INFO_0_PL NULL
#define CATEGORY_CPU_LABEL_PL NULL
#define CATEGORY_CPU_INFO_0_PL NULL
#define CATEGORY_SYSTEM_LABEL_PL NULL
#define CATEGORY_SYSTEM_INFO_0_PL NULL
#define CATEGORY_AUDIO_LABEL_PL NULL
#define CATEGORY_AUDIO_INFO_0_PL NULL
#define CATEGORY_NETWORK_LABEL_PL NULL
#define CATEGORY_NETWORK_INFO_0_PL NULL
#define VITA3K_BACKEND_RENDERER_LABEL_PL NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_PL NULL
#define OPTION_VAL_VULKAN_PL NULL
#define OPTION_VAL_OPENGL_PL NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_PL NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_PL NULL
#define OPTION_VAL_1_PL NULL
#define OPTION_VAL_2_PL NULL
#define OPTION_VAL_3_PL NULL
#define OPTION_VAL_4_PL NULL
#define VITA3K_SCREEN_FILTER_LABEL_PL NULL
#define VITA3K_SCREEN_FILTER_INFO_0_PL NULL
#define OPTION_VAL_BILINEAR_PL NULL
#define OPTION_VAL_NEAREST_PL NULL
#define OPTION_VAL_BICUBIC_PL NULL
#define OPTION_VAL_FXAA_PL NULL
#define OPTION_VAL_FSR_PL NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_PL NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_PL NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_PL NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_PL NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_PL NULL
#define OPTION_VAL_8_PL NULL
#define OPTION_VAL_16_PL NULL
#define VITA3K_V_SYNC_LABEL_PL NULL
#define VITA3K_V_SYNC_INFO_0_PL NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_PL NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_PL NULL
#define VITA3K_MEMORY_MAPPING_LABEL_PL NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_PL NULL
#define OPTION_VAL_DOUBLE_BUFFER_PL NULL
#define OPTION_VAL_EXTERNAL_HOST_PL NULL
#define OPTION_VAL_PAGE_TABLE_PL NULL
#define OPTION_VAL_NATIVE_BUFFER_PL NULL
#define VITA3K_HIGH_ACCURACY_LABEL_PL NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_PL NULL
#define VITA3K_CPU_OPT_LABEL_PL NULL
#define VITA3K_CPU_OPT_INFO_0_PL NULL
#define VITA3K_PKG_MODE_LABEL_PL NULL
#define VITA3K_PKG_MODE_INFO_0_PL NULL
#define OPTION_VAL_RUN_PL NULL
#define OPTION_VAL_INSTALL_PL NULL
#define VITA3K_PSTV_MODE_LABEL_PL NULL
#define VITA3K_PSTV_MODE_INFO_0_PL NULL
#define VITA3K_MODULES_MODE_LABEL_PL NULL
#define VITA3K_MODULES_MODE_INFO_0_PL NULL
#define OPTION_VAL_0_PL NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_PL NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_PL NULL
#define VITA3K_FPS_HACK_LABEL_PL NULL
#define VITA3K_FPS_HACK_INFO_0_PL NULL
#define VITA3K_SYS_BUTTON_LABEL_PL NULL
#define VITA3K_SYS_BUTTON_INFO_0_PL NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_PL NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_PL NULL
#define VITA3K_AUDIO_VOLUME_LABEL_PL NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_PL NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_PL NULL
#define OPTION_VAL_10_PL NULL
#define OPTION_VAL_20_PL NULL
#define OPTION_VAL_30_PL NULL
#define OPTION_VAL_40_PL NULL
#define OPTION_VAL_50_PL NULL
#define OPTION_VAL_60_PL NULL
#define OPTION_VAL_70_PL NULL
#define OPTION_VAL_80_PL NULL
#define OPTION_VAL_90_PL NULL
#define OPTION_VAL_100_PL NULL
#define VITA3K_NGS_ENABLE_LABEL_PL NULL
#define VITA3K_NGS_ENABLE_INFO_0_PL NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_PL NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_PL NULL
#define VITA3K_SURFACE_SYNC_LABEL_PL NULL
#define VITA3K_SURFACE_SYNC_INFO_0_PL NULL
#define OPTION_VAL_ENABLED_PL NULL
#define OPTION_VAL_DISABLED_PL NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_PL NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_PL NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_PL NULL
#define OPTION_VAL_5_PL NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_PL NULL
#define OPTION_VAL_15_PL NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_PL NULL
#define OPTION_VAL_25_PL NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_PL NULL

struct retro_core_option_v2_category option_cats_pl[] = {
    { "gpu", CATEGORY_GPU_LABEL_PL, CATEGORY_GPU_INFO_0_PL },
    { "cpu", CATEGORY_CPU_LABEL_PL, CATEGORY_CPU_INFO_0_PL },
    { "system", CATEGORY_SYSTEM_LABEL_PL, CATEGORY_SYSTEM_INFO_0_PL },
    { "audio", CATEGORY_AUDIO_LABEL_PL, CATEGORY_AUDIO_INFO_0_PL },
    { "network", CATEGORY_NETWORK_LABEL_PL, CATEGORY_NETWORK_INFO_0_PL },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_pl[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_PL,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_PL,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_PL },
            { "OpenGL", OPTION_VAL_OPENGL_PL },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_PL,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_PL,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_PL },
            { "2", OPTION_VAL_2_PL },
            { "3", OPTION_VAL_3_PL },
            { "4", OPTION_VAL_4_PL },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_PL,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_PL,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_PL },
            { "Nearest", OPTION_VAL_NEAREST_PL },
            { "Bicubic", OPTION_VAL_BICUBIC_PL },
            { "FXAA", OPTION_VAL_FXAA_PL },
            { "FSR", OPTION_VAL_FSR_PL },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_PL,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_PL,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_PL },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_PL },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_PL },
            { "8", OPTION_VAL_8_PL },
            { "16", OPTION_VAL_16_PL },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_PL,
        NULL,
        VITA3K_V_SYNC_INFO_0_PL,
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
        VITA3K_ASYNC_PIPELINE_LABEL_PL,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_PL,
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
        VITA3K_MEMORY_MAPPING_LABEL_PL,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_PL,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_PL },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_PL },
            { "page-table", OPTION_VAL_PAGE_TABLE_PL },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_PL },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_PL,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_PL,
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
        VITA3K_CPU_OPT_LABEL_PL,
        NULL,
        VITA3K_CPU_OPT_INFO_0_PL,
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
        VITA3K_PKG_MODE_LABEL_PL,
        NULL,
        VITA3K_PKG_MODE_INFO_0_PL,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_PL },
            { "install", OPTION_VAL_INSTALL_PL },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_PL,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_PL,
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
        VITA3K_MODULES_MODE_LABEL_PL,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_PL,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_PL },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_PL },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_PL },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_PL,
        NULL,
        VITA3K_FPS_HACK_INFO_0_PL,
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
        VITA3K_SYS_BUTTON_LABEL_PL,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_PL,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_PL },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_PL },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_PL,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_PL,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_PL },
            { "10", OPTION_VAL_10_PL },
            { "20", OPTION_VAL_20_PL },
            { "30", OPTION_VAL_30_PL },
            { "40", OPTION_VAL_40_PL },
            { "50", OPTION_VAL_50_PL },
            { "60", OPTION_VAL_60_PL },
            { "70", OPTION_VAL_70_PL },
            { "80", OPTION_VAL_80_PL },
            { "90", OPTION_VAL_90_PL },
            { "100", OPTION_VAL_100_PL },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_PL,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_PL,
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
        VITA3K_PSN_SIGNED_IN_LABEL_PL,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_PL,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_PL,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_PL,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_PL },
            { "disabled", OPTION_VAL_DISABLED_PL },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_PL,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_PL,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_PL },
            { "5", OPTION_VAL_5_PL },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_PL },
            { "15", OPTION_VAL_15_PL },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_PL },
            { "25", OPTION_VAL_25_PL },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_PL },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_pl = {
   option_cats_pl,
   option_defs_pl
};

/* RETRO_LANGUAGE_PT_BR */

#define CATEGORY_GPU_LABEL_PT_BR NULL
#define CATEGORY_GPU_INFO_0_PT_BR NULL
#define CATEGORY_CPU_LABEL_PT_BR NULL
#define CATEGORY_CPU_INFO_0_PT_BR NULL
#define CATEGORY_SYSTEM_LABEL_PT_BR NULL
#define CATEGORY_SYSTEM_INFO_0_PT_BR NULL
#define CATEGORY_AUDIO_LABEL_PT_BR NULL
#define CATEGORY_AUDIO_INFO_0_PT_BR NULL
#define CATEGORY_NETWORK_LABEL_PT_BR NULL
#define CATEGORY_NETWORK_INFO_0_PT_BR NULL
#define VITA3K_BACKEND_RENDERER_LABEL_PT_BR NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_PT_BR NULL
#define OPTION_VAL_VULKAN_PT_BR NULL
#define OPTION_VAL_OPENGL_PT_BR NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_PT_BR NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_PT_BR NULL
#define OPTION_VAL_1_PT_BR NULL
#define OPTION_VAL_2_PT_BR NULL
#define OPTION_VAL_3_PT_BR NULL
#define OPTION_VAL_4_PT_BR NULL
#define VITA3K_SCREEN_FILTER_LABEL_PT_BR NULL
#define VITA3K_SCREEN_FILTER_INFO_0_PT_BR NULL
#define OPTION_VAL_BILINEAR_PT_BR NULL
#define OPTION_VAL_NEAREST_PT_BR NULL
#define OPTION_VAL_BICUBIC_PT_BR NULL
#define OPTION_VAL_FXAA_PT_BR NULL
#define OPTION_VAL_FSR_PT_BR NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_PT_BR NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_PT_BR NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_PT_BR NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_PT_BR NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_PT_BR NULL
#define OPTION_VAL_8_PT_BR NULL
#define OPTION_VAL_16_PT_BR NULL
#define VITA3K_V_SYNC_LABEL_PT_BR NULL
#define VITA3K_V_SYNC_INFO_0_PT_BR NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_PT_BR NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_PT_BR NULL
#define VITA3K_MEMORY_MAPPING_LABEL_PT_BR NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_PT_BR NULL
#define OPTION_VAL_DOUBLE_BUFFER_PT_BR NULL
#define OPTION_VAL_EXTERNAL_HOST_PT_BR NULL
#define OPTION_VAL_PAGE_TABLE_PT_BR NULL
#define OPTION_VAL_NATIVE_BUFFER_PT_BR NULL
#define VITA3K_HIGH_ACCURACY_LABEL_PT_BR NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_PT_BR NULL
#define VITA3K_CPU_OPT_LABEL_PT_BR NULL
#define VITA3K_CPU_OPT_INFO_0_PT_BR NULL
#define VITA3K_PKG_MODE_LABEL_PT_BR NULL
#define VITA3K_PKG_MODE_INFO_0_PT_BR NULL
#define OPTION_VAL_RUN_PT_BR NULL
#define OPTION_VAL_INSTALL_PT_BR NULL
#define VITA3K_PSTV_MODE_LABEL_PT_BR NULL
#define VITA3K_PSTV_MODE_INFO_0_PT_BR NULL
#define VITA3K_MODULES_MODE_LABEL_PT_BR NULL
#define VITA3K_MODULES_MODE_INFO_0_PT_BR NULL
#define OPTION_VAL_0_PT_BR NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_PT_BR NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_PT_BR NULL
#define VITA3K_FPS_HACK_LABEL_PT_BR NULL
#define VITA3K_FPS_HACK_INFO_0_PT_BR NULL
#define VITA3K_SYS_BUTTON_LABEL_PT_BR NULL
#define VITA3K_SYS_BUTTON_INFO_0_PT_BR NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_PT_BR NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_PT_BR NULL
#define VITA3K_AUDIO_VOLUME_LABEL_PT_BR NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_PT_BR NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_PT_BR NULL
#define OPTION_VAL_10_PT_BR NULL
#define OPTION_VAL_20_PT_BR NULL
#define OPTION_VAL_30_PT_BR NULL
#define OPTION_VAL_40_PT_BR NULL
#define OPTION_VAL_50_PT_BR NULL
#define OPTION_VAL_60_PT_BR NULL
#define OPTION_VAL_70_PT_BR NULL
#define OPTION_VAL_80_PT_BR NULL
#define OPTION_VAL_90_PT_BR NULL
#define OPTION_VAL_100_PT_BR NULL
#define VITA3K_NGS_ENABLE_LABEL_PT_BR NULL
#define VITA3K_NGS_ENABLE_INFO_0_PT_BR NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_PT_BR NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_PT_BR NULL
#define VITA3K_SURFACE_SYNC_LABEL_PT_BR NULL
#define VITA3K_SURFACE_SYNC_INFO_0_PT_BR NULL
#define OPTION_VAL_ENABLED_PT_BR NULL
#define OPTION_VAL_DISABLED_PT_BR NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_PT_BR NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_PT_BR NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_PT_BR NULL
#define OPTION_VAL_5_PT_BR NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_PT_BR NULL
#define OPTION_VAL_15_PT_BR NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_PT_BR NULL
#define OPTION_VAL_25_PT_BR NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_PT_BR NULL

struct retro_core_option_v2_category option_cats_pt_br[] = {
    { "gpu", CATEGORY_GPU_LABEL_PT_BR, CATEGORY_GPU_INFO_0_PT_BR },
    { "cpu", CATEGORY_CPU_LABEL_PT_BR, CATEGORY_CPU_INFO_0_PT_BR },
    { "system", CATEGORY_SYSTEM_LABEL_PT_BR, CATEGORY_SYSTEM_INFO_0_PT_BR },
    { "audio", CATEGORY_AUDIO_LABEL_PT_BR, CATEGORY_AUDIO_INFO_0_PT_BR },
    { "network", CATEGORY_NETWORK_LABEL_PT_BR, CATEGORY_NETWORK_INFO_0_PT_BR },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_pt_br[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_PT_BR,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_PT_BR,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_PT_BR },
            { "OpenGL", OPTION_VAL_OPENGL_PT_BR },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_PT_BR,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_PT_BR,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_PT_BR },
            { "2", OPTION_VAL_2_PT_BR },
            { "3", OPTION_VAL_3_PT_BR },
            { "4", OPTION_VAL_4_PT_BR },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_PT_BR,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_PT_BR,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_PT_BR },
            { "Nearest", OPTION_VAL_NEAREST_PT_BR },
            { "Bicubic", OPTION_VAL_BICUBIC_PT_BR },
            { "FXAA", OPTION_VAL_FXAA_PT_BR },
            { "FSR", OPTION_VAL_FSR_PT_BR },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_PT_BR,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_PT_BR,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_PT_BR },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_PT_BR },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_PT_BR },
            { "8", OPTION_VAL_8_PT_BR },
            { "16", OPTION_VAL_16_PT_BR },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_PT_BR,
        NULL,
        VITA3K_V_SYNC_INFO_0_PT_BR,
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
        VITA3K_ASYNC_PIPELINE_LABEL_PT_BR,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_PT_BR,
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
        VITA3K_MEMORY_MAPPING_LABEL_PT_BR,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_PT_BR,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_PT_BR },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_PT_BR },
            { "page-table", OPTION_VAL_PAGE_TABLE_PT_BR },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_PT_BR },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_PT_BR,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_PT_BR,
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
        VITA3K_CPU_OPT_LABEL_PT_BR,
        NULL,
        VITA3K_CPU_OPT_INFO_0_PT_BR,
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
        VITA3K_PKG_MODE_LABEL_PT_BR,
        NULL,
        VITA3K_PKG_MODE_INFO_0_PT_BR,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_PT_BR },
            { "install", OPTION_VAL_INSTALL_PT_BR },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_PT_BR,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_PT_BR,
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
        VITA3K_MODULES_MODE_LABEL_PT_BR,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_PT_BR,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_PT_BR },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_PT_BR },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_PT_BR },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_PT_BR,
        NULL,
        VITA3K_FPS_HACK_INFO_0_PT_BR,
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
        VITA3K_SYS_BUTTON_LABEL_PT_BR,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_PT_BR,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_PT_BR },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_PT_BR },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_PT_BR,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_PT_BR,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_PT_BR },
            { "10", OPTION_VAL_10_PT_BR },
            { "20", OPTION_VAL_20_PT_BR },
            { "30", OPTION_VAL_30_PT_BR },
            { "40", OPTION_VAL_40_PT_BR },
            { "50", OPTION_VAL_50_PT_BR },
            { "60", OPTION_VAL_60_PT_BR },
            { "70", OPTION_VAL_70_PT_BR },
            { "80", OPTION_VAL_80_PT_BR },
            { "90", OPTION_VAL_90_PT_BR },
            { "100", OPTION_VAL_100_PT_BR },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_PT_BR,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_PT_BR,
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
        VITA3K_PSN_SIGNED_IN_LABEL_PT_BR,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_PT_BR,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_PT_BR,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_PT_BR,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_PT_BR },
            { "disabled", OPTION_VAL_DISABLED_PT_BR },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_PT_BR,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_PT_BR,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_PT_BR },
            { "5", OPTION_VAL_5_PT_BR },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_PT_BR },
            { "15", OPTION_VAL_15_PT_BR },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_PT_BR },
            { "25", OPTION_VAL_25_PT_BR },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_PT_BR },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_pt_br = {
   option_cats_pt_br,
   option_defs_pt_br
};

/* RETRO_LANGUAGE_PT_PT */

#define CATEGORY_GPU_LABEL_PT_PT NULL
#define CATEGORY_GPU_INFO_0_PT_PT NULL
#define CATEGORY_CPU_LABEL_PT_PT NULL
#define CATEGORY_CPU_INFO_0_PT_PT NULL
#define CATEGORY_SYSTEM_LABEL_PT_PT NULL
#define CATEGORY_SYSTEM_INFO_0_PT_PT NULL
#define CATEGORY_AUDIO_LABEL_PT_PT NULL
#define CATEGORY_AUDIO_INFO_0_PT_PT NULL
#define CATEGORY_NETWORK_LABEL_PT_PT NULL
#define CATEGORY_NETWORK_INFO_0_PT_PT NULL
#define VITA3K_BACKEND_RENDERER_LABEL_PT_PT NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_PT_PT NULL
#define OPTION_VAL_VULKAN_PT_PT NULL
#define OPTION_VAL_OPENGL_PT_PT NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_PT_PT NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_PT_PT NULL
#define OPTION_VAL_1_PT_PT NULL
#define OPTION_VAL_2_PT_PT NULL
#define OPTION_VAL_3_PT_PT NULL
#define OPTION_VAL_4_PT_PT NULL
#define VITA3K_SCREEN_FILTER_LABEL_PT_PT NULL
#define VITA3K_SCREEN_FILTER_INFO_0_PT_PT NULL
#define OPTION_VAL_BILINEAR_PT_PT NULL
#define OPTION_VAL_NEAREST_PT_PT NULL
#define OPTION_VAL_BICUBIC_PT_PT NULL
#define OPTION_VAL_FXAA_PT_PT NULL
#define OPTION_VAL_FSR_PT_PT NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_PT_PT NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_PT_PT NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_PT_PT NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_PT_PT NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_PT_PT NULL
#define OPTION_VAL_8_PT_PT NULL
#define OPTION_VAL_16_PT_PT NULL
#define VITA3K_V_SYNC_LABEL_PT_PT NULL
#define VITA3K_V_SYNC_INFO_0_PT_PT NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_PT_PT NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_PT_PT NULL
#define VITA3K_MEMORY_MAPPING_LABEL_PT_PT NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_PT_PT NULL
#define OPTION_VAL_DOUBLE_BUFFER_PT_PT NULL
#define OPTION_VAL_EXTERNAL_HOST_PT_PT NULL
#define OPTION_VAL_PAGE_TABLE_PT_PT NULL
#define OPTION_VAL_NATIVE_BUFFER_PT_PT NULL
#define VITA3K_HIGH_ACCURACY_LABEL_PT_PT NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_PT_PT NULL
#define VITA3K_CPU_OPT_LABEL_PT_PT NULL
#define VITA3K_CPU_OPT_INFO_0_PT_PT NULL
#define VITA3K_PKG_MODE_LABEL_PT_PT NULL
#define VITA3K_PKG_MODE_INFO_0_PT_PT NULL
#define OPTION_VAL_RUN_PT_PT NULL
#define OPTION_VAL_INSTALL_PT_PT NULL
#define VITA3K_PSTV_MODE_LABEL_PT_PT NULL
#define VITA3K_PSTV_MODE_INFO_0_PT_PT NULL
#define VITA3K_MODULES_MODE_LABEL_PT_PT NULL
#define VITA3K_MODULES_MODE_INFO_0_PT_PT NULL
#define OPTION_VAL_0_PT_PT NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_PT_PT NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_PT_PT NULL
#define VITA3K_FPS_HACK_LABEL_PT_PT NULL
#define VITA3K_FPS_HACK_INFO_0_PT_PT NULL
#define VITA3K_SYS_BUTTON_LABEL_PT_PT NULL
#define VITA3K_SYS_BUTTON_INFO_0_PT_PT NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_PT_PT NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_PT_PT NULL
#define VITA3K_AUDIO_VOLUME_LABEL_PT_PT NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_PT_PT NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_PT_PT NULL
#define OPTION_VAL_10_PT_PT NULL
#define OPTION_VAL_20_PT_PT NULL
#define OPTION_VAL_30_PT_PT NULL
#define OPTION_VAL_40_PT_PT NULL
#define OPTION_VAL_50_PT_PT NULL
#define OPTION_VAL_60_PT_PT NULL
#define OPTION_VAL_70_PT_PT NULL
#define OPTION_VAL_80_PT_PT NULL
#define OPTION_VAL_90_PT_PT NULL
#define OPTION_VAL_100_PT_PT NULL
#define VITA3K_NGS_ENABLE_LABEL_PT_PT NULL
#define VITA3K_NGS_ENABLE_INFO_0_PT_PT NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_PT_PT NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_PT_PT NULL
#define VITA3K_SURFACE_SYNC_LABEL_PT_PT NULL
#define VITA3K_SURFACE_SYNC_INFO_0_PT_PT NULL
#define OPTION_VAL_ENABLED_PT_PT NULL
#define OPTION_VAL_DISABLED_PT_PT NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_PT_PT NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_PT_PT NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_PT_PT NULL
#define OPTION_VAL_5_PT_PT NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_PT_PT NULL
#define OPTION_VAL_15_PT_PT NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_PT_PT NULL
#define OPTION_VAL_25_PT_PT NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_PT_PT NULL

struct retro_core_option_v2_category option_cats_pt_pt[] = {
    { "gpu", CATEGORY_GPU_LABEL_PT_PT, CATEGORY_GPU_INFO_0_PT_PT },
    { "cpu", CATEGORY_CPU_LABEL_PT_PT, CATEGORY_CPU_INFO_0_PT_PT },
    { "system", CATEGORY_SYSTEM_LABEL_PT_PT, CATEGORY_SYSTEM_INFO_0_PT_PT },
    { "audio", CATEGORY_AUDIO_LABEL_PT_PT, CATEGORY_AUDIO_INFO_0_PT_PT },
    { "network", CATEGORY_NETWORK_LABEL_PT_PT, CATEGORY_NETWORK_INFO_0_PT_PT },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_pt_pt[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_PT_PT,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_PT_PT,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_PT_PT },
            { "OpenGL", OPTION_VAL_OPENGL_PT_PT },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_PT_PT,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_PT_PT,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_PT_PT },
            { "2", OPTION_VAL_2_PT_PT },
            { "3", OPTION_VAL_3_PT_PT },
            { "4", OPTION_VAL_4_PT_PT },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_PT_PT,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_PT_PT,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_PT_PT },
            { "Nearest", OPTION_VAL_NEAREST_PT_PT },
            { "Bicubic", OPTION_VAL_BICUBIC_PT_PT },
            { "FXAA", OPTION_VAL_FXAA_PT_PT },
            { "FSR", OPTION_VAL_FSR_PT_PT },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_PT_PT,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_PT_PT,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_PT_PT },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_PT_PT },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_PT_PT },
            { "8", OPTION_VAL_8_PT_PT },
            { "16", OPTION_VAL_16_PT_PT },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_PT_PT,
        NULL,
        VITA3K_V_SYNC_INFO_0_PT_PT,
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
        VITA3K_ASYNC_PIPELINE_LABEL_PT_PT,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_PT_PT,
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
        VITA3K_MEMORY_MAPPING_LABEL_PT_PT,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_PT_PT,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_PT_PT },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_PT_PT },
            { "page-table", OPTION_VAL_PAGE_TABLE_PT_PT },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_PT_PT },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_PT_PT,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_PT_PT,
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
        VITA3K_CPU_OPT_LABEL_PT_PT,
        NULL,
        VITA3K_CPU_OPT_INFO_0_PT_PT,
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
        VITA3K_PKG_MODE_LABEL_PT_PT,
        NULL,
        VITA3K_PKG_MODE_INFO_0_PT_PT,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_PT_PT },
            { "install", OPTION_VAL_INSTALL_PT_PT },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_PT_PT,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_PT_PT,
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
        VITA3K_MODULES_MODE_LABEL_PT_PT,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_PT_PT,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_PT_PT },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_PT_PT },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_PT_PT },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_PT_PT,
        NULL,
        VITA3K_FPS_HACK_INFO_0_PT_PT,
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
        VITA3K_SYS_BUTTON_LABEL_PT_PT,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_PT_PT,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_PT_PT },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_PT_PT },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_PT_PT,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_PT_PT,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_PT_PT },
            { "10", OPTION_VAL_10_PT_PT },
            { "20", OPTION_VAL_20_PT_PT },
            { "30", OPTION_VAL_30_PT_PT },
            { "40", OPTION_VAL_40_PT_PT },
            { "50", OPTION_VAL_50_PT_PT },
            { "60", OPTION_VAL_60_PT_PT },
            { "70", OPTION_VAL_70_PT_PT },
            { "80", OPTION_VAL_80_PT_PT },
            { "90", OPTION_VAL_90_PT_PT },
            { "100", OPTION_VAL_100_PT_PT },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_PT_PT,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_PT_PT,
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
        VITA3K_PSN_SIGNED_IN_LABEL_PT_PT,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_PT_PT,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_PT_PT,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_PT_PT,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_PT_PT },
            { "disabled", OPTION_VAL_DISABLED_PT_PT },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_PT_PT,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_PT_PT,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_PT_PT },
            { "5", OPTION_VAL_5_PT_PT },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_PT_PT },
            { "15", OPTION_VAL_15_PT_PT },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_PT_PT },
            { "25", OPTION_VAL_25_PT_PT },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_PT_PT },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_pt_pt = {
   option_cats_pt_pt,
   option_defs_pt_pt
};

/* RETRO_LANGUAGE_RU */

#define CATEGORY_GPU_LABEL_RU NULL
#define CATEGORY_GPU_INFO_0_RU NULL
#define CATEGORY_CPU_LABEL_RU NULL
#define CATEGORY_CPU_INFO_0_RU NULL
#define CATEGORY_SYSTEM_LABEL_RU NULL
#define CATEGORY_SYSTEM_INFO_0_RU NULL
#define CATEGORY_AUDIO_LABEL_RU NULL
#define CATEGORY_AUDIO_INFO_0_RU NULL
#define CATEGORY_NETWORK_LABEL_RU NULL
#define CATEGORY_NETWORK_INFO_0_RU NULL
#define VITA3K_BACKEND_RENDERER_LABEL_RU NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_RU NULL
#define OPTION_VAL_VULKAN_RU NULL
#define OPTION_VAL_OPENGL_RU NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_RU NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_RU NULL
#define OPTION_VAL_1_RU NULL
#define OPTION_VAL_2_RU NULL
#define OPTION_VAL_3_RU NULL
#define OPTION_VAL_4_RU NULL
#define VITA3K_SCREEN_FILTER_LABEL_RU NULL
#define VITA3K_SCREEN_FILTER_INFO_0_RU NULL
#define OPTION_VAL_BILINEAR_RU NULL
#define OPTION_VAL_NEAREST_RU NULL
#define OPTION_VAL_BICUBIC_RU NULL
#define OPTION_VAL_FXAA_RU NULL
#define OPTION_VAL_FSR_RU NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_RU NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_RU NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_RU NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_RU NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_RU NULL
#define OPTION_VAL_8_RU NULL
#define OPTION_VAL_16_RU NULL
#define VITA3K_V_SYNC_LABEL_RU NULL
#define VITA3K_V_SYNC_INFO_0_RU NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_RU NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_RU NULL
#define VITA3K_MEMORY_MAPPING_LABEL_RU NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_RU NULL
#define OPTION_VAL_DOUBLE_BUFFER_RU NULL
#define OPTION_VAL_EXTERNAL_HOST_RU NULL
#define OPTION_VAL_PAGE_TABLE_RU NULL
#define OPTION_VAL_NATIVE_BUFFER_RU NULL
#define VITA3K_HIGH_ACCURACY_LABEL_RU NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_RU NULL
#define VITA3K_CPU_OPT_LABEL_RU NULL
#define VITA3K_CPU_OPT_INFO_0_RU NULL
#define VITA3K_PKG_MODE_LABEL_RU NULL
#define VITA3K_PKG_MODE_INFO_0_RU NULL
#define OPTION_VAL_RUN_RU NULL
#define OPTION_VAL_INSTALL_RU NULL
#define VITA3K_PSTV_MODE_LABEL_RU NULL
#define VITA3K_PSTV_MODE_INFO_0_RU NULL
#define VITA3K_MODULES_MODE_LABEL_RU NULL
#define VITA3K_MODULES_MODE_INFO_0_RU NULL
#define OPTION_VAL_0_RU NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_RU NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_RU NULL
#define VITA3K_FPS_HACK_LABEL_RU NULL
#define VITA3K_FPS_HACK_INFO_0_RU NULL
#define VITA3K_SYS_BUTTON_LABEL_RU NULL
#define VITA3K_SYS_BUTTON_INFO_0_RU NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_RU NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_RU NULL
#define VITA3K_AUDIO_VOLUME_LABEL_RU NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_RU NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_RU NULL
#define OPTION_VAL_10_RU NULL
#define OPTION_VAL_20_RU NULL
#define OPTION_VAL_30_RU NULL
#define OPTION_VAL_40_RU NULL
#define OPTION_VAL_50_RU NULL
#define OPTION_VAL_60_RU NULL
#define OPTION_VAL_70_RU NULL
#define OPTION_VAL_80_RU NULL
#define OPTION_VAL_90_RU NULL
#define OPTION_VAL_100_RU NULL
#define VITA3K_NGS_ENABLE_LABEL_RU NULL
#define VITA3K_NGS_ENABLE_INFO_0_RU NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_RU NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_RU NULL
#define VITA3K_SURFACE_SYNC_LABEL_RU NULL
#define VITA3K_SURFACE_SYNC_INFO_0_RU NULL
#define OPTION_VAL_ENABLED_RU NULL
#define OPTION_VAL_DISABLED_RU NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_RU NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_RU NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_RU NULL
#define OPTION_VAL_5_RU NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_RU NULL
#define OPTION_VAL_15_RU NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_RU NULL
#define OPTION_VAL_25_RU NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_RU NULL

struct retro_core_option_v2_category option_cats_ru[] = {
    { "gpu", CATEGORY_GPU_LABEL_RU, CATEGORY_GPU_INFO_0_RU },
    { "cpu", CATEGORY_CPU_LABEL_RU, CATEGORY_CPU_INFO_0_RU },
    { "system", CATEGORY_SYSTEM_LABEL_RU, CATEGORY_SYSTEM_INFO_0_RU },
    { "audio", CATEGORY_AUDIO_LABEL_RU, CATEGORY_AUDIO_INFO_0_RU },
    { "network", CATEGORY_NETWORK_LABEL_RU, CATEGORY_NETWORK_INFO_0_RU },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_ru[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_RU,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_RU,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_RU },
            { "OpenGL", OPTION_VAL_OPENGL_RU },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_RU,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_RU,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_RU },
            { "2", OPTION_VAL_2_RU },
            { "3", OPTION_VAL_3_RU },
            { "4", OPTION_VAL_4_RU },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_RU,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_RU,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_RU },
            { "Nearest", OPTION_VAL_NEAREST_RU },
            { "Bicubic", OPTION_VAL_BICUBIC_RU },
            { "FXAA", OPTION_VAL_FXAA_RU },
            { "FSR", OPTION_VAL_FSR_RU },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_RU,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_RU,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_RU },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_RU },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_RU },
            { "8", OPTION_VAL_8_RU },
            { "16", OPTION_VAL_16_RU },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_RU,
        NULL,
        VITA3K_V_SYNC_INFO_0_RU,
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
        VITA3K_ASYNC_PIPELINE_LABEL_RU,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_RU,
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
        VITA3K_MEMORY_MAPPING_LABEL_RU,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_RU,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_RU },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_RU },
            { "page-table", OPTION_VAL_PAGE_TABLE_RU },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_RU },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_RU,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_RU,
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
        VITA3K_CPU_OPT_LABEL_RU,
        NULL,
        VITA3K_CPU_OPT_INFO_0_RU,
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
        VITA3K_PKG_MODE_LABEL_RU,
        NULL,
        VITA3K_PKG_MODE_INFO_0_RU,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_RU },
            { "install", OPTION_VAL_INSTALL_RU },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_RU,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_RU,
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
        VITA3K_MODULES_MODE_LABEL_RU,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_RU,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_RU },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_RU },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_RU },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_RU,
        NULL,
        VITA3K_FPS_HACK_INFO_0_RU,
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
        VITA3K_SYS_BUTTON_LABEL_RU,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_RU,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_RU },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_RU },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_RU,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_RU,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_RU },
            { "10", OPTION_VAL_10_RU },
            { "20", OPTION_VAL_20_RU },
            { "30", OPTION_VAL_30_RU },
            { "40", OPTION_VAL_40_RU },
            { "50", OPTION_VAL_50_RU },
            { "60", OPTION_VAL_60_RU },
            { "70", OPTION_VAL_70_RU },
            { "80", OPTION_VAL_80_RU },
            { "90", OPTION_VAL_90_RU },
            { "100", OPTION_VAL_100_RU },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_RU,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_RU,
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
        VITA3K_PSN_SIGNED_IN_LABEL_RU,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_RU,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_RU,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_RU,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_RU },
            { "disabled", OPTION_VAL_DISABLED_RU },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_RU,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_RU,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_RU },
            { "5", OPTION_VAL_5_RU },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_RU },
            { "15", OPTION_VAL_15_RU },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_RU },
            { "25", OPTION_VAL_25_RU },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_RU },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_ru = {
   option_cats_ru,
   option_defs_ru
};

/* RETRO_LANGUAGE_SK */

#define CATEGORY_GPU_LABEL_SK NULL
#define CATEGORY_GPU_INFO_0_SK NULL
#define CATEGORY_CPU_LABEL_SK NULL
#define CATEGORY_CPU_INFO_0_SK NULL
#define CATEGORY_SYSTEM_LABEL_SK NULL
#define CATEGORY_SYSTEM_INFO_0_SK NULL
#define CATEGORY_AUDIO_LABEL_SK NULL
#define CATEGORY_AUDIO_INFO_0_SK NULL
#define CATEGORY_NETWORK_LABEL_SK NULL
#define CATEGORY_NETWORK_INFO_0_SK NULL
#define VITA3K_BACKEND_RENDERER_LABEL_SK NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_SK NULL
#define OPTION_VAL_VULKAN_SK NULL
#define OPTION_VAL_OPENGL_SK NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_SK NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_SK NULL
#define OPTION_VAL_1_SK NULL
#define OPTION_VAL_2_SK NULL
#define OPTION_VAL_3_SK NULL
#define OPTION_VAL_4_SK NULL
#define VITA3K_SCREEN_FILTER_LABEL_SK NULL
#define VITA3K_SCREEN_FILTER_INFO_0_SK NULL
#define OPTION_VAL_BILINEAR_SK NULL
#define OPTION_VAL_NEAREST_SK NULL
#define OPTION_VAL_BICUBIC_SK NULL
#define OPTION_VAL_FXAA_SK NULL
#define OPTION_VAL_FSR_SK NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_SK NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_SK NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_SK NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_SK NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_SK NULL
#define OPTION_VAL_8_SK NULL
#define OPTION_VAL_16_SK NULL
#define VITA3K_V_SYNC_LABEL_SK NULL
#define VITA3K_V_SYNC_INFO_0_SK NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_SK NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_SK NULL
#define VITA3K_MEMORY_MAPPING_LABEL_SK NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_SK NULL
#define OPTION_VAL_DOUBLE_BUFFER_SK NULL
#define OPTION_VAL_EXTERNAL_HOST_SK NULL
#define OPTION_VAL_PAGE_TABLE_SK NULL
#define OPTION_VAL_NATIVE_BUFFER_SK NULL
#define VITA3K_HIGH_ACCURACY_LABEL_SK NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_SK NULL
#define VITA3K_CPU_OPT_LABEL_SK NULL
#define VITA3K_CPU_OPT_INFO_0_SK NULL
#define VITA3K_PKG_MODE_LABEL_SK NULL
#define VITA3K_PKG_MODE_INFO_0_SK NULL
#define OPTION_VAL_RUN_SK NULL
#define OPTION_VAL_INSTALL_SK NULL
#define VITA3K_PSTV_MODE_LABEL_SK NULL
#define VITA3K_PSTV_MODE_INFO_0_SK NULL
#define VITA3K_MODULES_MODE_LABEL_SK NULL
#define VITA3K_MODULES_MODE_INFO_0_SK NULL
#define OPTION_VAL_0_SK NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_SK NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_SK NULL
#define VITA3K_FPS_HACK_LABEL_SK NULL
#define VITA3K_FPS_HACK_INFO_0_SK NULL
#define VITA3K_SYS_BUTTON_LABEL_SK NULL
#define VITA3K_SYS_BUTTON_INFO_0_SK NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_SK NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_SK NULL
#define VITA3K_AUDIO_VOLUME_LABEL_SK NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_SK NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_SK NULL
#define OPTION_VAL_10_SK NULL
#define OPTION_VAL_20_SK NULL
#define OPTION_VAL_30_SK NULL
#define OPTION_VAL_40_SK NULL
#define OPTION_VAL_50_SK NULL
#define OPTION_VAL_60_SK NULL
#define OPTION_VAL_70_SK NULL
#define OPTION_VAL_80_SK NULL
#define OPTION_VAL_90_SK NULL
#define OPTION_VAL_100_SK NULL
#define VITA3K_NGS_ENABLE_LABEL_SK NULL
#define VITA3K_NGS_ENABLE_INFO_0_SK NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_SK NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_SK NULL
#define VITA3K_SURFACE_SYNC_LABEL_SK NULL
#define VITA3K_SURFACE_SYNC_INFO_0_SK NULL
#define OPTION_VAL_ENABLED_SK NULL
#define OPTION_VAL_DISABLED_SK NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_SK NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_SK NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_SK NULL
#define OPTION_VAL_5_SK NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_SK NULL
#define OPTION_VAL_15_SK NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_SK NULL
#define OPTION_VAL_25_SK NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_SK NULL

struct retro_core_option_v2_category option_cats_sk[] = {
    { "gpu", CATEGORY_GPU_LABEL_SK, CATEGORY_GPU_INFO_0_SK },
    { "cpu", CATEGORY_CPU_LABEL_SK, CATEGORY_CPU_INFO_0_SK },
    { "system", CATEGORY_SYSTEM_LABEL_SK, CATEGORY_SYSTEM_INFO_0_SK },
    { "audio", CATEGORY_AUDIO_LABEL_SK, CATEGORY_AUDIO_INFO_0_SK },
    { "network", CATEGORY_NETWORK_LABEL_SK, CATEGORY_NETWORK_INFO_0_SK },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_sk[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_SK,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_SK,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_SK },
            { "OpenGL", OPTION_VAL_OPENGL_SK },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_SK,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_SK,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_SK },
            { "2", OPTION_VAL_2_SK },
            { "3", OPTION_VAL_3_SK },
            { "4", OPTION_VAL_4_SK },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_SK,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_SK,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_SK },
            { "Nearest", OPTION_VAL_NEAREST_SK },
            { "Bicubic", OPTION_VAL_BICUBIC_SK },
            { "FXAA", OPTION_VAL_FXAA_SK },
            { "FSR", OPTION_VAL_FSR_SK },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_SK,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_SK,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_SK },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_SK },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_SK },
            { "8", OPTION_VAL_8_SK },
            { "16", OPTION_VAL_16_SK },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_SK,
        NULL,
        VITA3K_V_SYNC_INFO_0_SK,
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
        VITA3K_ASYNC_PIPELINE_LABEL_SK,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_SK,
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
        VITA3K_MEMORY_MAPPING_LABEL_SK,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_SK,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_SK },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_SK },
            { "page-table", OPTION_VAL_PAGE_TABLE_SK },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_SK },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_SK,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_SK,
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
        VITA3K_CPU_OPT_LABEL_SK,
        NULL,
        VITA3K_CPU_OPT_INFO_0_SK,
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
        VITA3K_PKG_MODE_LABEL_SK,
        NULL,
        VITA3K_PKG_MODE_INFO_0_SK,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_SK },
            { "install", OPTION_VAL_INSTALL_SK },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_SK,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_SK,
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
        VITA3K_MODULES_MODE_LABEL_SK,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_SK,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_SK },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_SK },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_SK },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_SK,
        NULL,
        VITA3K_FPS_HACK_INFO_0_SK,
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
        VITA3K_SYS_BUTTON_LABEL_SK,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_SK,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_SK },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_SK },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_SK,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_SK,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_SK },
            { "10", OPTION_VAL_10_SK },
            { "20", OPTION_VAL_20_SK },
            { "30", OPTION_VAL_30_SK },
            { "40", OPTION_VAL_40_SK },
            { "50", OPTION_VAL_50_SK },
            { "60", OPTION_VAL_60_SK },
            { "70", OPTION_VAL_70_SK },
            { "80", OPTION_VAL_80_SK },
            { "90", OPTION_VAL_90_SK },
            { "100", OPTION_VAL_100_SK },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_SK,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_SK,
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
        VITA3K_PSN_SIGNED_IN_LABEL_SK,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_SK,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_SK,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_SK,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_SK },
            { "disabled", OPTION_VAL_DISABLED_SK },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_SK,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_SK,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_SK },
            { "5", OPTION_VAL_5_SK },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_SK },
            { "15", OPTION_VAL_15_SK },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_SK },
            { "25", OPTION_VAL_25_SK },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_SK },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_sk = {
   option_cats_sk,
   option_defs_sk
};

/* RETRO_LANGUAGE_SV */

#define CATEGORY_GPU_LABEL_SV NULL
#define CATEGORY_GPU_INFO_0_SV NULL
#define CATEGORY_CPU_LABEL_SV NULL
#define CATEGORY_CPU_INFO_0_SV NULL
#define CATEGORY_SYSTEM_LABEL_SV NULL
#define CATEGORY_SYSTEM_INFO_0_SV NULL
#define CATEGORY_AUDIO_LABEL_SV NULL
#define CATEGORY_AUDIO_INFO_0_SV NULL
#define CATEGORY_NETWORK_LABEL_SV NULL
#define CATEGORY_NETWORK_INFO_0_SV NULL
#define VITA3K_BACKEND_RENDERER_LABEL_SV NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_SV NULL
#define OPTION_VAL_VULKAN_SV NULL
#define OPTION_VAL_OPENGL_SV NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_SV NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_SV NULL
#define OPTION_VAL_1_SV NULL
#define OPTION_VAL_2_SV NULL
#define OPTION_VAL_3_SV NULL
#define OPTION_VAL_4_SV NULL
#define VITA3K_SCREEN_FILTER_LABEL_SV NULL
#define VITA3K_SCREEN_FILTER_INFO_0_SV NULL
#define OPTION_VAL_BILINEAR_SV NULL
#define OPTION_VAL_NEAREST_SV NULL
#define OPTION_VAL_BICUBIC_SV NULL
#define OPTION_VAL_FXAA_SV NULL
#define OPTION_VAL_FSR_SV NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_SV NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_SV NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_SV NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_SV NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_SV NULL
#define OPTION_VAL_8_SV NULL
#define OPTION_VAL_16_SV NULL
#define VITA3K_V_SYNC_LABEL_SV NULL
#define VITA3K_V_SYNC_INFO_0_SV NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_SV NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_SV NULL
#define VITA3K_MEMORY_MAPPING_LABEL_SV NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_SV NULL
#define OPTION_VAL_DOUBLE_BUFFER_SV NULL
#define OPTION_VAL_EXTERNAL_HOST_SV NULL
#define OPTION_VAL_PAGE_TABLE_SV NULL
#define OPTION_VAL_NATIVE_BUFFER_SV NULL
#define VITA3K_HIGH_ACCURACY_LABEL_SV NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_SV NULL
#define VITA3K_CPU_OPT_LABEL_SV NULL
#define VITA3K_CPU_OPT_INFO_0_SV NULL
#define VITA3K_PKG_MODE_LABEL_SV NULL
#define VITA3K_PKG_MODE_INFO_0_SV NULL
#define OPTION_VAL_RUN_SV NULL
#define OPTION_VAL_INSTALL_SV NULL
#define VITA3K_PSTV_MODE_LABEL_SV NULL
#define VITA3K_PSTV_MODE_INFO_0_SV NULL
#define VITA3K_MODULES_MODE_LABEL_SV NULL
#define VITA3K_MODULES_MODE_INFO_0_SV NULL
#define OPTION_VAL_0_SV NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_SV NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_SV NULL
#define VITA3K_FPS_HACK_LABEL_SV NULL
#define VITA3K_FPS_HACK_INFO_0_SV NULL
#define VITA3K_SYS_BUTTON_LABEL_SV NULL
#define VITA3K_SYS_BUTTON_INFO_0_SV NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_SV NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_SV NULL
#define VITA3K_AUDIO_VOLUME_LABEL_SV NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_SV NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_SV NULL
#define OPTION_VAL_10_SV NULL
#define OPTION_VAL_20_SV NULL
#define OPTION_VAL_30_SV NULL
#define OPTION_VAL_40_SV NULL
#define OPTION_VAL_50_SV NULL
#define OPTION_VAL_60_SV NULL
#define OPTION_VAL_70_SV NULL
#define OPTION_VAL_80_SV NULL
#define OPTION_VAL_90_SV NULL
#define OPTION_VAL_100_SV NULL
#define VITA3K_NGS_ENABLE_LABEL_SV NULL
#define VITA3K_NGS_ENABLE_INFO_0_SV NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_SV NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_SV NULL
#define VITA3K_SURFACE_SYNC_LABEL_SV NULL
#define VITA3K_SURFACE_SYNC_INFO_0_SV NULL
#define OPTION_VAL_ENABLED_SV NULL
#define OPTION_VAL_DISABLED_SV NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_SV NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_SV NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_SV NULL
#define OPTION_VAL_5_SV NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_SV NULL
#define OPTION_VAL_15_SV NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_SV NULL
#define OPTION_VAL_25_SV NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_SV NULL

struct retro_core_option_v2_category option_cats_sv[] = {
    { "gpu", CATEGORY_GPU_LABEL_SV, CATEGORY_GPU_INFO_0_SV },
    { "cpu", CATEGORY_CPU_LABEL_SV, CATEGORY_CPU_INFO_0_SV },
    { "system", CATEGORY_SYSTEM_LABEL_SV, CATEGORY_SYSTEM_INFO_0_SV },
    { "audio", CATEGORY_AUDIO_LABEL_SV, CATEGORY_AUDIO_INFO_0_SV },
    { "network", CATEGORY_NETWORK_LABEL_SV, CATEGORY_NETWORK_INFO_0_SV },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_sv[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_SV,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_SV,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_SV },
            { "OpenGL", OPTION_VAL_OPENGL_SV },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_SV,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_SV,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_SV },
            { "2", OPTION_VAL_2_SV },
            { "3", OPTION_VAL_3_SV },
            { "4", OPTION_VAL_4_SV },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_SV,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_SV,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_SV },
            { "Nearest", OPTION_VAL_NEAREST_SV },
            { "Bicubic", OPTION_VAL_BICUBIC_SV },
            { "FXAA", OPTION_VAL_FXAA_SV },
            { "FSR", OPTION_VAL_FSR_SV },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_SV,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_SV,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_SV },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_SV },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_SV },
            { "8", OPTION_VAL_8_SV },
            { "16", OPTION_VAL_16_SV },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_SV,
        NULL,
        VITA3K_V_SYNC_INFO_0_SV,
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
        VITA3K_ASYNC_PIPELINE_LABEL_SV,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_SV,
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
        VITA3K_MEMORY_MAPPING_LABEL_SV,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_SV,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_SV },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_SV },
            { "page-table", OPTION_VAL_PAGE_TABLE_SV },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_SV },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_SV,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_SV,
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
        VITA3K_CPU_OPT_LABEL_SV,
        NULL,
        VITA3K_CPU_OPT_INFO_0_SV,
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
        VITA3K_PKG_MODE_LABEL_SV,
        NULL,
        VITA3K_PKG_MODE_INFO_0_SV,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_SV },
            { "install", OPTION_VAL_INSTALL_SV },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_SV,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_SV,
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
        VITA3K_MODULES_MODE_LABEL_SV,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_SV,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_SV },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_SV },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_SV },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_SV,
        NULL,
        VITA3K_FPS_HACK_INFO_0_SV,
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
        VITA3K_SYS_BUTTON_LABEL_SV,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_SV,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_SV },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_SV },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_SV,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_SV,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_SV },
            { "10", OPTION_VAL_10_SV },
            { "20", OPTION_VAL_20_SV },
            { "30", OPTION_VAL_30_SV },
            { "40", OPTION_VAL_40_SV },
            { "50", OPTION_VAL_50_SV },
            { "60", OPTION_VAL_60_SV },
            { "70", OPTION_VAL_70_SV },
            { "80", OPTION_VAL_80_SV },
            { "90", OPTION_VAL_90_SV },
            { "100", OPTION_VAL_100_SV },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_SV,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_SV,
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
        VITA3K_PSN_SIGNED_IN_LABEL_SV,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_SV,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_SV,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_SV,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_SV },
            { "disabled", OPTION_VAL_DISABLED_SV },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_SV,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_SV,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_SV },
            { "5", OPTION_VAL_5_SV },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_SV },
            { "15", OPTION_VAL_15_SV },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_SV },
            { "25", OPTION_VAL_25_SV },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_SV },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_sv = {
   option_cats_sv,
   option_defs_sv
};

/* RETRO_LANGUAGE_TR */

#define CATEGORY_GPU_LABEL_TR NULL
#define CATEGORY_GPU_INFO_0_TR NULL
#define CATEGORY_CPU_LABEL_TR NULL
#define CATEGORY_CPU_INFO_0_TR NULL
#define CATEGORY_SYSTEM_LABEL_TR NULL
#define CATEGORY_SYSTEM_INFO_0_TR NULL
#define CATEGORY_AUDIO_LABEL_TR NULL
#define CATEGORY_AUDIO_INFO_0_TR NULL
#define CATEGORY_NETWORK_LABEL_TR NULL
#define CATEGORY_NETWORK_INFO_0_TR NULL
#define VITA3K_BACKEND_RENDERER_LABEL_TR NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_TR NULL
#define OPTION_VAL_VULKAN_TR NULL
#define OPTION_VAL_OPENGL_TR NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_TR NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_TR NULL
#define OPTION_VAL_1_TR NULL
#define OPTION_VAL_2_TR NULL
#define OPTION_VAL_3_TR NULL
#define OPTION_VAL_4_TR NULL
#define VITA3K_SCREEN_FILTER_LABEL_TR NULL
#define VITA3K_SCREEN_FILTER_INFO_0_TR NULL
#define OPTION_VAL_BILINEAR_TR NULL
#define OPTION_VAL_NEAREST_TR NULL
#define OPTION_VAL_BICUBIC_TR NULL
#define OPTION_VAL_FXAA_TR NULL
#define OPTION_VAL_FSR_TR NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_TR NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_TR NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_TR NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_TR NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_TR NULL
#define OPTION_VAL_8_TR NULL
#define OPTION_VAL_16_TR NULL
#define VITA3K_V_SYNC_LABEL_TR NULL
#define VITA3K_V_SYNC_INFO_0_TR NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_TR NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_TR NULL
#define VITA3K_MEMORY_MAPPING_LABEL_TR NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_TR NULL
#define OPTION_VAL_DOUBLE_BUFFER_TR NULL
#define OPTION_VAL_EXTERNAL_HOST_TR NULL
#define OPTION_VAL_PAGE_TABLE_TR NULL
#define OPTION_VAL_NATIVE_BUFFER_TR NULL
#define VITA3K_HIGH_ACCURACY_LABEL_TR NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_TR NULL
#define VITA3K_CPU_OPT_LABEL_TR NULL
#define VITA3K_CPU_OPT_INFO_0_TR NULL
#define VITA3K_PKG_MODE_LABEL_TR NULL
#define VITA3K_PKG_MODE_INFO_0_TR NULL
#define OPTION_VAL_RUN_TR NULL
#define OPTION_VAL_INSTALL_TR NULL
#define VITA3K_PSTV_MODE_LABEL_TR NULL
#define VITA3K_PSTV_MODE_INFO_0_TR NULL
#define VITA3K_MODULES_MODE_LABEL_TR NULL
#define VITA3K_MODULES_MODE_INFO_0_TR NULL
#define OPTION_VAL_0_TR NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_TR NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_TR NULL
#define VITA3K_FPS_HACK_LABEL_TR NULL
#define VITA3K_FPS_HACK_INFO_0_TR NULL
#define VITA3K_SYS_BUTTON_LABEL_TR NULL
#define VITA3K_SYS_BUTTON_INFO_0_TR NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_TR NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_TR NULL
#define VITA3K_AUDIO_VOLUME_LABEL_TR NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_TR NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_TR NULL
#define OPTION_VAL_10_TR NULL
#define OPTION_VAL_20_TR NULL
#define OPTION_VAL_30_TR NULL
#define OPTION_VAL_40_TR NULL
#define OPTION_VAL_50_TR NULL
#define OPTION_VAL_60_TR NULL
#define OPTION_VAL_70_TR NULL
#define OPTION_VAL_80_TR NULL
#define OPTION_VAL_90_TR NULL
#define OPTION_VAL_100_TR NULL
#define VITA3K_NGS_ENABLE_LABEL_TR NULL
#define VITA3K_NGS_ENABLE_INFO_0_TR NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_TR NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_TR NULL
#define VITA3K_SURFACE_SYNC_LABEL_TR NULL
#define VITA3K_SURFACE_SYNC_INFO_0_TR NULL
#define OPTION_VAL_ENABLED_TR NULL
#define OPTION_VAL_DISABLED_TR NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_TR NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_TR NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_TR NULL
#define OPTION_VAL_5_TR NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_TR NULL
#define OPTION_VAL_15_TR NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_TR NULL
#define OPTION_VAL_25_TR NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_TR NULL

struct retro_core_option_v2_category option_cats_tr[] = {
    { "gpu", CATEGORY_GPU_LABEL_TR, CATEGORY_GPU_INFO_0_TR },
    { "cpu", CATEGORY_CPU_LABEL_TR, CATEGORY_CPU_INFO_0_TR },
    { "system", CATEGORY_SYSTEM_LABEL_TR, CATEGORY_SYSTEM_INFO_0_TR },
    { "audio", CATEGORY_AUDIO_LABEL_TR, CATEGORY_AUDIO_INFO_0_TR },
    { "network", CATEGORY_NETWORK_LABEL_TR, CATEGORY_NETWORK_INFO_0_TR },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_tr[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_TR,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_TR,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_TR },
            { "OpenGL", OPTION_VAL_OPENGL_TR },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_TR,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_TR,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_TR },
            { "2", OPTION_VAL_2_TR },
            { "3", OPTION_VAL_3_TR },
            { "4", OPTION_VAL_4_TR },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_TR,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_TR,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_TR },
            { "Nearest", OPTION_VAL_NEAREST_TR },
            { "Bicubic", OPTION_VAL_BICUBIC_TR },
            { "FXAA", OPTION_VAL_FXAA_TR },
            { "FSR", OPTION_VAL_FSR_TR },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_TR,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_TR,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_TR },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_TR },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_TR },
            { "8", OPTION_VAL_8_TR },
            { "16", OPTION_VAL_16_TR },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_TR,
        NULL,
        VITA3K_V_SYNC_INFO_0_TR,
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
        VITA3K_ASYNC_PIPELINE_LABEL_TR,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_TR,
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
        VITA3K_MEMORY_MAPPING_LABEL_TR,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_TR,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_TR },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_TR },
            { "page-table", OPTION_VAL_PAGE_TABLE_TR },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_TR },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_TR,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_TR,
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
        VITA3K_CPU_OPT_LABEL_TR,
        NULL,
        VITA3K_CPU_OPT_INFO_0_TR,
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
        VITA3K_PKG_MODE_LABEL_TR,
        NULL,
        VITA3K_PKG_MODE_INFO_0_TR,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_TR },
            { "install", OPTION_VAL_INSTALL_TR },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_TR,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_TR,
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
        VITA3K_MODULES_MODE_LABEL_TR,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_TR,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_TR },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_TR },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_TR },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_TR,
        NULL,
        VITA3K_FPS_HACK_INFO_0_TR,
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
        VITA3K_SYS_BUTTON_LABEL_TR,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_TR,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_TR },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_TR },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_TR,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_TR,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_TR },
            { "10", OPTION_VAL_10_TR },
            { "20", OPTION_VAL_20_TR },
            { "30", OPTION_VAL_30_TR },
            { "40", OPTION_VAL_40_TR },
            { "50", OPTION_VAL_50_TR },
            { "60", OPTION_VAL_60_TR },
            { "70", OPTION_VAL_70_TR },
            { "80", OPTION_VAL_80_TR },
            { "90", OPTION_VAL_90_TR },
            { "100", OPTION_VAL_100_TR },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_TR,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_TR,
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
        VITA3K_PSN_SIGNED_IN_LABEL_TR,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_TR,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_TR,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_TR,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_TR },
            { "disabled", OPTION_VAL_DISABLED_TR },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_TR,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_TR,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_TR },
            { "5", OPTION_VAL_5_TR },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_TR },
            { "15", OPTION_VAL_15_TR },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_TR },
            { "25", OPTION_VAL_25_TR },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_TR },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_tr = {
   option_cats_tr,
   option_defs_tr
};

/* RETRO_LANGUAGE_UK */

#define CATEGORY_GPU_LABEL_UK NULL
#define CATEGORY_GPU_INFO_0_UK NULL
#define CATEGORY_CPU_LABEL_UK NULL
#define CATEGORY_CPU_INFO_0_UK NULL
#define CATEGORY_SYSTEM_LABEL_UK NULL
#define CATEGORY_SYSTEM_INFO_0_UK NULL
#define CATEGORY_AUDIO_LABEL_UK NULL
#define CATEGORY_AUDIO_INFO_0_UK NULL
#define CATEGORY_NETWORK_LABEL_UK NULL
#define CATEGORY_NETWORK_INFO_0_UK NULL
#define VITA3K_BACKEND_RENDERER_LABEL_UK NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_UK NULL
#define OPTION_VAL_VULKAN_UK NULL
#define OPTION_VAL_OPENGL_UK NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_UK NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_UK NULL
#define OPTION_VAL_1_UK NULL
#define OPTION_VAL_2_UK NULL
#define OPTION_VAL_3_UK NULL
#define OPTION_VAL_4_UK NULL
#define VITA3K_SCREEN_FILTER_LABEL_UK NULL
#define VITA3K_SCREEN_FILTER_INFO_0_UK NULL
#define OPTION_VAL_BILINEAR_UK NULL
#define OPTION_VAL_NEAREST_UK NULL
#define OPTION_VAL_BICUBIC_UK NULL
#define OPTION_VAL_FXAA_UK NULL
#define OPTION_VAL_FSR_UK NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_UK NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_UK NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_UK NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_UK NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_UK NULL
#define OPTION_VAL_8_UK NULL
#define OPTION_VAL_16_UK NULL
#define VITA3K_V_SYNC_LABEL_UK NULL
#define VITA3K_V_SYNC_INFO_0_UK NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_UK NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_UK NULL
#define VITA3K_MEMORY_MAPPING_LABEL_UK NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_UK NULL
#define OPTION_VAL_DOUBLE_BUFFER_UK NULL
#define OPTION_VAL_EXTERNAL_HOST_UK NULL
#define OPTION_VAL_PAGE_TABLE_UK NULL
#define OPTION_VAL_NATIVE_BUFFER_UK NULL
#define VITA3K_HIGH_ACCURACY_LABEL_UK NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_UK NULL
#define VITA3K_CPU_OPT_LABEL_UK NULL
#define VITA3K_CPU_OPT_INFO_0_UK NULL
#define VITA3K_PKG_MODE_LABEL_UK NULL
#define VITA3K_PKG_MODE_INFO_0_UK NULL
#define OPTION_VAL_RUN_UK NULL
#define OPTION_VAL_INSTALL_UK NULL
#define VITA3K_PSTV_MODE_LABEL_UK NULL
#define VITA3K_PSTV_MODE_INFO_0_UK NULL
#define VITA3K_MODULES_MODE_LABEL_UK NULL
#define VITA3K_MODULES_MODE_INFO_0_UK NULL
#define OPTION_VAL_0_UK NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_UK NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_UK NULL
#define VITA3K_FPS_HACK_LABEL_UK NULL
#define VITA3K_FPS_HACK_INFO_0_UK NULL
#define VITA3K_SYS_BUTTON_LABEL_UK NULL
#define VITA3K_SYS_BUTTON_INFO_0_UK NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_UK NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_UK NULL
#define VITA3K_AUDIO_VOLUME_LABEL_UK NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_UK NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_UK NULL
#define OPTION_VAL_10_UK NULL
#define OPTION_VAL_20_UK NULL
#define OPTION_VAL_30_UK NULL
#define OPTION_VAL_40_UK NULL
#define OPTION_VAL_50_UK NULL
#define OPTION_VAL_60_UK NULL
#define OPTION_VAL_70_UK NULL
#define OPTION_VAL_80_UK NULL
#define OPTION_VAL_90_UK NULL
#define OPTION_VAL_100_UK NULL
#define VITA3K_NGS_ENABLE_LABEL_UK NULL
#define VITA3K_NGS_ENABLE_INFO_0_UK NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_UK NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_UK NULL
#define VITA3K_SURFACE_SYNC_LABEL_UK NULL
#define VITA3K_SURFACE_SYNC_INFO_0_UK NULL
#define OPTION_VAL_ENABLED_UK NULL
#define OPTION_VAL_DISABLED_UK NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_UK NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_UK NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_UK NULL
#define OPTION_VAL_5_UK NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_UK NULL
#define OPTION_VAL_15_UK NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_UK NULL
#define OPTION_VAL_25_UK NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_UK NULL

struct retro_core_option_v2_category option_cats_uk[] = {
    { "gpu", CATEGORY_GPU_LABEL_UK, CATEGORY_GPU_INFO_0_UK },
    { "cpu", CATEGORY_CPU_LABEL_UK, CATEGORY_CPU_INFO_0_UK },
    { "system", CATEGORY_SYSTEM_LABEL_UK, CATEGORY_SYSTEM_INFO_0_UK },
    { "audio", CATEGORY_AUDIO_LABEL_UK, CATEGORY_AUDIO_INFO_0_UK },
    { "network", CATEGORY_NETWORK_LABEL_UK, CATEGORY_NETWORK_INFO_0_UK },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_uk[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_UK,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_UK,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_UK },
            { "OpenGL", OPTION_VAL_OPENGL_UK },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_UK,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_UK,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_UK },
            { "2", OPTION_VAL_2_UK },
            { "3", OPTION_VAL_3_UK },
            { "4", OPTION_VAL_4_UK },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_UK,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_UK,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_UK },
            { "Nearest", OPTION_VAL_NEAREST_UK },
            { "Bicubic", OPTION_VAL_BICUBIC_UK },
            { "FXAA", OPTION_VAL_FXAA_UK },
            { "FSR", OPTION_VAL_FSR_UK },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_UK,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_UK,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_UK },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_UK },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_UK },
            { "8", OPTION_VAL_8_UK },
            { "16", OPTION_VAL_16_UK },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_UK,
        NULL,
        VITA3K_V_SYNC_INFO_0_UK,
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
        VITA3K_ASYNC_PIPELINE_LABEL_UK,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_UK,
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
        VITA3K_MEMORY_MAPPING_LABEL_UK,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_UK,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_UK },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_UK },
            { "page-table", OPTION_VAL_PAGE_TABLE_UK },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_UK },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_UK,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_UK,
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
        VITA3K_CPU_OPT_LABEL_UK,
        NULL,
        VITA3K_CPU_OPT_INFO_0_UK,
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
        VITA3K_PKG_MODE_LABEL_UK,
        NULL,
        VITA3K_PKG_MODE_INFO_0_UK,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_UK },
            { "install", OPTION_VAL_INSTALL_UK },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_UK,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_UK,
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
        VITA3K_MODULES_MODE_LABEL_UK,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_UK,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_UK },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_UK },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_UK },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_UK,
        NULL,
        VITA3K_FPS_HACK_INFO_0_UK,
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
        VITA3K_SYS_BUTTON_LABEL_UK,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_UK,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_UK },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_UK },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_UK,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_UK,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_UK },
            { "10", OPTION_VAL_10_UK },
            { "20", OPTION_VAL_20_UK },
            { "30", OPTION_VAL_30_UK },
            { "40", OPTION_VAL_40_UK },
            { "50", OPTION_VAL_50_UK },
            { "60", OPTION_VAL_60_UK },
            { "70", OPTION_VAL_70_UK },
            { "80", OPTION_VAL_80_UK },
            { "90", OPTION_VAL_90_UK },
            { "100", OPTION_VAL_100_UK },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_UK,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_UK,
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
        VITA3K_PSN_SIGNED_IN_LABEL_UK,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_UK,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_UK,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_UK,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_UK },
            { "disabled", OPTION_VAL_DISABLED_UK },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_UK,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_UK,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_UK },
            { "5", OPTION_VAL_5_UK },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_UK },
            { "15", OPTION_VAL_15_UK },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_UK },
            { "25", OPTION_VAL_25_UK },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_UK },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_uk = {
   option_cats_uk,
   option_defs_uk
};

/* RETRO_LANGUAGE_VAL */

#define CATEGORY_GPU_LABEL_VAL NULL
#define CATEGORY_GPU_INFO_0_VAL NULL
#define CATEGORY_CPU_LABEL_VAL NULL
#define CATEGORY_CPU_INFO_0_VAL NULL
#define CATEGORY_SYSTEM_LABEL_VAL NULL
#define CATEGORY_SYSTEM_INFO_0_VAL NULL
#define CATEGORY_AUDIO_LABEL_VAL NULL
#define CATEGORY_AUDIO_INFO_0_VAL NULL
#define CATEGORY_NETWORK_LABEL_VAL NULL
#define CATEGORY_NETWORK_INFO_0_VAL NULL
#define VITA3K_BACKEND_RENDERER_LABEL_VAL NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_VAL NULL
#define OPTION_VAL_VULKAN_VAL NULL
#define OPTION_VAL_OPENGL_VAL NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_VAL NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_VAL NULL
#define OPTION_VAL_1_VAL NULL
#define OPTION_VAL_2_VAL NULL
#define OPTION_VAL_3_VAL NULL
#define OPTION_VAL_4_VAL NULL
#define VITA3K_SCREEN_FILTER_LABEL_VAL NULL
#define VITA3K_SCREEN_FILTER_INFO_0_VAL NULL
#define OPTION_VAL_BILINEAR_VAL NULL
#define OPTION_VAL_NEAREST_VAL NULL
#define OPTION_VAL_BICUBIC_VAL NULL
#define OPTION_VAL_FXAA_VAL NULL
#define OPTION_VAL_FSR_VAL NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_VAL NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_VAL NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_VAL NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_VAL NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_VAL NULL
#define OPTION_VAL_8_VAL NULL
#define OPTION_VAL_16_VAL NULL
#define VITA3K_V_SYNC_LABEL_VAL NULL
#define VITA3K_V_SYNC_INFO_0_VAL NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_VAL NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_VAL NULL
#define VITA3K_MEMORY_MAPPING_LABEL_VAL NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_VAL NULL
#define OPTION_VAL_DOUBLE_BUFFER_VAL NULL
#define OPTION_VAL_EXTERNAL_HOST_VAL NULL
#define OPTION_VAL_PAGE_TABLE_VAL NULL
#define OPTION_VAL_NATIVE_BUFFER_VAL NULL
#define VITA3K_HIGH_ACCURACY_LABEL_VAL NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_VAL NULL
#define VITA3K_CPU_OPT_LABEL_VAL NULL
#define VITA3K_CPU_OPT_INFO_0_VAL NULL
#define VITA3K_PKG_MODE_LABEL_VAL NULL
#define VITA3K_PKG_MODE_INFO_0_VAL NULL
#define OPTION_VAL_RUN_VAL NULL
#define OPTION_VAL_INSTALL_VAL NULL
#define VITA3K_PSTV_MODE_LABEL_VAL NULL
#define VITA3K_PSTV_MODE_INFO_0_VAL NULL
#define VITA3K_MODULES_MODE_LABEL_VAL NULL
#define VITA3K_MODULES_MODE_INFO_0_VAL NULL
#define OPTION_VAL_0_VAL NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_VAL NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_VAL NULL
#define VITA3K_FPS_HACK_LABEL_VAL NULL
#define VITA3K_FPS_HACK_INFO_0_VAL NULL
#define VITA3K_SYS_BUTTON_LABEL_VAL NULL
#define VITA3K_SYS_BUTTON_INFO_0_VAL NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_VAL NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_VAL NULL
#define VITA3K_AUDIO_VOLUME_LABEL_VAL NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_VAL NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_VAL NULL
#define OPTION_VAL_10_VAL NULL
#define OPTION_VAL_20_VAL NULL
#define OPTION_VAL_30_VAL NULL
#define OPTION_VAL_40_VAL NULL
#define OPTION_VAL_50_VAL NULL
#define OPTION_VAL_60_VAL NULL
#define OPTION_VAL_70_VAL NULL
#define OPTION_VAL_80_VAL NULL
#define OPTION_VAL_90_VAL NULL
#define OPTION_VAL_100_VAL NULL
#define VITA3K_NGS_ENABLE_LABEL_VAL NULL
#define VITA3K_NGS_ENABLE_INFO_0_VAL NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_VAL NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_VAL NULL
#define VITA3K_SURFACE_SYNC_LABEL_VAL NULL
#define VITA3K_SURFACE_SYNC_INFO_0_VAL NULL
#define OPTION_VAL_ENABLED_VAL NULL
#define OPTION_VAL_DISABLED_VAL NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_VAL NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_VAL NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_VAL NULL
#define OPTION_VAL_5_VAL NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_VAL NULL
#define OPTION_VAL_15_VAL NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_VAL NULL
#define OPTION_VAL_25_VAL NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_VAL NULL

struct retro_core_option_v2_category option_cats_val[] = {
    { "gpu", CATEGORY_GPU_LABEL_VAL, CATEGORY_GPU_INFO_0_VAL },
    { "cpu", CATEGORY_CPU_LABEL_VAL, CATEGORY_CPU_INFO_0_VAL },
    { "system", CATEGORY_SYSTEM_LABEL_VAL, CATEGORY_SYSTEM_INFO_0_VAL },
    { "audio", CATEGORY_AUDIO_LABEL_VAL, CATEGORY_AUDIO_INFO_0_VAL },
    { "network", CATEGORY_NETWORK_LABEL_VAL, CATEGORY_NETWORK_INFO_0_VAL },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_val[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_VAL,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_VAL,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_VAL },
            { "OpenGL", OPTION_VAL_OPENGL_VAL },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_VAL,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_VAL,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VAL },
            { "2", OPTION_VAL_2_VAL },
            { "3", OPTION_VAL_3_VAL },
            { "4", OPTION_VAL_4_VAL },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_VAL,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_VAL,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_VAL },
            { "Nearest", OPTION_VAL_NEAREST_VAL },
            { "Bicubic", OPTION_VAL_BICUBIC_VAL },
            { "FXAA", OPTION_VAL_FXAA_VAL },
            { "FSR", OPTION_VAL_FSR_VAL },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_VAL,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_VAL,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_VAL },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_VAL },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_VAL },
            { "8", OPTION_VAL_8_VAL },
            { "16", OPTION_VAL_16_VAL },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_VAL,
        NULL,
        VITA3K_V_SYNC_INFO_0_VAL,
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
        VITA3K_ASYNC_PIPELINE_LABEL_VAL,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_VAL,
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
        VITA3K_MEMORY_MAPPING_LABEL_VAL,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_VAL,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_VAL },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_VAL },
            { "page-table", OPTION_VAL_PAGE_TABLE_VAL },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_VAL },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_VAL,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_VAL,
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
        VITA3K_CPU_OPT_LABEL_VAL,
        NULL,
        VITA3K_CPU_OPT_INFO_0_VAL,
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
        VITA3K_PKG_MODE_LABEL_VAL,
        NULL,
        VITA3K_PKG_MODE_INFO_0_VAL,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_VAL },
            { "install", OPTION_VAL_INSTALL_VAL },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_VAL,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_VAL,
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
        VITA3K_MODULES_MODE_LABEL_VAL,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_VAL,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VAL },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_VAL },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_VAL },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_VAL,
        NULL,
        VITA3K_FPS_HACK_INFO_0_VAL,
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
        VITA3K_SYS_BUTTON_LABEL_VAL,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_VAL,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_VAL },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_VAL },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_VAL,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_VAL,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_VAL },
            { "10", OPTION_VAL_10_VAL },
            { "20", OPTION_VAL_20_VAL },
            { "30", OPTION_VAL_30_VAL },
            { "40", OPTION_VAL_40_VAL },
            { "50", OPTION_VAL_50_VAL },
            { "60", OPTION_VAL_60_VAL },
            { "70", OPTION_VAL_70_VAL },
            { "80", OPTION_VAL_80_VAL },
            { "90", OPTION_VAL_90_VAL },
            { "100", OPTION_VAL_100_VAL },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_VAL,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_VAL,
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
        VITA3K_PSN_SIGNED_IN_LABEL_VAL,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_VAL,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_VAL,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_VAL,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_VAL },
            { "disabled", OPTION_VAL_DISABLED_VAL },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_VAL,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_VAL,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_VAL },
            { "5", OPTION_VAL_5_VAL },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_VAL },
            { "15", OPTION_VAL_15_VAL },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_VAL },
            { "25", OPTION_VAL_25_VAL },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_VAL },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_val = {
   option_cats_val,
   option_defs_val
};

/* RETRO_LANGUAGE_VN */

#define CATEGORY_GPU_LABEL_VN NULL
#define CATEGORY_GPU_INFO_0_VN NULL
#define CATEGORY_CPU_LABEL_VN NULL
#define CATEGORY_CPU_INFO_0_VN NULL
#define CATEGORY_SYSTEM_LABEL_VN NULL
#define CATEGORY_SYSTEM_INFO_0_VN NULL
#define CATEGORY_AUDIO_LABEL_VN NULL
#define CATEGORY_AUDIO_INFO_0_VN NULL
#define CATEGORY_NETWORK_LABEL_VN NULL
#define CATEGORY_NETWORK_INFO_0_VN NULL
#define VITA3K_BACKEND_RENDERER_LABEL_VN NULL
#define VITA3K_BACKEND_RENDERER_INFO_0_VN NULL
#define OPTION_VAL_VULKAN_VN NULL
#define OPTION_VAL_OPENGL_VN NULL
#define VITA3K_RESOLUTION_MULTIPLIER_LABEL_VN NULL
#define VITA3K_RESOLUTION_MULTIPLIER_INFO_0_VN NULL
#define OPTION_VAL_1_VN NULL
#define OPTION_VAL_2_VN NULL
#define OPTION_VAL_3_VN NULL
#define OPTION_VAL_4_VN NULL
#define VITA3K_SCREEN_FILTER_LABEL_VN NULL
#define VITA3K_SCREEN_FILTER_INFO_0_VN NULL
#define OPTION_VAL_BILINEAR_VN NULL
#define OPTION_VAL_NEAREST_VN NULL
#define OPTION_VAL_BICUBIC_VN NULL
#define OPTION_VAL_FXAA_VN NULL
#define OPTION_VAL_FSR_VN NULL
#define VITA3K_ANISOTROPIC_FILTERING_LABEL_VN NULL
#define VITA3K_ANISOTROPIC_FILTERING_INFO_0_VN NULL
#define OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_VN NULL
#define OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_VN NULL
#define OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_VN NULL
#define OPTION_VAL_8_VN NULL
#define OPTION_VAL_16_VN NULL
#define VITA3K_V_SYNC_LABEL_VN NULL
#define VITA3K_V_SYNC_INFO_0_VN NULL
#define VITA3K_ASYNC_PIPELINE_LABEL_VN NULL
#define VITA3K_ASYNC_PIPELINE_INFO_0_VN NULL
#define VITA3K_MEMORY_MAPPING_LABEL_VN NULL
#define VITA3K_MEMORY_MAPPING_INFO_0_VN NULL
#define OPTION_VAL_DOUBLE_BUFFER_VN NULL
#define OPTION_VAL_EXTERNAL_HOST_VN NULL
#define OPTION_VAL_PAGE_TABLE_VN NULL
#define OPTION_VAL_NATIVE_BUFFER_VN NULL
#define VITA3K_HIGH_ACCURACY_LABEL_VN NULL
#define VITA3K_HIGH_ACCURACY_INFO_0_VN NULL
#define VITA3K_CPU_OPT_LABEL_VN NULL
#define VITA3K_CPU_OPT_INFO_0_VN NULL
#define VITA3K_PKG_MODE_LABEL_VN NULL
#define VITA3K_PKG_MODE_INFO_0_VN NULL
#define OPTION_VAL_RUN_VN NULL
#define OPTION_VAL_INSTALL_VN NULL
#define VITA3K_PSTV_MODE_LABEL_VN NULL
#define VITA3K_PSTV_MODE_INFO_0_VN NULL
#define VITA3K_MODULES_MODE_LABEL_VN NULL
#define VITA3K_MODULES_MODE_INFO_0_VN NULL
#define OPTION_VAL_0_VN NULL
#define OPTION_VAL_1_VITA3K_MODULES_MODE_VN NULL
#define OPTION_VAL_2_VITA3K_MODULES_MODE_VN NULL
#define VITA3K_FPS_HACK_LABEL_VN NULL
#define VITA3K_FPS_HACK_INFO_0_VN NULL
#define VITA3K_SYS_BUTTON_LABEL_VN NULL
#define VITA3K_SYS_BUTTON_INFO_0_VN NULL
#define OPTION_VAL_0_VITA3K_SYS_BUTTON_VN NULL
#define OPTION_VAL_1_VITA3K_SYS_BUTTON_VN NULL
#define VITA3K_AUDIO_VOLUME_LABEL_VN NULL
#define VITA3K_AUDIO_VOLUME_INFO_0_VN NULL
#define OPTION_VAL_0_VITA3K_AUDIO_VOLUME_VN NULL
#define OPTION_VAL_10_VN NULL
#define OPTION_VAL_20_VN NULL
#define OPTION_VAL_30_VN NULL
#define OPTION_VAL_40_VN NULL
#define OPTION_VAL_50_VN NULL
#define OPTION_VAL_60_VN NULL
#define OPTION_VAL_70_VN NULL
#define OPTION_VAL_80_VN NULL
#define OPTION_VAL_90_VN NULL
#define OPTION_VAL_100_VN NULL
#define VITA3K_NGS_ENABLE_LABEL_VN NULL
#define VITA3K_NGS_ENABLE_INFO_0_VN NULL
#define VITA3K_PSN_SIGNED_IN_LABEL_VN NULL
#define VITA3K_PSN_SIGNED_IN_INFO_0_VN NULL
#define VITA3K_SURFACE_SYNC_LABEL_VN NULL
#define VITA3K_SURFACE_SYNC_INFO_0_VN NULL
#define OPTION_VAL_ENABLED_VN NULL
#define OPTION_VAL_DISABLED_VN NULL
#define VITA3K_FILE_LOADING_DELAY_LABEL_VN NULL
#define VITA3K_FILE_LOADING_DELAY_INFO_0_VN NULL
#define OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_VN NULL
#define OPTION_VAL_5_VN NULL
#define OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_VN NULL
#define OPTION_VAL_15_VN NULL
#define OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_VN NULL
#define OPTION_VAL_25_VN NULL
#define OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_VN NULL

struct retro_core_option_v2_category option_cats_vn[] = {
    { "gpu", CATEGORY_GPU_LABEL_VN, CATEGORY_GPU_INFO_0_VN },
    { "cpu", CATEGORY_CPU_LABEL_VN, CATEGORY_CPU_INFO_0_VN },
    { "system", CATEGORY_SYSTEM_LABEL_VN, CATEGORY_SYSTEM_INFO_0_VN },
    { "audio", CATEGORY_AUDIO_LABEL_VN, CATEGORY_AUDIO_INFO_0_VN },
    { "network", CATEGORY_NETWORK_LABEL_VN, CATEGORY_NETWORK_INFO_0_VN },
    { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_vn[] = {
    // ── GPU ──────────────────────────────────────────────────────────────
    {
        "vita3k_backend_renderer",
        VITA3K_BACKEND_RENDERER_LABEL_VN,
        NULL,
        VITA3K_BACKEND_RENDERER_INFO_0_VN,
        NULL,
        "gpu",
        {
            { "Vulkan", OPTION_VAL_VULKAN_VN },
            { "OpenGL", OPTION_VAL_OPENGL_VN },
            { NULL, NULL },
        },
        "Vulkan"
    },
    {
        "vita3k_resolution_multiplier",
        VITA3K_RESOLUTION_MULTIPLIER_LABEL_VN,
        NULL,
        VITA3K_RESOLUTION_MULTIPLIER_INFO_0_VN,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VN },
            { "2", OPTION_VAL_2_VN },
            { "3", OPTION_VAL_3_VN },
            { "4", OPTION_VAL_4_VN },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_screen_filter",
        VITA3K_SCREEN_FILTER_LABEL_VN,
        NULL,
        VITA3K_SCREEN_FILTER_INFO_0_VN,
        NULL,
        "gpu",
        {
            { "Bilinear", OPTION_VAL_BILINEAR_VN },
            { "Nearest", OPTION_VAL_NEAREST_VN },
            { "Bicubic", OPTION_VAL_BICUBIC_VN },
            { "FXAA", OPTION_VAL_FXAA_VN },
            { "FSR", OPTION_VAL_FSR_VN },
            { NULL, NULL },
        },
        "Bilinear"
    },
    {
        "vita3k_anisotropic_filtering",
        VITA3K_ANISOTROPIC_FILTERING_LABEL_VN,
        NULL,
        VITA3K_ANISOTROPIC_FILTERING_INFO_0_VN,
        NULL,
        "gpu",
        {
            { "1", OPTION_VAL_1_VITA3K_ANISOTROPIC_FILTERING_VN },
            { "2", OPTION_VAL_2_VITA3K_ANISOTROPIC_FILTERING_VN },
            { "4", OPTION_VAL_4_VITA3K_ANISOTROPIC_FILTERING_VN },
            { "8", OPTION_VAL_8_VN },
            { "16", OPTION_VAL_16_VN },
            { NULL, NULL },
        },
        "1"
    },
    {
        "vita3k_v_sync",
        VITA3K_V_SYNC_LABEL_VN,
        NULL,
        VITA3K_V_SYNC_INFO_0_VN,
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
        VITA3K_ASYNC_PIPELINE_LABEL_VN,
        NULL,
        VITA3K_ASYNC_PIPELINE_INFO_0_VN,
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
        VITA3K_MEMORY_MAPPING_LABEL_VN,
        NULL,
        VITA3K_MEMORY_MAPPING_INFO_0_VN,
        NULL,
        "gpu",
        {
            { "disabled", NULL },
            { "double-buffer", OPTION_VAL_DOUBLE_BUFFER_VN },
            { "external-host", OPTION_VAL_EXTERNAL_HOST_VN },
            { "page-table", OPTION_VAL_PAGE_TABLE_VN },
            { "native-buffer", OPTION_VAL_NATIVE_BUFFER_VN },
            { NULL, NULL },
        },
        "double-buffer"
    },
    {
        "vita3k_high_accuracy",
        VITA3K_HIGH_ACCURACY_LABEL_VN,
        NULL,
        VITA3K_HIGH_ACCURACY_INFO_0_VN,
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
        VITA3K_CPU_OPT_LABEL_VN,
        NULL,
        VITA3K_CPU_OPT_INFO_0_VN,
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
        VITA3K_PKG_MODE_LABEL_VN,
        NULL,
        VITA3K_PKG_MODE_INFO_0_VN,
        NULL,
        "system",
        {
            { "run", OPTION_VAL_RUN_VN },
            { "install", OPTION_VAL_INSTALL_VN },
            { NULL, NULL },
        },
        "run"
    },
    {
        "vita3k_pstv_mode",
        VITA3K_PSTV_MODE_LABEL_VN,
        NULL,
        VITA3K_PSTV_MODE_INFO_0_VN,
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
        VITA3K_MODULES_MODE_LABEL_VN,
        NULL,
        VITA3K_MODULES_MODE_INFO_0_VN,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VN },
            { "1", OPTION_VAL_1_VITA3K_MODULES_MODE_VN },
            { "2", OPTION_VAL_2_VITA3K_MODULES_MODE_VN },
            { NULL, NULL },
        },
        "0"
    },
    {
        "vita3k_fps_hack",
        VITA3K_FPS_HACK_LABEL_VN,
        NULL,
        VITA3K_FPS_HACK_INFO_0_VN,
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
        VITA3K_SYS_BUTTON_LABEL_VN,
        NULL,
        VITA3K_SYS_BUTTON_INFO_0_VN,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_SYS_BUTTON_VN },
            { "1", OPTION_VAL_1_VITA3K_SYS_BUTTON_VN },
            { NULL, NULL },
        },
        "1"
    },
    // ── Audio ────────────────────────────────────────────────────────────
    {
        "vita3k_audio_volume",
        VITA3K_AUDIO_VOLUME_LABEL_VN,
        NULL,
        VITA3K_AUDIO_VOLUME_INFO_0_VN,
        NULL,
        "audio",
        {
            { "0", OPTION_VAL_0_VITA3K_AUDIO_VOLUME_VN },
            { "10", OPTION_VAL_10_VN },
            { "20", OPTION_VAL_20_VN },
            { "30", OPTION_VAL_30_VN },
            { "40", OPTION_VAL_40_VN },
            { "50", OPTION_VAL_50_VN },
            { "60", OPTION_VAL_60_VN },
            { "70", OPTION_VAL_70_VN },
            { "80", OPTION_VAL_80_VN },
            { "90", OPTION_VAL_90_VN },
            { "100", OPTION_VAL_100_VN },
            { NULL, NULL },
        },
        "100"
    },
    {
        "vita3k_ngs_enable",
        VITA3K_NGS_ENABLE_LABEL_VN,
        NULL,
        VITA3K_NGS_ENABLE_INFO_0_VN,
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
        VITA3K_PSN_SIGNED_IN_LABEL_VN,
        NULL,
        VITA3K_PSN_SIGNED_IN_INFO_0_VN,
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
        "vita3k_surface_sync",
        VITA3K_SURFACE_SYNC_LABEL_VN,
        NULL,
        VITA3K_SURFACE_SYNC_INFO_0_VN,
        NULL,
        "gpu",
        {
            { "enabled", OPTION_VAL_ENABLED_VN },
            { "disabled", OPTION_VAL_DISABLED_VN },
            { NULL, NULL },
        },
        "enabled"
    },
    {
        "vita3k_file_loading_delay",
        VITA3K_FILE_LOADING_DELAY_LABEL_VN,
        NULL,
        VITA3K_FILE_LOADING_DELAY_INFO_0_VN,
        NULL,
        "system",
        {
            { "0", OPTION_VAL_0_VITA3K_FILE_LOADING_DELAY_VN },
            { "5", OPTION_VAL_5_VN },
            { "10", OPTION_VAL_10_VITA3K_FILE_LOADING_DELAY_VN },
            { "15", OPTION_VAL_15_VN },
            { "20", OPTION_VAL_20_VITA3K_FILE_LOADING_DELAY_VN },
            { "25", OPTION_VAL_25_VN },
            { "30", OPTION_VAL_30_VITA3K_FILE_LOADING_DELAY_VN },
            { NULL, NULL },
        },
        "0"
    },
    { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_vn = {
   option_cats_vn,
   option_defs_vn
};


#ifdef __cplusplus
}
#endif

#endif