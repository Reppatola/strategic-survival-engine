// ============================================================
// HeroRenderer.cpp — теперь тонкая обёртка над Rust
// Вся логика рендера героя живёт в rust-bio/src/render.rs
// ============================================================
#include "render/HeroRenderer.h"
#include <cstdint>

// ------------------------------------------------------------
// FFI: функция из Rust (rust-bio/src/lib.rs)
// ------------------------------------------------------------
extern "C" void rust_render_hero(
    std::uint32_t* buffer,
    int width,
    int height,
    int cx,
    int cy,
    float facing,
    float scale
);

namespace SSE::Render {

void drawHeroFromSlices(std::uint32_t* buffer,
                        int w, int h,
                        int cx, int cy,
                        float facing,
                        float scale)
{
    rust_render_hero(buffer, w, h, cx, cy, facing, scale);
}

} // namespace SSE::Render
