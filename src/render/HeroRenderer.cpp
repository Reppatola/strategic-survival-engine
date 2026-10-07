// ============================================================
// HeroRenderer.cpp — тонкая обёртка над Rust
// ============================================================
#include "render/HeroRenderer.h"
#include <cstdint>

extern "C" void rust_render_hero(
    std::uint32_t* buffer,
    int width, int height,
    int cx, int cy,
    float facing, float scale,
    unsigned int pose,
    float anim_phase
);

namespace SSE::Render {

void drawHeroFromSlices(std::uint32_t* buffer,
                        int w, int h,
                        int cx, int cy,
                        float facing,
                        float scale,
                        unsigned int pose,
                        float anim_phase)
{
    rust_render_hero(buffer, w, h, cx, cy, facing, scale, pose, anim_phase);
}

} // namespace SSE::Render
