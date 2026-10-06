#ifndef SSE_HERO1_HERO1_H
#define SSE_HERO1_HERO1_H

#include "data/characters/hero1/head.h"
#include "data/characters/hero1/torso_upper.h"
#include "data/characters/hero1/torso_lower.h"
#include "data/characters/hero1/arm_left.h"
#include "data/characters/hero1/arm_right.h"
#include "data/characters/hero1/leg_left.h"
#include "data/characters/hero1/leg_right.h"
#include "data/characters/hero1/foot_left.h"
#include "data/characters/hero1/foot_right.h"

namespace SSE::Hero1 {

// ============================================================
// ГЕРОЙ 01
// 10 частей тела. Каждая — срезы + материал + крепление.
// ============================================================

struct Hero1Info {
    const char* name        = "Герой";
    float       total_height = 175.0f;   // см
    float       total_weight = 75.0f;    // кг
};

inline constexpr Hero1Info INFO = {};

// Список всех частей — для рендера
inline constexpr const char* PART_NAMES[] = {
    "head",
    "torso_upper",
    "torso_lower",
    "arm_left",
    "arm_right",
    "leg_left",
    "leg_right",
    "foot_left",
    "foot_right",
};

inline constexpr int PART_COUNT = sizeof(PART_NAMES) / sizeof(const char*);

} // namespace SSE::Hero1

#endif
