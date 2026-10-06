#include "world/Patch.h"
#include "data/grass/GrassType.h"
#include "data/land/LandType.h"
#include <cmath>

namespace SSE {

// ============================================================
// УТИЛИТА — случайная точка внутри круга
// ============================================================
static void random_in_circle(std::int32_t cx, std::int32_t cy,
                             std::int32_t radius, Random& rng,
                             std::int32_t& out_x, std::int32_t& out_y) {
    float angle = rng.floatRange(0.0f, 6.2831853f);
    float r = radius * std::sqrt(rng.floatRange(0.0f, 1.0f));
    out_x = cx + static_cast<std::int32_t>(std::cos(angle) * r);
    out_y = cy + static_cast<std::int32_t>(std::sin(angle) * r);
}

// ============================================================
// ЛУГ — земля чернозём + много травы + редкие деревья
// ============================================================
Patch Patch::createMeadow(std::int32_t id, std::int32_t cx, std::int32_t cy,
                          std::int32_t radius, Random& rng) {
    Patch p;
    p.id = id;
    p.center_x = cx;
    p.center_y = cy;
    p.radius_px = radius;

    // --- Земля ---
    p.land = LandPatch::create(cx, cy, radius, LandType::chernozem(), rng);

    // --- Трава ---
    GrassType gt = GrassType::meadow();
    std::int32_t grass_count = static_cast<std::int32_t>(
        radius * radius * 0.02f
    );
    for (std::int32_t i = 0; i < grass_count; ++i) {
        std::int32_t gx, gy;
        random_in_circle(cx, cy, radius, rng, gx, gy);
        p.grass.push_back(GrassBlade::create(gx, gy, gt, rng));
    }

    // --- Деревья (редкие) ---
    std::int32_t tree_count = rng.intRange(2, 5);
    for (std::int32_t i = 0; i < tree_count; ++i) {
        Patch::TreeInstance t;
        // На лугу — в основном берёза
        t.type = (rng.floatRange(0.0f, 1.0f) < 0.6f)
            ? TreeType::birch() : TreeType::oak();
        random_in_circle(cx, cy, radius - 30, rng, t.x, t.y);
        t.scale = rng.floatRange(0.8f, 1.2f);
        t.rotation_rad = rng.floatRange(0.0f, 6.2831853f);
        p.trees.push_back(t);
    }

    // --- Пара камней ---
    std::int32_t stone_count = rng.intRange(1, 3);
    StoneType st = StoneType::pebble();
    for (std::int32_t i = 0; i < stone_count; ++i) {
        std::int32_t sx, sy;
        random_in_circle(cx, cy, radius - 20, rng, sx, sy);
        p.stones.push_back(Stone::create(sx, sy, st, rng));
    }

    return p;
}

// ============================================================
// ЛЕС — земля лесная + густая трава + много деревьев
// ============================================================
Patch Patch::createForest(std::int32_t id, std::int32_t cx, std::int32_t cy,
                          std::int32_t radius, Random& rng) {
    Patch p;
    p.id = id;
    p.center_x = cx;
    p.center_y = cy;
    p.radius_px = radius;

    // --- Земля ---
    p.land = LandPatch::create(cx, cy, radius, LandType::chernozem(), rng);

    // --- Трава (лесная) ---
    GrassType gt = GrassType::forest();
    std::int32_t grass_count = static_cast<std::int32_t>(
        radius * radius * 0.015f
    );
    for (std::int32_t i = 0; i < grass_count; ++i) {
        std::int32_t gx, gy;
        random_in_circle(cx, cy, radius, rng, gx, gy);
        p.grass.push_back(GrassBlade::create(gx, gy, gt, rng));
    }

    // --- Много деревьев ---
    std::int32_t tree_count = rng.intRange(15, 30);
    for (std::int32_t i = 0; i < tree_count; ++i) {
        Patch::TreeInstance t;
        // В лесу — в основном ель и сосна
        float roll = rng.floatRange(0.0f, 1.0f);
        if (roll < 0.4f)       t.type = TreeType::spruce();
        else if (roll < 0.7f)  t.type = TreeType::pine();
        else if (roll < 0.9f)  t.type = TreeType::oak();
        else                    t.type = TreeType::birch();

        random_in_circle(cx, cy, radius - 20, rng, t.x, t.y);
        t.scale = rng.floatRange(0.9f, 1.3f);
        t.rotation_rad = rng.floatRange(0.0f, 6.2831853f);
        p.trees.push_back(t);
    }

    // --- Камни ---
    std::int32_t stone_count = rng.intRange(2, 5);
    StoneType st = StoneType::granite();
    for (std::int32_t i = 0; i < stone_count; ++i) {
        std::int32_t sx, sy;
        random_in_circle(cx, cy, radius - 20, rng, sx, sy);
        p.stones.push_back(Stone::create(sx, sy, st, rng));
    }

    return p;
}

// ============================================================
// ПУСТЫНЯ — песок + почти нет травы + кактусы-камни
// ============================================================
Patch Patch::createDesert(std::int32_t id, std::int32_t cx, std::int32_t cy,
                          std::int32_t radius, Random& rng) {
    Patch p;
    p.id = id;
    p.center_x = cx;
    p.center_y = cy;
    p.radius_px = radius;

    // --- Земля — песок ---
    p.land = LandPatch::create(cx, cy, radius, LandType::sand(), rng);

    // --- Трава — редкая сухая ---
    GrassType gt = GrassType::dry();
    std::int32_t grass_count = static_cast<std::int32_t>(
        radius * radius * 0.003f
    );
    for (std::int32_t i = 0; i < grass_count; ++i) {
        std::int32_t gx, gy;
        random_in_circle(cx, cy, radius, rng, gx, gy);
        p.grass.push_back(GrassBlade::create(gx, gy, gt, rng));
    }

    // --- Камни больше ---
    std::int32_t stone_count = rng.intRange(3, 7);
    StoneType st = StoneType::sandstone();
    for (std::int32_t i = 0; i < stone_count; ++i) {
        std::int32_t sx, sy;
        random_in_circle(cx, cy, radius - 20, rng, sx, sy);
        p.stones.push_back(Stone::create(sx, sy, st, rng));
    }

    return p;
}

} // namespace SSE
