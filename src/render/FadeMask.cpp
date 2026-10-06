#include "render/FadeMask.h"
#include "app/Config.h"
#include <cmath>

namespace SSE::Render {

using namespace SSE::Config;

static std::uint8_t s_fade[SCR_W * SCR_H];

void buildFadeMask() {
    const float r_core_sq = R_CORE * R_CORE;
    const float r_fade_sq = R_FADE * R_FADE;
    const float sigma = (R_FADE - R_CORE) / 2.5f;
    const float inv_2sigma2 = 1.0f / (2.0f * sigma * sigma);

    for (int y = 0; y < SCR_H; ++y) {
        float dy = static_cast<float>(y - CYP);
        float dy2 = dy * dy;
        std::uint8_t* row = &s_fade[y * SCR_W];

        for (int x = 0; x < SCR_W; ++x) {
            float dx = static_cast<float>(x - CXP);
            float sq = dx * dx + dy2;

            if (sq >= r_fade_sq) {
                row[x] = 0;
            } else if (sq <= r_core_sq) {
                row[x] = 255;
            } else {
                float d = std::sqrt(sq);
                float t = d - R_CORE;
                float a = std::exp(-t * t * inv_2sigma2);
                if (a < 0) a = 0;
                if (a > 1) a = 1;
                row[x] = static_cast<std::uint8_t>(a * 255.0f);
            }
        }
    }
}

std::uint8_t fadeAt(int x, int y) {
    if (static_cast<unsigned>(x) >= SCR_W) return 0;
    if (static_cast<unsigned>(y) >= SCR_H) return 0;
    return s_fade[y * SCR_W + x];
}

const std::uint8_t* fadeData() { return s_fade; }

} // namespace SSE::Render
