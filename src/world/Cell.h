#pragma once
#include <vector>
#include <cstdint>

namespace SSE {

struct ActivePixel {
    std::int16_t dx;
    std::int16_t dy;
    std::uint32_t color;
};

struct CachedCell {
    std::vector<ActivePixel> pixels;
    bool loaded = false;

    void clear() {
        loaded = false;
        pixels.clear();
        pixels.shrink_to_fit();
    }
};

} // namespace SSE
