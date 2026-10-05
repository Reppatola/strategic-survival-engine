#ifndef SSE_DATA_WATER_WATERCOLOR_H
#define SSE_DATA_WATER_WATERCOLOR_H

#include "core/Color.h"

namespace SSE {
namespace WaterColor {

// --- Чистая вода (ручей, озеро) ---
inline constexpr Color CLEAR[] = {
    {80, 140, 190},
    {90, 150, 200},
    {75, 135, 185},
    {85, 145, 195},
};

// --- Глубокая вода (океан, глубина) ---
inline constexpr Color DEEP[] = {
    {30, 70, 130},
    {40, 80, 140},
    {35, 75, 135},
    {45, 85, 145},
};

// --- Мутная вода (болото, лужа) ---
inline constexpr Color MUDDY[] = {
    {90, 100, 70},
    {100, 110, 80},
    {85, 95, 65},
    {95, 105, 75},
};

// --- Замёрзшая вода (лёд) ---
inline constexpr Color ICE[] = {
    {200, 220, 230},
    {210, 230, 240},
    {190, 210, 220},
    {205, 225, 235},
};

// --- Отражение неба (мелкая вода) ---
inline constexpr Color SKY_REFLECT[] = {
    {130, 170, 210},
    {140, 180, 220},
    {125, 165, 205},
    {135, 175, 215},
};

}  // namespace WaterColor
}  // namespace SSE

#endif  // SSE_DATA_WATER_WATERCOLOR_H