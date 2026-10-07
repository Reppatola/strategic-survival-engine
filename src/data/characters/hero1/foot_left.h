#ifndef SSE_HERO1_FOOT_LEFT_H
#define SSE_HERO1_FOOT_LEFT_H

#include "data/characters/Slice.h"
#include "data/characters/BodyPart.h"

namespace SSE::Hero1::FootLeft {

using namespace SSE::Characters;

// ============================================================
// ЛЕВАЯ СТОПА — под телом, носки чуть видны впереди.
// ============================================================

inline constexpr AttachPoint ATTACH   = AttachPoint::ANKLE_L;
inline constexpr PartKind   KIND     = PartKind::FOOT;
inline constexpr float      ATTACH_Z = 6.0f;
inline constexpr float      ATTACH_X = -8.5f;

inline constexpr HSlice H_SLICES[] = {
    //   z     width  depth  off_x  off_y
    {   6.0f,   9.0f, 22.0f,  0.0f,  2.0f },
    {   4.0f,   9.0f, 22.0f,  0.0f,  2.0f },
    {   2.0f,   8.5f, 21.0f,  0.0f,  2.0f },
    {   0.0f,   8.0f, 20.0f,  0.0f,  2.0f },
};

inline constexpr int H_SLICES_COUNT = sizeof(H_SLICES) / sizeof(HSlice);

inline constexpr VSlice V_SLICES[] = {
    { -4.5f,   6.0f, 22.0f,  0.0f,  2.0f },
    {  0.0f,   6.0f, 22.0f,  0.0f,  2.0f },
    {  4.5f,   6.0f, 22.0f,  0.0f,  2.0f },
};

inline constexpr int V_SLICES_COUNT = sizeof(V_SLICES) / sizeof(VSlice);

inline constexpr PartMaterial MATERIAL = {
    {  40,  30,  25, 255 },
    {  20,  15,  10, 255 },
    {  60,  50,  40, 255 }
};

} // namespace SSE::Hero1::FootLeft

#endif
