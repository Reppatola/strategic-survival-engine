#ifndef SSE_DATA_STONE_STONETYPE_H
#define SSE_DATA_STONE_STONETYPE_H

#include <cstdint>
#include <string>

#include "core/Color.h"
#include "data/stone/StoneColor.h"

namespace SSE {

struct StoneType {
    std::string name;
    const Color* palette;
    std::uint8_t palette_size;

    // --- Форма камня ---
    enum class Form : std::uint8_t {
        PEBBLE,   // галька, мелкий
        ROCK,     // валун, средний
        BOULDER,  // глыба, крупный
        SLAB      // плоская плита
    };
    Form form = Form::ROCK;

    float size_min_px = 4.0f;
    float size_max_px = 12.0f;

    // Может ли на нём расти мох
    bool can_have_moss = false;

    // --- Фабрики ---

    static StoneType granite() {
        return {"гранит",
                StoneColor::GREY,
                sizeof(StoneColor::GREY) / sizeof(Color),
                Form::ROCK,
                8.0f,
                20.0f,
                true};
    }
    static StoneType sandstone() {
        return {"песчаник",
                StoneColor::BROWN,
                sizeof(StoneColor::BROWN) / sizeof(Color),
                Form::ROCK,
                6.0f,
                15.0f,
                false};
    }
    static StoneType limestone() {
        return {"известняк",
                StoneColor::WHITE,
                sizeof(StoneColor::WHITE) / sizeof(Color),
                Form::BOULDER,
                10.0f,
                25.0f,
                false};
    }
    static StoneType slate() {
        return {"сланец",
                StoneColor::DARK,
                sizeof(StoneColor::DARK) / sizeof(Color),
                Form::SLAB,
                8.0f,
                18.0f,
                true};
    }
    static StoneType pebble() {
        return {"галька",
                StoneColor::GREY,
                sizeof(StoneColor::GREY) / sizeof(Color),
                Form::PEBBLE,
                2.0f,
                5.0f,
                false};
    }
};

}  // namespace SSE

#endif  // SSE_DATA_STONE_STONETYPE_H