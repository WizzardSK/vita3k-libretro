// Vita3K libretro core: the load progress drawn with Vita3K's overlays

#include "libretro_load_overlay.h"

#include <overlay/font.h>
#include <overlay/types.h>

#include <algorithm>
#include <cmath>

namespace overlay {

libretro_load_progress::libretro_load_progress() {
    visible = true;

    m_background.set_pos(0, 0);
    m_background.set_size(virtual_width, virtual_height);
    m_background.back_color = { 0.f, 0.f, 0.f, 1.f };
    m_background.border_radius = 0;

    // as the shader precompile progress' card
    m_card.back_color = { 0.059f, 0.059f, 0.059f, 0.784f };
    m_card.border_radius = k_card_radius;

    m_title.fore_color = { 0.863f, 0.863f, 0.863f, 1.f };
    m_title.back_color = { 0.f, 0.f, 0.f, 0.f };
    // larger and bold: legible on a TV and a phone (sco8487)
    m_title.set_font(default_font_name, k_font, true);
    m_title.align_text(overlay_element::left);

    m_bar_track.back_color = { 0.235f, 0.235f, 0.235f, 1.f };
    m_bar_track.border_radius = 2;
    m_bar_fill.back_color = { 1.f, 1.f, 1.f, 0.863f };
    m_bar_fill.border_radius = 2;
}

void libretro_load_progress::set_step(const std::string &text) {
    m_title.set_text(text);
    m_title.auto_resize();
    refresh();
}

// phase: seconds since the overlay was made, for the animation
void libretro_load_progress::layout(float phase) {
    const uint16_t card_w = virtual_width * 5 / 8;
    const int16_t card_x = static_cast<int16_t>((virtual_width - card_w) / 2);
    const int16_t card_y = static_cast<int16_t>((virtual_height - k_card_h) / 2);
    m_card.set_pos(card_x, card_y);
    m_card.set_size(card_w, k_card_h);

    const int16_t text_x = static_cast<int16_t>(card_x + k_margin);
    const uint16_t text_w = card_w - k_margin * 2;
    const int16_t text_y = static_cast<int16_t>(card_y + 14);
    m_title.set_pos(text_x, text_y);
    m_title.set_size(text_w, 28);

    const int16_t bar_y = static_cast<int16_t>(card_y + 54);
    m_bar_track.set_pos(text_x, bar_y);
    m_bar_track.set_size(text_w, k_bar_h);
    // a quarter of the bar going back and forth, 1.6 s each way
    const uint16_t chunk = text_w / 4;
    float t = std::fmod(phase / 1.6f, 2.f);
    if (t > 1.f)
        t = 2.f - t;
    const float eased = t * t * (3.f - 2.f * t);
    m_bar_fill.set_pos(static_cast<int16_t>(text_x + (text_w - chunk) * eased), bar_y);
    m_bar_fill.set_size(chunk, k_bar_h);
}

compiled_resource libretro_load_progress::get_compiled() {
    compiled_resource result;
    if (!visible)
        return result;

    const float phase = std::chrono::duration<float>(std::chrono::steady_clock::now() - m_start).count();
    layout(phase);

    result.add(m_background.get_compiled());
    result.add(m_card.get_compiled());
    result.add(m_title.get_compiled());
    result.add(m_bar_track.get_compiled());
    result.add(m_bar_fill.get_compiled());
    // drawn again for the next step of the animation
    refresh();
    return result;
}

} // namespace overlay
