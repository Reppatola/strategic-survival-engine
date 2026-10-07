#ifndef SSE_RENDER_VISION_MASK_H
#define SSE_RENDER_VISION_MASK_H

#include "app/Config.h"
#include <cmath>
#include <cstdint>

namespace SSE::Render {

// ============================================================
// ЗРЕНИЕ ГЕРОЯ
//
// Три зоны (по данным физиологии):
//   фокус:      ±30°    — 255
//   периферия:  ±100°   — 140
//   слепая:     остальное — 0
//
// sin_f, cos_f — синус и косинус направления взгляда героя.
// Направление 0 = юг (+Y мира = низ экрана).
//
// Возвращает 0..255 — множитель видимости.
// ============================================================
inline std::uint8_t visionAt(int sx, int sy,
                             float sin_f, float cos_f)
{
    const float dx = static_cast<float>(sx - SSE::Config::CXP);
    const float dy = static_cast<float>(sy - SSE::Config::CYP);

    const float d2 = dx * dx + dy * dy;

    // Близко к герою — видно всё, вне зависимости от угла
    if (d2 < 400.0f) return 255;    // радиус 20 px

    const float d   = std::sqrt(d2);
    const float dot = (dx * sin_f + dy * cos_f) / d;

    // cos(30°) = 0.866
    if (dot >  0.866f) return 255;   // фокус
    // cos(100°) = -0.174
    if (dot > -0.174f) return 140;   // периферия
    return 0;                         // слепая зона
}

} // namespace SSE::Render

#endif
