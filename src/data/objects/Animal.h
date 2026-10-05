#ifndef SSE_DATA_OBJECTS_ANIMAL_H
#define SSE_DATA_OBJECTS_ANIMAL_H

#include <cstdint>
#include <string>

#include "core/Color.h"

namespace SSE {

struct Animal {
    std::uint32_t id = 0;

    float x = 0.0f;
    float y = 0.0f;

    // Вид животного
    enum class Species : std::uint8_t {
        RABBIT,  // кролик — быстрый, мелкий
        DEER,    // олень — средний, пугливый
        WOLF,    // волк — быстрый, опасный
        BEAR,    // медведь — крупный, опасный
        BIRD     // птица — летающая
    };
    Species species = Species::RABBIT;

    // Состояние
    enum class State : std::uint8_t {
        GRAZE,   // пасётся
        WANDER,  // бродит
        FLEE,    // убегает
        HUNT,    // охотится
        DEAD
    };
    State state = State::WANDER;

    float health = 50.0f;
    float speed = 2.5f;
    float perception_radius = 180.0f;

    // Внешность
    Color body_color = {140, 110, 80};
    float body_radius_px = 4.0f;
};

}  // namespace SSE

#endif