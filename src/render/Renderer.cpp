#include "render/Renderer.h"
#include "render/FadeMask.h"
#include "render/HeroRenderer.h"
#include "render/VisionMask.h"
#include "world/Sphere.h"
#include "app/Config.h"
#include "data/body/BodyState.h"
#include <algorithm>
#include <cmath>
#include <cstdint>

namespace SSE::Render {

using namespace Config;

// ============================================================
// FFI: рендер зомби из Rust
// ============================================================
extern "C" void rust_render_zombie(
    std::uint32_t* buffer,
    int width, int height,
    int cx, int cy,
    float facing, float scale,
    unsigned int pose, float anim_phase,
    float obs_height_cm,
    float fade
);

inline std::uint32_t colorFromRGB(std::uint8_t r, std::uint8_t g, std::uint8_t b) {
    return 0xFF000000u
         | (static_cast<std::uint32_t>(r) << 16)
         | (static_cast<std::uint32_t>(g) << 8)
         | static_cast<std::uint32_t>(b);
}

// ------------------------------------------------------------
// Клип по Y: рисуем ТОЛЬКО в зоне мира
// ------------------------------------------------------------
inline bool in_world_y(int sy) {
    return sy >= WORLD_TOP && sy < WORLD_BOT;
}

// ------------------------------------------------------------
// Смешать цвет c с фоном по коэффициенту alpha (0..255)
// ------------------------------------------------------------
inline std::uint32_t blendColor(std::uint32_t c, std::uint32_t bg, std::uint32_t a)
{
    if (a == 0)   return bg;
    if (a >= 250) return c;

    std::uint32_t inv = 255 - a;

    std::uint32_t r = ((((c >> 16) & 0xFF) * a + ((bg >> 16) & 0xFF) * inv) >> 8);
    std::uint32_t g = ((((c >>  8) & 0xFF) * a + ((bg >>  8) & 0xFF) * inv) >> 8);
    std::uint32_t b = ((( c        & 0xFF) * a + ( bg        & 0xFF) * inv) >> 8);

    return 0xFF000000u | (r << 16) | (g << 8) | b;
}

// ------------------------------------------------------------
// Blit ячейки — БЕЗ радиального fade, С зрением
// ------------------------------------------------------------
static void blitCellOpaque(std::uint32_t* screen,
                           const CachedCell& cell,
                           int dst_x, int dst_y,
                           float sin_f, float cos_f)
{
    for (const auto& p : cell.pixels) {
        int sx = dst_x + p.dx;
        int sy = dst_y + p.dy;

        if (static_cast<unsigned>(sx) >= SCR_W) continue;
        if (!in_world_y(sy)) continue;

        std::uint8_t vis = visionAt(sx, sy, sin_f, cos_f);
        if (vis == 0) continue;

        std::uint32_t* dst = &screen[sy * SCR_W + sx];

        if (vis >= 250) {
            *dst = p.color;
        } else {
            *dst = blendColor(p.color, *dst, vis);
        }
    }
}

// ------------------------------------------------------------
// Blit ячейки — С радиальным fade И зрением
// ------------------------------------------------------------
static void blitCellFaded(std::uint32_t* screen,
                          const CachedCell& cell,
                          int dst_x, int dst_y,
                          float sin_f, float cos_f)
{
    for (const auto& p : cell.pixels) {
        int sx = dst_x + p.dx;
        int sy = dst_y + p.dy;

        if (static_cast<unsigned>(sx) >= SCR_W) continue;
        if (!in_world_y(sy)) continue;

        std::uint8_t fade = fadeAt(sx, sy);
        if (!fade) continue;

        std::uint8_t vis = visionAt(sx, sy, sin_f, cos_f);
        if (!vis) continue;

        std::uint32_t a = (static_cast<std::uint32_t>(fade) *
                           static_cast<std::uint32_t>(vis)) >> 8;
        if (!a) continue;

        std::uint32_t* dst = &screen[sy * SCR_W + sx];

        if (a >= 250) {
            *dst = p.color;
        } else {
            *dst = blendColor(p.color, *dst, a);
        }
    }
}

// ------------------------------------------------------------
// Метка старта
// ------------------------------------------------------------
static void drawStartMarker(std::uint32_t* sbuf, float cx, float cy) {
    float dx = Sphere::wrapDelta(0.0f - cx);
    float dy = Sphere::wrapDelta(0.0f - cy);
    int sx = CXP + static_cast<int>(dx);
    int sy = CYP + static_cast<int>(dy);

    auto put = [sbuf](int x, int y, std::uint32_t color) {
        if (static_cast<unsigned>(x) < SCR_W && in_world_y(y)) {
            sbuf[y * SCR_W + x] = color;
        }
    };

    for (int t = 0; t < 360; t += 4) {
        float a = t * 3.14159f / 180.0f;
        int px = sx + static_cast<int>(std::cos(a) * 22);
        int py = sy + static_cast<int>(std::sin(a) * 22);
        put(px, py, colorFromRGB(255, 60, 60));
    }
    for (int i = -14; i <= 14; ++i) {
        put(sx + i, sy, colorFromRGB(255, 220, 100));
        put(sx, sy + i, colorFromRGB(255, 220, 100));
    }
    for (int oy = -3; oy <= 3; ++oy)
        for (int ox = -3; ox <= 3; ++ox)
            if (ox*ox + oy*oy <= 9)
                put(sx + ox, sy + oy, 0xFFFFFFFFu);
}

// ------------------------------------------------------------
// Главный рендер
// ------------------------------------------------------------
void renderWorld(std::uint32_t* buffer,
                 int /*width*/, int /*height*/,
                 const World& world,
                 const Character& character,
                 float dt)
{
    const std::uint32_t bg = colorFromRGB(45, 32, 22);
    for (int y = WORLD_TOP; y < WORLD_BOT; ++y) {
        std::uint32_t* row = &buffer[y * SCR_W];
        std::fill(row, row + SCR_W, bg);
    }

    float cx = character.world_x;
    float cy = character.world_y;

    const float sin_f = std::sin(character.state.facing_rad);
    const float cos_f = std::cos(character.state.facing_rad);

    int center_ix = static_cast<int>(cx / CELL_SIZE);
    int center_iy = static_cast<int>(cy / CELL_SIZE);

    int rc = static_cast<int>(R_FADE / CELL_SIZE) + 2;

    const CachedCell* cells = world.cells();

    // ---------- Ячейки мира ----------
    for (int dy = -rc; dy <= rc; ++dy) {
        for (int dx = -rc; dx <= rc; ++dx) {
            int wix = Sphere::wrapCell(center_ix + dx);
            int wiy = Sphere::wrapCell(center_iy + dy);
            int idx = wiy * WORLD_CELLS + wix;

            const CachedCell& cell = cells[idx];
            if (!cell.loaded || cell.pixels.empty()) continue;

            float cell_world_x = static_cast<float>(wix * CELL_SIZE);
            float cell_world_y = static_cast<float>(wiy * CELL_SIZE);

            float ddx = Sphere::wrapDelta(cell_world_x - cx);
            float ddy = Sphere::wrapDelta(cell_world_y - cy);

            int dst_x = CXP + static_cast<int>(ddx);
            int dst_y = CYP + static_cast<int>(ddy);

            if (dst_x + CELL_SIZE < 0 || dst_x >= SCR_W) continue;
            if (dst_y + CELL_SIZE < WORLD_TOP || dst_y >= WORLD_BOT) continue;

            float cell_half = CELL_SIZE * 0.5f;
            float c_cx = ddx + cell_half;
            float c_cy = ddy + cell_half;

            float dx_near = std::max(0.0f, std::abs(c_cx) - cell_half);
            float dy_near = std::max(0.0f, std::abs(c_cy) - cell_half);
            float nearest_sq = dx_near * dx_near + dy_near * dy_near;

            float dx_far = std::abs(c_cx) + cell_half;
            float dy_far = std::abs(c_cy) + cell_half;
            float farthest_sq = dx_far * dx_far + dy_far * dy_far;

            if (farthest_sq <= R_CORE * R_CORE) {
                blitCellOpaque(buffer, cell, dst_x, dst_y, sin_f, cos_f);
            } else if (nearest_sq < R_FADE * R_FADE) {
                blitCellFaded(buffer, cell, dst_x, dst_y, sin_f, cos_f);
            }
        }
    }

    drawStartMarker(buffer, cx, cy);

    // ============================================================
    // ЗОМБИ
    // ============================================================
    {
        static float zw_x    = 300.0f;
        static float zw_y    = 0.0f;
        static float z_phase = 0.0f;

        float dx = Sphere::wrapDelta(cx - zw_x);
        float dy = Sphere::wrapDelta(cy - zw_y);
        float dist = std::sqrt(dx * dx + dy * dy);

        constexpr float ZOMBIE_SPEED = 60.0f;
        constexpr float ZOMBIE_STOP  = 20.0f;

        bool moving = false;
        if (dist > ZOMBIE_STOP) {
            float step = ZOMBIE_SPEED * dt;
            if (step > dist - ZOMBIE_STOP) step = dist - ZOMBIE_STOP;

            zw_x += (dx / dist) * step;
            zw_y += (dy / dist) * step;
            zw_x = Sphere::wrapFloat(zw_x);
            zw_y = Sphere::wrapFloat(zw_y);
            moving = true;
        }

        if (moving) {
            z_phase += dt * 3.14f;
            if (z_phase > 6.2831853f) z_phase -= 6.2831853f;
        } else {
            z_phase = 0.0f;
        }

        float zdx = Sphere::wrapDelta(zw_x - cx);
        float zdy = Sphere::wrapDelta(zw_y - cy);
        float zdist = std::sqrt(zdx * zdx + zdy * zdy);

        if (zdist < R_FADE) {
            int zcx = CXP + static_cast<int>(zdx);
            int zcy = CYP + static_cast<int>(zdy);

            std::uint8_t vis = visionAt(zcx, zcy, sin_f, cos_f);

            if (vis > 0) {
                float fade = 1.0f;
                float fade_start = R_FADE * 0.7f;
                if (zdist > fade_start) {
                    fade = 1.0f - (zdist - fade_start) / (R_FADE - fade_start);
                    if (fade < 0.0f) fade = 0.0f;
                }

                fade = fade * (static_cast<float>(vis) / 255.0f);

                if (fade > 0.02f) {
                    float z_facing = std::atan2(dx, dy);
                    constexpr float OBS_HEIGHT = 3000.0f;

                    rust_render_zombie(buffer, SCR_W, SCR_H,
                                        zcx, zcy,
                                        z_facing,
                                        0.8f,
                                        moving ? 1u : 0u,
                                        z_phase,
                                        OBS_HEIGHT,
                                        fade);
                }
            }
        }
    }

    // ============================================================
    // ГЕРОЙ
    // ============================================================
    Render::drawHeroFromSlices(buffer, SCR_W, SCR_H,
                                CXP, CYP,
                                character.state.facing_rad,
                                0.8f,
                                static_cast<unsigned int>(character.state.pose),
                                character.state.anim_phase);
}

} // namespace SSE::Render
