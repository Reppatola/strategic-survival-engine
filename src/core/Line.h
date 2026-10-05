#ifndef SSE_CORE_LINE_H
#define SSE_CORE_LINE_H

#include <cmath>
#include <cstdint>
#include <vector>

#include "Pixel.h"

namespace SSE {

// ============================================================
// ЛИНИЯ — два пикселя + толщина
// Линия умеет "разложиться" на пиксели (растеризация).
// Это основа: из линий будут состоять листья, травинки, стволы.
// ============================================================
struct Line {
    Pixel a;                     // начало
    Pixel b;                     // конец
    std::int32_t thickness = 1;  // толщина в пикселях

    Line() = default;
    Line(const Pixel& a_, const Pixel& b_, std::int32_t t = 1) : a(a_), b(b_), thickness(t) {}

    // Разложить линию на отдельные пиксели.
    // Возвращает вектор пикселей — то, что нужно нарисовать.
    [[nodiscard]] std::vector<Pixel> rasterize() const {
        std::vector<Pixel> result;

        std::int32_t dx = b.x - a.x;
        std::int32_t dy = b.y - a.y;

        std::int32_t steps = std::max(std::abs(dx), std::abs(dy));
        if (steps == 0) {
            result.push_back(a);
            return result;
        }

        // Линейная интерполяция цвета от a к b
        for (std::int32_t i = 0; i <= steps; ++i) {
            float t = static_cast<float>(i) / static_cast<float>(steps);

            std::int32_t px = a.x + static_cast<std::int32_t>(dx * t);
            std::int32_t py = a.y + static_cast<std::int32_t>(dy * t);

            Color c = a.color.mix(b.color, t);

            // Если толщина > 1 — рисуем квадратик вокруг точки
            if (thickness <= 1) {
                result.emplace_back(px, py, c);
            } else {
                std::int32_t half = thickness / 2;
                for (std::int32_t oy = -half; oy <= half; ++oy) {
                    for (std::int32_t ox = -half; ox <= half; ++ox) {
                        result.emplace_back(px + ox, py + oy, c);
                    }
                }
            }
        }
        return result;
    }
};

}  // namespace SSE

#endif  // SSE_CORE_LINE_H