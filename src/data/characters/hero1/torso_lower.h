#ifndef SSE_HERO1_TORSO_LOWER_H
#define SSE_HERO1_TORSO_LOWER_H

#include "data/characters/Slice.h"
#include "data/characters/BodyPart.h"

namespace SSE::Hero1::TorsoLower {

using namespace SSE::Characters;

// ============================================================
// НИЗ ТОРСА ГЕРОЯ 01
// Живот + таз. Скрыт под плечами при виде сверху.
// ============================================================

inline constexpr AttachPoint ATTACH   = AttachPoint::CHEST_BOTTOM;
inline constexpr PartKind   KIND     = PartKind::TORSO_LOWER;
inline constexpr float      ATTACH_Z = 115.0f;
inline constexpr float      ATTACH_X = 0.0f;

inline constexpr HSlice H_SLICES[] = {
    //   z      width  depth  off_x  off_y
    { 115.0f,  28.0f, 16.0f,  0.0f,  0.0f },
    { 110.0f,  27.0f, 16.0f,  0.0f,  0.0f },
    { 105.0f,  26.0f, 16.0f,  0.0f,  0.0f },  // талия
    { 100.0f,  26.0f, 16.0f,  0.0f,  0.0f },
    {  95.0f,  28.0f, 17.0f,  0.0f,  0.0f },
    {  92.0f,  30.0f, 18.0f,  0.0f,  0.0f },
    {  90.0f,  32.0f, 18.0f,  0.0f,  0.0f },  // таз
    {  87.0f,  32.0f, 18.0f,  0.0f,  0.0f },
    {  84.0f,  30.0f, 17.0f,  0.0f,  0.0f },
};

inline constexpr int H_SLICES_COUNT = sizeof(H_SLICES) / sizeof(HSlice);

inline constexpr VSlice V_SLICES[] = {
    { -16.0f, 31.0f, 10.0f,  0.0f,  0.0f },
    {  -8.0f, 31.0f, 16.0f,  0.0f,  0.0f },
    {   0.0f, 31.0f, 18.0f,  0.0f,  0.0f },
    {   8.0f, 31.0f, 16.0f,  0.0f,  0.0f },
    {  16.0f, 31.0f, 10.0f,  0.0f,  0.0f },
};

inline constexpr int V_SLICES_COUNT = sizeof(V_SLICES) / sizeof(VSlice);

inline constexpr PartMaterial MATERIAL = {
    {  80, 100, 160, 255 },
    {  60,  70, 100, 255 },
    {  40,  40,  40, 255 }
};

} // namespace SSE::Hero1::TorsoLower

#endif
