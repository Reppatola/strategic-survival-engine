#ifndef SSE_DATA_BODY_BODYPROJECTION_H
#define SSE_DATA_BODY_BODYPROJECTION_H

#include "data/body/BodyState.h"
#include <cstdint>

namespace SSE::Body {

// ============================================================
// ПРОЕКЦИЯ ТЕЛА — что видит наблюдатель СВЕРХУ
//
// Наблюдатель НЕ видит тело целиком.
// Он видит только то, что обращено к нему сверху.
//
// Проекция = результат (pose, facing) → видимые части.
// ============================================================

// Какие части тела видны сверху
struct VisibleParts {
    bool head    = true;
    bool shoulders = true;
    bool back    = true;   // спина (если стоит спиной)
    bool chest   = false;  // грудь (если стоит лицом)
    bool arms    = false;  // руки (если вытянуты)
    bool feet    = false;  // стопы (если выступают)
    bool knees   = false;  // колени (если сидит/идёт)
};

// ============================================================
// Вычисление проекции по состоянию
// Пока простые правила — потом расширим.
// ============================================================
inline VisibleParts project(const BodyState& state) {
    VisibleParts v;

    switch (state.pose) {
        case Pose::STANDING:
            v.head = true;
            v.shoulders = true;
            v.back = (state.facing == Facing::N ||
                      state.facing == Facing::NE ||
                      state.facing == Facing::NW);
            v.chest = !v.back;
            v.arms = false;
            v.feet = false;
            break;

        case Pose::WALKING:
        case Pose::RUNNING:
            v.head = true;
            v.shoulders = true;
            v.back = (state.facing == Facing::N ||
                      state.facing == Facing::NE ||
                      state.facing == Facing::NW);
            v.chest = !v.back;
            v.arms = true;
            v.feet = true;
            v.knees = true;
            break;

        case Pose::SNEAKING:
            v.head = true;
            v.shoulders = true;
            v.arms = true;
            v.knees = true;
            break;

        case Pose::SITTING:
            v.head = true;
            v.shoulders = true;
            v.knees = true;
            break;

        case Pose::LYING:
            v.head = true;
            v.arms = true;
            v.feet = true;
            break;

        case Pose::CRAWLING:
            v.head = true;
            v.shoulders = true;
            v.arms = true;
            v.knees = true;
            break;

        case Pose::DEAD:
            v.head = true;
            v.arms = true;
            v.feet = true;
            break;
    }

    return v;
}

} // namespace SSE::Body

#endif
