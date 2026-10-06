#ifndef SSE_HERO1_HEAD_H
#define SSE_HERO1_HEAD_H

#include "data/characters/Slice.h"
#include "data/characters/BodyPart.h"

namespace SSE::Hero1::Head {

using namespace SSE::Characters;

// ============================================================
// ГОЛОВА ГЕРОЯ 01
//
// Диапазон Z: 146 (низ) → 175 (макушка).
// Все срезы сдвинуты НАЗАД (off_y = -2):
//   позвоночник сзади от центра груди.
//   затылок — ровно с границей спины.
//   лицо — выступает вперёд.
// ============================================================

inline constexpr AttachPoint ATTACH   = AttachPoint::NECK;
inline constexpr PartKind   KIND     = PartKind::HEAD;
inline constexpr float      ATTACH_Z = 145.0f;
inline constexpr float      ATTACH_X = 0.0f;

inline constexpr HSlice H_SLICES[] = {
    //   z      width  depth  off_x  off_y
    { 175.0f,   8.0f, 10.0f,  0.0f, -2.0f },  // макушка — сдвинута назад
    { 174.0f,  10.0f, 13.0f,  0.0f, -2.0f },
    { 172.0f,  13.0f, 16.0f,  0.0f, -2.0f },
    { 170.0f,  15.0f, 18.0f,  0.0f, -2.0f },
    { 168.0f,  16.0f, 19.5f,  0.0f, -2.0f },
    { 165.0f,  16.0f, 20.0f,  0.0f, -2.0f },
    { 162.0f,  16.0f, 20.0f,  0.0f, -1.8f },
    { 160.0f,  15.5f, 20.0f,  0.0f, -1.6f },
    { 158.0f,  15.0f, 19.5f,  0.0f, -1.2f },
    { 156.0f,  14.0f, 18.5f,  0.0f, -0.8f },
    { 154.0f,  13.0f, 17.0f,  0.0f, -0.5f },
    { 152.0f,  12.0f, 15.0f,  0.0f, -0.2f },
    { 149.0f,  13.0f, 14.0f,  0.0f,  0.0f },
    { 146.0f,  14.0f, 13.0f,  0.0f,  0.0f },  // низ — встык
};

inline constexpr int H_SLICES_COUNT = sizeof(H_SLICES) / sizeof(HSlice);

inline constexpr VSlice V_SLICES[] = {
    { -8.0f,  30.0f, 12.0f,  0.0f, -2.0f },
    { -4.0f,  30.0f, 17.0f,  0.0f, -2.0f },
    {  0.0f,  30.0f, 20.0f,  0.0f, -2.0f },
    {  4.0f,  30.0f, 17.0f,  0.0f, -2.0f },
    {  8.0f,  30.0f, 12.0f,  0.0f, -2.0f },
};

inline constexpr int V_SLICES_COUNT = sizeof(V_SLICES) / sizeof(VSlice);

inline constexpr PartMaterial MATERIAL = {
    { 220, 180, 140, 255 },
    {  90,  65,  40, 255 },
    {  40,  40,  40, 255 }
};

} // namespace SSE::Hero1::Head

#endif
