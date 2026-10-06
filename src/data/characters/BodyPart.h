#ifndef SSE_DATA_CHARACTERS_BODYPART_H
#define SSE_DATA_CHARACTERS_BODYPART_H

#include "data/characters/Slice.h"
#include "core/Color.h"
#include <cstdint>

namespace SSE::Characters {

// ============================================================
// ЧАСТЬ ТЕЛА
// Каждая часть — это:
//   - горизонтальные срезы (форма сверху вниз)
//   - вертикальные срезы (форма слева направо)
//   - точка крепления к скелету (в мировых координатах)
//   - материал (цвета)
// ============================================================

// Куда часть крепится в скелете
enum class AttachPoint : std::uint8_t {
    NONE,           // корневая часть (низ тела)
    NECK,           // к шее (голова)
    CHEST_TOP,      // к верхней части груди
    CHEST_BOTTOM,   // к нижней части груди (талия)
    SHOULDER_L,     // к левому плечу
    SHOULDER_R,     // к правому плечу
    ELBOW_L,        // к левому локтю
    ELBOW_R,        // к правому локтю
    HIP_L,          // к левому бедру
    HIP_R,          // к правому бедру
    KNEE_L,         // к левому колену
    KNEE_R,         // к правому колену
    ANKLE_L,        // к левой стопе
    ANKLE_R         // к правой стопе
};

// Что это за часть (для материала)
enum class PartKind : std::uint8_t {
    HEAD,           // голова (кожа + волосы)
    TORSO_UPPER,    // верх торса (грудь, одежда)
    TORSO_LOWER,    // низ торса (живот, пояс)
    ARM_UPPER,      // плечо
    ARM_LOWER,      // предплечье
    HAND,           // кисть
    LEG_UPPER,      // бедро
    LEG_LOWER,      // голень
    FOOT,           // стопа
    BACKPACK,       // рюкзак
    WEAPON,         // оружие
    HELMET          // шлем
};

// Материал части — какие цвета использовать
struct PartMaterial {
    Color primary   = {220, 180, 140, 255};  // кожа/основной
    Color secondary = { 90,  65,  40, 255};  // волосы/тени
    Color accent    = { 40,  40,  40, 255};  // детали
};

} // namespace SSE::Characters

#endif
