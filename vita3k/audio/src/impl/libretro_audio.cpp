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

#include "audio/impl/libretro_audio.h"

#include "kernel/thread/thread_state.h"

#include "util/log.h"

#include <algorithm>
#include <cmath>
#include <cstring>

// Enough for a couple of frontend frames of a port's buffers
static constexpr int NUM_AUDIO_BUFFERS = 16;

LibretroAudioAdapter::LibretroAudioAdapter(AudioState &audio_state)
    : AudioAdapter(audio_state) {}

bool LibretroAudioAdapter::init() {
    LOG_INFO("LibretroAudioAdapter initialized");
    return true;
}

AudioOutPortPtr LibretroAudioAdapter::open_port(int nb_channels, int freq, int nb_sample) {
    auto port = std::make_shared<LibretroAudioOutPort>();
    port->channels = nb_channels;
    port->freq = freq;
    port->len = nb_sample;
    port->len_bytes = nb_sample * nb_channels * sizeof(int16_t);
    port->len_microseconds = (static_cast<uint64_t>(nb_sample) * 1'000'000ULL) / freq;

    port->audio_buffers.resize(NUM_AUDIO_BUFFERS);
    for (auto &buf : port->audio_buffers) {
        buf.resize(port->len_bytes, 0);
    }

    LOG_INFO("LibretroAudioAdapter: opened port ch={} freq={} samples={} buf_size={}",
        nb_channels, freq, nb_sample, port->len_bytes);
    return port;
}

void LibretroAudioAdapter::audio_output(AudioOutPort &out_port, const void *buffer) {
    auto &port = static_cast<LibretroAudioOutPort &>(out_port);

    std::unique_lock<std::mutex> lock(port.mutex);
    // A full ring waits for retro_run to drain it, as SDL's audio callback
    // holds the guest in standalone: the game's audio thread runs at the
    // rate its audio is played. Giving up after a while dropped the audio
    // and let the game run ahead of it - played faster (sco). Only a stop
    // (stop_all_ports, at close) lets it go without room.
    port.cond_var.wait(lock, [&]() {
        return port.nb_buffers_ready < static_cast<int>(port.audio_buffers.size()) || port.stopping.load();
    });
    if (port.nb_buffers_ready >= static_cast<int>(port.audio_buffers.size()))
        return;

    if (buffer) {
        memcpy(port.audio_buffers[port.next_write_buffer].data(), buffer, port.len_bytes);
        port.next_write_buffer = (port.next_write_buffer + 1) % port.audio_buffers.size();
        port.nb_buffers_ready++;
    }
}

void LibretroAudioAdapter::set_volume(AudioOutPort &out_port, float volume) {
    // Volume is applied during drain
}

void LibretroAudioAdapter::switch_state(const bool pause) {
    // No-op for libretro — frontend controls pause
}

void LibretroAudioAdapter::wake_all_ports() {
    const std::lock_guard<std::mutex> lock(state.mutex);
    for (auto &[_, out_port] : state.out_ports) {
        auto &port = static_cast<LibretroAudioOutPort &>(*out_port);
        // stop_all_ports has set the port's stopping flag
        { const std::lock_guard<std::mutex> port_lock(port.mutex); }
        port.cond_var.notify_all();
    }
}

int LibretroAudioAdapter::get_rest_sample(AudioOutPort &out_port) {
    auto &port = static_cast<LibretroAudioOutPort &>(out_port);
    return port.nb_buffers_ready * port.len;
}

// The rate the core reports to the frontend
static constexpr int LIBRETRO_AUDIO_RATE = 48000;

// The ports play at the same time - a game's music on one, its voices and
// sounds on others - so they are mixed: added up sample by sample, each from
// the start of this drain. Each is first taken to 48 kHz, linearly, keeping
// its position from one drain to the next.
int libretro_audio_drain(AudioState &audio, std::vector<int16_t> &out_buffer) {
    out_buffer.clear();

    static std::vector<float> mix; // stereo
    static std::vector<float> input; // one port's stereo at its own rate
    mix.clear();

    const std::lock_guard<std::mutex> lock(audio.mutex);

    for (auto it = audio.out_ports.begin(); it != audio.out_ports.end(); ++it) {
        LibretroAudioOutPort *port = static_cast<LibretroAudioOutPort *>(it->second.get());
        if (!port)
            continue;

        input.clear();
        std::unique_lock<std::mutex> plock(port->mutex);
        const float vol = port->volume * audio.global_volume;
        const float vol_l = vol * static_cast<float>(port->left_channel_volume) / static_cast<float>(SCE_AUDIO_OUT_MAX_VOL);
        const float vol_r = vol * static_cast<float>(port->right_channel_volume) / static_cast<float>(SCE_AUDIO_OUT_MAX_VOL);
        while (port->nb_buffers_ready > 0) {
            const std::vector<uint8_t> &buf = port->audio_buffers[port->next_read_buffer];
            const int num_samples = port->len_bytes / static_cast<int>(sizeof(int16_t));
            const int16_t *samples = reinterpret_cast<const int16_t *>(buf.data());

            if (port->channels == 2) {
                for (int i = 0; i + 1 < num_samples; i += 2) {
                    input.push_back(samples[i] * vol_l);
                    input.push_back(samples[i + 1] * vol_r);
                }
            } else {
                // Mono, to both sides
                for (int i = 0; i < num_samples; i++) {
                    input.push_back(samples[i] * vol_l);
                    input.push_back(samples[i] * vol_r);
                }
            }

            port->next_read_buffer = (port->next_read_buffer + 1) % port->audio_buffers.size();
            port->nb_buffers_ready--;
        }
        plock.unlock();
        port->cond_var.notify_all();

        const size_t in_frames = input.size() / 2;
        if (!in_frames)
            continue;

        size_t out_frame = 0;
        const auto add = [&](float l, float r) {
            if (mix.size() < (out_frame + 1) * 2)
                mix.resize((out_frame + 1) * 2, 0.0f);
            mix[out_frame * 2] += l;
            mix[out_frame * 2 + 1] += r;
            out_frame++;
        };

        if (port->freq == LIBRETRO_AUDIO_RATE || port->freq <= 0) {
            for (size_t f = 0; f < in_frames; f++)
                add(input[f * 2], input[f * 2 + 1]);
        } else {
            // Positions are in input frames, with frame -1 the previous
            // drain's last one: an output sample between frames i-1 and i
            const double step = static_cast<double>(port->freq) / LIBRETRO_AUDIO_RATE;
            double pos = port->resample_pos;
            while (pos < static_cast<double>(in_frames)) {
                const double base = std::floor(pos);
                const double frac = pos - base;
                const long i = static_cast<long>(base); // between frame i-1 and i
                if (i >= static_cast<long>(in_frames))
                    break;
                const float a_l = i == 0 ? port->resample_prev[0] : input[(i - 1) * 2];
                const float a_r = i == 0 ? port->resample_prev[1] : input[(i - 1) * 2 + 1];
                const float b_l = input[i * 2];
                const float b_r = input[i * 2 + 1];
                add(a_l + static_cast<float>(frac) * (b_l - a_l), a_r + static_cast<float>(frac) * (b_r - a_r));
                pos += step;
            }
            port->resample_pos = pos - static_cast<double>(in_frames);
            port->resample_prev[0] = input[(in_frames - 1) * 2];
            port->resample_prev[1] = input[(in_frames - 1) * 2 + 1];
        }
    }

    out_buffer.resize(mix.size());
    for (size_t i = 0; i < mix.size(); i++)
        out_buffer[i] = static_cast<int16_t>(std::clamp(static_cast<int>(mix[i]), -32768, 32767));

    // Return number of stereo frames
    return static_cast<int>(out_buffer.size() / 2);
}
