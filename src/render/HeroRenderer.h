#ifndef SSE_RENDER_HERO_RENDERER_H
#define SSE_RENDER_HERO_RENDERER_H

#include <cstdint>

namespace SSE::Render {

void drawHeroFromSlices(std::uint32_t* buffer,
                        int screen_w, int screen_h,
                        int cx, int cy,
                        float facing,
                        float scale,
                        unsigned int pose,
                        float anim_phase);

} // namespace SSE::Render

#endif
