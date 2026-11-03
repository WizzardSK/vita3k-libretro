#pragma once

// The core's own texts (the load progress, its messages), translated on
// Crowdin with the core options: each is a category in libretro_core_options.h
// (key msg_...) that no option is in, so RetroArch does not list it (sco8487).
// Texts from the games (titles, trophies) are not among them.

#include <fmt/format.h>

#include <string>

// RetroArch's language, read once on the main thread (retro_load_game)
void lr_text_set_language(unsigned language);
// The text of key in that language, the English one where it has none
const char *lr_text(const char *key);
// The English text of key
const char *lr_text_us(const char *key);

// A text with {} filled in; a translation whose {} do not fit gives the
// English text
template <typename... Args>
std::string lr_textf(const char *key, const Args &...args) {
    try {
        return fmt::format(fmt::runtime(lr_text(key)), args...);
    } catch (const fmt::format_error &) {
        return fmt::format(fmt::runtime(lr_text_us(key)), args...);
    }
}
