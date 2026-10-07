// ============================================================
// SSE Prototype — точка входа
// ============================================================
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <string>

#include "app/Config.h"
#include "app/Game.h"
#include "platform/Win32Window.h"
#include "render/FadeMask.h"
#include "world/Sphere.h"
#include "data/body/BodyState.h"

using namespace SSE;
using namespace SSE::Config;

// ============================================================
// FFI: Rust-функции
// ============================================================
extern "C" float rust_get_phase_rate(unsigned int pose);

extern "C" float rust_step_db(
    unsigned int pose,
    const char* surface,  size_t surface_len,
    const char* footwear, size_t footwear_len
);

extern "C" void  rust_print_step_table();

extern "C" float rust_db_at_distance(float l1_db, float r_meters);

extern "C" float rust_hearing_radius(float l1_db, float threshold_db);

// ============================================================
// Хелпер: посчитать dB шага для текущей позы
// ============================================================
float compute_step_db(Body::Pose pose)
{
    // Пока — фиксированные поверхность и обувь.
    // Позже — из данных мира и экипировки.
    const char* surface  = "grass";
    const char* footwear = "sneakers";

    return rust_step_db(
        static_cast<unsigned int>(pose),
        surface,  std::strlen(surface),
        footwear, std::strlen(footwear)
    );
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    Platform::Win32Window window;
    if (!window.create(hInstance, SCR_W, SCR_H, "SSE — Hero"))
        return 1;

    Render::buildFadeMask();

    // --- Один раз печатаем таблицу шума шага в консоль ---
    rust_print_step_table();

    Game game;
    auto last = std::chrono::steady_clock::now();

    std::wstring hudLine1;
    const wchar_t* hudLine2 = L"WASD — move  |  SHIFT — run  |  CTRL — sneak  |  ESC — quit";
    float hudTimer = 999.0f;

    while (true) {
        if (!window.pumpMessages()) break;

        auto now = std::chrono::steady_clock::now();
        float dt = std::chrono::duration<float>(now - last).count();
        last = now;
        if (dt > 0.1f) dt = 0.1f;

        // ---------- Ввод ----------
        float mx = window.moveX();
        float my = window.moveY();

        Character& hero = game.character();

        if (mx != 0.0f || my != 0.0f) {
            float speed = SPEED_WALK;
            Body::Pose pose = Body::Pose::WALKING;

            if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
                speed = SPEED_RUN;
                pose  = Body::Pose::RUNNING;
            }
            if (GetAsyncKeyState(VK_CONTROL) & 0x8000) {
                speed = SPEED_SNEAK;
                pose  = Body::Pose::SNEAKING;
            }

            float len = std::sqrt(mx * mx + my * my);
            hero.world_x += mx / len * speed * dt;
            hero.world_y += my / len * speed * dt;
            hero.world_x = Sphere::wrapFloat(hero.world_x);
            hero.world_y = Sphere::wrapFloat(hero.world_y);

            hero.state.pose = pose;

            // Поворот
            float target = std::atan2(mx, my);
            float diff = target - hero.state.facing_rad;
            while (diff >  3.14159265f) diff -= 6.2831853f;
            while (diff < -3.14159265f) diff += 6.2831853f;

            float turn_speed = 10.0f;
            float max_turn = turn_speed * dt;
            if (diff >  max_turn) diff =  max_turn;
            if (diff < -max_turn) diff = -max_turn;

            hero.state.facing_rad += diff;

            // ФАЗА АНИМАЦИИ — частота из Rust
            float rate = rust_get_phase_rate(
                static_cast<unsigned int>(hero.state.pose));
            hero.state.anim_phase += dt * rate;

            constexpr float TWO_PI = 6.2831853f;
            while (hero.state.anim_phase >= TWO_PI)
                hero.state.anim_phase -= TWO_PI;
        } else {
            hero.state.pose = Body::Pose::STANDING;
            hero.state.anim_phase = 0.0f;
        }

        // ---------- Мир ----------
        game.update(dt);

        // ---------- Рендер ----------
        std::uint32_t* fb = window.beginFrame(SCR_W, SCR_H);
        if (fb) {
            game.render(fb, SCR_W, SCR_H);

            hudTimer += dt;
            if (hudTimer >= 0.25f) {
                hudTimer = 0.0f;

                // Шум текущего шага
                float step_db = compute_step_db(hero.state.pose);

                // Радиус слышимости для порога зомби (30 dB)
                float hear_r = (step_db > 0.0f)
                    ? rust_hearing_radius(step_db, 30.0f)
                    : 0.0f;

                // Громкость на 10 м
                float at_10m = (step_db > 0.0f)
                    ? rust_db_at_distance(step_db, 10.0f)
                    : 0.0f;

                wchar_t buf[320];
                swprintf_s(buf,
                    L"Pos: %.0f,%.0f | Cells:%zu | FPS:%.1f | pose=%d phase=%.2f | step=%.1fdB  R(30dB)=%.1fm  @10m=%.1fdB",
                    hero.world_x,
                    hero.world_y,
                    game.world().loadedCount(),
                    game.fps(),
                    static_cast<int>(hero.state.pose),
                    hero.state.anim_phase,
                    step_db,
                    hear_r,
                    at_10m);
                hudLine1 = buf;
            }

            HDC mdc = window.memDC();
            SetBkMode(mdc, TRANSPARENT);

            SetTextColor(mdc, RGB(255, 255, 255));
            if (!hudLine1.empty()) {
                TextOutW(mdc, 10, 10,
                         hudLine1.c_str(),
                         static_cast<int>(hudLine1.size()));
            }

            SetTextColor(mdc, RGB(160, 160, 160));
            TextOutW(mdc, 10, 32,
                     hudLine2,
                     static_cast<int>(wcslen(hudLine2)));

            window.endFrame();
        }

        Sleep(1);
    }

    return 0;
}
