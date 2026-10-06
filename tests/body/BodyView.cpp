// ============================================================
// BodyView — визуальный тест тела
// Скелет + оболочка. Вертикальные волосы и талия.
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

constexpr int   WIN_W = 500;
constexpr int   WIN_H = 750;
constexpr float SCALE = 4.0f;

Body::Skeleton     g_skeleton;
Body::HumanAnatomy g_anatomy;

// --- см → экран ---
inline int SX(float wx) {
    return WIN_W / 2 + static_cast<int>(wx * SCALE);
}
inline int SY(float wz) {
    const float margin_bottom = 40.0f;
    return WIN_H - static_cast<int>(margin_bottom + wz * SCALE);
}

// ============================================================
// ОВАЛ
// ============================================================
void fillEllipse(HDC hdc, float cx, float cz,
                 float w_cm, float h_cm, COLORREF color)
{
    int sx = SX(cx);
    int sy = SY(cz);
    int half_w = static_cast<int>(w_cm * SCALE * 0.5f);
    int half_h = static_cast<int>(h_cm * SCALE * 0.5f);
    if (half_w < 1) half_w = 1;
    if (half_h < 1) half_h = 1;

    HBRUSH br  = CreateSolidBrush(color);
    HPEN   pen = CreatePen(PS_SOLID, 1, color);
    HBRUSH oldBr  = static_cast<HBRUSH>(SelectObject(hdc, br));
    HPEN   oldPen = static_cast<HPEN>(SelectObject(hdc, pen));

    Ellipse(hdc, sx - half_w, sy - half_h, sx + half_w, sy + half_h);

    SelectObject(hdc, oldBr);
    SelectObject(hdc, oldPen);
    DeleteObject(br);
    DeleteObject(pen);
}

// ============================================================
// КАПСУЛА — толстая линия с круглыми концами
// ============================================================
void drawCapsule(HDC hdc, float x1, float z1, float x2, float z2,
                 float thickness_cm, COLORREF color)
{
    int thickness_px = static_cast<int>(thickness_cm * SCALE);
    if (thickness_px < 2) thickness_px = 2;

    HPEN pen = CreatePen(PS_SOLID | PS_ENDCAP_ROUND,
                         thickness_px, color);
    HPEN oldPen = static_cast<HPEN>(SelectObject(hdc, pen));

    MoveToEx(hdc, SX(x1), SY(z1), nullptr);
    LineTo  (hdc, SX(x2), SY(z2));

    SelectObject(hdc, oldPen);
    DeleteObject(pen);
}

// ============================================================
// ТЕЛО
// ============================================================
void drawBody(HDC hdc) {
    const COLORREF cBG     = RGB(20, 20, 30);
    const COLORREF cSkin   = RGB(220, 180, 140);
    const COLORREF cShirt  = RGB(80, 100, 160);
    const COLORREF cPants  = RGB(60, 70, 100);
    const COLORREF cShoes  = RGB(40, 30, 25);
    const COLORREF cHair   = RGB(60, 40, 25);
    const COLORREF cGround = RGB(100, 80, 60);
    const COLORREF cText   = RGB(200, 200, 200);

    RECT rc = {0, 0, WIN_W, WIN_H};
    HBRUSH bg = CreateSolidBrush(cBG);
    FillRect(hdc, &rc, bg);
    DeleteObject(bg);

    const auto& s = g_skeleton;
    const auto& A = g_anatomy;

    // --- Линия земли ---
    {
        HPEN gp = CreatePen(PS_SOLID, 2, cGround);
        HPEN op = static_cast<HPEN>(SelectObject(hdc, gp));
        MoveToEx(hdc, 0, SY(0), nullptr);
        LineTo  (hdc, WIN_W, SY(0));
        SelectObject(hdc, op);
        DeleteObject(gp);
    }

    // ========================================================
    // НОГИ (задний план)
    // ========================================================
    drawCapsule(hdc, s.hip_left.x, s.hip_left.z,
                     s.knee_left.x, s.knee_left.z,
                     A.leg.thigh_width, cPants);
    drawCapsule(hdc, s.hip_right.x, s.hip_right.z,
                     s.knee_right.x, s.knee_right.z,
                     A.leg.thigh_width, cPants);

    drawCapsule(hdc, s.knee_left.x, s.knee_left.z,
                     s.ankle_left.x, s.ankle_left.z,
                     A.leg.calf_width, cPants);
    drawCapsule(hdc, s.knee_right.x, s.knee_right.z,
                     s.ankle_right.x, s.ankle_right.z,
                     A.leg.calf_width, cPants);

    fillEllipse(hdc, s.ankle_left.x,  s.ankle_left.z,
                     A.leg.foot_width, A.leg.ankle_height * 2.0f, cShoes);
    fillEllipse(hdc, s.ankle_right.x, s.ankle_right.z,
                     A.leg.foot_width, A.leg.ankle_height * 2.0f, cShoes);

    // ========================================================
    // ТОРС
    // ========================================================
    // Таз — штаны
    fillEllipse(hdc, 0, s.pelvis.z,
                     A.torso.pelvis_width, A.torso.pelvis_height, cPants);

    // Талия — ВЕРТИКАЛЬНЫЙ овал (перекрывает таз и грудь)
    {
        float waist_draw_height = A.torso.waist_height + 18.0f;
        fillEllipse(hdc, 0, s.waist.z,
                         A.torso.waist_width, waist_draw_height, cShirt);
    }

    // Грудь
    fillEllipse(hdc, 0, s.chest.z,
                     A.torso.chest_width, A.torso.chest_height, cShirt);

    // Плечи — широкий овал сверху груди
    fillEllipse(hdc, 0, s.shoulder_left.z - 2.0f,
                     A.torso.shoulder_width, 14.0f, cShirt);

    // ========================================================
    // РУКИ
    // ========================================================
    // Рукава (плечо → локоть)
    drawCapsule(hdc, s.shoulder_left.x, s.shoulder_left.z,
                     s.elbow_left.x, s.elbow_left.z,
                     A.arm.upper_width, cShirt);
    drawCapsule(hdc, s.shoulder_right.x, s.shoulder_right.z,
                     s.elbow_right.x, s.elbow_right.z,
                     A.arm.upper_width, cShirt);

    // Предплечья (локоть → кисть) — кожа
    drawCapsule(hdc, s.elbow_left.x, s.elbow_left.z,
                     s.wrist_left.x, s.wrist_left.z,
                     A.arm.forearm_width, cSkin);
    drawCapsule(hdc, s.elbow_right.x, s.elbow_right.z,
                     s.wrist_right.x, s.wrist_right.z,
                     A.arm.forearm_width, cSkin);

    // Кисти
    fillEllipse(hdc, s.wrist_left.x,  s.wrist_left.z - 5.0f,
                     A.arm.hand_width, 12.0f, cSkin);
    fillEllipse(hdc, s.wrist_right.x, s.wrist_right.z - 5.0f,
                     A.arm.hand_width, 12.0f, cSkin);

    // ========================================================
    // ШЕЯ
    // ========================================================
    fillEllipse(hdc, 0, s.head_base.z,
                     A.head.neck_width, A.head.neck_height + 2.0f, cSkin);

    // ========================================================
    // ГОЛОВА
    // ========================================================
    fillEllipse(hdc, 0, s.head_center.z,
                     A.head.width, A.head.height, cSkin);

    // ========================================================
    // ВОЛОСЫ — вертикальный овал
    // ========================================================
    {
        float hair_width    = A.head.width - 2.0f;
        float hair_height   = A.head.height * 0.85f;
        float hair_center_z = s.head_center.z + A.head.height * 0.15f;

        fillEllipse(hdc, 0, hair_center_z,
                         hair_width, hair_height, cHair);
    }

    // ========================================================
    // ИНФО
    // ========================================================
    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, cText);

    std::wstring title = L"Body — STANDARD_MALE 175 cm";
    TextOutW(hdc, 10, 10, title.c_str(), static_cast<int>(title.size()));

    wchar_t buf[128];
    swprintf_s(buf, L"Scale: %.1f px/cm", SCALE);
    TextOutW(hdc, 10, 30, buf, static_cast<int>(wcslen(buf)));

    SetTextColor(hdc, RGB(140, 140, 160));
    struct Mark { float z; const wchar_t* name; };
    Mark marks[] = {
        { 175, L"head"     },
        { 143, L"shoulder" },
        { 130, L"chest"    },
        { 105, L"waist"    },
        {  89, L"pelvis"   },
        {  84, L"hip"      },
        {  48, L"knee"     },
        {   6, L"foot"     },
        {   0, L"ground"   },
    };
    for (const auto& m : marks) {
        int y = SY(m.z);
        swprintf_s(buf, L"%s   %.0f", m.name, m.z);
        TextOutW(hdc, WIN_W - 140, y - 8, buf, static_cast<int>(wcslen(buf)));
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
            drawBody(hdc);
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
    g_anatomy  = Body::STANDARD_MALE;

    const char* CLASS_NAME = "BodyViewWnd";
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

    HWND hwnd = CreateWindow(CLASS_NAME, "Body View",
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
