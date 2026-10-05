#ifndef SSE_DATA_OBJECTS_PLAYER_H
#define SSE_DATA_OBJECTS_PLAYER_H

#include <cstdint>
#include <string>

#include "core/Color.h"

namespace SSE {

// ============================================================
// ИГРОК — персонаж наблюдателя.
// Игрок — не наблюдатель. Игрок — тело в мире.
// ============================================================
struct Player {
    std::uint32_t id = 0;

    float x = 0.0f;
    float y = 0.0f;

    float speed = 3.0f;           // пикселей/сек
    float look_angle_rad = 0.0f;  // куда смотрит

    // --- Здоровье ---
    float health = 100.0f;
    float max_health = 100.0f;

    // --- Восприятие (радиусы чувств) ---
    float vision_radius = 250.0f;
    float hearing_radius = 400.0f;

    // --- Привязка (точка возрождения) ---
    float spawn_x = 0.0f;
    float spawn_y = 0.0f;

    // --- Внешность ---
    Color body_color = {240, 220, 100};
    float body_radius_px = 6.0f;
};

}  // namespace SSE

#endif