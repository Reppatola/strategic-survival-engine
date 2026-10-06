#ifndef SSE_DATA_CHARACTER_CHARACTER_H
#define SSE_DATA_CHARACTER_CHARACTER_H

#include "core/Color.h"
#include "data/body/Anatomy.h"
#include "data/body/Skeleton.h"
#include "data/body/BodyState.h"
#include "data/clothing/headwear/HatSizes.h"
#include "data/clothing/torso/HoodieSizes.h"
#include "data/clothing/legs/PantsSizes.h"
#include "data/clothing/feet/ShoeSizes.h"
#include <string>

namespace SSE {

// ============================================================
// ПЕРСОНАЖ
// Скелет + форма + одежда + поза + мировые координаты.
// ============================================================
struct Character {
    // --- Идентификация ---
    std::string name   = "Герой";
    std::string gender = "male";

    // --- Позиция в мире ---
    float world_x = 0.0f;
    float world_y = 0.0f;

    // --- Данные тела ---
    Body::HumanAnatomy anatomy = Body::STANDARD_MALE;
    Body::Skeleton     skeleton;
    Body::BodyState    state;

    // --- Одежда (размер + цвет) ---
    struct Outfit {
        int   hat_size  = 57;
        Color hat_color = {60, 40, 25, 255};

        int   hoodie_size  = 46;
        Color hoodie_color = {80, 100, 160, 255};

        int   pants_size  = 50;
        Color pants_color = {60, 70, 100, 255};

        int   shoe_size  = 43;
        Color shoe_color = {40, 30, 25, 255};
    } outfit;

    void buildSkeleton(float facing_rad = 0.0f) {
        skeleton = Body::Skeleton::fromAnatomy(anatomy, facing_rad);
    }

    const Clothing::Headwear::HatSize*  hat() const {
        return Clothing::Headwear::findHatSize(outfit.hat_size);
    }
    const Clothing::Torso::HoodieSize*  hoodie() const {
        return Clothing::Torso::findHoodieSize(outfit.hoodie_size);
    }
    const Clothing::Legs::PantsSize*    pants() const {
        return Clothing::Legs::findPantsSize(outfit.pants_size);
    }
    const Clothing::Feet::ShoeSize*     shoes() const {
        return Clothing::Feet::findShoeSize(outfit.shoe_size);
    }
};

} // namespace SSE

#endif
