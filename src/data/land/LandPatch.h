#ifndef SSE_DATA_LAND_LANDPATCH_H
#define SSE_DATA_LAND_LANDPATCH_H

#include <cstdint>

#include "core/Color.h"
#include "core/Random.h"
#include "data/land/LandType.h"

namespace SSE {

// ============================================================
// ПАТЧ ЗЕМЛИ
// Один кусок земли на шаре. Каждый патч имеет:
//   - позицию на шаре (пока плоскость — x, y)
//   - радиус (пока круг — потом многоугольник на поверхности шара)
//   - тип земли
//   - свой уникальный базовый оттенок (выбранный из палитры типа)
// ============================================================
struct LandPatch {
    std::int32_t x = 0;  // позиция на плоскости (позже — на шаре)
    std::int32_t y = 0;
    std::int32_t radius = 100;  // радиус патча в пикселях

    LandType type;     // тип земли
    Color base_color;  // основной цвет этого патча (из палитры)

    // ============================================================
    // Создать патч: тип задаёт палитру, random выбирает оттенок.
    // Так два патча одного типа земли — разные по цвету.
    // ============================================================
    static LandPatch create(std::int32_t x, std::int32_t y, std::int32_t radius,
                            const LandType& type, Random& rng) {
        LandPatch p;
        p.x = x;
        p.y = y;
        p.radius = radius;
        p.type = type;

        // Выбор случайного оттенка из палитры типа
        std::int32_t idx = rng.intRange(0, type.palette_size - 1);
        p.base_color = type.palette[idx];
        return p;
    }

    // Цвет этого патча — базовый + случайное затемнение/осветление
    [[nodiscard]] Color color_at(std::int32_t /*px*/, std::int32_t /*py*/) const {
        return base_color;
    }
};

}  // namespace SSE

#endif  // SSE_DATA_LAND_LANDPATCH_H