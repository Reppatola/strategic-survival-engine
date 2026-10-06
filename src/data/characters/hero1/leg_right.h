#ifndef SSE_HERO1_LEG_RIGHT_H
#define SSE_HERO1_LEG_RIGHT_H

#include "data/characters/Slice.h"
#include "data/characters/BodyPart.h"

namespace SSE::Hero1::LegRight {

using namespace SSE::Characters;

inline constexpr AttachPoint ATTACH   = AttachPoint::HIP_R;
inline constexpr PartKind   KIND     = PartKind::LEG_UPPER;
inline constexpr float      ATTACH_Z = 84.0f;
inline constexpr float      ATTACH_X = 8.5f;   // правое бедро

inline constexpr HSlice H_SLICES[] = {
    {  84.0f,  16.0f, 16.0f,  0.0f,  0.0f },
    {  75.0f,  15.0f, 15.0f,  0.0f,  0.0f },
    {  65.0f,  13.0f, 13.0f,  0.0f,  0.0f },
    {  55.0f,  11.5f, 11.5f,  0.0f,  0.0f },
    {  48.0f,  11.0f, 11.0f,  0.0f,  0.0f },
    {  42.0f,  10.5f, 10.5f,  0.0f,  0.0f },
    {  35.0f,  10.0f, 10.0f,  0.0f,  0.0f },
    {  25.0f,   9.0f,  9.0f,  0.0f,  0.0f },
    {  15.0f,   8.0f,  8.0f,  0.0f,  0.0f },
    {   6.0f,   7.0f,  7.0f,  0.0f,  0.0f },
};

inline constexpr int H_SLICES_COUNT = sizeof(H_SLICES) / sizeof(HSlice);

inline constexpr VSlice V_SLICES[] = {
    { -8.0f,  78.0f,  9.0f,  0.0f,  0.0f },
    {  0.0f,  78.0f, 16.0f,  0.0f,  0.0f },
    {  8.0f,  78.0f,  9.0f,  0.0f,  0.0f },
};

inline constexpr int V_SLICES_COUNT = sizeof(V_SLICES) / sizeof(VSlice);

inline constexpr PartMaterial MATERIAL = {
    {  60,  70, 100, 255 },
    {  40,  30,  25, 255 },
    {  40,  40,  40, 255 }
};

} // namespace SSE::Hero1::LegRight

#endif
