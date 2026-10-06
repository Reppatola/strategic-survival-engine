#ifndef SSE_HERO1_TORSO_LOWER_H
#define SSE_HERO1_TORSO_LOWER_H

#include "data/characters/Slice.h"
#include "data/characters/BodyPart.h"

namespace SSE::Hero1::TorsoLower {

using namespace SSE::Characters;

// ============================================================
// НИЗ ТОРСА ГЕРОЯ 01
// Живот + таз.
// Диапазон Z: 84 (бедро) → 115 (талия)
// ============================================================

inline constexpr AttachPoint ATTACH   = AttachPoint::CHEST_BOTTOM;
inline constexpr PartKind   KIND     = PartKind::TORSO_LOWER;
inline constexpr float      ATTACH_Z = 115.0f;

inline constexpr HSlice H_SLICES[] = {
    //   z      width  depth  off_x  off_y
    { 115.0f,  30.0f, 19.0f,  0.0f,  0.0f },
    { 110.0f,  28.0f, 19.0f,  0.0f,  0.0f },
    { 105.0f,  27.0f, 19.0f,  0.0f,  0.0f },  // талия — самая узкая
    { 100.0f,  27.0f, 19.0f,  0.0f,  0.0f },
    {  95.0f,  30.0f, 20.0f,  0.0f,  0.0f },
    {  92.0f,  33.0f, 21.0f,  0.0f,  0.0f },
    {  90.0f,  34.0f, 22.0f,  0.0f,  0.0f },  // таз
    {  87.0f,  34.0f, 22.0f,  0.0f,  0.0f },
    {  84.0f,  32.0f, 21.0f,  0.0f,  0.0f },
};

inline constexpr int H_SLICES_COUNT = sizeof(H_SLICES) / sizeof(HSlice);

inline constexpr VSlice V_SLICES[] = {
    //   x     height  depth  off_z  off_y
    { -17.0f, 31.0f, 12.0f,  0.0f,  0.0f },   // край таза слева
    { -10.0f, 31.0f, 19.0f,  0.0f,  0.0f },
    {   0.0f, 31.0f, 22.0f,  0.0f,  0.0f },   // центр
    {  10.0f, 31.0f, 19.0f,  0.0f,  0.0f },
    {  17.0f, 31.0f, 12.0f,  0.0f,  0.0f },   // край таза справа
};

inline constexpr int V_SLICES_COUNT = sizeof(V_SLICES) / sizeof(VSlice);

inline constexpr PartMaterial MATERIAL = {
    {  80, 100, 160, 255 },   // рубашка
    {  60,  70, 100, 255 },   // штаны (переход в таз)
    {  40,  40,  40, 255 }
};

} // namespace SSE::Hero1::TorsoLower

#endif
