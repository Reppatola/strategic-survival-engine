#ifndef SSE_RENDER_DRAW_HERO_H
#define SSE_RENDER_DRAW_HERO_H

#include "data/character/Character.h"
#include <cstdint>

namespace SSE::Render {

// Рисует тело героя СВЕРХУ в буфер экрана.
// (cx, cy) — экранная позиция центра героя.
void drawHero(std::uint32_t* buffer,
              int screen_w, int screen_h,
              int cx, int cy,
              const Character& character);

} // namespace SSE::Render

#endif
