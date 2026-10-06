#ifndef SSE_DATA_BODY_SKELETON_H
#define SSE_DATA_BODY_SKELETON_H

#include "data/body/Anatomy.h"
#include <cstdint>
#include <cmath>

namespace SSE::Body {

// ============================================================
// СКЕЛЕТ — позиции частей тела в ПРОСТРАНСТВЕ
// Все координаты в САНТИМЕТРАХ.
// Система координат локальная:
//   X+ = вправо
//   Y+ = вперёд (по направлению взгляда)
//   Z+ = вверх (0 = уровень земли)
//
// Расчёт идёт СВЕРХУ ВНИЗ — от макушки.
// Это защищает от накопления ошибок.
// ============================================================

struct Point3 {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

struct Skeleton {
    Point3 head_base;
    Point3 head_center;
    Point3 head_top;

    Point3 chest;
    Point3 waist;
    Point3 pelvis;

    Point3 shoulder_left;
    Point3 shoulder_right;
    Point3 elbow_left;
    Point3 elbow_right;
    Point3 wrist_left;
    Point3 wrist_right;

    Point3 hip_left;
    Point3 hip_right;
    Point3 knee_left;
    Point3 knee_right;
    Point3 ankle_left;
    Point3 ankle_right;

    float torso_angle = 0.0f;
    float head_angle  = 0.0f;

    static Skeleton fromAnatomy(const HumanAnatomy& A, float facing_rad);
};

// ============================================================
// РЕАЛИЗАЦИЯ
// ============================================================
inline Skeleton Skeleton::fromAnatomy(const HumanAnatomy& A, float facing_rad) {
    Skeleton s;

    float cos_f = std::cos(facing_rad);
    float sin_f = std::sin(facing_rad);

    auto rot = [cos_f, sin_f](float lx, float ly) -> Point3 {
        return Point3{
            lx * cos_f - ly * sin_f,
            lx * sin_f + ly * cos_f,
            0.0f
        };
    };

    const float H = A.total_height;

    // ----------------------------------------------------------
    // СЧИТАЕМ СВЕРХУ ВНИЗ — от макушки
    // ----------------------------------------------------------
    float head_top_z      = H;
    float head_base_z     = head_top_z    - A.head.height;
    float chest_top_z     = head_base_z   - A.head.neck_height;
    float chest_bottom_z  = chest_top_z   - A.torso.chest_height;
    float waist_top_z     = chest_bottom_z;
    float waist_bottom_z  = waist_top_z   - A.torso.waist_height;
    float pelvis_top_z    = waist_bottom_z;
    float pelvis_bottom_z = pelvis_top_z  - A.torso.pelvis_height;

    // --- Голова ---
    s.head_top    = rot(0.0f, 0.0f); s.head_top.z    = head_top_z;
    s.head_center = rot(0.0f, 0.0f); s.head_center.z = (head_top_z + head_base_z) * 0.5f;
    s.head_base   = rot(0.0f, 0.0f); s.head_base.z   = head_base_z;

    // --- Торс ---
    s.chest  = rot(0.0f, 0.0f); s.chest.z  = (chest_top_z  + chest_bottom_z)  * 0.5f;
    s.waist  = rot(0.0f, 0.0f); s.waist.z  = (waist_top_z  + waist_bottom_z)  * 0.5f;
    s.pelvis = rot(0.0f, 0.0f); s.pelvis.z = (pelvis_top_z + pelvis_bottom_z) * 0.5f;

    // --- Плечи — на 2 см ниже верха груди ---
    float half_sh = A.torso.shoulder_width * 0.5f;
    s.shoulder_left  = rot(-half_sh, 0.0f);
    s.shoulder_right = rot( half_sh, 0.0f);
    s.shoulder_left.z  = chest_top_z - 2.0f;
    s.shoulder_right.z = s.shoulder_left.z;

    // --- Руки ---
    float elbow_z = s.shoulder_left.z - A.arm.shoulder_to_elbow;
    s.elbow_left  = rot(-half_sh, 0.0f); s.elbow_left.z  = elbow_z;
    s.elbow_right = rot( half_sh, 0.0f); s.elbow_right.z = elbow_z;

    float wrist_z = elbow_z - A.arm.elbow_to_wrist;
    s.wrist_left  = rot(-half_sh, 0.0f); s.wrist_left.z  = wrist_z;
    s.wrist_right = rot( half_sh, 0.0f); s.wrist_right.z = wrist_z;

    // --- Ноги ---
    float hip_x = A.torso.pelvis_width * 0.25f;

    s.hip_left   = rot(-hip_x, 0.0f); s.hip_left.z   = A.leg.hip_height;
    s.hip_right  = rot( hip_x, 0.0f); s.hip_right.z  = A.leg.hip_height;

    s.knee_left  = rot(-hip_x, 0.0f); s.knee_left.z  = A.leg.knee_height;
    s.knee_right = rot( hip_x, 0.0f); s.knee_right.z = A.leg.knee_height;

    s.ankle_left  = rot(-hip_x, 0.0f); s.ankle_left.z  = A.leg.ankle_height;
    s.ankle_right = rot( hip_x, 0.0f); s.ankle_right.z = A.leg.ankle_height;

    return s;
}

} // namespace SSE::Body

#endif
