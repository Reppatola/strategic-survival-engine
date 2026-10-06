#ifndef SSE_DATA_BODY_BODYSTATE_H
#define SSE_DATA_BODY_BODYSTATE_H

#include <cstdint>

namespace SSE::Body {

// ============================================================
// СОСТОЯНИЕ ТЕЛА
// ============================================================

enum class Pose : std::uint8_t {
    STANDING,
    WALKING,
    RUNNING,
    SNEAKING,
    SITTING,
    LYING,
    CRAWLING,
    DEAD
};

enum class Facing : std::uint8_t {
    N,  NE, E,  SE,
    S,  SW, W,  NW
};

struct BodyState {
    Pose   pose   = Pose::STANDING;
    Facing facing = Facing::S;

    // Угол направления (0 = юг, против часовой)
    float facing_rad = 0.0f;
    float target_rad = 0.0f;

    float anim_phase = 0.0f;   // 0..2π — фаза анимации
    float health     = 100.0f;
};

} // namespace SSE::Body

#endif
