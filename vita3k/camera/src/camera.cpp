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

#include "config/state.h"

#include <array>
#include <camera/camera.h>
#include <camera/state.h>
#include <rtc/rtc.h>
#include <stb_image.h>
#include <util/log.h>

#ifdef BUILD_LIBRETRO
// The libretro core's camera: upstream's three sources without SDL. A solid
// colour, an image file (stb_image, as upstream), or the frontend's camera in
// place of upstream's SDL web camera. Each frame is kept as RGB at the size
// the game opened the camera with, and turned into the game's format on read.
#include <util/fs.h>

#include <algorithm>
#include <chrono>
#include <cstring>
#include <mutex>
#include <thread>
#include <vector>

namespace {

struct HostCamera {
    std::mutex mutex;
    std::function<bool()> start;
    std::function<void()> stop;
    std::vector<uint32_t> pixels; // XRGB8888
    unsigned width = 0;
    unsigned height = 0;
    uint64_t serial = 0; // counts the frames handed in
    int users = 0; // cameras started on it
};

HostCamera &host_camera() {
    static HostCamera camera;
    return camera;
}

uint64_t now_us() {
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

// XRGB8888 of src_w x src_h (pitch in pixels) into dst_w x dst_h, nearest
void scale_xrgb(const uint32_t *src, unsigned src_w, unsigned src_h, size_t src_pitch, std::vector<uint32_t> &dst, unsigned dst_w, unsigned dst_h) {
    dst.resize(static_cast<size_t>(dst_w) * dst_h);
    if (!src_w || !src_h)
        return;
    for (unsigned y = 0; y < dst_h; y++) {
        const uint32_t *row = src + static_cast<size_t>(y * src_h / dst_h) * src_pitch;
        for (unsigned x = 0; x < dst_w; x++)
            dst[static_cast<size_t>(y) * dst_w + x] = row[x * src_w / dst_w];
    }
}

} // namespace

void set_host_camera_control(std::function<bool()> start, std::function<void()> stop) {
    HostCamera &host = host_camera();
    const std::lock_guard lock(host.mutex);
    host.start = std::move(start);
    host.stop = std::move(stop);
}

void push_host_camera_frame(const uint32_t *pixels, unsigned width, unsigned height, size_t pitch_bytes) {
    if (!pixels || !width || !height)
        return;
    HostCamera &host = host_camera();
    const std::lock_guard lock(host.mutex);
    const size_t pitch = pitch_bytes / sizeof(uint32_t);
    host.pixels.resize(static_cast<size_t>(width) * height);
    for (unsigned y = 0; y < height; y++)
        memcpy(&host.pixels[static_cast<size_t>(y) * width], pixels + y * pitch, width * sizeof(uint32_t));
    host.width = width;
    host.height = height;
    host.serial++;
}

class Camera::CameraImpl {
public:
    std::mutex frame_mutex;
    std::vector<uint32_t> frame; // XRGB8888 at info.width x info.height, empty without one
    bool host_started = false;
    uint64_t host_serial = 0;
};

Camera::Camera()
    : pImpl(std::make_unique<CameraImpl>()) {}
Camera::~Camera() = default;

static void stop_host_camera(Camera *self) {
    if (!self->pImpl->host_started)
        return;
    self->pImpl->host_started = false;
    HostCamera &host = host_camera();
    const std::lock_guard lock(host.mutex);
    if (--host.users == 0 && host.stop)
        host.stop();
}

static bool init_host_camera(Camera *self) {
    HostCamera &host = host_camera();
    const std::lock_guard lock(host.mutex);
    if (host.users == 0 && (!host.start || !host.start())) {
        LOG_ERROR("The frontend's camera could not be started (none, or not allowed in its settings)");
        return false;
    }
    host.users++;
    self->pImpl->host_started = true;
    self->pImpl->host_serial = host.serial;
    return true;
}

static bool init_image(Camera *self) {
    FILE *f = FOPEN(fs_utils::utf8_to_path(self->image).c_str(), "rb");
    if (!f) {
        LOG_ERROR("Failed to open camera image file: {} Error: {}", self->image, strerror(errno));
        return false;
    }
    int width = 0, height = 0;
    stbi_uc *data = stbi_load_from_file(f, &width, &height, nullptr, STBI_rgb_alpha);
    fclose(f);
    if (!data) {
        LOG_ERROR("Failed to load camera image from {}: {}", self->image, stbi_failure_reason());
        return false;
    }
    std::vector<uint32_t> xrgb(static_cast<size_t>(width) * height);
    for (size_t i = 0; i < xrgb.size(); i++)
        xrgb[i] = (data[i * 4] << 16) | (data[i * 4 + 1] << 8) | data[i * 4 + 2];
    stbi_image_free(data);
    scale_xrgb(xrgb.data(), width, height, width, self->pImpl->frame, self->info.width, self->info.height);
    return true;
}

static void init_solid_color(Camera *self) {
    // the colour as upstream keeps it, ABGR8888: R in the low byte
    const uint32_t c = self->color;
    const uint32_t xrgb = ((c & 0xFF) << 16) | (c & 0xFF00) | ((c >> 16) & 0xFF);
    self->pImpl->frame.assign(static_cast<size_t>(self->info.width) * self->info.height, xrgb);
}

static void refresh_camera_image(Camera *self) {
    const std::lock_guard lock(self->pImpl->frame_mutex);
    stop_host_camera(self);
    self->pImpl->frame.clear();
    if (self->type == CameraType::WebCamera) {
        if (init_host_camera(self))
            return;
        self->type = CameraType::Image;
    }
    if (self->type == CameraType::Image) {
        if (init_image(self))
            return;
        self->type = CameraType::SolidColor;
    }
    init_solid_color(self);
}

int Camera::get_attribute(CameraAttributes attribute) {
    switch (attribute) {
    case CameraAttributes::Saturation: return SCE_CAMERA_SATURATION_10;
    case CameraAttributes::Brightness: return 128; // 0-255
    case CameraAttributes::Contrast: return 128; // random default value  0-255
    case CameraAttributes::Sharpness: return SCE_CAMERA_SHARPNESS_100;
    case CameraAttributes::Reverse: return SCE_CAMERA_REVERSE_OFF;
    case CameraAttributes::Effect: return SCE_CAMERA_EFFECT_NORMAL;
    case CameraAttributes::EV: return 0;
    case CameraAttributes::Zoom: return 10; // 10-40
    case CameraAttributes::AntiFlicker: return SCE_CAMERA_ANTIFLICKER_AUTO;
    case CameraAttributes::ISO: return SCE_CAMERA_ISO_AUTO;
    case CameraAttributes::Gain: return SCE_CAMERA_GAIN_AUTO;
    case CameraAttributes::WhiteBalance: return SCE_CAMERA_WB_AUTO;
    case CameraAttributes::Backlight: return SCE_CAMERA_BACKLIGHT_OFF;
    case CameraAttributes::Nightmode: return SCE_CAMERA_NIGHTMODE_OFF;
    case CameraAttributes::ExposureCeiling: return 0;
    case CameraAttributes::AutoControlHold: return 0;
    // undescribed parameters
    case CameraAttributes::ImageQuality: return 0;
    case CameraAttributes::NoiseReduction: return 0;
    case CameraAttributes::SharpnessOff: return 0;
    }
    return 0;
}

int Camera::set_attribute(CameraAttributes attribute, int value) { return 0; }

int Camera::open(SceCameraInfo *info, uint64_t base_tick, uint64_t start_tick) {
    tick_diff_us = rtc_get_ticks(base_tick) - start_tick - now_us();
    this->is_opened = true;
    this->info = {};
    memcpy(&(this->info), info, std::min<size_t>(sizeof(SceCameraInfo), info->size));
    uint32_t numerator = this->info.framerate, denominator = 1;
    if (this->info.framerate == SCE_CAMERA_FRAMERATE_3_FPS) {
        numerator = 375;
        denominator = 100;
    } else if (this->info.framerate == SCE_CAMERA_FRAMERATE_7_FPS) {
        numerator = 75;
        denominator = 10;
    }
    frame_interval_us = numerator ? 1000000ull * denominator / numerator : 0;
    return 0;
}

int Camera::close() {
    this->is_started = false;
    this->is_opened = false;
    return 0;
}

int Camera::start() {
    refresh_camera_image(this);
    this->is_started = true;
    this->frame_idx = 0;
    return 0;
}

int Camera::stop() {
    this->is_started = false;
    const std::lock_guard lock(pImpl->frame_mutex);
    stop_host_camera(this);
    pImpl->frame.clear();
    return 0;
}

// The frame (XRGB8888) in the format the game opened the camera with
static void convert_frame(const SceCameraInfo &info, const std::vector<uint32_t> &frame,
    void *pIBase, void *pUBase, void *pVBase, SceSize sizeIBase, SceSize sizeUBase, SceSize sizeVBase) {
    const unsigned w = info.width, h = info.height;
    const bool limited = info.range == SCE_CAMERA_DATA_RANGE_BT601;
    const auto rgb = [&](unsigned x, unsigned y, int &r, int &g, int &b) {
        const uint32_t p = frame[static_cast<size_t>(y) * w + x];
        r = (p >> 16) & 0xFF;
        g = (p >> 8) & 0xFF;
        b = p & 0xFF;
    };
    // BT.601, full range (JPEG, SDL's YUV default) or limited
    const auto luma = [&](int r, int g, int b) {
        const int y = limited ? 16 + ((66 * r + 129 * g + 25 * b + 128) >> 8) : ((77 * r + 150 * g + 29 * b + 128) >> 8);
        return static_cast<uint8_t>(std::clamp(y, 0, 255));
    };
    const auto chroma_u = [&](int r, int g, int b) {
        const int u = limited ? 128 + ((-38 * r - 74 * g + 112 * b + 128) >> 8) : 128 + ((-43 * r - 85 * g + 128 * b + 128) >> 8);
        return static_cast<uint8_t>(std::clamp(u, 0, 255));
    };
    const auto chroma_v = [&](int r, int g, int b) {
        const int v = limited ? 128 + ((112 * r - 94 * g - 18 * b + 128) >> 8) : 128 + ((128 * r - 107 * g - 21 * b + 128) >> 8);
        return static_cast<uint8_t>(std::clamp(v, 0, 255));
    };
    uint8_t *Y = static_cast<uint8_t *>(pIBase);
    uint8_t *U = static_cast<uint8_t *>(pUBase);
    uint8_t *V = static_cast<uint8_t *>(pVBase);
    int r, g, b;

    switch (info.format) {
    case SCE_CAMERA_FORMAT_YUV420_PLANE:
    case SCE_CAMERA_FORMAT_YUV422_PLANE: {
        const bool is_420 = info.format == SCE_CAMERA_FORMAT_YUV420_PLANE;
        for (unsigned y = 0; y < h; y++) {
            for (unsigned x = 0; x < w; x++) {
                rgb(x, y, r, g, b);
                const size_t i = static_cast<size_t>(y) * w + x;
                if (i < sizeIBase)
                    Y[i] = luma(r, g, b);
                if ((x & 1) || (is_420 && (y & 1)))
                    continue;
                const size_t c = static_cast<size_t>(is_420 ? y / 2 : y) * (w / 2) + x / 2;
                if (U && c < sizeUBase)
                    U[c] = chroma_u(r, g, b);
                if (V && c < sizeVBase)
                    V[c] = chroma_v(r, g, b);
            }
        }
        break;
    }
    case SCE_CAMERA_FORMAT_YUV422_PACKED: {
        // Y0 U0 Y1 V0, as SDL's YUY2 upstream uses
        for (unsigned y = 0; y < h; y++) {
            for (unsigned x = 0; x + 1 < w; x += 2) {
                const size_t i = (static_cast<size_t>(y) * w + x) * 2;
                if (i + 3 >= sizeIBase)
                    return;
                int r1, g1, b1;
                rgb(x, y, r, g, b);
                rgb(x + 1, y, r1, g1, b1);
                Y[i] = luma(r, g, b);
                Y[i + 1] = chroma_u(r, g, b);
                Y[i + 2] = luma(r1, g1, b1);
                Y[i + 3] = chroma_v(r, g, b);
            }
        }
        break;
    }
    case SCE_CAMERA_FORMAT_ABGR: {
        // SDL's ABGR8888 as upstream uses: R, G, B, A in memory
        const size_t count = std::min<size_t>(frame.size(), sizeIBase / 4);
        for (size_t i = 0; i < count; i++) {
            const uint32_t p = frame[i];
            Y[i * 4] = (p >> 16) & 0xFF;
            Y[i * 4 + 1] = (p >> 8) & 0xFF;
            Y[i * 4 + 2] = p & 0xFF;
            Y[i * 4 + 3] = 0xFF;
        }
        break;
    }
    default: {
        // ARGB, and RAW8 as upstream takes it: SDL's ARGB8888, B, G, R, A in memory
        const size_t count = std::min<size_t>(frame.size(), sizeIBase / 4);
        for (size_t i = 0; i < count; i++) {
            const uint32_t p = frame[i] | 0xFF000000u;
            memcpy(Y + i * 4, &p, 4);
        }
        break;
    }
    }
}

int Camera::read(SceCameraRead *read, void *pIBase, void *pUBase, void *pVBase, SceSize sizeIBase, SceSize sizeUBase, SceSize sizeVBase) {
    const std::lock_guard lock(pImpl->frame_mutex);
    const uint64_t current_us = now_us();
    if (next_frame_timestamp_us == 0) {
        next_frame_timestamp_us = current_us;
    } else if (current_us < next_frame_timestamp_us) {
        if (read->mode == SCE_CAMERA_READ_MODE_WAIT_NEXTFRAME_ON) {
            std::this_thread::sleep_for(std::chrono::microseconds(next_frame_timestamp_us - current_us));
        } else {
            read->frame = frame_idx;
            read->timestamp = last_frame_timestamp_us;
            read->status = SCE_CAMERA_STATUS_IS_ALREADY_READ;
            return 0;
        }
    }
    last_frame_timestamp_us = next_frame_timestamp_us + tick_diff_us;
    next_frame_timestamp_us += frame_interval_us;

    if (pImpl->host_started) {
        HostCamera &host = host_camera();
        const std::lock_guard host_lock(host.mutex);
        if (host.serial != pImpl->host_serial && host.width && host.height) {
            scale_xrgb(host.pixels.data(), host.width, host.height, host.width, pImpl->frame, info.width, info.height);
            pImpl->host_serial = host.serial;
        }
    }

    read->frame = frame_idx++;
    read->status = SCE_CAMERA_STATUS_IS_ACTIVE;
    read->timestamp = last_frame_timestamp_us;
    if (pImpl->frame.size() == static_cast<size_t>(info.width) * info.height && !pImpl->frame.empty()) {
        convert_frame(info, pImpl->frame, pIBase, pUBase, pVBase, sizeIBase, sizeUBase, sizeVBase);
    } else {
        // no frame from the frontend's camera yet: black
        memset(pIBase, 0, sizeIBase);
        if (pUBase && sizeUBase)
            memset(pUBase, 128, sizeUBase);
        if (pVBase && sizeVBase)
            memset(pVBase, 128, sizeVBase);
    }
    return 0;
}

void Camera::update_config(int type, const std::string &id, const std::string &image, uint32_t color) {
    if (static_cast<int>(this->type) == type && this->id == id && this->image == image && this->color == color)
        return;
    this->type = static_cast<CameraType>(type);
    this->id = id;
    this->image = image;
    this->color = color;
    if (is_started)
        refresh_camera_image(this);
}

// The core sets the cameras from its options; nothing to pick here
void init_default_cameras(Config &cfg) {}

void CameraState::deinit() {
    for (auto &cam : cameras) {
        if (cam.is_started)
            cam.stop();
        cam.is_opened = false;
        cam.is_started = false;
        cam.info = {};
        cam.frame_idx = 0;
        cam.last_frame_timestamp_us = 0;
        cam.next_frame_timestamp_us = 0;
        cam.frame_interval_us = 0;
        cam.tick_diff_us = 0;
    }
    active_camera = SCE_CAMERA_DEVICE_UNKNOWN;
}
#else // !BUILD_LIBRETRO
#include <SDL3/SDL_camera.h>
#include <SDL3/SDL_timer.h>

struct stbi_deleter {
    void operator()(stbi_uc *d) const { stbi_image_free(d); }
};

struct SDL_SurfaceDeleter {
    void operator()(SDL_Surface *s) const { SDL_DestroySurface(s); }
};

struct SDL_CameraDeleter {
    void operator()(SDL_Camera *c) const { SDL_CloseCamera(c); }
};

struct SDL_Deleter {
    void operator()(void *c) const { SDL_free(c); }
};

using SDL_SurfacePtr = std::unique_ptr<SDL_Surface, SDL_SurfaceDeleter>;
using stbi_uc_ptr = std::unique_ptr<stbi_uc, stbi_deleter>;
using SDL_CameraPtr = std::unique_ptr<SDL_Camera, SDL_CameraDeleter>;
using SDL_CameraListPtr = std::unique_ptr<SDL_CameraID[], SDL_Deleter>;

class Camera::CameraImpl {
public:
    SDL_CameraPtr sdl_camera;
    SDL_CameraID device_id;
    SDL_SurfacePtr frame;
    SDL_PixelFormat format;
    SDL_Colorspace colorspace;
    std::mutex frame_mutex;
};

Camera::Camera()
    : pImpl(std::make_unique<CameraImpl>()) {}
Camera::~Camera() = default;

static bool init_web_camera(Camera *self) {
    // open web camera via SDL3
    int num_cameras;
    SDL_CameraListPtr cameras(SDL_GetCameras(&num_cameras));
    if (!cameras) {
        LOG_ERROR("SDL_GetCameras failed. Error: {}", SDL_GetError());
        return false;
    }
    self->pImpl->device_id = 0;
    for (int i = 0; i < num_cameras; i++) {
        auto camera_name = SDL_GetCameraName(cameras[i]);
        if (camera_name && self->id == camera_name) {
            self->pImpl->device_id = cameras[i];
            break;
        }
    }
    if (self->pImpl->device_id == 0) {
        LOG_ERROR("Web camera with id '{}' not found.", self->id);
        return false;
    }
    uint16_t framerate_numerator = self->info.framerate;
    uint16_t framerate_denominator = 1;
    if (self->info.framerate == SCE_CAMERA_FRAMERATE_3_FPS) {
        framerate_numerator = 375;
        framerate_denominator = 100;
    } else if (self->info.framerate == SCE_CAMERA_FRAMERATE_7_FPS) {
        framerate_numerator = 75;
        framerate_denominator = 10;
    }
    self->frame_interval_us = SDL_US_PER_SECOND * framerate_denominator / framerate_numerator;
    SDL_CameraSpec camera_spec{
        .format = self->pImpl->format, /**< Frame format */
        .colorspace = self->pImpl->colorspace, /**< Frame colorspace */
        .width = self->info.width, /**< Frame width */
        .height = self->info.height, /**< Frame height */
        .framerate_numerator = framerate_numerator, /**< Frame rate numerator ((num / denom) == FPS, (denom / num) == duration in seconds) */
        .framerate_denominator = framerate_denominator /**< Frame rate demoninator ((num / denom) == FPS, (denom / num) == duration in seconds) */
    };
    self->pImpl->sdl_camera.reset(SDL_OpenCamera(self->pImpl->device_id, &camera_spec));
    if (!self->pImpl->sdl_camera) {
        LOG_ERROR("Failed to open camera: {}", SDL_GetError());
        return false;
    }
    return true;
}

static bool init_image(Camera *self) {
    FILE *f = FOPEN(fs_utils::utf8_to_path(self->image).c_str(), "rb");
    if (!f) {
        LOG_ERROR("Failed to open camera image file: {} Error: {}", self->image, strerror(errno));
        return false;
    }

    int32_t width = 0, height = 0;
    stbi_uc_ptr data(stbi_load_from_file(f, &width, &height, nullptr, STBI_rgb));
    fclose(f);
    if (!data) {
        LOG_ERROR("Failed to load camera image from {}: {}", self->image, stbi_failure_reason());
        return false;
    }

    SDL_SurfacePtr image_surface(SDL_CreateSurfaceFrom(width, height, SDL_PIXELFORMAT_RGB24, data.get(), width * SDL_BYTESPERPIXEL(SDL_PIXELFORMAT_RGB24)));
    if (!image_surface) {
        LOG_ERROR("Failed to create SDL surface from image data: {}", SDL_GetError());
        return false;
    }

    if (width != self->info.width || height != self->info.height) {
        image_surface.reset(SDL_ScaleSurface(image_surface.get(), self->info.width, self->info.height, SDL_SCALEMODE_LINEAR));
        if (!image_surface) {
            LOG_ERROR("Failed to scale SDL surface: {}", SDL_GetError());
            return false;
        }
    }

    image_surface.reset(SDL_ConvertSurfaceAndColorspace(image_surface.get(), self->pImpl->format, nullptr, self->pImpl->colorspace, 0));
    if (!image_surface) {
        LOG_ERROR("Failed to convert SDL surface: {}", SDL_GetError());
        return false;
    }

    // If frame does not own its data then duplicate it
    if (image_surface->flags & SDL_SURFACE_PREALLOCATED) {
        image_surface.reset(SDL_DuplicateSurface(image_surface.get()));
        if (!image_surface) {
            LOG_ERROR("Failed to duplicate SDL surface: {}", SDL_GetError());
            return false;
        }
    }
    self->pImpl->frame = std::move(image_surface);

    return true;
}

static bool init_solid_color(Camera *self) {
    SDL_SurfacePtr image_surface(SDL_CreateSurface(self->info.width, self->info.height, SDL_PIXELFORMAT_ABGR8888));
    if (!image_surface) {
        LOG_ERROR("Failed to create SDL surface for solid color: {}", SDL_GetError());
        return false;
    }
    if (!SDL_FillSurfaceRect(image_surface.get(), nullptr, self->color)) {
        LOG_ERROR("Failed to fill SDL surface with solid color: {}", SDL_GetError());
        return false;
    }
    SDL_SurfacePtr converted_surface(SDL_ConvertSurfaceAndColorspace(image_surface.get(), self->pImpl->format, nullptr, self->pImpl->colorspace, 0));
    if (!converted_surface) {
        LOG_ERROR("Failed to convert SDL surface for solid color: {}", SDL_GetError());
        return false;
    }
    self->pImpl->frame = std::move(converted_surface);
    return true;
}

static void refresh_camera_image(Camera *self) {
    const std::lock_guard lock(self->pImpl->frame_mutex);

    self->pImpl->sdl_camera.reset();
    self->pImpl->frame.reset();
    if (self->type == CameraType::WebCamera) {
        if (!init_web_camera(self))
            self->type = CameraType::Image;
    }
    if (self->type == CameraType::Image) {
        if (!init_image(self))
            self->type = CameraType::SolidColor;
    }
    if (self->type == CameraType::SolidColor) {
        if (!init_solid_color(self))
            self->pImpl->frame.reset();
    }
}

int Camera::get_attribute(CameraAttributes attribute) {
    switch (attribute) {
    case CameraAttributes::Saturation: return SCE_CAMERA_SATURATION_10;
    case CameraAttributes::Brightness: return 128; // 0-255
    case CameraAttributes::Contrast: return 128; // random default value  0-255
    case CameraAttributes::Sharpness: return SCE_CAMERA_SHARPNESS_100;
    case CameraAttributes::Reverse: return SCE_CAMERA_REVERSE_OFF;
    case CameraAttributes::Effect: return SCE_CAMERA_EFFECT_NORMAL;
    case CameraAttributes::EV: return 0;
    case CameraAttributes::Zoom: return 10; // 10-40
    case CameraAttributes::AntiFlicker: return SCE_CAMERA_ANTIFLICKER_AUTO;
    case CameraAttributes::ISO: return SCE_CAMERA_ISO_AUTO;
    case CameraAttributes::Gain: return SCE_CAMERA_GAIN_AUTO;
    case CameraAttributes::WhiteBalance: return SCE_CAMERA_WB_AUTO;
    case CameraAttributes::Backlight: return SCE_CAMERA_BACKLIGHT_OFF;
    case CameraAttributes::Nightmode: return SCE_CAMERA_NIGHTMODE_OFF;
    case CameraAttributes::ExposureCeiling: return 0;
    case CameraAttributes::AutoControlHold: return 0;
    // undescribed parameters
    case CameraAttributes::ImageQuality: return 0;
    case CameraAttributes::NoiseReduction: return 0;
    case CameraAttributes::SharpnessOff: return 0;
    }
    return 0;
}

int Camera::set_attribute(CameraAttributes attribute, int value) {
    return 0;
}

int Camera::open(SceCameraInfo *info, uint64_t base_tick, uint64_t start_tick) {
    tick_diff_us = rtc_get_ticks(base_tick) - start_tick - (SDL_GetTicksNS() / SDL_NS_PER_US);
    this->is_opened = true;
    this->info = {};
    memcpy(&(this->info), info, std::min<size_t>(sizeof(SceCameraInfo), info->size));
    switch (this->info.format) {
    case SCE_CAMERA_FORMAT_YUV420_PLANE: // YUV 4:2:0 planar
        this->pImpl->format = SDL_PIXELFORMAT_YV12;
        this->pImpl->colorspace = SDL_COLORSPACE_YUV_DEFAULT;
        break;
    case SCE_CAMERA_FORMAT_YUV422_PLANE: // YUV 4:2:2 planar
        this->pImpl->format = SDL_PIXELFORMAT_YUY2; // use packed format cause SDL does not have YUV 4:2:2 planar
        this->pImpl->colorspace = SDL_COLORSPACE_YUV_DEFAULT;
        break;
    case SCE_CAMERA_FORMAT_YUV422_PACKED: // YUV 4:2:2 packed
        this->pImpl->format = SDL_PIXELFORMAT_YUY2;
        this->pImpl->colorspace = SDL_COLORSPACE_YUV_DEFAULT;
        break;
    case SCE_CAMERA_FORMAT_ARGB: // ARGB format
        this->pImpl->format = SDL_PIXELFORMAT_ARGB8888;
        this->pImpl->colorspace = SDL_COLORSPACE_RGB_DEFAULT;
        break;
    case SCE_CAMERA_FORMAT_ABGR: // ABGR format
        this->pImpl->format = SDL_PIXELFORMAT_ABGR8888;
        this->pImpl->colorspace = SDL_COLORSPACE_RGB_DEFAULT;
        break;
    case SCE_CAMERA_FORMAT_RAW8: // unsupported, use default
    default:
        this->pImpl->format = SDL_PIXELFORMAT_ARGB8888; // ABGR format
        this->pImpl->colorspace = SDL_COLORSPACE_RGB_DEFAULT;
    }

    if (this->info.range == SCE_CAMERA_DATA_RANGE_BT601) {
        this->pImpl->colorspace = SDL_COLORSPACE_BT601_LIMITED;
    }

    return 0;
}

int Camera::start() {
    refresh_camera_image(this);
    this->is_started = true;
    this->frame_idx = 0;
    return 0;
}

int Camera::read(SceCameraRead *read, void *pIBase, void *pUBase, void *pVBase, SceSize sizeIBase, SceSize sizeUBase, SceSize sizeVBase) {
    const std::lock_guard lock(pImpl->frame_mutex);
    constexpr uint64_t minimal_delay_ns = SDL_NS_PER_US; // arbitrary value
    uint64_t sdl_current_time_ns = SDL_GetTicksNS();
    uint64_t sdl_current_time_us = sdl_current_time_ns / SDL_NS_PER_US;
    if (next_frame_timestamp_us == 0) {
        next_frame_timestamp_us = sdl_current_time_us;
    } else {
        uint64_t wait_time_ns = (sdl_current_time_ns < next_frame_timestamp_us * SDL_NS_PER_US) ? (next_frame_timestamp_us * SDL_NS_PER_US - sdl_current_time_ns) : 0;
        if (wait_time_ns > minimal_delay_ns) {
            if (read->mode == SCE_CAMERA_READ_MODE_WAIT_NEXTFRAME_ON) {
                SDL_DelayPrecise(wait_time_ns);
            } else {
                read->frame = frame_idx;
                read->timestamp = last_frame_timestamp_us;
                read->status = SCE_CAMERA_STATUS_IS_ALREADY_READ;
                return 0;
            }
        }
    }
    // next frame
    last_frame_timestamp_us = next_frame_timestamp_us;
    next_frame_timestamp_us = next_frame_timestamp_us + frame_interval_us;
    if (type == CameraType::WebCamera) {
        Uint64 timestampNS = 0;
        auto surface = SDL_AcquireCameraFrame(pImpl->sdl_camera.get(), &timestampNS);
        // drains all buffered frames to get the latest one
        Uint64 next_timestampNS;
        auto next_surface = SDL_AcquireCameraFrame(pImpl->sdl_camera.get(), &next_timestampNS);
        int i = 16; // Safety counter to avoid endless loop.
                    // sdl buffer is 8 surfaces, so if we read much more than 8 times, something go really wrong
        while (next_surface && i > 0) {
            SDL_ReleaseCameraFrame(pImpl->sdl_camera.get(), surface);
            surface = next_surface;
            timestampNS = next_timestampNS;
            next_surface = SDL_AcquireCameraFrame(pImpl->sdl_camera.get(), &next_timestampNS);
            i--;
        }
        if (next_surface)
            SDL_ReleaseCameraFrame(pImpl->sdl_camera.get(), next_surface);
        if (surface) {
            pImpl->frame.reset(SDL_DuplicateSurface(surface));
            SDL_ReleaseCameraFrame(pImpl->sdl_camera.get(), surface);
            LOG_ERROR_IF(!pImpl->frame, "Failed to duplicate camera surface: {}", SDL_GetError());
            last_frame_timestamp_us = timestampNS / SDL_NS_PER_US + tick_diff_us;
        }
    }
    read->frame = frame_idx++;
    read->status = SCE_CAMERA_STATUS_IS_ACTIVE;
    read->timestamp = last_frame_timestamp_us;
    if (pImpl->frame) {
        if (this->info.format == SCE_CAMERA_FORMAT_YUV420_PLANE) {
            sizeIBase = std::min(sizeIBase, (SceSize)(pImpl->frame->pitch * pImpl->frame->h));
            sizeUBase = std::min(sizeUBase, (SceSize)(pImpl->frame->pitch * pImpl->frame->h / 4));
            sizeVBase = std::min(sizeVBase, (SceSize)(pImpl->frame->pitch * pImpl->frame->h / 4));
            memcpy(pIBase, (uint8_t *)pImpl->frame->pixels, sizeIBase);
            memcpy(pVBase, (uint8_t *)pImpl->frame->pixels + (pImpl->frame->pitch * pImpl->frame->h), sizeUBase);
            memcpy(pUBase, (uint8_t *)pImpl->frame->pixels + (pImpl->frame->pitch * pImpl->frame->h * 5 / 4), sizeVBase);
        } else if (this->info.format == SCE_CAMERA_FORMAT_YUV422_PLANE) {
            // convert SDL_PIXELFORMAT_YUY2 Y0+U0+Y1+V0 to planar format
            const int width = pImpl->frame->w;
            const int height = pImpl->frame->h;
            if (!SDL_LockSurface(pImpl->frame.get())) {
                LOG_ERROR("Failed to lock camera frame surface: {}", SDL_GetError());
                goto BAD_FRAME;
            };
            uint8_t const *packed = (uint8_t *)pImpl->frame->pixels;
            uint8_t *Y = (uint8_t *)pIBase;
            uint8_t *U = (uint8_t *)pUBase;
            uint8_t *V = (uint8_t *)pVBase;
            int pitch = pImpl->frame->pitch;
            for (ptrdiff_t y = 0; y < height; y++) {
                uint8_t const *row = packed + y * pitch;
                for (ptrdiff_t x = 0; x < width; x += 2) {
                    const size_t y_index = y * width + x;
                    const size_t uv_index = y_index / 2;
                    if (y_index < sizeIBase)
                        Y[y_index] = row[x * 2];
                    if (y_index + 1 < sizeIBase)
                        Y[y_index + 1] = row[x * 2 + 2];
                    if (uv_index < sizeUBase)
                        U[uv_index] = row[x * 2 + 1];
                    if (uv_index < sizeVBase)
                        V[uv_index] = row[x * 2 + 3];
                }
            }
            SDL_UnlockSurface(pImpl->frame.get());
        } else {
            sizeIBase = std::min(sizeIBase, (SceSize)(pImpl->frame->pitch * pImpl->frame->h)); // here pitch is width in bytes
            memcpy(pIBase, pImpl->frame->pixels, sizeIBase);
        }
    } else {
    BAD_FRAME:
        LOG_ERROR_ONCE("No camera frame available.");
        memset(pIBase, 0, sizeIBase);
        if (pUBase && sizeUBase)
            memset(pUBase, 127, sizeUBase);
        if (pVBase && sizeVBase)
            memset(pVBase, 127, sizeVBase);
    }
    return 0;
}

int Camera::close() {
    this->is_started = false;
    this->is_opened = false;
    return 0;
}

int Camera::stop() {
    this->is_started = false;
    pImpl->frame.reset();
    pImpl->sdl_camera.reset();
    return 0;
}

void Camera::update_config(int type, const std::string &id, const std::string &image, uint32_t color) {
    if (static_cast<int>(this->type) == type && this->id == id && this->image == image && this->color == color)
        return;
    this->type = static_cast<CameraType>(type);
    this->id = id;
    this->image = image;
    this->color = color;
    if (is_started)
        refresh_camera_image(this);
}

void CameraState::deinit() {
    for (auto &cam : cameras) {
        if (cam.is_started)
            cam.stop();

        cam.is_opened = false;
        cam.is_started = false;
        cam.info = {};
        cam.frame_idx = 0;
        cam.last_frame_timestamp_us = 0;
        cam.next_frame_timestamp_us = 0;
        cam.frame_interval_us = 0;
        cam.tick_diff_us = 0;
    }
    active_camera = SCE_CAMERA_DEVICE_UNKNOWN;
}

BOOST_DESCRIBE_ENUM(SDL_CameraPosition, SDL_CAMERA_POSITION_UNKNOWN, SDL_CAMERA_POSITION_FRONT_FACING, SDL_CAMERA_POSITION_BACK_FACING)

void init_default_cameras(Config &cfg) {
    if (!((cfg.front_camera_type == WebCamera && cfg.front_camera_id.empty()) || (cfg.back_camera_type == WebCamera && cfg.back_camera_id.empty())))
        return;
    LOG_DEBUG("Initialize default cameras...");
    int num_cameras;
    SDL_CameraListPtr cameras(SDL_GetCameras(&num_cameras));
    for (int i = 0; i < num_cameras; i++) {
        auto position = SDL_GetCameraPosition(cameras[i]);
        LOG_TRACE("Found camera: name='{}' position={}", SDL_GetCameraName(cameras[i]), position);
        if (position == SDL_CAMERA_POSITION_FRONT_FACING) {
            cfg.front_camera_id = SDL_GetCameraName(cameras[i]);
            cfg.front_camera_type = WebCamera;
        }
        if (position == SDL_CAMERA_POSITION_BACK_FACING) {
            cfg.back_camera_id = SDL_GetCameraName(cameras[i]);
            cfg.back_camera_type = WebCamera;
        }
    }
    if (num_cameras > 0) {
        if (cfg.front_camera_id.empty()) {
            cfg.front_camera_id = SDL_GetCameraName(cameras[0]);
            cfg.front_camera_type = WebCamera;
        }
        if (cfg.back_camera_id.empty()) {
            cfg.back_camera_id = SDL_GetCameraName(cameras[0]);
            cfg.back_camera_type = WebCamera;
        }
    } else {
        cfg.front_camera_type = SolidColor;
        cfg.back_camera_type = SolidColor;
    }
}
#endif // !BUILD_LIBRETRO
