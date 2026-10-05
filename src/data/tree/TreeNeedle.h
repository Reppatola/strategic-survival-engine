#ifndef SSE_DATA_TREE_TREENEEDLE_H
#define SSE_DATA_TREE_TREENEEDLE_H

#include <cstdint>

#include "core/Color.h"
#include "core/Random.h"

namespace SSE {

// ============================================================
// ИГОЛКА — для хвойных деревьев.
// Иголка — тонкая линия, растущая вбок от ветки.
// ============================================================
struct TreeNeedle {
    enum class Shape : std::uint8_t {
        NONE = 0,     // нет иголок (лиственные)
        SHORT_SPIKE,  // короткая (ель)
        LONG_SPIKE    // длинная (сосна)
    };

    float length_px = 4.0f;
    float angle_rad = 0.0f;
    Shape shape = Shape::SHORT_SPIKE;
    Color color{};

    static TreeNeedle create(Shape s, const Color* palette, std::uint8_t palette_size,
                             Random& rng) {
        TreeNeedle n;
        n.shape = s;
        n.length_px =
            (s == Shape::SHORT_SPIKE) ? rng.floatRange(3.0f, 5.0f) : rng.floatRange(5.0f, 8.0f);
        n.angle_rad = rng.floatRange(0.0f, 6.2831853f);
        std::int32_t idx = rng.intRange(0, palette_size - 1);
        n.color = palette[idx];
        return n;
    }
};

}  // namespace SSE

#endif  // SSE_DATA_TREE_TREENEEDLE_H