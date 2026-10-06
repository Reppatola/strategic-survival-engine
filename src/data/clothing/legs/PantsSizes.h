#ifndef SSE_DATA_CLOTHING_LEGS_PANTSSIZES_H
#define SSE_DATA_CLOTHING_LEGS_PANTSSIZES_H

#include <cstdint>

namespace SSE::Clothing::Legs {

// ============================================================
// ТАБЛИЦА РАЗМЕРОВ МУЖСКИХ БРЮК
// Полуобхваты = половина измерения. Умножаем на 2 для полного.
// ============================================================

struct PantsSize {
    std::int32_t size;             // 50..68
    float waist_half;              // полуобхват талии
    float hips_half;               // полуобхват бёдер
    float length_side;             // длина по боковому шву
    float length_inner;            // длина внутренняя
    float thigh_half;              // полуобхват бедра
};

inline constexpr PantsSize PANTS_SIZES[] = {
    // size  waist  hips  side  inner  thigh
    { 50, 48.0f, 56.0f, 98.0f, 68.0f, 34.0f },
    { 52, 50.0f, 58.0f, 98.0f, 68.0f, 35.0f },
    { 54, 52.0f, 60.0f, 98.0f, 68.0f, 36.0f },
    { 56, 54.0f, 62.0f, 98.0f, 68.0f, 37.0f },
    { 58, 56.0f, 65.0f, 98.0f, 68.0f, 38.0f },
    { 60, 58.0f, 67.0f, 98.0f, 68.0f, 39.0f },
    { 62, 60.0f, 69.0f, 98.0f, 68.0f, 40.0f },
    { 64, 62.0f, 71.0f, 98.0f, 68.0f, 41.0f },
};

inline constexpr int PANTS_SIZE_COUNT =
    sizeof(PANTS_SIZES) / sizeof(PantsSize);

inline constexpr const PantsSize* findPantsSize(std::int32_t size) {
    for (int i = 0; i < PANTS_SIZE_COUNT; ++i) {
        if (PANTS_SIZES[i].size == size) return &PANTS_SIZES[i];
    }
    return &PANTS_SIZES[0];   // 50 по умолчанию
}

} // namespace SSE::Clothing::Legs

#endif
