#include "render/HeroRenderer.h"
#include "core/Color.h"
#include <cmath>
#include <cstdint>

namespace SSE::Render {

using namespace SSE::Hero1;
using namespace SSE::Characters;

// ------------------------------------------------------------
// Проверка: точка (x, y) внутри среза
// ------------------------------------------------------------
static bool pointInSlice(float x, float y, const HSlice& s) {
    float dx = x - s.offset_x;
    float dy = y - s.offset_y;
    float rx = s.width  * 0.5f;
    float ry = s.depth  * 0.5f;
    if (rx < 0.1f || ry < 0.1f) return false;
    return (dx * dx) / (rx * rx) + (dy * dy) / (ry * ry) <= 1.0f;
}

// ------------------------------------------------------------
// Найти верхний Z и часть тела в точке (lx, ly) —
// в ЛОКАЛЬНОЙ системе героя (до поворота)
// ------------------------------------------------------------
static float highestZLocal(float lx, float ly, int& part_out) {
    float best_z = -1.0f;
    int   best_part = -1;

    #define CHECK_PART(NS, ID, XOFF)                              \
        for (int i = 0; i < NS::H_SLICES_COUNT; ++i) {            \
            float px = lx - XOFF;                                  \
            float py = ly;                                         \
            if (pointInSlice(px, py, NS::H_SLICES[i])) {           \
                if (NS::H_SLICES[i].z > best_z) {                  \
                    best_z = NS::H_SLICES[i].z;                    \
                    best_part = ID;                                \
                }                                                  \
            }                                                      \
        }

    CHECK_PART(Head,       0, Head::ATTACH_X)
    CHECK_PART(TorsoUpper, 1, TorsoUpper::ATTACH_X)
    CHECK_PART(TorsoLower, 2, TorsoLower::ATTACH_X)
    CHECK_PART(ArmLeft,    3, ArmLeft::ATTACH_X)
    CHECK_PART(ArmRight,   4, ArmRight::ATTACH_X)
    CHECK_PART(LegLeft,    5, LegLeft::ATTACH_X)
    CHECK_PART(LegRight,   6, LegRight::ATTACH_X)
    CHECK_PART(FootLeft,   7, FootLeft::ATTACH_X)
    CHECK_PART(FootRight,  8, FootRight::ATTACH_X)

    #undef CHECK_PART

    part_out = best_part;
    return best_z;
}

// ------------------------------------------------------------
// Цвет части
// ------------------------------------------------------------
static std::uint32_t colorForPart(int part, float z) {
    std::uint32_t base = 0;

    switch (part) {
        case 0: base = 0xFF5A4128u; break;   // голова — волосы
        case 1: base = 0xFF5064A0u; break;   // верх торса
        case 2: base = 0xFF3C4664u; break;   // низ торса
        case 3: base = 0xFF5064A0u; break;   // левая рука
        case 4: base = 0xFF5064A0u; break;   // правая рука
        case 5: base = 0xFF3C4664u; break;   // левая нога
        case 6: base = 0xFF3C4664u; break;   // правая нога
        case 7: base = 0xFF281E19u; break;   // левая стопа
        case 8: base = 0xFF281E19u; break;   // правая стопа
        default: return 0;
    }

    // Осветление по высоте
    float br = 0.7f + (z / 175.0f) * 0.3f;
    int r = ((base >> 16) & 0xFF);
    int g = ((base >>  8) & 0xFF);
    int b = ( base        & 0xFF);

    r = static_cast<int>(r * br);
    g = static_cast<int>(g * br);
    b = static_cast<int>(b * br);

    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;

    return 0xFF000000u | (r << 16) | (g << 8) | b;
}

// ------------------------------------------------------------
// Отрисовка героя из срезов
// ------------------------------------------------------------
void drawHeroFromSlices(std::uint32_t* buffer,
                        int w, int h,
                        int cx, int cy,
                        float facing,
                        float scale)
{
    // Границы в локальных координатах (см) — с запасом
    constexpr float LOCAL_X_MAX = 30.0f;
    constexpr float LOCAL_Y_MAX = 30.0f;

    float ca = std::cos(facing);
    float sa = std::sin(facing);

    // Пробегаем по квадрату в экранных пикселях,
    // потом переводим в локальные координаты героя.
    int px_max = static_cast<int>(LOCAL_X_MAX * scale) + 2;
    int py_max = static_cast<int>(LOCAL_Y_MAX * scale) + 2;

    for (int dy = -py_max; dy <= py_max; ++dy) {
        for (int dx = -px_max; dx <= px_max; ++dx) {
            int px = cx + dx;
            int py = cy + dy;

            if (static_cast<unsigned>(px) >= static_cast<unsigned>(w)) continue;
            if (static_cast<unsigned>(py) >= static_cast<unsigned>(h)) continue;

            // Экран → см
            float wx = dx / scale;
            float wy = dy / scale;

            // Мировое → локальное (обратный поворот)
            //   мировое (wx, wy), угол facing
            //   локальное (lx, ly) — вдоль тела
            //   Матрица: [ lx ]   [ ca  -sa ] [ wx ]
            //           [ ly ] = [ sa   ca ] [ wy ]
            float lx = wx * ca - wy * sa;
            float ly = wx * sa + wy * ca;

            int part = -1;
            float z = highestZLocal(lx, ly, part);

            if (z >= 0.0f && part >= 0) {
                buffer[py * w + px] = colorForPart(part, z);
            }
        }
    }
}

} // namespace SSE::Render
