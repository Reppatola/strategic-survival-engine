#ifndef SSE_DATA_WEATHER_WINDDATA_H
#define SSE_DATA_WEATHER_WINDDATA_H

#include <cstdint>

namespace SSE {

// ============================================================
// ВЕТЕР
// Редкие локальные очаги. Каждый очаг живёт ограниченное время.
// ============================================================
struct WindGust {
    float x = 0.0f;
    float y = 0.0f;
    float radius_px = 50.0f;
    float life_sec = 2.0f;
    float age_sec = 0.0f;
    float dir_x = -1.0f;
    float dir_y = 0.0f;
    float strength = 1.0f;
};

struct WindData {
    // Параметры появления очагов
    float spawn_min_sec = 2.0f;
    float spawn_max_sec = 6.0f;

    float radius_min_px = 40.0f;
    float radius_max_px = 90.0f;

    float life_min_sec = 1.0f;
    float life_max_sec = 2.5f;

    float strength_max = 1.0f;

    // Мировое направление ветра (общее)
    float global_dir_x = -1.0f;
    float global_dir_y = 0.0f;
};

}  // namespace SSE

#endif