#pragma once
#include "app/Config.h"
#include <cmath>

namespace SSE::Sphere {

using namespace SSE::Config;

inline float wrapFloat(float v) {
    v = std::fmod(v, static_cast<float>(WORLD_SIZE));
    if (v < 0) v += WORLD_SIZE;
    return v;
}

inline int wrapCell(int i) {
    i %= WORLD_CELLS;
    if (i < 0) i += WORLD_CELLS;
    return i;
}

inline float wrapDelta(float d) {
    d = std::fmod(d + WORLD_SIZE * 0.5f, static_cast<float>(WORLD_SIZE));
    if (d < 0) d += WORLD_SIZE;
    return d - WORLD_SIZE * 0.5f;
}

inline int cellIdx(int ix, int iy) {
    return wrapCell(iy) * WORLD_CELLS + wrapCell(ix);
}

} // namespace SSE::Sphere
