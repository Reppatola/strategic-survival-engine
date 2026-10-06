#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <chrono>
#include <cmath>
#include <cstdio>

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
    float speed = 400.0f;

    while (true) {
        if (!window.pumpMessages()) break;

        auto now = std::chrono::steady_clock::now();
        float dt = std::chrono::duration<float>(now - last).count();
        last = now;
        if (dt > 0.1f) dt = 0.1f;

        float mx = window.moveX();
        float my = window.moveY();

        if (mx != 0.0f || my != 0.0f) {
            float len = std::sqrt(mx * mx + my * my);
            game.cylinder().x += static_cast<int>(mx / len * speed * dt);
            game.cylinder().y += static_cast<int>(my / len * speed * dt);
            game.cylinder().x = static_cast<int>(Sphere::wrapFloat(
                static_cast<float>(game.cylinder().x)));
            game.cylinder().y = static_cast<int>(Sphere::wrapFloat(
                static_cast<float>(game.cylinder().y)));
        }

        game.update(dt);

        // --- Рисуем в DIB ---
        std::uint32_t* fb = window.beginFrame(SCR_W, SCR_H);
        if (fb) {
            // 1. Сцена
            game.render(fb, SCR_W, SCR_H);

            // 2. HUD — в ТОТ ЖЕ DIB (через memDC), а не поверх экрана
            HDC mdc = window.memDC();
            SetBkMode(mdc, TRANSPARENT);
            SetTextColor(mdc, RGB(255, 255, 255));

            float mdx = Sphere::wrapDelta(0.0f - static_cast<float>(game.cylinder().x));
            float mdy = Sphere::wrapDelta(0.0f - static_cast<float>(game.cylinder().y));
            float mdist = std::sqrt(mdx * mdx + mdy * mdy);

            wchar_t buf[256];
            swprintf_s(buf,
                L"Pos: %d, %d  |  Start: %.0f px  |  Cells: %zu  |  Queue: %zu  |  FPS: %.1f",
                game.cylinder().x, game.cylinder().y, mdist,
                game.world().loadedCount(), game.world().queueSize(), game.fps());
            TextOutW(mdc, 10, 10, buf, static_cast<int>(wcslen(buf)));

            SetTextColor(mdc, RGB(160, 160, 160));
            swprintf_s(buf, L"WASD — move  |  ESC — quit");
            TextOutW(mdc, 10, 32, buf, static_cast<int>(wcslen(buf)));

            // 3. Показать — одним BitBlt
            window.endFrame();
        }

        Sleep(1);
    }

    return 0;
}
