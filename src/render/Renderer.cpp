#include "render/Renderer.h"
#include "render/FadeMask.h"
#include "render/DrawHero.h"
#include "world/Sphere.h"
#include "app/Config.h"
#include <algorithm>
#include <cmath>
#include <cstdint>

namespace SSE::Render {

using namespace Config;

inline std::uint32_t colorFromRGB(std::uint8_t r, std::uint8_t g, std::uint8_t b) {
    return 0xFF000000u
         | (static_cast<std::uint32_t>(r) << 16)
         | (static_cast<std::uint32_t>(g) << 8)
         | static_cast<std::uint32_t>(b);
}

// ------------------------------------------------------------
// Blit ячейки — БЕЗ fade
// ------------------------------------------------------------
static void blitCellOpaque(std::uint32_t* screen,
                           const CachedCell& cell,
                           int dst_x, int dst_y)
{
    for (const auto& p : cell.pixels) {
        int sx = dst_x + p.dx;
        int sy = dst_y + p.dy;
        if (static_cast<unsigned>(sx) < SCR_W &&
            static_cast<unsigned>(sy) < SCR_H) {
            screen[sy * SCR_W + sx] = p.color;
        }
    }
}

// ------------------------------------------------------------
// Blit ячейки — С fade
// ------------------------------------------------------------
static void blitCellFaded(std::uint32_t* screen,
                          const CachedCell& cell,
                          int dst_x, int dst_y)
{
    for (const auto& p : cell.pixels) {
        int sx = dst_x + p.dx;
        int sy = dst_y + p.dy;

        if (static_cast<unsigned>(sx) >= SCR_W) continue;
        if (static_cast<unsigned>(sy) >= SCR_H) continue;

        std::uint8_t fade = fadeAt(sx, sy);
        if (!fade) continue;

        std::uint32_t c = p.color;
        if (fade >= 250) {
            screen[sy * SCR_W + sx] = c;
            continue;
        }

        std::uint32_t a = fade;
        std::uint32_t inv = 255 - a;
        std::uint32_t* dst = &screen[sy * SCR_W + sx];
        std::uint32_t bg = *dst;

        std::uint32_t r = ((((c >> 16) & 0xFF) * a + ((bg >> 16) & 0xFF) * inv) >> 8);
        std::uint32_t g = ((((c >>  8) & 0xFF) * a + ((bg >>  8) & 0xFF) * inv) >> 8);
        std::uint32_t b = ((( c        & 0xFF) * a + ( bg        & 0xFF) * inv) >> 8);

        *dst = 0xFF000000u | (r << 16) | (g << 8) | b;
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
        if (static_cast<unsigned>(x) < SCR_W && static_cast<unsigned>(y) < SCR_H) {
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
                 const Character& character)
{
    const std::uint32_t bg = colorFromRGB(45, 32, 22);
    std::fill(buffer, buffer + SCR_W * SCR_H, bg);

    float cx = character.world_x;
    float cy = character.world_y;

    int center_ix = static_cast<int>(cx / CELL_SIZE);
    int center_iy = static_cast<int>(cy / CELL_SIZE);

    int rc = static_cast<int>(R_FADE / CELL_SIZE) + 2;

    const CachedCell* cells = world.cells();

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
            if (dst_y + CELL_SIZE < 0 || dst_y >= SCR_H) continue;

            float c_cx = ddx + CELL_SIZE * 0.5f;
            float c_cy = ddy + CELL_SIZE * 0.5f;
            float center_sq = c_cx * c_cx + c_cy * c_cy;
            float cell_radius_sq = CELL_SIZE * CELL_SIZE * 0.5f;

            if (center_sq + cell_radius_sq <= R_CORE * R_CORE) {
                blitCellOpaque(buffer, cell, dst_x, dst_y);
            } else if (center_sq - cell_radius_sq < R_FADE * R_FADE) {
                blitCellFaded(buffer, cell, dst_x, dst_y);
            }
        }
    }

    drawStartMarker(buffer, cx, cy);

    // ГЕРОЙ — вместо цилиндра
    drawHero(buffer, SCR_W, SCR_H, CXP, CYP, character);
}

} // namespace SSE::Render
