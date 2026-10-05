#ifndef SSE_DATA_OBJECTS_ZOMBIE_H
#define SSE_DATA_OBJECTS_ZOMBIE_H

#include <cstdint>
#include <string>

#include "core/Color.h"

namespace SSE {

// ============================================================
// ЗОМБИ
// Сущность мира. Данные: позиция, состояние, здоровье.
// ============================================================
struct Zombie {
    // --- Идентификация ---
    std::uint32_t id = 0;

    // --- Позиция ---
    float x = 0.0f;
    float y = 0.0f;

    // --- Состояние ---
    enum class State : std::uint8_t {
        IDLE,    // стоит
        WANDER,  // бродит
        HUNT,    // идёт на цель
        ATTACK,  // атакует
        EAT,     // ест
        DEAD
    };
    State state = State::WANDER;

    // --- Характеристики ---
    float health = 100.0f;
    float speed = 1.5f;  // пикселей/сек
    float perception_radius = 200.0f;
    float hearing_radius = 300.0f;

    // --- Память ---
    float last_known_target_x = 0.0f;
    float last_known_target_y = 0.0f;
    bool has_target_memory = false;

    // --- Внешность ---
    Color body_color = {90, 110, 80};
    Color head_color = {130, 120, 100};
    float body_radius_px = 4.0f;
    float head_radius_px = 3.0f;
};

}  // namespace SSE

#endif