#ifndef SSE_CORE_COLOR_H
#define SSE_CORE_COLOR_H

#include <cstdint>

namespace SSE {

// ============================================================
// ЦВЕТ — основа всего
// Любой объект в мире имеет цвет. Цвет — это данные: 4 числа.
// ============================================================
struct Color {
    std::uint8_t r = 0;    // красный  0..255
    std::uint8_t g = 0;    // зелёный  0..255
    std::uint8_t b = 0;    // синий    0..255
    std::uint8_t a = 255;  // прозрачность 0..255

    // --- Конструкторы ---
    constexpr Color() = default;
    constexpr Color(std::uint8_t r_, std::uint8_t g_, std::uint8_t b_, std::uint8_t a_ = 255)
        : r(r_), g(g_), b(b_), a(a_) {}

    // --- Утилиты ---
    // Затемнить цвет (коэффициент 0..1)
    [[nodiscard]] constexpr Color darker(float k) const {
        return Color(static_cast<std::uint8_t>(r * k), static_cast<std::uint8_t>(g * k),
                     static_cast<std::uint8_t>(b * k), a);
    }

    // Осветлить цвет (коэффициент 0..1)
    [[nodiscard]] constexpr Color lighter(float k) const {
        return Color(static_cast<std::uint8_t>(r + (255 - r) * k),
                     static_cast<std::uint8_t>(g + (255 - g) * k),
                     static_cast<std::uint8_t>(b + (255 - b) * k), a);
    }

    // Смешать два цвета (t = 0 → этот, t = 1 → другой)
    [[nodiscard]] constexpr Color mix(const Color& other, float t) const {
        return Color(static_cast<std::uint8_t>(r * (1 - t) + other.r * t),
                     static_cast<std::uint8_t>(g * (1 - t) + other.g * t),
                     static_cast<std::uint8_t>(b * (1 - t) + other.b * t), a);
    }
};

}  // namespace SSE

#endif  // SSE_CORE_COLOR_H