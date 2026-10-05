#ifndef SSE_DATA_STONE_STONECOLOR_H
#define SSE_DATA_STONE_STONECOLOR_H

#include "core/Color.h"

namespace SSE {
namespace StoneColor {

// --- Серый камень (гранит, базальт) ---
inline constexpr Color GREY[] = {
    {110, 108, 105},
    {125, 120, 115},
    {100, 98, 95},
    {135, 130, 125},
};

// --- Коричневый камень (песчаник) ---
inline constexpr Color BROWN[] = {
    {140, 110, 80},
    {155, 120, 90},
    {130, 100, 75},
    {150, 115, 85},
};

// --- Белый камень (известняк, мел) ---
inline constexpr Color WHITE[] = {
    {220, 215, 205},
    {235, 230, 220},
    {210, 205, 195},
    {225, 220, 210},
};

// --- Тёмный камень (сланец, обсидиан) ---
inline constexpr Color DARK[] = {
    {55, 52, 50},
    {70, 65, 60},
    {45, 42, 40},
    {65, 60, 55},
};

// --- Мох на камне (зелёный налёт) ---
inline constexpr Color MOSS[] = {
    {70, 95, 55},
    {80, 105, 65},
    {60, 85, 45},
    {75, 100, 60},
};

}  // namespace StoneColor
}  // namespace SSE

#endif  // SSE_DATA_STONE_STONECOLOR_H