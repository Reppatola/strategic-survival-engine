#ifndef SSE_DATA_OBJECTS_BUILDING_H
#define SSE_DATA_OBJECTS_BUILDING_H

#include <cstdint>
#include <string>

#include "core/Color.h"

namespace SSE {

// ============================================================
// СТРОЕНИЕ — дом, амбар, стена, башня.
// Вид сверху: прямоугольник (или несколько).
// ============================================================
struct Building {
    std::uint32_t id = 0;

    std::int32_t x = 0;
    std::int32_t y = 0;

    std::int32_t width_px = 40;
    std::int32_t height_px = 30;

    enum class Type : std::uint8_t {
        HOUSE,  // дом
        BARN,   // амбар
        WALL,   // стена
        TOWER,  // башня
        RUIN    // руины
    };
    Type type = Type::HOUSE;

    // Внешность
    Color wall_color = {150, 130, 100};
    Color roof_color = {110, 60, 50};
    Color edge_color = {60, 40, 30};

    float elevation_px = 12.0f;   // высота объекта над землёй (эффект объёма) эффект объёма)

    // Состояние
    bool destroyed = false;
    float integrity = 1.0f;  // 0..1
};

}  // namespace SSE

#endif
