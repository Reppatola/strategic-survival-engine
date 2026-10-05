#ifndef SSE_DATA_WEATHER_TIMEOFDAY_H
#define SSE_DATA_WEATHER_TIMEOFDAY_H

#include <cstdint>

#include "core/Color.h"

namespace SSE {

// ============================================================
// ВРЕМЯ СУТОК
// 0.0 = полночь, 0.25 = утро, 0.5 = полдень, 0.75 = вечер
// ============================================================
struct TimeOfDay {
    float t = 0.5f;                   // 0..1
    float day_duration_sec = 600.0f;  // полный цикл — 10 минут

    // Фаза
    enum class Phase : std::uint8_t { NIGHT, DAWN, MORNING, NOON, AFTERNOON, DUSK, EVENING };

    Phase phase() const {
        if (t < 0.20f) return Phase::NIGHT;
        if (t < 0.30f) return Phase::DAWN;
        if (t < 0.45f) return Phase::MORNING;
        if (t < 0.55f) return Phase::NOON;
        if (t < 0.70f) return Phase::AFTERNOON;
        if (t < 0.80f) return Phase::DUSK;
        return Phase::EVENING;
    }

    // Множитель яркости (0.3 ночью, 1.0 днём)
    float brightness() const {
        // Простая кривая: 1 в полдень, 0.3 в полночь
        float d = 1.0f - std::abs(t - 0.5f) * 2.0f;  // 0..1
        return 0.3f + 0.7f * d;
    }

    void advance(float dt_sec) {
        t += dt_sec / day_duration_sec;
        while (t >= 1.0f) t -= 1.0f;
    }
};

}  // namespace SSE

#endif