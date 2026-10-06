#ifndef SSE_DATA_BODY_BODYSTATE_H
#define SSE_DATA_BODY_BODYSTATE_H

#include <cstdint>

namespace SSE::Body {

// ============================================================
// СОСТОЯНИЕ ТЕЛА
// Данные знают — что тело делает сейчас.
// Наблюдатель видит только результат.
// ============================================================

enum class Pose : std::uint8_t {
    STANDING,     // стоит
    WALKING,      // идёт
    RUNNING,      // бежит
    SNEAKING,     // крадётся
    SITTING,      // сидит
    LYING,        // лежит
    CRAWLING,     // ползёт
    DEAD          // мёртв
};

enum class Facing : std::uint8_t {
    N,  NE, E,  SE,
    S,  SW, W,  NW
};

struct BodyState {
    Pose   pose   = Pose::STANDING;
    Facing facing = Facing::S;

    float anim_phase = 0.0f;   // 0..1 — фаза анимации
    float health     = 100.0f;
};

} // namespace SSE::Body

#endif
