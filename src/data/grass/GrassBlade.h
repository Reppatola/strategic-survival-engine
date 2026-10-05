#ifndef SSE_DATA_GRASS_GRASSBLADE_H
#define SSE_DATA_GRASS_GRASSBLADE_H

#include <cmath>
#include <cstdint>
#include <vector>

#include "core/Color.h"
#include "core/Random.h"
#include "data/grass/GrassType.h"

namespace SSE {

// ============================================================
// ТРАВИНКА — одна единица травы.
// Состоит из листьев. Каждый лист — угол + длина + цвет.
// ============================================================
struct GrassBlade {
    // Один лист
    struct Leaf {
        float angle_rad;  // направление
        float length_px;  // длина
        Color color;      // цвет
    };

    std::int32_t x = 0;  // позиция на земле
    std::int32_t y = 0;
    std::vector<Leaf> leaves;

    // ============================================================
    // Создать травинку по типу: количество листьев, длины, цвета.
    // ============================================================
    static GrassBlade create(std::int32_t x, std::int32_t y, const GrassType& type, Random& rng) {
        GrassBlade b;
        b.x = x;
        b.y = y;

        std::int32_t n = rng.intRange(type.leaves_min, type.leaves_max);
        b.leaves.reserve(n);

        // Базовый оттенок для всей травинки
        std::int32_t color_idx = rng.intRange(0, type.palette_size - 1);
        Color base = type.palette[color_idx];

        for (std::int32_t i = 0; i < n; ++i) {
            Leaf leaf;
            leaf.angle_rad = rng.floatRange(0.0f, 6.2831853f);  // 0..2π
            leaf.length_px = rng.floatRange(type.length_min_px, type.length_max_px);

            // Небольшая вариация цвета листа
            float k = rng.floatRange(0.85f, 1.15f);
            leaf.color = base.darker(k);
            b.leaves.push_back(leaf);
        }
        return b;
    }
};

}  // namespace SSE

#endif  // SSE_DATA_GRASS_GRASSBLADE_H