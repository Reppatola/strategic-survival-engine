#ifndef SSE_HERO1_FOOT_LEFT_H
#define SSE_HERO1_FOOT_LEFT_H

#include "data/characters/Slice.h"
#include "data/characters/BodyPart.h"

namespace SSE::Hero1::FootLeft {

using namespace SSE::Characters;

// ============================================================
// ЛЕВАЯ СТОПА ГЕРОЯ 01
// 26 см длина × 10 см ширина × 6 см высота.
//
// Стопа СМЕЩЕНА ВПЕРЁД от точки крепления (ankle):
//   пятка (сзади):   8 см (offset_y = 5 - 13 = -8)
//   носок (спереди): 18 см (offset_y = 5 + 13 = +18)
// ============================================================

inline constexpr AttachPoint ATTACH   = AttachPoint::ANKLE_L;
inline constexpr PartKind   KIND     = PartKind::FOOT;
inline constexpr float      ATTACH_Z = 6.0f;
inline constexpr float      ATTACH_X = -8.5f;

inline constexpr HSlice H_SLICES[] = {
    //   z     width  depth  off_x  off_y
    {   6.0f,  10.0f, 26.0f,  0.0f,  5.0f },   // смещено вперёд на 5 см
    {   4.0f,  10.0f, 26.0f,  0.0f,  5.0f },
    {   2.0f,   9.5f, 25.0f,  0.0f,  5.0f },
    {   0.0f,   9.0f, 24.0f,  0.0f,  5.0f },
};

inline constexpr int H_SLICES_COUNT = sizeof(H_SLICES) / sizeof(HSlice);

inline constexpr VSlice V_SLICES[] = {
    { -5.0f,   6.0f, 26.0f,  0.0f,  5.0f },
    {  0.0f,   6.0f, 26.0f,  0.0f,  5.0f },
    {  5.0f,   6.0f, 26.0f,  0.0f,  5.0f },
};

inline constexpr int V_SLICES_COUNT = sizeof(V_SLICES) / sizeof(VSlice);

inline constexpr PartMaterial MATERIAL = {
    {  40,  30,  25, 255 },
    {  20,  15,  10, 255 },
    {  60,  50,  40, 255 }
};

} // namespace SSE::Hero1::FootLeft

#endif
