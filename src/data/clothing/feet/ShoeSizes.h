#ifndef SSE_DATA_CLOTHING_FEET_SHOESIZES_H
#define SSE_DATA_CLOTHING_FEET_SHOESIZES_H

#include <cstdint>

namespace SSE::Clothing::Feet {

// ============================================================
// ТАБЛИЦА РАЗМЕРОВ ОБУВИ (EU)
// ============================================================

struct ShoeSize {
    std::int32_t size;             // EU: 38..46
    float foot_length;             // длина стопы, см
    float foot_width;              // ширина, см
    float foot_height;             // высота, см
};

inline constexpr ShoeSize SHOE_SIZES[] = {
    // size  length  width  height
    { 38, 24.5f, 9.5f, 5.5f },
    { 39, 25.0f, 9.7f, 5.6f },
    { 40, 25.5f, 9.8f, 5.8f },
    { 41, 26.0f, 10.0f, 6.0f },
    { 42, 26.5f, 10.1f, 6.1f },
    { 43, 27.0f, 10.3f, 6.2f },
    { 44, 27.5f, 10.5f, 6.4f },
    { 45, 28.0f, 10.7f, 6.5f },
    { 46, 28.5f, 10.9f, 6.7f },
};

inline constexpr int SHOE_SIZE_COUNT =
    sizeof(SHOE_SIZES) / sizeof(ShoeSize);

inline constexpr const ShoeSize* findShoeSize(std::int32_t size) {
    for (int i = 0; i < SHOE_SIZE_COUNT; ++i) {
        if (SHOE_SIZES[i].size == size) return &SHOE_SIZES[i];
    }
    return &SHOE_SIZES[5];   // 43 по умолчанию
}

} // namespace SSE::Clothing::Feet

#endif
