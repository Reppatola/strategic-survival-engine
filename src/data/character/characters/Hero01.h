#ifndef SSE_DATA_CHARACTER_CHARACTERS_HERO01_H
#define SSE_DATA_CHARACTER_CHARACTERS_HERO01_H

#include "data/character/Character.h"

namespace SSE::Characters {

// ============================================================
// ГЕРОЙ 01 — стандартный мужчина 175 см
// Одет: кепка, толстовка, брюки, ботинки.
// ============================================================
inline Character hero01() {
    Character c;

    c.name   = "Герой";
    c.gender = "male";

    c.anatomy = Body::STANDARD_MALE;

    c.state.pose   = Body::Pose::STANDING;
    c.state.facing = Body::Facing::S;
    c.buildSkeleton(0.0f);

    // Одежда
    c.outfit.hat_size     = 57;
    c.outfit.hat_color    = {60, 40, 25, 255};

    c.outfit.hoodie_size  = 46;
    c.outfit.hoodie_color = {80, 100, 160, 255};

    c.outfit.pants_size   = 50;
    c.outfit.pants_color  = {60, 70, 100, 255};

    c.outfit.shoe_size    = 43;
    c.outfit.shoe_color   = {40, 30, 25, 255};

    return c;
}

} // namespace SSE::Characters

#endif
