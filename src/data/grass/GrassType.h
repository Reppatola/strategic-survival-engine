#ifndef SSE_DATA_GRASS_GRASSTYPE_H
#define SSE_DATA_GRASS_GRASSTYPE_H

#include <cstdint>
#include <string>

#include "core/Color.h"
#include "data/grass/GrassColor.h"

namespace SSE {

// ============================================================
// ТИП ТРАВЫ
// Описывает вид травы: как выглядит, какая палитра, какая форма.
// ============================================================
struct GrassType {
    std::string name;  // "луговая", "сухая", "болотная"
    const Color* palette;
    std::uint8_t palette_size;

    // --- Форма ---
    std::uint8_t leaves_min = 3;
    std::uint8_t leaves_max = 5;
    float length_min_px = 3.0f;
    float length_max_px = 7.0f;

    // --- Условия появления ---
    float fertility_min = 0.0f;  // минимальная плодородность земли

    // --- Фабрики ---

    static GrassType meadow() {
        return {"луговая",
                GrassColor::SPRING,
                sizeof(GrassColor::SPRING) / sizeof(Color),
                3,
                5,
                3.0f,
                7.0f,
                0.3f};
    }

    static GrassType summer() {
        return {"летняя",
                GrassColor::SUMMER,
                sizeof(GrassColor::SUMMER) / sizeof(Color),
                3,
                6,
                4.0f,
                8.0f,
                0.5f};
    }

    static GrassType autumn() {
        return {"осенняя",
                GrassColor::AUTUMN,
                sizeof(GrassColor::AUTUMN) / sizeof(Color),
                2,
                4,
                3.0f,
                6.0f,
                0.3f};
    }

    static GrassType dry() {
        return {"сухая", GrassColor::DRY, sizeof(GrassColor::DRY) / sizeof(Color), 2, 3, 2.0f, 5.0f,
                0.0f};
    }

    static GrassType swamp() {
        return {"болотная",
                GrassColor::SWAMP,
                sizeof(GrassColor::SWAMP) / sizeof(Color),
                4,
                7,
                5.0f,
                10.0f,
                0.6f};
    }

    static GrassType forest() {
        return {"лесная",
                GrassColor::FOREST,
                sizeof(GrassColor::FOREST) / sizeof(Color),
                3,
                5,
                3.0f,
                6.0f,
                0.4f};
    }
};

}  // namespace SSE

#endif  // SSE_DATA_GRASS_GRASSTYPE_H