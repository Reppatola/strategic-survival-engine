#ifndef SSE_RENDER_RENDERER_H
#define SSE_RENDER_RENDERER_H

#include "world/World.h"
#include "data/character/Character.h"
#include <cstdint>

namespace SSE::Render {

void renderWorld(std::uint32_t* buffer,
                 int width,
                 int height,
                 const World& world,
                 const Character& character,
                 float dt);

} // namespace SSE::Render

#endif
