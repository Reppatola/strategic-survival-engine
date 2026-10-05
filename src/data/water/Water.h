#ifndef SSE_DATA_WATER_WATER_H
#define SSE_DATA_WATER_WATER_H

#include <cstdint>

#include "core/Color.h"
#include "core/Random.h"
#include "data/water/WaterType.h"

namespace SSE {

struct Water {
    std::int32_t x = 0;
    std::int32_t y = 0;

    // Размер (для круга — радиус, для реки — длина/ширина)
    float radius_px = 30.0f;
    float length_px = 0.0f;  // для реки/ручья
    float width_px = 0.0f;

    float rotation_rad = 0.0f;  // для реки/ручья — направление течения
    WaterType::Form form = WaterType::Form::POND;

    Color color{};

    static Water create(std::int32_t x, std::int32_t y, const WaterType& type, Random& rng) {
        Water w;
        w.x = x;
        w.y = y;
        w.form = type.form;

        std::int32_t idx = rng.intRange(0, type.palette_size - 1);
        w.color = type.palette[idx];

        switch (type.form) {
            case WaterType::Form::PUDDLE:
                w.radius_px = rng.floatRange(5.0f, 15.0f);
                break;
            case WaterType::Form::POND:
                w.radius_px = rng.floatRange(20.0f, 40.0f);
                break;
            case WaterType::Form::LAKE:
                w.radius_px = rng.floatRange(60.0f, 120.0f);
                break;
            case WaterType::Form::RIVER:
                w.length_px = rng.floatRange(150.0f, 300.0f);
                w.width_px = rng.floatRange(15.0f, 30.0f);
                w.rotation_rad = rng.floatRange(0.0f, 6.2831853f);
                break;
            case WaterType::Form::STREAM:
                w.length_px = rng.floatRange(80.0f, 150.0f);
                w.width_px = rng.floatRange(4.0f, 8.0f);
                w.rotation_rad = rng.floatRange(0.0f, 6.2831853f);
                break;
        }
        return w;
    }
};

}  // namespace SSE

#endif  // SSE_DATA_WATER_WATER_H