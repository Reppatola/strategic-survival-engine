// ============================================================
// SkeletonView — визуальный тест скелета
// Вид СПЕРЕДИ. Показывает пропорции тела.
// ============================================================
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <cmath>
#include <cstdio>
#include <string>

#include "data/body/Anatomy.h"
#include "data/body/Skeleton.h"

using namespace SSE;
using namespace SSE::Body;

// --- Параметры окна ---
constexpr int   WIN_W = 400;
constexpr int   WIN_H = 750;
constexpr float SCALE = 4.0f;   // пикселей на сантиметр

Body::Skeleton g_skeleton;


// ============================================================
// Координаты скелета (см) → экран (px)
//   X скелета → X экрана
//   Z скелета → Y экрана (инвертирован: z=0 внизу)
// ============================================================
inline int SX(float wx) {
    return WIN_W / 2 + static_cast<int>(wx * SCALE);
}

inline int SY(float wz) {
    const float margin_bottom = 40.0f;
    return WIN_H - static_cast<int>(margin_bottom + wz * SCALE);
}


// ============================================================
// Рисование
// ============================================================
void drawPoint(HDC hdc, float x, float z, COLORREF color, int radius = 5) {
    int sx = SX(x);
    int sy = SY(z);

    HBRUSH br = CreateSolidBrush(color);
    HPEN   pen = CreatePen(PS_SOLID, 1, color);
    HBRUSH oldBr = static_cast<HBRUSH>(SelectObject(hdc, br));
    HPEN   oldPen = static_cast<HPEN>(SelectObject(hdc, pen));

    Ellipse(hdc, sx - radius, sy - radius, sx + radius, sy + radius);

    SelectObject(hdc, oldBr);
    SelectObject(hdc, oldPen);
    DeleteObject(br);
    DeleteObject(pen);
}

void drawBone(HDC hdc, float x1, float z1, float x2, float z2,
              COLORREF color, int width = 3)
{
    HPEN pen = CreatePen(PS_SOLID, width, color);
    HPEN oldPen = static_cast<HPEN>(SelectObject(hdc, pen));

    MoveToEx(hdc, SX(x1), SY(z1), nullptr);
    LineTo(hdc, SX(x2), SY(z2));

    SelectObject(hdc, oldPen);
    DeleteObject(pen);
}

void drawSkeleton(HDC hdc) {
    // Цвета
    const COLORREF cBG     = RGB(20, 20, 30);
    const COLORREF cBone   = RGB(220, 220, 220);
    const COLORREF cJoint  = RGB(100, 200, 255);
    const COLORREF cHead   = RGB(255, 220, 100);
    const COLORREF cFoot   = RGB(200, 100, 100);
    const COLORREF cGround = RGB(100, 80, 60);
    const COLORREF cText   = RGB(200, 200, 200);

    // Фон
    RECT rc = {0, 0, WIN_W, WIN_H};
    HBRUSH bg = CreateSolidBrush(cBG);
    FillRect(hdc, &rc, bg);
    DeleteObject(bg);

    const auto& s = g_skeleton;

    // --- ГОЛОВА ---
    drawBone(hdc, s.head_top.x, s.head_top.z,
                  s.head_center.x, s.head_center.z, cBone, 2);
    drawBone(hdc, s.head_center.x, s.head_center.z,
                  s.head_base.x, s.head_base.z, cBone, 2);

    // --- ПОЗВОНОЧНИК ---
    drawBone(hdc, s.head_base.x, s.head_base.z,
                  s.chest.x, s.chest.z, cBone);
    drawBone(hdc, s.chest.x, s.chest.z,
                  s.waist.x, s.waist.z, cBone);
    drawBone(hdc, s.waist.x, s.waist.z,
                  s.pelvis.x, s.pelvis.z, cBone);

    // --- ПЛЕЧИ ---
    drawBone(hdc, s.shoulder_left.x, s.shoulder_left.z,
                  s.shoulder_right.x, s.shoulder_right.z, cBone, 5);

    // --- РУКИ ---
    drawBone(hdc, s.shoulder_left.x, s.shoulder_left.z,
                  s.elbow_left.x, s.elbow_left.z, cBone);
    drawBone(hdc, s.elbow_left.x, s.elbow_left.z,
                  s.wrist_left.x, s.wrist_left.z, cBone);
    drawBone(hdc, s.shoulder_right.x, s.shoulder_right.z,
                  s.elbow_right.x, s.elbow_right.z, cBone);
    drawBone(hdc, s.elbow_right.x, s.elbow_right.z,
                  s.wrist_right.x, s.wrist_right.z, cBone);

    // --- ТАЗ → БЁДРА ---
    drawBone(hdc, s.pelvis.x, s.pelvis.z,
                  s.hip_left.x, s.hip_left.z, cBone);
    drawBone(hdc, s.pelvis.x, s.pelvis.z,
                  s.hip_right.x, s.hip_right.z, cBone);

    // --- НОГИ ---
    drawBone(hdc, s.hip_left.x, s.hip_left.z,
                  s.knee_left.x, s.knee_left.z, cBone);
    drawBone(hdc, s.knee_left.x, s.knee_left.z,
                  s.ankle_left.x, s.ankle_left.z, cBone);
    drawBone(hdc, s.hip_right.x, s.hip_right.z,
                  s.knee_right.x, s.knee_right.z, cBone);
    drawBone(hdc, s.knee_right.x, s.knee_right.z,
                  s.ankle_right.x, s.ankle_right.z, cBone);

    // --- ТОЧКИ ---
    // Голова
    drawPoint(hdc, s.head_top.x,    s.head_top.z,    cHead, 6);
    drawPoint(hdc, s.head_center.x, s.head_center.z, cHead, 6);
    drawPoint(hdc, s.head_base.x,   s.head_base.z,   cJoint);

    // Плечи
    drawPoint(hdc, s.shoulder_left.x,  s.shoulder_left.z,  cJoint, 7);
    drawPoint(hdc, s.shoulder_right.x, s.shoulder_right.z, cJoint, 7);

    // Позвоночник
    drawPoint(hdc, s.chest.x,  s.chest.z,  cJoint);
    drawPoint(hdc, s.waist.x,  s.waist.z,  cJoint);
    drawPoint(hdc, s.pelvis.x, s.pelvis.z, cJoint);

    // Таз
    drawPoint(hdc, s.hip_left.x,  s.hip_left.z,  cJoint);
    drawPoint(hdc, s.hip_right.x, s.hip_right.z, cJoint);

    // Колени
    drawPoint(hdc, s.knee_left.x,  s.knee_left.z,  cJoint);
    drawPoint(hdc, s.knee_right.x, s.knee_right.z, cJoint);

    // Стопы
    drawPoint(hdc, s.ankle_left.x,  s.ankle_left.z,  cFoot);
    drawPoint(hdc, s.ankle_right.x, s.ankle_right.z, cFoot);

    // Локти, кисти
    drawPoint(hdc, s.elbow_left.x,  s.elbow_left.z,  cJoint);
    drawPoint(hdc, s.elbow_right.x, s.elbow_right.z, cJoint);
    drawPoint(hdc, s.wrist_left.x,  s.wrist_left.z,  cJoint);
    drawPoint(hdc, s.wrist_right.x, s.wrist_right.z, cJoint);

    // --- ЛИНИЯ ЗЕМЛИ ---
    HPEN groundPen = CreatePen(PS_SOLID, 2, cGround);
    HPEN oldPen = static_cast<HPEN>(SelectObject(hdc, groundPen));
    MoveToEx(hdc, 0, SY(0), nullptr);
    LineTo(hdc, WIN_W, SY(0));
    SelectObject(hdc, oldPen);
    DeleteObject(groundPen);

    // --- ИНФО ---
    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, cText);

    std::wstring title = L"Skeleton — STANDARD_MALE 175 cm";
    TextOutW(hdc, 10, 10, title.c_str(), static_cast<int>(title.size()));

    wchar_t buf[128];
    swprintf_s(buf, L"Scale: %.1f px/cm", SCALE);
    TextOutW(hdc, 10, 30, buf, static_cast<int>(wcslen(buf)));

    // Метки высот справа
    SetTextColor(hdc, RGB(140, 140, 160));
    struct Mark { float z; const wchar_t* name; };
    Mark marks[] = {
        { 175, L"head      175" },
        { 143, L"shoulder  143" },
        { 130, L"chest     130" },
        { 105, L"waist     105" },
        {  84, L"hip        84" },
        {  48, L"knee       48" },
        {   6, L"foot        6" },
        {   0, L"ground      0" },
    };
    for (const auto& m : marks) {
        int y = SY(m.z);
        swprintf_s(buf, L"%s", m.name);
        TextOutW(hdc, WIN_W - 130, y - 8, buf, static_cast<int>(wcslen(buf)));
    }
}


// ============================================================
// Win32
// ============================================================
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            drawSkeleton(hdc);
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
    g_skeleton = Body::Skeleton::fromAnatomy(Body::STANDARD_MALE, 0.0f);

    const char* CLASS_NAME = "SkeletonViewWnd";
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

    HWND hwnd = CreateWindow(CLASS_NAME, "Skeleton View",
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
