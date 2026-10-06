#ifndef SSE_DATA_CLOTHING_TORSO_HOODIESIZES_H
#define SSE_DATA_CLOTHING_TORSO_HOODIESIZES_H

#include <cstdint>

namespace SSE::Clothing::Torso {

// ============================================================
// ТАБЛИЦА РАЗМЕРОВ МУЖСКИХ ТОЛСТОВОК
// Из реальных размерных сеток.
// ============================================================

struct HoodieSize {
    std::int32_t size;              // 38..62
    float body_height;              // рост, см
    float chest_width;              // ширина изделия = обхват груди
    float body_length;              // длина от плеча
    float sleeve_length;            // рукав от плеча
};

inline constexpr HoodieSize HOODIE_SIZES[] = {
    // size  body_h  chest_w  length  sleeve
    { 38, 158.0f, 47.0f, 62.0f, 61.0f },
    { 40, 164.0f, 48.0f, 63.0f, 64.0f },
    { 42, 170.0f, 50.0f, 64.0f, 65.0f },
    { 44, 176.0f, 52.0f, 66.0f, 66.0f },
    { 46, 176.0f, 54.0f, 67.0f, 69.0f },
    { 48, 176.0f, 56.0f, 67.0f, 70.0f },
    { 50, 176.0f, 58.0f, 68.0f, 70.0f },
    { 52, 176.0f, 60.0f, 68.0f, 70.0f },
    { 54, 176.0f, 62.0f, 68.0f, 70.0f },
    { 56, 176.0f, 64.0f, 68.0f, 70.0f },
    { 58, 176.0f, 66.0f, 68.0f, 71.0f },
    { 60, 176.0f, 68.0f, 69.0f, 71.0f },
    { 62, 176.0f, 71.0f, 70.0f, 72.0f },
};

inline constexpr int HOODIE_SIZE_COUNT =
    sizeof(HOODIE_SIZES) / sizeof(HoodieSize);

inline constexpr const HoodieSize* findHoodieSize(std::int32_t size) {
    for (int i = 0; i < HOODIE_SIZE_COUNT; ++i) {
        if (HOODIE_SIZES[i].size == size) return &HOODIE_SIZES[i];
    }
    return &HOODIE_SIZES[4];   // 46 по умолчанию
}

} // namespace SSE::Clothing::Torso

#endif
