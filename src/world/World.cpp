#include "world/World.h"
#include "world/Sphere.h"
#include "core/Random.h"
#include "data/grass/GrassType.h"
#include "data/grass/GrassBlade.h"
#include <algorithm>
#include <cmath>

namespace SSE {

using namespace Config;

// ============================================================
// Трава для мира — использует параметры из GrassType
// ============================================================
static GrassType makeGrassType() {
    return GrassType::meadow();
}

// ============================================================
// World
// ============================================================
World::World()
    : cells_(std::make_unique<CachedCell[]>(WORLD_TOTAL))
    , queued_(WORLD_TOTAL, 0)
{
}

// ---------- утилиты рисования в буфер ячейки ----------
static inline void putPixelBGRA(std::uint32_t* buf, int w, int h,
                                int x, int y, std::uint32_t color) {
    if (static_cast<unsigned>(x) >= static_cast<unsigned>(w)) return;
    if (static_cast<unsigned>(y) >= static_cast<unsigned>(h)) return;
    buf[y * w + x] = color;
}

static inline std::uint32_t colorFromRGB(std::uint8_t r, std::uint8_t g,
                                         std::uint8_t b) {
    return 0xFF000000u
         | (static_cast<std::uint32_t>(r) << 16)
         | (static_cast<std::uint32_t>(g) << 8)
         | static_cast<std::uint32_t>(b);
}

static void drawLineToBuffer(std::uint32_t* buf, int w, int h,
                             int x1, int y1, int x2, int y2,
                             std::uint32_t color) {
    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        putPixelBGRA(buf, w, h, x1, y1, color);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx)  { err += dx; y1 += sy; }
    }
}

// ============================================================
// СОЗДАНИЕ ЯЧЕЙКИ
// ============================================================
void World::loadCellData(int idx) {
    int wix = idx % WORLD_CELLS;
    int wiy = idx / WORLD_CELLS;

    std::uint32_t seed =
        static_cast<std::uint32_t>(wix * 73856093) ^
        static_cast<std::uint32_t>(wiy * 19349663) ^ 0x9e3779b9u;
    Random rng(seed);

    static const GrassType gGrass = makeGrassType();

    std::vector<std::uint32_t> temp(CELL_SIZE * CELL_SIZE, 0);

    int count = static_cast<int>(CELL_SIZE * CELL_SIZE * CELL_DENSITY);

    for (int i = 0; i < count; ++i) {
        float bx = rng.floatRange(0.0f, static_cast<float>(CELL_SIZE - 1));
        float by = rng.floatRange(0.0f, static_cast<float>(CELL_SIZE - 1));

        GrassBlade blade = GrassBlade::create(0, 0, gGrass, rng);
        int bxi = static_cast<int>(bx);
        int byi = static_cast<int>(by);

        for (const auto& leaf : blade.leaves) {
            int tip_x = bxi + static_cast<int>(
                std::cos(leaf.angle_rad) * leaf.length_px);
            int tip_y = byi + static_cast<int>(
                std::sin(leaf.angle_rad) * leaf.length_px);

            std::uint32_t col = colorFromRGB(leaf.color.r,
                                             leaf.color.g,
                                             leaf.color.b);
            drawLineToBuffer(temp.data(), CELL_SIZE, CELL_SIZE,
                             bxi, byi, tip_x, tip_y, col);
        }
    }

    CachedCell& cell = cells_[idx];
    cell.pixels.clear();
    cell.pixels.reserve(4096);

    for (int y = 0; y < CELL_SIZE; ++y) {
        const std::uint32_t* row = &temp[y * CELL_SIZE];
        for (int x = 0; x < CELL_SIZE; ++x) {
            std::uint32_t c = row[x];
            if (c) {
                cell.pixels.push_back({
                    static_cast<std::int16_t>(x),
                    static_cast<std::int16_t>(y),
                    c
                });
            }
        }
    }

    std::sort(cell.pixels.begin(), cell.pixels.end(),
              [](const ActivePixel& a, const ActivePixel& b) {
                  if (a.dy != b.dy) return a.dy < b.dy;
                  return a.dx < b.dx;
              });

    cell.loaded = true;
    ++loadedCount_;
}

// ============================================================
// ВЫГРУЗКА ДАЛЁКИХ
// ============================================================
void World::unloadFarCells(float cx, float cy, int ccx, int ccy, int r_cells) {
    float unload_r2 = (R_LOAD * 1.4f) * (R_LOAD * 1.4f);

    for (int iy = ccy - r_cells - 2; iy <= ccy + r_cells + 2; ++iy) {
        for (int ix = ccx - r_cells - 2; ix <= ccx + r_cells + 2; ++ix) {
            int idx = Sphere::cellIdx(ix, iy);
            CachedCell& cell = cells_[idx];
            if (!cell.loaded) continue;

            int wix = idx % WORLD_CELLS;
            int wiy = idx / WORLD_CELLS;
            float cell_cx = (wix + 0.5f) * CELL_SIZE;
            float cell_cy = (wiy + 0.5f) * CELL_SIZE;
            float ddx = Sphere::wrapDelta(cell_cx - cx);
            float ddy = Sphere::wrapDelta(cell_cy - cy);
            if (ddx * ddx + ddy * ddy > unload_r2) {
                cell.clear();
                queued_[idx] = 0;
                --loadedCount_;
            }
        }
    }
}

// ============================================================
// ДОЗАПОЛНЕНИЕ ОЧЕРЕДИ
// ============================================================
void World::refillQueue(float cx, float cy, int ccx, int ccy, int r_cells) {
    int ddx_cells = ccx - lastScanCcx_;
    int ddy_cells = ccy - lastScanCcy_;
    bool moved = (std::abs(ddx_cells) >= 1 || std::abs(ddy_cells) >= 1)
              || (lastScanCcx_ == -999999);

    if (!moved) return;

    lastScanCcx_ = ccx;
    lastScanCcy_ = ccy;

    struct Pending { int idx; float dist; };
    std::vector<Pending> pending;
    pending.reserve(64);

    float load_r2 = R_LOAD * R_LOAD;

    for (int dy = -r_cells; dy <= r_cells; ++dy) {
        for (int dx = -r_cells; dx <= r_cells; ++dx) {
            int wix = Sphere::wrapCell(ccx + dx);
            int wiy = Sphere::wrapCell(ccy + dy);
            int idx = wiy * WORLD_CELLS + wix;

            if (cells_[idx].loaded) continue;
            if (queued_[idx]) continue;

            float cell_cx = (wix + 0.5f) * CELL_SIZE;
            float cell_cy = (wiy + 0.5f) * CELL_SIZE;
            float ddx = Sphere::wrapDelta(cell_cx - cx);
            float ddy = Sphere::wrapDelta(cell_cy - cy);
            float d2 = ddx * ddx + ddy * ddy;
            if (d2 < load_r2) {
                pending.push_back({idx, d2});
            }
        }
    }

    std::sort(pending.begin(), pending.end(),
              [](const Pending& a, const Pending& b) {
                  return a.dist > b.dist;
              });

    for (auto it = pending.rbegin(); it != pending.rend(); ++it) {
        loadQueue_.push_front(it->idx);
        queued_[it->idx] = 1;
    }
}

// ============================================================
// ОБРАБОТКА ОЧЕРЕДИ
// ============================================================
void World::processQueue() {
    int to_load = LOAD_PER_FRAME_BASE;
    if (static_cast<int>(loadQueue_.size()) > LOAD_QUEUE_FAST_THRESHOLD) {
        to_load += static_cast<int>(loadQueue_.size() / 15);
    }

    for (int i = 0; i < to_load && !loadQueue_.empty(); ++i) {
        int idx = loadQueue_.front();
        loadQueue_.pop_front();
        if (cells_[idx].loaded) { queued_[idx] = 0; continue; }
        loadCellData(idx);
        queued_[idx] = 0;
    }
}

// ============================================================
// ОБЩИЙ АПДЕЙТ
// ============================================================
void World::update(float cx, float cy) {
    int ccx = static_cast<int>(std::floor(cx / CELL_SIZE));
    int ccy = static_cast<int>(std::floor(cy / CELL_SIZE));

    int r_cells = static_cast<int>(R_LOAD / CELL_SIZE) + 2;

    if (ccx != lastUnloadCcx_ || ccy != lastUnloadCcy_) {
        lastUnloadCcx_ = ccx;
        lastUnloadCcy_ = ccy;
        unloadFarCells(cx, cy, ccx, ccy, r_cells);
    }

    refillQueue(cx, cy, ccx, ccy, r_cells);
    processQueue();
}

} // namespace SSE
