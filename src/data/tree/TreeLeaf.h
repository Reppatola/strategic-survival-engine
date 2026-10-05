#ifndef SSE_DATA_TREE_TREELEAF_H
#define SSE_DATA_TREE_TREELEAF_H

#include <cmath>
#include <cstdint>

#include "core/Color.h"
#include "core/Random.h"

namespace SSE {

// ============================================================
// ЛИСТ — для лиственных деревьев.
// Форма: круглый, овальный, сердцевидный (пока — как данные).
// ============================================================
struct TreeLeaf {
    enum class Shape : std::uint8_t {
        NONE = 0,  // нет листьев (хвойные)
        ROUND,     // круглый
        OVAL,      // овальный
        HEART      // сердцевидный
    };

    float size_px = 3.0f;  // размер
    Shape shape = Shape::ROUND;
    Color color{};

    static TreeLeaf create(Shape s, const Color* palette, std::uint8_t palette_size, Random& rng) {
        TreeLeaf l;
        l.shape = s;
        l.size_px = rng.floatRange(2.0f, 4.0f);
        std::int32_t idx = rng.intRange(0, palette_size - 1);
        l.color = palette[idx];
        return l;
    }
};

}  // namespace SSE

#endif  // SSE_DATA_TREE_TREELEAF_H