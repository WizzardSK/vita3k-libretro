// Vita3K libretro core: the load progress drawn with Vita3K's overlays
#pragma once

#include <overlay/controls.h>
#include <overlay/overlay.h>

#include <array>
#include <chrono>
#include <memory>
#include <string>

namespace overlay {

// What the core is doing while the content is prepared (firmware and content
// installs, Run Mode work), in a card over black as the shader precompile
// progress has it: the step, with an indeterminate bar under it (sco8487 chose
// the bar over a spinner, and no percent: the steps are of very unequal
// lengths).
struct libretro_load_progress : public overlay {
    libretro_load_progress();

    void set_step(const std::string &text);

    compiled_resource get_compiled() override;

private:
    void layout(float phase);

    rounded_rect m_background;
    rounded_rect m_card;
    label m_title;
    rounded_rect m_bar_track;
    rounded_rect m_bar_fill;
    std::chrono::steady_clock::time_point m_start = std::chrono::steady_clock::now();

    static constexpr uint16_t k_card_h = 76;
    static constexpr uint16_t k_card_radius = 8;
    static constexpr uint16_t k_margin = 16;
    static constexpr uint16_t k_font = 18;
    static constexpr uint16_t k_bar_h = 4;
};

} // namespace overlay
