#ifndef SSE_DATA_CLOTHING_HEADWEAR_HATSIZES_H
#define SSE_DATA_CLOTHING_HEADWEAR_HATSIZES_H

#include <cstdint>

namespace SSE::Clothing::Headwear {

// ============================================================
// ТАБЛИЦА РАЗМЕРОВ ГОЛОВНЫХ УБОРОВ
// Размер = обхват головы в см.
// Ширина/глубина вычислены по формуле эллипса.
// ============================================================

struct HatSize {
    std::int32_t size;              // 54..65 (обхват, см)
    float        circumference;     // обхват
    float        width;             // ширина (между ушами)
    float        depth;             // глубина (лоб → затылок)
    const char*  label;             // XXS..XXXL
};

inline constexpr HatSize HAT_SIZES[] = {
    // size  circumference   width   depth   label
    { 54, 54.0f, 15.5f, 18.9f, "XXS" },
    { 55, 55.0f, 15.8f, 19.3f, "XS"  },
    { 56, 56.0f, 16.1f, 19.6f, "S"   },
    { 57, 57.0f, 16.3f, 20.0f, "M"   },
    { 58, 58.0f, 16.6f, 20.3f, "L"   },
    { 59, 59.0f, 16.9f, 20.7f, "XL"  },
    { 60, 60.0f, 17.2f, 21.0f, "XXL" },
    { 61, 61.0f, 17.5f, 21.4f, "XXL" },
    { 62, 62.0f, 17.8f, 21.7f, "XXXL" },
    { 63, 63.0f, 18.1f, 22.1f, "XXXL" },
    { 64, 64.0f, 18.4f, 22.4f, "XXXXL" },
    { 65, 65.0f, 18.7f, 22.8f, "XXXXL" },
};

inline constexpr int HAT_SIZE_COUNT =
    sizeof(HAT_SIZES) / sizeof(HatSize);

// Найти размер по обхвату
inline constexpr const HatSize* findHatSize(std::int32_t size) {
    for (int i = 0; i < HAT_SIZE_COUNT; ++i) {
        if (HAT_SIZES[i].size == size) return &HAT_SIZES[i];
    }
    return &HAT_SIZES[3];   // M по умолчанию
}

} // namespace SSE::Clothing::Headwear

#endif
