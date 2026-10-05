#ifndef SSE_DATA_TREE_TREECOLOR_H
#define SSE_DATA_TREE_TREECOLOR_H

#include "core/Color.h"

namespace SSE {
namespace TreeColor {

// ============================================================
// ЦВЕТА ДЕРЕВА
// Ствол, листья, иголки — у каждого своя палитра.
// ============================================================

// --- Кора ---
inline constexpr Color TRUNK_OAK[] = {
    {85, 60, 40},
    {90, 65, 45},
    {80, 55, 35},
    {95, 70, 50},
};
inline constexpr Color TRUNK_BIRCH[] = {
    {220, 215, 200},
    {230, 225, 210},
    {210, 205, 190},
    {225, 218, 205},
};
inline constexpr Color TRUNK_PINE[] = {
    {95, 60, 45},
    {105, 70, 55},
    {100, 65, 50},
    {110, 75, 60},
};

// --- Листья лиственных ---
inline constexpr Color LEAF_OAK_SUMMER[] = {
    {60, 120, 50},
    {70, 130, 60},
    {80, 140, 70},
    {65, 125, 55},
};
inline constexpr Color LEAF_OAK_AUTUMN[] = {
    {170, 130, 50},
    {190, 140, 60},
    {180, 110, 40},
    {160, 120, 45},
};
inline constexpr Color LEAF_BIRCH_SUMMER[] = {
    {100, 160, 70},
    {110, 170, 80},
    {120, 180, 90},
    {105, 165, 75},
};
inline constexpr Color LEAF_BIRCH_AUTUMN[] = {
    {220, 200, 100},
    {230, 210, 110},
    {210, 190, 90},
    {225, 205, 105},
};

// --- Иголки хвойных ---
inline constexpr Color NEEDLE_SPRUCE[] = {
    {30, 70, 40},
    {35, 80, 45},
    {40, 90, 50},
    {25, 65, 35},
};
inline constexpr Color NEEDLE_PINE[] = {
    {50, 100, 55},
    {55, 110, 60},
    {60, 120, 65},
    {45, 95, 50},
};

}  // namespace TreeColor
}  // namespace SSE

#endif  // SSE_DATA_TREE_TREECOLOR_H