#ifndef SSE_DATA_WATER_WATERTYPE_H
#define SSE_DATA_WATER_WATERTYPE_H

#include <cstdint>
#include <string>

#include "core/Color.h"
#include "data/water/WaterColor.h"

namespace SSE {

struct WaterType {
    std::string name;
    const Color* palette;
    std::uint8_t palette_size;

    float speed = 0.0f;  // течение (0 = стоячая)

    enum class Form : std::uint8_t {
        PUDDLE,  // лужа — маленький круг
        POND,    // пруд — средний круг
        RIVER,   // река — длинная полоса
        LAKE,    // озеро — большой круг
        STREAM   // ручей — тонкая извилистая
    };
    Form form = Form::POND;

    static WaterType puddle() {
        return {"лужа", WaterColor::MUDDY, sizeof(WaterColor::MUDDY) / sizeof(Color), 0.0f,
                Form::PUDDLE};
    }
    static WaterType pond() {
        return {"пруд", WaterColor::CLEAR, sizeof(WaterColor::CLEAR) / sizeof(Color), 0.05f,
                Form::POND};
    }
    static WaterType river() {
        return {"река", WaterColor::CLEAR, sizeof(WaterColor::CLEAR) / sizeof(Color), 1.5f,
                Form::RIVER};
    }
    static WaterType lake() {
        return {"озеро", WaterColor::DEEP, sizeof(WaterColor::DEEP) / sizeof(Color), 0.02f,
                Form::LAKE};
    }
    static WaterType stream() {
        return {"ручей", WaterColor::SKY_REFLECT, sizeof(WaterColor::SKY_REFLECT) / sizeof(Color),
                0.8f, Form::STREAM};
    }
    static WaterType frozen() {
        return {"лёд", WaterColor::ICE, sizeof(WaterColor::ICE) / sizeof(Color), 0.0f, Form::POND};
    }
};

}  // namespace SSE

#endif  // SSE_DATA_WATER_WATERTYPE_H