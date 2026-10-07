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
#include <algorithm>

#include "app/Config.h"
#include "app/Game.h"
#include "platform/Win32Window.h"
#include "render/FadeMask.h"
#include "world/Sphere.h"
#include "data/body/BodyState.h"

using namespace SSE;
using namespace SSE::Config;

// ============================================================
// FFI
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
// UI: нижняя панель
// ============================================================
static void drawBottomPanel(std::uint32_t* fb)
{
    constexpr std::uint32_t panel_bg    = 0xFF14141C;
    constexpr std::uint32_t border_top  = 0xFF5064A0;
    constexpr std::uint32_t text_dim    = 0xFF808090;
    constexpr std::uint32_t text_active = 0xFFB8C8E8;

    // Заливка
    for (int y = WORLD_BOT; y < SCR_H; ++y) {
        std::uint32_t* row = &fb[y * SCR_W];
        std::fill(row, row + SCR_W, panel_bg);
    }

    // Тонкая граница сверху
    {
        std::uint32_t* row = &fb[WORLD_BOT * SCR_W];
        std::fill(row, row + SCR_W, border_top);
    }

    // Заголовок панели
    HDC hdc = nullptr;   // залить текстом через memDC
    (void)hdc;
    (void)text_dim;
    (void)text_active;
}

float compute_step_db(Body::Pose pose)
{
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

    rust_print_step_table();

    Game game;
    auto last = std::chrono::steady_clock::now();

    std::wstring hudLine1;
    const wchar_t* hudLine2 = L"WASD — move  |  SHIFT — run  |  CTRL — sneak  |  ESC — quit";
    std::wstring hudLine2b;
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

            float target = std::atan2(mx, my);
            float diff = target - hero.state.facing_rad;
            while (diff >  3.14159265f) diff -= 6.2831853f;
            while (diff < -3.14159265f) diff += 6.2831853f;

            float turn_speed = 10.0f;
            float max_turn = turn_speed * dt;
            if (diff >  max_turn) diff =  max_turn;
            if (diff < -max_turn) diff = -max_turn;

            hero.state.facing_rad += diff;

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

            // Залить нижнюю панель
            drawBottomPanel(fb);

            HDC mdc = window.memDC();
            SetBkMode(mdc, TRANSPARENT);

            // ---------- Верхний HUD ----------
            hudTimer += dt;
            if (hudTimer >= 0.25f) {
                hudTimer = 0.0f;

                float step_db = compute_step_db(hero.state.pose);
                float hear_r = (step_db > 0.0f)
                    ? rust_hearing_radius(step_db, 30.0f)
                    : 0.0f;
                float at_10m = (step_db > 0.0f)
                    ? rust_db_at_distance(step_db, 10.0f)
                    : 0.0f;

                wchar_t buf[320];
                swprintf_s(buf,
                    L"FPS:%.1f  |  Cells:%zu  |  pose:%d",
                    game.fps(),
                    game.world().loadedCount(),
                    static_cast<int>(hero.state.pose));
                hudLine1 = buf;

                swprintf_s(buf,
                    L"step=%.1fdB  R[30dB]=%.1fm  @10m=%.1fdB",
                    step_db, hear_r, at_10m);
                hudLine2b = buf;
            }

            SetTextColor(mdc, RGB(255, 255, 255));
            if (!hudLine1.empty()) {
                TextOutW(mdc, 10, 6,
                         hudLine1.c_str(),
                         static_cast<int>(hudLine1.size()));
            }

            SetTextColor(mdc, RGB(200, 200, 220));
            if (!hudLine2b.empty()) {
                TextOutW(mdc, 10, 24,
                         hudLine2b.c_str(),
                         static_cast<int>(hudLine2b.size()));
            }

            SetTextColor(mdc, RGB(140, 140, 150));
            TextOutW(mdc, 10, 42,
                     hudLine2,
                     static_cast<int>(wcslen(hudLine2)));

            // ---------- Нижняя панель: заголовок ----------
            SetTextColor(mdc, RGB(80, 100, 160));
            const wchar_t* panel_title = L"[ ДИАЛОГ / СТАТУС / ИНВЕНТАРЬ ]";
            TextOutW(mdc, 20, WORLD_BOT + 12,
                     panel_title,
                     static_cast<int>(wcslen(panel_title)));

            SetTextColor(mdc, RGB(120, 120, 130));
            const wchar_t* panel_hint = L"здесь будет UI на C++ — текст, квесты, торговля";
            TextOutW(mdc, 20, WORLD_BOT + 40,
                     panel_hint,
                     static_cast<int>(wcslen(panel_hint)));

            window.endFrame();
        }

        Sleep(1);
    }

    return 0;
}
