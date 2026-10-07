#ifndef SSE_HERO1_HEAD_H
#define SSE_HERO1_HEAD_H

#include "data/characters/Slice.h"
#include "data/characters/BodyPart.h"

namespace SSE::Hero1::Head {

using namespace SSE::Characters;

// ============================================================
// ГОЛОВА ГЕРОЯ 01 — чуть крупнее
// Ширина: 15 см. Глубина: 17 см.
// ============================================================

inline constexpr AttachPoint ATTACH   = AttachPoint::NECK;
inline constexpr PartKind   KIND     = PartKind::HEAD;
inline constexpr float      ATTACH_Z = 145.0f;
inline constexpr float      ATTACH_X = 0.0f;

inline constexpr HSlice H_SLICES[] = {
    //   z      width  depth  off_x  off_y
    { 175.0f,   7.5f,  9.0f,  0.0f, -1.5f },  // макушка
    { 172.0f,  11.0f, 13.0f,  0.0f, -1.5f },
    { 168.0f,  13.5f, 16.0f,  0.0f, -1.5f },
    { 165.0f,  15.0f, 17.0f,  0.0f, -1.5f },  // максимум
    { 160.0f,  15.0f, 17.0f,  0.0f, -1.2f },
    { 156.0f,  14.5f, 16.5f,  0.0f, -0.8f },
    { 152.0f,  14.0f, 15.5f,  0.0f, -0.3f },
    { 148.0f,  14.5f, 15.0f,  0.0f,  0.0f },  // переход в плечи
    { 146.0f,  15.0f, 14.0f,  0.0f,  0.0f },
};

inline constexpr int H_SLICES_COUNT = sizeof(H_SLICES) / sizeof(HSlice);

inline constexpr VSlice V_SLICES[] = {
    { -7.5f,  30.0f, 10.0f,  0.0f, -1.5f },
    { -4.0f,  30.0f, 14.0f,  0.0f, -1.5f },
    {  0.0f,  30.0f, 17.0f,  0.0f, -1.5f },
    {  4.0f,  30.0f, 14.0f,  0.0f, -1.5f },
    {  7.5f,  30.0f, 10.0f,  0.0f, -1.5f },
};

inline constexpr int V_SLICES_COUNT = sizeof(V_SLICES) / sizeof(VSlice);

inline constexpr PartMaterial MATERIAL = {
    { 220, 180, 140, 255 },
    {  90,  65,  40, 255 },
    {  40,  40,  40, 255 }
};

} // namespace SSE::Hero1::Head

#endif
