#ifndef SSE_DATA_SCALE_SCALE_H
#define SSE_DATA_SCALE_SCALE_H

namespace SSE::Scale {

// ============================================================
// ЕДИНИЦЫ ИЗМЕРЕНИЯ МИРА
//
// 1 см = 1 пиксель. Физически честно.
// Все размеры в проекте — в САНТИМЕТРАХ.
// При рендере сантиметры становятся пикселями напрямую.
// ============================================================

constexpr float PIXELS_PER_CM = 1.0f;

// Перевод см → px (для рендера)
inline constexpr float cm(float value) {
    return value * PIXELS_PER_CM;
}

} // namespace SSE::Scale

#endif
