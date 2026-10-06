#ifndef SSE_DATA_BODY_ANATOMY_H
#define SSE_DATA_BODY_ANATOMY_H

namespace SSE::Body {

// ============================================================
// АНАТОМИЯ ЧЕЛОВЕКА
// Все размеры в САНТИМЕТРАХ.
// Сверено с антропометрическими стандартами.
//
// Правило баланса:
//   head.height + neck_height +
//   chest_height + waist_height + pelvis_height
//   = head_base (высота от земли до основания головы)
// ============================================================

struct HeadAnatomy {
    float height      = 22.0f;   // макушка → подбородок
    float width       = 16.0f;   // между ушами
    float depth       = 20.0f;   // затылок → нос
    float neck_height = 8.0f;
    float neck_width  = 10.0f;
};

struct TorsoAnatomy {
    // Плечи — на уровне ВЕРХА груди
    float shoulder_width      = 44.0f;
    float shoulder_from_chest = 13.0f;

    // Грудь: от основания шеи до талии
    float chest_width  = 44.0f;
    float chest_depth  = 22.0f;
    float chest_height = 30.0f;

    // Талия: узкая часть торса
    float waist_width  = 26.0f;
    float waist_depth  = 20.0f;
    float waist_height = 20.0f;

    // Таз: нижняя часть торса
    float pelvis_width  = 34.0f;
    float pelvis_depth  = 22.0f;
    float pelvis_height = 11.0f;
};

struct ArmAnatomy {
    float shoulder_to_elbow = 30.0f;
    float elbow_to_wrist    = 26.0f;
    float hand_length       = 19.0f;
    float upper_width       = 11.0f;
    float forearm_width     = 9.0f;
    float hand_width        = 9.0f;
};

struct LegAnatomy {
    float ankle_height  = 6.0f;
    float knee_height   = 48.0f;
    float hip_height    = 84.0f;

    float hip_to_knee   = 45.0f;
    float knee_to_ankle = 42.0f;
    float foot_length   = 26.0f;
    float thigh_width   = 16.0f;
    float calf_width    = 11.0f;
    float foot_width    = 10.0f;
};

struct HumanAnatomy {
    float total_height   = 175.0f;
    float total_weight   = 75.0f;
    float shoulder_width = 44.0f;

    HeadAnatomy  head;
    TorsoAnatomy torso;
    ArmAnatomy   arm;
    LegAnatomy   leg;
};

// ============================================================
// СТАНДАРТНЫЙ МУЖЧИНА 175 см
// Проверка: 22+8 + 30+20+11 = 91;  175 − 91 = 84 (hip_height) ✓
// ============================================================
inline constexpr HumanAnatomy STANDARD_MALE = {
    175.0f, 75.0f, 44.0f,
    // head
    { 22.0f, 16.0f, 20.0f, 8.0f, 10.0f },
    // torso
    { 44.0f, 13.0f,
      44.0f, 22.0f, 30.0f,   // chest
      26.0f, 20.0f, 20.0f,   // waist
      34.0f, 22.0f, 11.0f }, // pelvis
    // arm
    { 30.0f, 26.0f, 19.0f, 11.0f, 9.0f, 9.0f },
    // leg
    { 6.0f, 48.0f, 84.0f, 45.0f, 42.0f, 26.0f, 16.0f, 11.0f, 10.0f }
};

// ============================================================
// СТАНДАРТНАЯ ЖЕНЩИНА 165 см
// Проверка: 21+7 + 28+19+11 = 86;  165 − 86 = 79 (hip_height) ✓
// ============================================================
inline constexpr HumanAnatomy STANDARD_FEMALE = {
    165.0f, 60.0f, 40.0f,
    // head
    { 21.0f, 15.0f, 19.0f, 7.0f, 9.0f },
    // torso
    { 40.0f, 12.0f,
      40.0f, 20.0f, 28.0f,   // chest
      24.0f, 18.0f, 19.0f,   // waist
      36.0f, 22.0f, 11.0f }, // pelvis
    // arm
    { 28.0f, 24.0f, 17.0f, 9.0f, 8.0f, 8.0f },
    // leg
    { 6.0f, 45.0f, 79.0f, 42.0f, 40.0f, 24.0f, 14.0f, 10.0f, 9.0f }
};

} // namespace SSE::Body

#endif
