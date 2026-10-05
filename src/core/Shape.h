#ifndef SSE_CORE_SHAPE_H
#define SSE_CORE_SHAPE_H

#include <cmath>
#include <cstdint>
#include <vector>

#include "Color.h"
#include "Line.h"
#include "Pixel.h"

namespace SSE {

// ============================================================
// ФОРМА — базовые геометрические фигуры.
// Форма умеет разложиться на пиксели — как линия.
// Из форм будут состоять объекты мира.
// ============================================================

// --- Круг (диск) ---
struct Circle {
    std::int32_t cx = 0;
    std::int32_t cy = 0;
    std::int32_t radius = 1;
    Color color{};

    Circle() = default;
    Circle(std::int32_t x, std::int32_t y, std::int32_t r, const Color& c)
        : cx(x), cy(y), radius(r), color(c) {}

    // Разложить круг на пиксели
    [[nodiscard]] std::vector<Pixel> rasterize() const {
        std::vector<Pixel> result;
        std::int32_t r2 = radius * radius;
        for (std::int32_t dy = -radius; dy <= radius; ++dy) {
            for (std::int32_t dx = -radius; dx <= radius; ++dx) {
                if (dx * dx + dy * dy <= r2) {
                    result.emplace_back(cx + dx, cy + dy, color);
                }
            }
        }
        return result;
    }

    // Только контур круга (кольцо толщиной 1)
    [[nodiscard]] std::vector<Pixel> outline() const {
        std::vector<Pixel> result;
        std::int32_t x = radius;
        std::int32_t y = 0;
        std::int32_t err = 0;

        while (x >= y) {
            result.emplace_back(cx + x, cy + y, color);
            result.emplace_back(cx + y, cy + x, color);
            result.emplace_back(cx - y, cy + x, color);
            result.emplace_back(cx - x, cy + y, color);
            result.emplace_back(cx - x, cy - y, color);
            result.emplace_back(cx - y, cy - x, color);
            result.emplace_back(cx + y, cy - x, color);
            result.emplace_back(cx + x, cy - y, color);

            if (err <= 0) {
                y += 1;
                err += 2 * y + 1;
            }
            if (err > 0) {
                x -= 1;
                err -= 2 * x + 1;
            }
        }
        return result;
    }
};

// --- Прямоугольник ---
struct Rectangle {
    std::int32_t x = 0;  // левый верхний угол
    std::int32_t y = 0;
    std::int32_t width = 1;
    std::int32_t height = 1;
    Color color{};

    Rectangle() = default;
    Rectangle(std::int32_t x_, std::int32_t y_, std::int32_t w, std::int32_t h, const Color& c)
        : x(x_), y(y_), width(w), height(h), color(c) {}

    [[nodiscard]] std::vector<Pixel> rasterize() const {
        std::vector<Pixel> result;
        for (std::int32_t dy = 0; dy < height; ++dy) {
            for (std::int32_t dx = 0; dx < width; ++dx) {
                result.emplace_back(x + dx, y + dy, color);
            }
        }
        return result;
    }
};

// --- Треугольник (равнобедренный, вершина сверху) ---
struct Triangle {
    std::int32_t x = 0;       // центр основания
    std::int32_t y = 0;       // вершина
    std::int32_t width = 1;   // ширина основания
    std::int32_t height = 1;  // высота
    Color color{};

    Triangle() = default;
    Triangle(std::int32_t x_, std::int32_t y_, std::int32_t w, std::int32_t h, const Color& c)
        : x(x_), y(y_), width(w), height(h), color(c) {}

    [[nodiscard]] std::vector<Pixel> rasterize() const {
        std::vector<Pixel> result;
        for (std::int32_t row = 0; row < height; ++row) {
            float t = static_cast<float>(row) / height;
            std::int32_t row_width = static_cast<std::int32_t>(width * t);
            std::int32_t half = row_width / 2;
            for (std::int32_t dx = -half; dx <= half; ++dx) {
                result.emplace_back(x + dx, y + row, color);
            }
        }
        return result;
    }
};

}  // namespace SSE

#endif  // SSE_CORE_SHAPE_H