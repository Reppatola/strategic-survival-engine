#ifndef SSE_DATA_OBJECTS_CYLINDER_H
#define SSE_DATA_OBJECTS_CYLINDER_H

#include <cstdint>

#include "core/Color.h"

namespace SSE {

// ============================================================
// ЦИЛИНДР — нулевая точка наблюдателя.
// Просто данные: позиция, размер, цвет, направление взгляда.
// ============================================================
struct Cylinder {
    std::int32_t x = 0;
    std::int32_t y = 0;

    std::int32_t radius_px = 12;
    std::int32_t wall_height_px = 10;  // визуальная "стенка" снизу

    Color color_top = {245, 235, 110};
    Color color_side = {95, 125, 200};
    Color color_edge = {30, 20, 5};
    Color color_marker = {220, 50, 50};

    // Направление взгляда (0 = север, по часовой)
    float look_angle_rad = 0.0f;
};

}  // namespace SSE

#endif