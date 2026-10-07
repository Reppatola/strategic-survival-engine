#ifndef SSE_RENDER_HERO_RENDERER_H
#define SSE_RENDER_HERO_RENDERER_H

#include "data/characters/hero1/hero1.h"
#include <cstdint>

namespace SSE::Render {

// Рисует тело героя сверху в буфер экрана.
// cx, cy — экранная позиция центра героя
// facing — угол направления (радианы, 0 = юг)
// scale — пикселей на сантиметр
void drawHeroFromSlices(std::uint32_t* buffer,
                        int screen_w, int screen_h,
                        int cx, int cy,
                        float facing,
                        float scale);

} // namespace SSE::Render

#endif
