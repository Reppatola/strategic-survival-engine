#ifndef SSE_DATA_LAND_LANDTYPE_H
#define SSE_DATA_LAND_LANDTYPE_H

#include <cstdint>
#include <string>

#include "core/Color.h"
#include "data/land/LandColor.h"

namespace SSE {

// ============================================================
// ТИП ЗЕМЛИ
// Описывает: как выглядит, какая палитра, какая структура.
// Земля одного типа — множество патчей, каждый со своим оттенком.
// ============================================================
struct LandType {
    std::string name;           // "чернозём", "песок", "глина"
    const Color* palette;       // указатель на палитру
    std::uint8_t palette_size;  // сколько оттенков в палитре

    // Физические характеристики (влияют на движение, траву)
    float roughness = 0.0f;  // 0 = гладко, 1 = шершаво
    float wetness = 0.0f;    // 0 = сухо, 1 = мокро
    float fertility = 0.0f;  // 0 = бесплодно, 1 = плодородно

    // --- Фабрики типов ---

    static LandType chernozem() {
        return {"чернозём",
                LandColor::CHERNOZEM,
                sizeof(LandColor::CHERNOZEM) / sizeof(Color),
                0.4f,
                0.7f,
                1.0f};
    }

    static LandType drySoil() {
        return {"сухая земля",
                LandColor::DRY_SOIL,
                sizeof(LandColor::DRY_SOIL) / sizeof(Color),
                0.6f,
                0.1f,
                0.3f};
    }

    static LandType sand() {
        return {"песок", LandColor::SAND, sizeof(LandColor::SAND) / sizeof(Color), 0.3f, 0.0f,
                0.0f};
    }

    static LandType clay() {
        return {"глина", LandColor::CLAY, sizeof(LandColor::CLAY) / sizeof(Color), 0.5f, 0.4f,
                0.2f};
    }

    static LandType stony() {
        return {"каменистая",
                LandColor::STONE_GROUND,
                sizeof(LandColor::STONE_GROUND) / sizeof(Color),
                0.9f,
                0.0f,
                0.0f};
    }
};

}  // namespace SSE

#endif  // SSE_DATA_LAND_LANDTYPE_H