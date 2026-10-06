#ifndef SSE_DATA_GRASS_GRASSTYPE_H
#define SSE_DATA_GRASS_GRASSTYPE_H

#include "core/Color.h"
#include "data/grass/GrassColor.h"
#include <cstdint>
#include <string>

namespace SSE {

// ============================================================
// ТИП ТРАВЫ
// Длины в ПИКСЕЛЯХ. Ячейка = 256 px, тело героя = 175 px.
// ============================================================
struct GrassType {
    std::string name;
    const Color* palette;
    std::uint8_t palette_size;

    // --- Форма ---
    std::uint8_t leaves_min = 2;
    std::uint8_t leaves_max = 3;
    float length_min_px = 8.0f;
    float length_max_px = 15.0f;

    // --- Условия появления ---
    float fertility_min = 0.0f;

    // --- Фабрики ---

    static GrassType meadow() {
        return {
            "луговая",
            GrassColor::SPRING,
            sizeof(GrassColor::SPRING) / sizeof(Color),
            2, 3, 8.0f, 15.0f, 0.3f
        };
    }

    static GrassType summer() {
        return {
            "летняя",
            GrassColor::SUMMER,
            sizeof(GrassColor::SUMMER) / sizeof(Color),
            2, 3, 10.0f, 18.0f, 0.5f
        };
    }

    static GrassType autumn() {
        return {
            "осенняя",
            GrassColor::AUTUMN,
            sizeof(GrassColor::AUTUMN) / sizeof(Color),
            2, 3, 8.0f, 14.0f, 0.3f
        };
    }

    static GrassType dry() {
        return {
            "сухая",
            GrassColor::DRY,
            sizeof(GrassColor::DRY) / sizeof(Color),
            2, 2, 6.0f, 12.0f, 0.0f
        };
    }

    static GrassType swamp() {
        return {
            "болотная",
            GrassColor::SWAMP,
            sizeof(GrassColor::SWAMP) / sizeof(Color),
            3, 4, 12.0f, 20.0f, 0.6f
        };
    }

    static GrassType forest() {
        return {
            "лесная",
            GrassColor::FOREST,
            sizeof(GrassColor::FOREST) / sizeof(Color),
            2, 3, 8.0f, 14.0f, 0.4f
        };
    }
};

} // namespace SSE

#endif
