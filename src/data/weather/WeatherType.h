#ifndef SSE_DATA_WEATHER_WEATHERTYPE_H
#define SSE_DATA_WEATHER_WEATHERTYPE_H

#include <cstdint>
#include <string>

#include "core/Color.h"

namespace SSE {

// ============================================================
// ТИП ПОГОДЫ
// Меняет: цвет неба, видимость, цвет земли/травы.
// ============================================================
struct WeatherType {
    std::string name;

    Color sky_color;          // цвет неба (или общего фона)
    float visibility = 1.0f;  // 0..1 — дальность обзора
    float brightness = 1.0f;  // 0..1 — общая яркость

    bool has_rain = false;
    bool has_snow = false;
    bool has_fog = false;

    static WeatherType clear() {
        return {"ясно", {130, 170, 210}, 1.0f, 1.0f, false, false, false};
    }
    static WeatherType cloudy() {
        return {"облачно", {110, 120, 130}, 0.9f, 0.85f, false, false, false};
    }
    static WeatherType rain() { return {"дождь", {70, 80, 95}, 0.6f, 0.6f, true, false, false}; }
    static WeatherType storm() { return {"гроза", {40, 45, 60}, 0.4f, 0.4f, true, false, false}; }
    static WeatherType fog() { return {"туман", {150, 155, 160}, 0.3f, 0.7f, false, false, true}; }
    static WeatherType snow() { return {"снег", {200, 210, 220}, 0.5f, 0.9f, false, true, false}; }
};

}  // namespace SSE

#endif