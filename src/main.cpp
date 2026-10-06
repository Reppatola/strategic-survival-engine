// ============================================================
// SSE Prototype — точка входа
// Режимы скорости: CTRL — красться, обычная — ходьба, SHIFT — бег
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

using namespace SSE;
using namespace SSE::Config;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int) {
    Platform::Win32Window window;
    if (!window.create(hInstance, SCR_W, SCR_H, "SSE — Optimized"))
        return 1;

    Render::buildFadeMask();

    Game game;
    auto last = std::chrono::steady_clock::now();

    // --- Базовая скорость ---
    // Изменяется модификаторами:
    //   SHIFT    → ×2.5  (бег)
    //   CTRL     → ×0.4  (красться)
    const float BASE_SPEED = 120.0f;

    // --- Кэш HUD ---
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

        if (mx != 0.0f || my != 0.0f) {
            // Модификаторы скорости
            float mult = 1.0f;
            if (GetAsyncKeyState(VK_SHIFT)   & 0x8000) mult = 2.5f; // SHIFT — бег
            if (GetAsyncKeyState(VK_CONTROL) & 0x8000) mult = 0.4f; // CTRL  — красться

            float effective_speed = BASE_SPEED * mult;

            float len = std::sqrt(mx * mx + my * my);
            game.cylinder().x += static_cast<int>(mx / len * effective_speed * dt);
            game.cylinder().y += static_cast<int>(my / len * effective_speed * dt);
            game.cylinder().x = static_cast<int>(Sphere::wrapFloat(
                static_cast<float>(game.cylinder().x)));
            game.cylinder().y = static_cast<int>(Sphere::wrapFloat(
                static_cast<float>(game.cylinder().y)));
        }

        // ---------- Мир ----------
        game.update(dt);

        // ---------- Рендер ----------
        std::uint32_t* fb = window.beginFrame(SCR_W, SCR_H);
        if (fb) {
            // Сцена
            game.render(fb, SCR_W, SCR_H);

            // HUD — обновляем текст раз в 0.25 сек
            hudTimer += dt;
            if (hudTimer >= 0.25f) {
                hudTimer = 0.0f;

                float mdx = Sphere::wrapDelta(
                    0.0f - static_cast<float>(game.cylinder().x));
                float mdy = Sphere::wrapDelta(
                    0.0f - static_cast<float>(game.cylinder().y));
                float mdist = std::sqrt(mdx * mdx + mdy * mdy);

                wchar_t buf[256];
                swprintf_s(buf,
                    L"Pos: %d, %d  |  Start: %.0f px  |  Cells: %zu  |  Queue: %zu  |  FPS: %.1f",
                    game.cylinder().x,
                    game.cylinder().y,
                    mdist,
                    game.world().loadedCount(),
                    game.world().queueSize(),
                    game.fps());
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
