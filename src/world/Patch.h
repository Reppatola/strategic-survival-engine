#ifndef SSE_WORLD_PATCH_H
#define SSE_WORLD_PATCH_H

#include "data/land/LandPatch.h"
#include "data/grass/GrassBlade.h"
#include "data/tree/TreeType.h"
#include "data/stone/Stone.h"
#include "data/water/Water.h"
#include "data/objects/Building.h"
#include "data/objects/Zombie.h"
#include "data/objects/Animal.h"
#include "core/Random.h"
#include <cstdint>
#include <vector>

namespace SSE {

// ============================================================
// ПАТЧ — один кусок мира на шаре.
//
// Пока — плоскость. Позже — многоугольник на поверхности сферы.
// Патч содержит ВСЁ, что есть в его границах:
//   - земля (какая почва)
//   - трава (какие травинки)
//   - деревья (какие и где)
//   - камни
//   - вода
//   - строения
//   - зомби, животные
//
// Патч не знает, как он выглядит. Он знает, ЧТО у него есть.
// Отрисовка — отдельно.
// ============================================================
class Patch {
public:
    Patch() = default;

    // --- Идентификация ---
    std::int32_t id = 0;
    std::int32_t center_x = 0;      // центр патча (пиксели)
    std::int32_t center_y = 0;
    std::int32_t radius_px = 350;   // размер патча

    // --- Ландшафт ---
    LandPatch land;

    // --- Растительность ---
    std::vector<GrassBlade> grass;

    // Деревья: тип + позиция + поворот
    struct TreeInstance {
        TreeType type;
        std::int32_t x;
        std::int32_t y;
        float scale = 1.0f;
        float rotation_rad = 0.0f;
    };
    std::vector<TreeInstance> trees;

    // --- Камни ---
    std::vector<Stone> stones;

    // --- Вода ---
    std::vector<Water> water;

    // --- Строения ---
    std::vector<Building> buildings;

    // --- Сущности ---
    std::vector<Zombie> zombies;
    std::vector<Animal> animals;

    // ============================================================
    // ФАБРИКИ — создание патча по типу биома
    // ============================================================

    // --- Создание патча: луг ---
    static Patch createMeadow(std::int32_t id,
                              std::int32_t cx, std::int32_t cy,
                              std::int32_t radius,
                              Random& rng);

    // --- Создание патча: лес ---
    static Patch createForest(std::int32_t id,
                              std::int32_t cx, std::int32_t cy,
                              std::int32_t radius,
                              Random& rng);

    // --- Создание патча: пустыня ---
    static Patch createDesert(std::int32_t id,
                              std::int32_t cx, std::int32_t cy,
                              std::int32_t radius,
                              Random& rng);

    // --- Проверка: попадает ли точка в патч ---
    [[nodiscard]] bool contains(std::int32_t x, std::int32_t y) const {
        std::int32_t dx = x - center_x;
        std::int32_t dy = y - center_y;
        return (dx * dx + dy * dy) <= radius_px * radius_px;
    }
};

} // namespace SSE

#endif
