#ifndef SSE_HERO1_TORSO_UPPER_H
#define SSE_HERO1_TORSO_UPPER_H

#include "data/characters/Slice.h"
#include "data/characters/BodyPart.h"

namespace SSE::Hero1::TorsoUpper {

using namespace SSE::Characters;

// ============================================================
// ВЕРХ ТОРСА ГЕРОЯ 01
// Грудь + плечи. Плечи — часть груди.
// Диапазон Z: 115 (талия) → 145 (шея)
// Плечи (z≈143): ширина 44 см.
// ============================================================

inline constexpr AttachPoint ATTACH   = AttachPoint::CHEST_TOP;
inline constexpr PartKind   KIND     = PartKind::TORSO_UPPER;
inline constexpr float      ATTACH_Z = 145.0f;

// --- Горизонтальные срезы ---
inline constexpr HSlice H_SLICES[] = {
    //   z      width  depth  off_x  off_y
    { 145.0f,  14.0f, 11.0f,  0.0f,  0.0f },  // основание шеи
    { 144.0f,  28.0f, 16.0f,  0.0f,  0.0f },  // начало плеч
    { 143.0f,  40.0f, 20.0f,  0.0f,  0.0f },  // плечи — широко
    { 141.0f,  44.0f, 22.0f,  0.0f,  0.0f },  // максимум
    { 138.0f,  44.0f, 22.0f,  0.0f,  0.0f },
    { 134.0f,  43.0f, 22.0f,  0.0f,  0.0f },
    { 130.0f,  42.0f, 22.0f,  0.0f,  0.0f },
    { 125.0f,  40.0f, 22.0f,  0.0f,  0.0f },
    { 120.0f,  36.0f, 21.0f,  0.0f,  0.0f },
    { 117.0f,  32.0f, 20.0f,  0.0f,  0.0f },
    { 115.0f,  30.0f, 19.0f,  0.0f,  0.0f },
};

inline constexpr int H_SLICES_COUNT = sizeof(H_SLICES) / sizeof(HSlice);

inline constexpr VSlice V_SLICES[] = {
    { -22.0f, 30.0f, 10.0f,  0.0f,  0.0f },
    { -15.0f, 30.0f, 20.0f,  0.0f,  0.0f },
    {  -8.0f, 30.0f, 22.0f,  0.0f,  0.0f },
    {   0.0f, 30.0f, 22.0f,  0.0f,  0.0f },
    {   8.0f, 30.0f, 22.0f,  0.0f,  0.0f },
    {  15.0f, 30.0f, 20.0f,  0.0f,  0.0f },
    {  22.0f, 30.0f, 10.0f,  0.0f,  0.0f },
};

inline constexpr int V_SLICES_COUNT = sizeof(V_SLICES) / sizeof(VSlice);

inline constexpr PartMaterial MATERIAL = {
    {  80, 100, 160, 255 },
    { 220, 180, 140, 255 },
    {  40,  40,  40, 255 }
};

} // namespace SSE::Hero1::TorsoUpper

#endif
