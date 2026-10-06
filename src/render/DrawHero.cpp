#include "render/DrawHero.h"
#include "core/Color.h"
#include <cmath>
#include <cstdint>
#include <algorithm>

namespace SSE::Render {

inline std::uint32_t toPixel(const Color& c) {
    return 0xFF000000u
         | (static_cast<std::uint32_t>(c.r) << 16)
         | (static_cast<std::uint32_t>(c.g) << 8)
         | static_cast<std::uint32_t>(c.b);
}

// ============================================================
// Капсула (толстая линия)
// ============================================================
static void drawCapsule(std::uint32_t* buffer, int w, int h,
                        float x1, float y1,
                        float x2, float y2,
                        float thickness,
                        std::uint32_t color)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float len = std::sqrt(dx * dx + dy * dy);
    if (len < 0.1f) return;

    float half_t = thickness * 0.5f;

    int min_x = static_cast<int>(std::min(x1, x2) - half_t - 1);
    int max_x = static_cast<int>(std::max(x1, x2) + half_t + 1);
    int min_y = static_cast<int>(std::min(y1, y2) - half_t - 1);
    int max_y = static_cast<int>(std::max(y1, y2) + half_t + 1);

    if (min_x < 0) min_x = 0;
    if (min_y < 0) min_y = 0;
    if (max_x >= w) max_x = w - 1;
    if (max_y >= h) max_y = h - 1;

    float half_t2 = half_t * half_t;
    float len2 = len * len;

    for (int y = min_y; y <= max_y; ++y) {
        for (int x = min_x; x <= max_x; ++x) {
            float px = x + 0.5f - x1;
            float py = y + 0.5f - y1;

            float t = (px * dx + py * dy) / len2;
            if (t < 0.0f) t = 0.0f;
            if (t > 1.0f) t = 1.0f;

            float proj_x = t * dx;
            float proj_y = t * dy;

            float dist_x = px - proj_x;
            float dist_y = py - proj_y;
            float dist2 = dist_x * dist_x + dist_y * dist_y;

            if (dist2 <= half_t2) {
                buffer[y * w + x] = color;
            }
        }
    }
}

// ============================================================
// Отрисовка героя
// ============================================================
void drawHero(std::uint32_t* buffer,
              int w, int h,
              int cx, int cy,
              const Character& c)
{
    const auto& A = c.anatomy;
    const auto& S = c.state;

    std::uint32_t cHat    = toPixel(c.outfit.hat_color);
    std::uint32_t cShirt  = toPixel(c.outfit.hoodie_color);
    std::uint32_t cPants  = toPixel(c.outfit.pants_color);
    std::uint32_t cShoes  = toPixel(c.outfit.shoe_color);
    std::uint32_t cSkin   = 0xFFDCB48Cu;
    std::uint32_t cMarker = 0xFFDC3C3Cu;

    // --- Анимация ---
    float leg_amp = 0.0f;
    float arm_amp = 0.0f;

    switch (S.pose) {
        case Body::Pose::WALKING:  leg_amp = 18.0f; arm_amp = 12.0f; break;
        case Body::Pose::RUNNING:  leg_amp = 30.0f; arm_amp = 20.0f; break;
        case Body::Pose::SNEAKING: leg_amp = 10.0f; arm_amp = 6.0f;  break;
        default: break;
    }

    float s = std::sin(S.anim_phase);

    float leftLegLocal  = +leg_amp * s;
    float rightLegLocal = -leg_amp * s;
    float leftArmLocal  = -arm_amp * s;
    float rightArmLocal = +arm_amp * s;

    // --- Поворот ---
    float angle = S.facing_rad;
    float ca = std::cos(angle);
    float sa = std::sin(angle);

    auto toWorld = [ca, sa](float lx, float ly, float& wx, float& wy) {
        wx = lx * ca + ly * sa;
        wy = -lx * sa + ly * ca;
    };

    float fcx = static_cast<float>(cx);
    float fcy = static_cast<float>(cy);

    float hip_x      = A.torso.pelvis_width * 0.25f;
    float shoulder_x = A.torso.chest_width * 0.5f - 4.0f;

    // ============================================================
    // ЛЯМБДА — повёрнутый эллипс
    // ============================================================
    auto fillRotatedEllipse = [&](float px, float py,
                                  float half_w, float half_d,
                                  std::uint32_t color)
    {
        int rad = static_cast<int>(std::max(half_w, half_d) + 1);
        int icx = static_cast<int>(px);
        int icy = static_cast<int>(py);

        for (int oy = -rad; oy <= rad; ++oy) {
            for (int ox = -rad; ox <= rad; ++ox) {
                // Мировое (ox, oy) → локальное (обратный поворот)
                float lx =  ox * ca - oy * sa;
                float ly =  ox * sa + oy * ca;

                if ((lx * lx) / (half_w * half_w) +
                    (ly * ly) / (half_d * half_d) <= 1.0f) {
                    int ppx = icx + ox;
                    int ppy = icy + oy;
                    if (static_cast<unsigned>(px) < static_cast<unsigned>(w) &&
                        static_cast<unsigned>(py) < static_cast<unsigned>(h)) {
                        buffer[ppy * w + ppx] = color;
                    }
                }
            }
        }
    };

    // ============================================================
    // НОГИ (двухзвенные) + СТОПЫ
    // ============================================================
    float knee_share = 0.4f;

    // Левая нога
    {
        float kwx, kwy, awx, awy;
        toWorld(-hip_x, leftLegLocal * knee_share, kwx, kwy);
        toWorld(-hip_x, leftLegLocal, awx, awy);

        drawCapsule(buffer, w, h,
                    fcx, fcy,
                    fcx + kwx, fcy + kwy,
                    A.leg.thigh_width * 0.5f, cPants);
        drawCapsule(buffer, w, h,
                    fcx + kwx, fcy + kwy,
                    fcx + awx, fcy + awy,
                    A.leg.calf_width * 0.5f, cPants);

        // Стопа — ПОВЁРНУТЫЙ эллипс
        fillRotatedEllipse(fcx + awx, fcy + awy,
                           A.leg.foot_width * 0.5f,
                           A.leg.foot_length * 0.4f,
                           cShoes);
    }

    // Правая нога
    {
        float kwx, kwy, awx, awy;
        toWorld(+hip_x, rightLegLocal * knee_share, kwx, kwy);
        toWorld(+hip_x, rightLegLocal, awx, awy);

        drawCapsule(buffer, w, h,
                    fcx, fcy,
                    fcx + kwx, fcy + kwy,
                    A.leg.thigh_width * 0.5f, cPants);
        drawCapsule(buffer, w, h,
                    fcx + kwx, fcy + kwy,
                    fcx + awx, fcy + awy,
                    A.leg.calf_width * 0.5f, cPants);

        fillRotatedEllipse(fcx + awx, fcy + awy,
                           A.leg.foot_width * 0.5f,
                           A.leg.foot_length * 0.4f,
                           cShoes);
    }

    // ============================================================
    // РУКИ (двухзвенные) + КИСТИ
    // ============================================================
    float elbow_share = 0.3f;

    // Левая рука
    {
        float ew, ey, ww, wy;
        toWorld(-shoulder_x, leftArmLocal * elbow_share, ew, ey);
        toWorld(-shoulder_x, leftArmLocal, ww, wy);

        drawCapsule(buffer, w, h,
                    fcx, fcy,
                    fcx + ew, fcy + ey,
                    A.arm.upper_width * 0.5f, cShirt);
        drawCapsule(buffer, w, h,
                    fcx + ew, fcy + ey,
                    fcx + ww, fcy + wy,
                    A.arm.forearm_width * 0.5f, cShirt);

        // Кисть — ПОВЁРНУТЫЙ эллипс
        fillRotatedEllipse(fcx + ww, fcy + wy,
                           A.arm.hand_width * 0.5f,
                           A.arm.hand_length * 0.3f,
                           cSkin);
    }

    // Правая рука
    {
        float ew, ey, ww, wy;
        toWorld(+shoulder_x, rightArmLocal * elbow_share, ew, ey);
        toWorld(+shoulder_x, rightArmLocal, ww, wy);

        drawCapsule(buffer, w, h,
                    fcx, fcy,
                    fcx + ew, fcy + ey,
                    A.arm.upper_width * 0.5f, cShirt);
        drawCapsule(buffer, w, h,
                    fcx + ew, fcy + ey,
                    fcx + ww, fcy + wy,
                    A.arm.forearm_width * 0.5f, cShirt);

        fillRotatedEllipse(fcx + ww, fcy + wy,
                           A.arm.hand_width * 0.5f,
                           A.arm.hand_length * 0.3f,
                           cSkin);
    }

    // ============================================================
    // ТОРС — повёрнутые эллипсы
    // ============================================================
    fillRotatedEllipse(fcx, fcy,
                       A.torso.pelvis_width * 0.5f,
                       A.torso.pelvis_depth * 0.5f,
                       cPants);

    fillRotatedEllipse(fcx, fcy,
                       A.torso.waist_width * 0.5f,
                       A.torso.waist_depth * 0.5f,
                       cShirt);

    fillRotatedEllipse(fcx, fcy,
                       A.torso.chest_width * 0.5f,
                       A.torso.chest_depth * 0.5f,
                       cShirt);

    fillRotatedEllipse(fcx, fcy,
                       A.head.neck_width * 0.5f,
                       A.head.neck_width * 0.5f,
                       cSkin);

    // ============================================================
    // ГОЛОВА
    // ============================================================
    fillRotatedEllipse(fcx, fcy,
                       A.head.width * 0.5f,
                       A.head.depth * 0.5f,
                       cHat);

    // ============================================================
    // ИНДИКАТОР НАПРАВЛЕНИЯ
    // ============================================================
    {
        float fwd_x, fwd_y;
        toWorld(0.0f, A.head.depth * 0.5f + 1.0f, fwd_x, fwd_y);

        int fx = cx + static_cast<int>(fwd_x);
        int fy = cy + static_cast<int>(fwd_y);

        for (int row = 0; row < 4; ++row) {
            int half = (3 - row);
            for (int dx = -half; dx <= half; ++dx) {
                int px = fx + dx;
                int py = fy + row;
                if (static_cast<unsigned>(px) < static_cast<unsigned>(w) &&
                    static_cast<unsigned>(py) < static_cast<unsigned>(h)) {
                    buffer[py * w + px] = cMarker;
                }
            }
        }
    }
}

} // namespace SSE::Render
