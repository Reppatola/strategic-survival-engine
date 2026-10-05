#ifndef SSE_WORLD_OBSERVER_H
#define SSE_WORLD_OBSERVER_H

#include <cstdint>

#include "data/objects/Player.h"

namespace SSE {

// ============================================================
// НАБЛЮДАТЕЛЬ
// Не часть мира. Точка зрения.
// Имеет:
//   - позицию на плоскости (следует за игроком)
//   - радиус восприятия (что видно)
//   - ссылку на игрока (чьими глазами смотрит)
//
// Наблюдатель — не игрок. Игрок существует в мире.
// Наблюдатель — интерфейс. Он видит мир ОТ ИГРОКА.
// ============================================================
class Observer {
   public:
    Observer() = default;

    // Привязать наблюдателя к игроку — наблюдатель смотрит его глазами
    void attachTo(const Player* player) { target_player_ = player; }
    void detach() { target_player_ = nullptr; }

    // Текущая позиция наблюдения (следует за игроком)
    [[nodiscard]] float viewX() const;
    [[nodiscard]] float viewY() const;

    // Радиус восприятия — что видно
    [[nodiscard]] float visionRadius() const { return vision_radius_; }
    void setVisionRadius(float r) { vision_radius_ = r; }

    // Направление взгляда (для будущего — конус обзора)
    [[nodiscard]] float lookAngle() const { return look_angle_; }
    void setLookAngle(float a) { look_angle_ = a; }

    // Проверка: попадает ли точка в зону восприятия?
    [[nodiscard]] bool canSee(float world_x, float world_y) const;

   private:
    const Player* target_player_ = nullptr;

    // Позиция наблюдателя, если он не привязан к игроку
    float own_x_ = 0.0f;
    float own_y_ = 0.0f;

    float vision_radius_ = 250.0f;
    float look_angle_ = 0.0f;
};

}  // namespace SSE

#endif