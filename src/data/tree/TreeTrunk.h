#ifndef SSE_DATA_TREE_TREETRUNK_H
#define SSE_DATA_TREE_TREETRUNK_H

#include <cstdint>

#include "core/Color.h"
#include "core/Random.h"

namespace SSE {

// ============================================================
// СТВОЛ — основа любого дерева.
// Растёт от точки на земле вверх.
// ============================================================
struct TreeTrunk {
    float height_px = 20.0f;  // высота ствола
    float width_px = 4.0f;    // толщина
    Color color{};            // цвет коры

    // Ветки: от ствола отходят в стороны
    struct Branch {
        float height_ratio;  // 0..1 — на какой высоте от ствола
        float angle_rad;     // направление
        float length_px;     // длина
    };
    std::uint8_t branch_count = 0;

    static TreeTrunk create(float height, float width, const Color* palette,
                            std::uint8_t palette_size, Random& rng) {
        TreeTrunk t;
        t.height_px = height;
        t.width_px = width;
        std::int32_t idx = rng.intRange(0, palette_size - 1);
        t.color = palette[idx];
        t.branch_count = static_cast<std::uint8_t>(rng.intRange(2, 5));
        return t;
    }
};

}  // namespace SSE

#endif  // SSE_DATA_TREE_TREETRUNK_H