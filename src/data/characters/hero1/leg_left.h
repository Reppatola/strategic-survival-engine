#ifndef SSE_HERO1_LEG_LEFT_H
#define SSE_HERO1_LEG_LEFT_H

#include "data/characters/Slice.h"
#include "data/characters/BodyPart.h"

namespace SSE::Hero1::LegLeft {

using namespace SSE::Characters;

// ============================================================
// ЛЕВАЯ НОГА ГЕРОЯ 01
// Бедро (Z=84) → колено (Z=48) → голень → стопа (Z=6)
// ============================================================

inline constexpr AttachPoint ATTACH   = AttachPoint::HIP_L;
inline constexpr PartKind   KIND     = PartKind::LEG_UPPER;
inline constexpr float      ATTACH_Z = 84.0f;
inline constexpr float      ATTACH_X = -8.5f;   // левое бедро

inline constexpr HSlice H_SLICES[] = {
    //   z      width  depth  off_x  off_y
    {  84.0f,  16.0f, 16.0f,  0.0f,  0.0f },   // бедро
    {  75.0f,  15.0f, 15.0f,  0.0f,  0.0f },
    {  65.0f,  13.0f, 13.0f,  0.0f,  0.0f },
    {  55.0f,  11.5f, 11.5f,  0.0f,  0.0f },
    {  48.0f,  11.0f, 11.0f,  0.0f,  0.0f },   // колено
    {  42.0f,  10.5f, 10.5f,  0.0f,  0.0f },
    {  35.0f,  10.0f, 10.0f,  0.0f,  0.0f },
    {  25.0f,   9.0f,  9.0f,  0.0f,  0.0f },
    {  15.0f,   8.0f,  8.0f,  0.0f,  0.0f },
    {   6.0f,   7.0f,  7.0f,  0.0f,  0.0f },   // низ голени
};

inline constexpr int H_SLICES_COUNT = sizeof(H_SLICES) / sizeof(HSlice);

inline constexpr VSlice V_SLICES[] = {
    { -8.0f,  78.0f,  9.0f,  0.0f,  0.0f },
    {  0.0f,  78.0f, 16.0f,  0.0f,  0.0f },
    {  8.0f,  78.0f,  9.0f,  0.0f,  0.0f },
};

inline constexpr int V_SLICES_COUNT = sizeof(V_SLICES) / sizeof(VSlice);

inline constexpr PartMaterial MATERIAL = {
    {  60,  70, 100, 255 },   // штаны
    {  40,  30,  25, 255 },   // ботинок
    {  40,  40,  40, 255 }
};

} // namespace SSE::Hero1::LegLeft

#endif
