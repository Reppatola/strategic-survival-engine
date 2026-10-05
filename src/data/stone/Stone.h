#ifndef SSE_DATA_STONE_STONE_H
#define SSE_DATA_STONE_STONE_H

#include <cstdint>

#include "core/Color.h"
#include "core/Random.h"
#include "data/stone/StoneType.h"

namespace SSE {

// ============================================================
// КАМЕНЬ — объект на земле.
// Форма (для вида сверху) — многоугольник или круг.
// ============================================================
struct Stone {
    std::int32_t x = 0;
    std::int32_t y = 0;
    float size_px = 8.0f;
    Color color{};
    StoneType::Form form = StoneType::Form::ROCK;

    // Углы для многоугольника (вид сверху)
    // Храним как данные — сколько вершин и как они развёрнуты.
    std::uint8_t vertex_count = 6;
    float rotation_rad = 0.0f;

    bool has_moss = false;
    Color moss_color{};

    static Stone create(std::int32_t x, std::int32_t y, const StoneType& type, Random& rng) {
        Stone s;
        s.x = x;
        s.y = y;
        s.size_px = rng.floatRange(type.size_min_px, type.size_max_px);
        s.form = type.form;

        std::int32_t idx = rng.intRange(0, type.palette_size - 1);
        s.color = type.palette[idx];

        // Форма определяет количество вершин
        switch (type.form) {
            case StoneType::Form::PEBBLE:
                s.vertex_count = 5;
                break;
            case StoneType::Form::ROCK:
                s.vertex_count = 6;
                break;
            case StoneType::Form::BOULDER:
                s.vertex_count = 8;
                break;
            case StoneType::Form::SLAB:
                s.vertex_count = 4;
                break;
        }
        s.rotation_rad = rng.floatRange(0.0f, 6.2831853f);

        // Мох — если разрешён, с вероятностью 30%
        if (type.can_have_moss && rng.floatRange(0.0f, 1.0f) < 0.3f) {
            s.has_moss = true;
            std::int32_t mi = rng.intRange(0, sizeof(StoneColor::MOSS) / sizeof(Color) - 1);
            s.moss_color = StoneColor::MOSS[mi];
        }
        return s;
    }
};

}  // namespace SSE

#endif  // SSE_DATA_STONE_STONE_H