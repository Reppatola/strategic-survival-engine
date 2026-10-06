// ============================================================
// HeroTopDown — вид сверху героя ИЗ СРЕЗОВ
// Никаких овалов. Только данные.
// ============================================================
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <cmath>
#include <cstdio>
#include <string>

#include "data/characters/hero1/hero1.h"

using namespace SSE::Hero1;
using namespace SSE::Characters;

constexpr int   WIN_W = 800;
constexpr int   WIN_H = 800;
constexpr float SCALE = 6.0f;   // пикселей на сантиметр

// ------------------------------------------------------------
// Мировые (см) → экран
// X тела (влево-вправо) → экран X
// Y тела (вперёд-назад) → экран Y
// ------------------------------------------------------------
inline int SX(float wx) {
    return WIN_W / 2 + static_cast<int>(wx * SCALE);
}
inline int SY(float wy) {
    return WIN_H / 2 + static_cast<int>(wy * SCALE);
}

// ------------------------------------------------------------
// Проверка: точка (x, y) внутри среза-эллипса
// ------------------------------------------------------------
bool pointInSlice(float x, float y, const HSlice& s) {
    float dx = x - s.offset_x;
    float dy = y - s.offset_y;
    float rx = s.width * 0.5f;
    float ry = s.depth * 0.5f;
    if (rx < 0.1f || ry < 0.1f) return false;
    return (dx * dx) / (rx * rx) + (dy * dy) / (ry * ry) <= 1.0f;
}

// ------------------------------------------------------------
// Найти верхний Z для точки (x, y)
// Возвращает: z-координату или -1, если ничего нет.
// part_out — указатель, куда записать ID части (для цвета).
// ------------------------------------------------------------
float highestZAt(float x, float y, int& part_out) {
    float best_z = -1.0f;
    int   best_part = -1;

    // Голова
    for (int i = 0; i < Head::H_SLICES_COUNT; ++i) {
        if (pointInSlice(x, y, Head::H_SLICES[i])) {
            if (Head::H_SLICES[i].z > best_z) {
                best_z = Head::H_SLICES[i].z;
                best_part = 0;  // ID = 0 (голова)
            }
        }
    }
    // Верх торса
    for (int i = 0; i < TorsoUpper::H_SLICES_COUNT; ++i) {
        if (pointInSlice(x, y, TorsoUpper::H_SLICES[i])) {
            if (TorsoUpper::H_SLICES[i].z > best_z) {
                best_z = TorsoUpper::H_SLICES[i].z;
                best_part = 1;
            }
        }
    }
    // Низ торса
    for (int i = 0; i < TorsoLower::H_SLICES_COUNT; ++i) {
        if (pointInSlice(x, y, TorsoLower::H_SLICES[i])) {
            if (TorsoLower::H_SLICES[i].z > best_z) {
                best_z = TorsoLower::H_SLICES[i].z;
                best_part = 2;
            }
        }
    }
    // Левая рука
    for (int i = 0; i < ArmLeft::H_SLICES_COUNT; ++i) {
        float lx = x - ArmLeft::ATTACH_X;
        float ly = y;
        if (pointInSlice(lx, ly, ArmLeft::H_SLICES[i])) {
            if (ArmLeft::H_SLICES[i].z > best_z) {
                best_z = ArmLeft::H_SLICES[i].z;
                best_part = 3;
            }
        }
    }
    // Правая рука
    for (int i = 0; i < ArmRight::H_SLICES_COUNT; ++i) {
        float lx = x - ArmRight::ATTACH_X;
        float ly = y;
        if (pointInSlice(lx, ly, ArmRight::H_SLICES[i])) {
            if (ArmRight::H_SLICES[i].z > best_z) {
                best_z = ArmRight::H_SLICES[i].z;
                best_part = 4;
            }
        }
    }
    // Левая нога
    for (int i = 0; i < LegLeft::H_SLICES_COUNT; ++i) {
        float lx = x - LegLeft::ATTACH_X;
        float ly = y;
        if (pointInSlice(lx, ly, LegLeft::H_SLICES[i])) {
            if (LegLeft::H_SLICES[i].z > best_z) {
                best_z = LegLeft::H_SLICES[i].z;
                best_part = 5;
            }
        }
    }
    // Правая нога
    for (int i = 0; i < LegRight::H_SLICES_COUNT; ++i) {
        float lx = x - LegRight::ATTACH_X;
        float ly = y;
        if (pointInSlice(lx, ly, LegRight::H_SLICES[i])) {
            if (LegRight::H_SLICES[i].z > best_z) {
                best_z = LegRight::H_SLICES[i].z;
                best_part = 6;
            }
        }
    }
    // Стопы
    for (int i = 0; i < FootLeft::H_SLICES_COUNT; ++i) {
        float lx = x - FootLeft::ATTACH_X;
        float ly = y;
        if (pointInSlice(lx, ly, FootLeft::H_SLICES[i])) {
            if (FootLeft::H_SLICES[i].z > best_z) {
                best_z = FootLeft::H_SLICES[i].z;
                best_part = 7;
            }
        }
    }
    for (int i = 0; i < FootRight::H_SLICES_COUNT; ++i) {
        float lx = x - FootRight::ATTACH_X;
        float ly = y;
        if (pointInSlice(lx, ly, FootRight::H_SLICES[i])) {
            if (FootRight::H_SLICES[i].z > best_z) {
                best_z = FootRight::H_SLICES[i].z;
                best_part = 8;
            }
        }
    }

    part_out = best_part;
    return best_z;
}

// ------------------------------------------------------------
// Цвет по ID части
// ------------------------------------------------------------
COLORREF colorForPart(int part) {
    switch (part) {
        case 0: return RGB( 90,  65,  40);   // голова — волосы
        case 1: return RGB( 80, 100, 160);   // верх торса — рубашка
        case 2: return RGB( 60,  70, 100);   // низ торса — штаны
        case 3: return RGB( 80, 100, 160);   // левая рука
        case 4: return RGB( 80, 100, 160);   // правая рука
        case 5: return RGB( 60,  70, 100);   // левая нога
        case 6: return RGB( 60,  70, 100);   // правая нога
        case 7: return RGB( 40,  30,  25);   // левая стопа
        case 8: return RGB( 40,  30,  25);   // правая стопа
        default: return RGB( 20,  20,  30);
    }
}

// ------------------------------------------------------------
// Отрисовка
// ------------------------------------------------------------
void drawHeroTopDown(HDC hdc) {
    const COLORREF cBG   = RGB(20, 20, 30);
    const COLORREF cGrid = RGB(40, 40, 55);
    const COLORREF cText = RGB(200, 200, 200);

    RECT rc = {0, 0, WIN_W, WIN_H};
    HBRUSH bg = CreateSolidBrush(cBG);
    FillRect(hdc, &rc, bg);
    DeleteObject(bg);

    // Сетка 10 см
    {
        HPEN pen = CreatePen(PS_SOLID, 1, cGrid);
        HPEN oldPen = static_cast<HPEN>(SelectObject(hdc, pen));
        for (int x = -40; x <= 40; x += 10) {
            MoveToEx(hdc, SX(static_cast<float>(x)), 0, nullptr);
            LineTo  (hdc, SX(static_cast<float>(x)), WIN_H);
        }
        for (int y = -40; y <= 40; y += 10) {
            MoveToEx(hdc, 0, SY(static_cast<float>(y)), nullptr);
            LineTo  (hdc, WIN_W, SY(static_cast<float>(y)));
        }
        SelectObject(hdc, oldPen);
        DeleteObject(pen);
    }

    // --------------------------------------------------------
    // ГЛАВНОЕ: для каждой точки экрана — найти верхний Z
    // --------------------------------------------------------
    for (int sy = 0; sy < WIN_H; ++sy) {
        for (int sx = 0; sx < WIN_W; ++sx) {
            float wx = (sx - WIN_W / 2.0f) / SCALE;
            float wy = (sy - WIN_H / 2.0f) / SCALE;

            int part = -1;
            float z = highestZAt(wx, wy, part);

            if (z >= 0.0f && part >= 0) {
                // Цвет части + лёгкая тень по высоте
                COLORREF base = colorForPart(part);
                int r = GetRValue(base);
                int g = GetGValue(base);
                int b = GetBValue(base);

                // Чем выше — тем светлее
                float br = 0.6f + (z / 175.0f) * 0.4f;
                r = static_cast<int>(r * br);
                g = static_cast<int>(g * br);
                b = static_cast<int>(b * br);

                SetPixelV(hdc, sx, sy, RGB(r, g, b));
            }
        }
    }

    // Информация
    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, cText);

    wchar_t buf[256];
    swprintf_s(buf, L"Hero Top-Down — из срезов");
    TextOutW(hdc, 10, 10, buf, static_cast<int>(wcslen(buf)));

    swprintf_s(buf, L"Scale: %.1f px/cm", SCALE);
    TextOutW(hdc, 10, 32, buf, static_cast<int>(wcslen(buf)));

    swprintf_s(buf, L"Тело построено алгоритмом highestZAt(x, y)");
    TextOutW(hdc, 10, 54, buf, static_cast<int>(wcslen(buf)));
}

// ------------------------------------------------------------
// Win32
// ------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            drawHeroTopDown(hdc);
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_KEYDOWN:
            if (wParam == VK_ESCAPE) PostQuitMessage(0);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int) {
    const char* CLASS_NAME = "HeroTopDownWnd";
    WNDCLASS wc = {};
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInst;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
    wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
    RegisterClass(&wc);

    RECT rect = {0, 0, WIN_W, WIN_H};
    AdjustWindowRect(&rect,
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, FALSE);

    HWND hwnd = CreateWindow(CLASS_NAME, "Hero Top-Down (from slices)",
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT,
        rect.right - rect.left, rect.bottom - rect.top,
        nullptr, nullptr, hInst, nullptr);

    if (!hwnd) return 1;

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
