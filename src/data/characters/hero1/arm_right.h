#ifndef SSE_HERO1_ARM_RIGHT_H
#define SSE_HERO1_ARM_RIGHT_H

#include "data/characters/Slice.h"
#include "data/characters/BodyPart.h"

namespace SSE::Hero1::ArmRight {

using namespace SSE::Characters;

inline constexpr AttachPoint ATTACH   = AttachPoint::SHOULDER_R;
inline constexpr PartKind   KIND     = PartKind::ARM_UPPER;
inline constexpr float      ATTACH_Z = 143.0f;
inline constexpr float      ATTACH_X = 16.0f;   // внутри плеча

inline constexpr HSlice H_SLICES[] = {
    { 143.0f,  14.0f, 14.0f,  0.0f,  0.0f },
    { 138.0f,  12.0f, 11.0f,  0.0f,  0.0f },
    { 132.0f,  11.0f, 10.0f,  0.0f,  0.0f },
    { 125.0f,  10.0f,  9.0f,  0.0f,  0.0f },
    { 118.0f,   9.0f,  8.5f,  0.0f,  0.0f },
    { 113.0f,   8.5f,  8.0f,  0.0f,  0.0f },
    { 105.0f,   8.0f,  7.5f,  0.0f,  0.0f },
    {  95.0f,   7.5f,  7.0f,  0.0f,  0.0f },
    {  90.0f,   7.0f,  6.5f,  0.0f,  0.0f },
    {  87.0f,   6.5f,  6.0f,  0.0f,  0.0f },
};

inline constexpr int H_SLICES_COUNT = sizeof(H_SLICES) / sizeof(HSlice);

inline constexpr VSlice V_SLICES[] = {
    { -7.0f,  56.0f,  9.0f,  0.0f,  0.0f },
    {  0.0f,  56.0f, 14.0f,  0.0f,  0.0f },
    {  7.0f,  56.0f,  9.0f,  0.0f,  0.0f },
};

inline constexpr int V_SLICES_COUNT = sizeof(V_SLICES) / sizeof(VSlice);

inline constexpr PartMaterial MATERIAL = {
    {  80, 100, 160, 255 },
    { 220, 180, 140, 255 },
    {  40,  40,  40, 255 }
};

} // namespace SSE::Hero1::ArmRight

#endif
