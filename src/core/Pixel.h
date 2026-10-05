#ifndef SSE_CORE_PIXEL_H
#define SSE_CORE_PIXEL_H

#include <cstdint>

#include "Color.h"

namespace SSE {

// ============================================================
// ПИКСЕЛЬ — атом изображения
// Пиксель = позиция (x, y) + цвет.
// ============================================================
struct Pixel {
    std::int32_t x = 0;  // позиция по горизонтали
    std::int32_t y = 0;  // позиция по вертикали
    Color color{};       // цвет пикселя

    constexpr Pixel() = default;
    constexpr Pixel(std::int32_t x_, std::int32_t y_, const Color& c) : x(x_), y(y_), color(c) {}
};

}  // namespace SSE

#endif  // SSE_CORE_PIXEL_H