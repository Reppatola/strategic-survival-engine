#ifndef SSE_DATA_TREE_TREETYPE_H
#define SSE_DATA_TREE_TREETYPE_H

#include <cstdint>
#include <string>

#include "core/Color.h"
#include "data/tree/TreeColor.h"
#include "data/tree/TreeLeaf.h"
#include "data/tree/TreeNeedle.h"
#include "data/tree/TreeTrunk.h"

namespace SSE {

// ============================================================
// ТИП ДЕРЕВА
// Описывает вид: дуб, ель, берёза, сосна.
// Хвойное или лиственное — определяется через leaf_shape / needle_shape.
// ============================================================
struct TreeType {
    std::string name;

    // Ствол
    const Color* trunk_palette;
    std::uint8_t trunk_palette_size;
    float trunk_height_min = 15.0f;
    float trunk_height_max = 25.0f;
    float trunk_width_min = 3.0f;
    float trunk_width_max = 6.0f;

    // Листья (если лиственное) — иначе NONE
    TreeLeaf::Shape leaf_shape = TreeLeaf::Shape::NONE;
    const Color* leaf_palette = nullptr;
    std::uint8_t leaf_palette_size = 0;
    std::uint8_t leaves_min = 0;
    std::uint8_t leaves_max = 0;

    // Иголки (если хвойное) — иначе NONE
    TreeNeedle::Shape needle_shape = TreeNeedle::Shape::NONE;
    const Color* needle_palette = nullptr;
    std::uint8_t needle_palette_size = 0;
    std::uint8_t needles_min = 0;
    std::uint8_t needles_max = 0;

    // --- Фабрики ---

    static TreeType oak() {
        TreeType t;
        t.name = "дуб";
        t.trunk_palette = TreeColor::TRUNK_OAK;
        t.trunk_palette_size = sizeof(TreeColor::TRUNK_OAK) / sizeof(Color);
        t.trunk_height_min = 20.0f;
        t.trunk_height_max = 30.0f;
        t.trunk_width_min = 4.0f;
        t.trunk_width_max = 7.0f;
        t.leaf_shape = TreeLeaf::Shape::ROUND;
        t.leaf_palette = TreeColor::LEAF_OAK_SUMMER;
        t.leaf_palette_size = sizeof(TreeColor::LEAF_OAK_SUMMER) / sizeof(Color);
        t.leaves_min = 15;
        t.leaves_max = 30;
        return t;
    }

    static TreeType birch() {
        TreeType t;
        t.name = "берёза";
        t.trunk_palette = TreeColor::TRUNK_BIRCH;
        t.trunk_palette_size = sizeof(TreeColor::TRUNK_BIRCH) / sizeof(Color);
        t.trunk_height_min = 25.0f;
        t.trunk_height_max = 35.0f;
        t.trunk_width_min = 2.0f;
        t.trunk_width_max = 4.0f;
        t.leaf_shape = TreeLeaf::Shape::OVAL;
        t.leaf_palette = TreeColor::LEAF_BIRCH_SUMMER;
        t.leaf_palette_size = sizeof(TreeColor::LEAF_BIRCH_SUMMER) / sizeof(Color);
        t.leaves_min = 20;
        t.leaves_max = 40;
        return t;
    }

    static TreeType spruce() {
        TreeType t;
        t.name = "ель";
        t.trunk_palette = TreeColor::TRUNK_PINE;
        t.trunk_palette_size = sizeof(TreeColor::TRUNK_PINE) / sizeof(Color);
        t.trunk_height_min = 30.0f;
        t.trunk_height_max = 45.0f;
        t.trunk_width_min = 2.0f;
        t.trunk_width_max = 4.0f;
        t.needle_shape = TreeNeedle::Shape::SHORT_SPIKE;
        t.needle_palette = TreeColor::NEEDLE_SPRUCE;
        t.needle_palette_size = sizeof(TreeColor::NEEDLE_SPRUCE) / sizeof(Color);
        t.needles_min = 40;
        t.needles_max = 80;
        return t;
    }

    static TreeType pine() {
        TreeType t;
        t.name = "сосна";
        t.trunk_palette = TreeColor::TRUNK_PINE;
        t.trunk_palette_size = sizeof(TreeColor::TRUNK_PINE) / sizeof(Color);
        t.trunk_height_min = 35.0f;
        t.trunk_height_max = 50.0f;
        t.trunk_width_min = 3.0f;
        t.trunk_width_max = 5.0f;
        t.needle_shape = TreeNeedle::Shape::LONG_SPIKE;
        t.needle_palette = TreeColor::NEEDLE_PINE;
        t.needle_palette_size = sizeof(TreeColor::NEEDLE_PINE) / sizeof(Color);
        t.needles_min = 30;
        t.needles_max = 60;
        return t;
    }
};

}  // namespace SSE

#endif  // SSE_DATA_TREE_TREETYPE_H