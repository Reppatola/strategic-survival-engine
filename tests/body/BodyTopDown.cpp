// ============================================================
// BodyTopDown — вид тела СВЕРХУ
// Что видит наблюдатель, глядя на героя вниз.
// Клавиши 1/2/3 — позы. ESC — выход.
// ============================================================
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <cmath>
#include <cstdio>
#include <string>

#include "data/body/Anatomy.h"
#include "data/body/Skeleton.h"
#include "data/body/BodyState.h"

using namespace SSE;
using namespace SSE::Body;

constexpr int   WIN_W = 600;
constexpr int   WIN_H = 700;
constexpr float SCALE = 5.0f;   // пикселей на сантиметр

Body::HumanAnatomy g_anatomy;
Body::Skeleton     g_skeleton;
Body::BodyState    g_state;

// --- см → экран ---
// X тела → X экрана (вправо)
// Y тела (вперёд) → Y экрана (вниз)
inline int SX(float wx) {
    return WIN_W / 2 + static_cast<int>(wx * SCALE);
}
inline int SY(float wy) {
    return WIN_H / 2 + static_cast<int>(wy * SCALE);
}

// ============================================================
// Овал по X (ширина) и Y (глубина)
// ============================================================
void fillEllipseXY(HDC hdc, float cx, float cy,
                   float w_cm, float d_cm, COLORREF color)
{
    int sx = SX(cx);
    int sy = SY(cy);
    int half_w = static_cast<int>(w_cm * SCALE * 0.5f);
    int half_d = static_cast<int>(d_cm * SCALE * 0.5f);
    if (half_w < 1) half_w = 1;
    if (half_d < 1) half_d = 1;

    HBRUSH br  = CreateSolidBrush(color);
    HPEN   pen = CreatePen(PS_SOLID, 1, color);
    HBRUSH oldBr  = static_cast<HBRUSH>(SelectObject(hdc, br));
    HPEN   oldPen = static_cast<HPEN>(SelectObject(hdc, pen));

    Ellipse(hdc, sx - half_w, sy - half_d, sx + half_w, sy + half_d);

    SelectObject(hdc, oldBr);
    SelectObject(hdc, oldPen);
    DeleteObject(br);
    DeleteObject(pen);
}

// ============================================================
// Капсула — для рук и ног при движении
// ============================================================
void drawCapsuleXY(HDC hdc,
                   float x1, float y1,
                   float x2, float y2,
                   float thickness_cm,
                   COLORREF color)
{
    int t = static_cast<int>(thickness_cm * SCALE);
    if (t < 2) t = 2;

    HPEN pen = CreatePen(PS_SOLID | PS_ENDCAP_ROUND, t, color);
    HPEN oldPen = static_cast<HPEN>(SelectObject(hdc, pen));

    MoveToEx(hdc, SX(x1), SY(y1), nullptr);
    LineTo  (hdc, SX(x2), SY(y2));

    SelectObject(hdc, oldPen);
    DeleteObject(pen);
}

// ============================================================
// Отрисовка тела сверху
// ============================================================
void drawBodyTopDown(HDC hdc) {
    const COLORREF cBG     = RGB(20, 20, 30);
    const COLORREF cSkin   = RGB(220, 180, 140);
    const COLORREF cShirt  = RGB(80, 100, 160);
    const COLORREF cPants  = RGB(60, 70, 100);
    const COLORREF cShoes  = RGB(40, 30, 25);
    const COLORREF cHair   = RGB(60, 40, 25);
    const COLORREF cText   = RGB(200, 200, 200);
    const COLORREF cHint   = RGB(140, 140, 140);
    const COLORREF cGrid   = RGB(40, 40, 55);

    // Фон
    RECT rc = {0, 0, WIN_W, WIN_H};
    HBRUSH bg = CreateSolidBrush(cBG);
    FillRect(hdc, &rc, bg);
    DeleteObject(bg);

    const auto& A = g_anatomy;

    // Сетка — 10 см
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

    // Смещения ног и рук по позе
    float leftLegY  = 0.0f, rightLegY = 0.0f;
    float leftArmY  = 0.0f, rightArmY = 0.0f;

    if (g_state.pose == Pose::WALKING) {
        leftLegY  = +12.0f;
        rightLegY = -12.0f;
        leftArmY  =  -8.0f;
        rightArmY =  +8.0f;
    } else if (g_state.pose == Pose::RUNNING) {
        leftLegY  = +22.0f;
        rightLegY = -22.0f;
        leftArmY  = -15.0f;
        rightArmY = +15.0f;
    }

    // --------------------------------------------------------
    // Слой 1: СТОПЫ — только то, что выступает за торс
    // --------------------------------------------------------
    float hip_x = A.torso.pelvis_width * 0.25f;

    // Стопы видны, только когда отходят от тела (при движении)
    if (std::abs(leftLegY) > 8.0f) {
        fillEllipseXY(hdc, -hip_x, leftLegY * 0.55f,
                      A.leg.foot_width, A.leg.foot_length * 0.7f, cShoes);
    }
    if (std::abs(rightLegY) > 8.0f) {
        fillEllipseXY(hdc,  hip_x, rightLegY * 0.55f,
                      A.leg.foot_width, A.leg.foot_length * 0.7f, cShoes);
    }

    // --------------------------------------------------------
    // Слой 2: РУКИ (по бокам, могут выступать вперёд/назад)
    // --------------------------------------------------------
    float arm_offset = A.torso.chest_width * 0.5f - 4.0f;

    drawCapsuleXY(hdc, -arm_offset, 0.0f, -arm_offset, leftArmY,
                  A.arm.upper_width, cShirt);
    drawCapsuleXY(hdc,  arm_offset, 0.0f,  arm_offset, rightArmY,
                  A.arm.upper_width, cShirt);

    // Кисти — видны ТОЛЬКО когда руки вынесены вперёд/назад (при движении)
    if (std::abs(leftArmY) > 3.0f) {
        fillEllipseXY(hdc, -arm_offset, leftArmY,
                      A.arm.hand_width, A.arm.hand_length * 0.6f, cSkin);
    }
    if (std::abs(rightArmY) > 3.0f) {
        fillEllipseXY(hdc,  arm_offset, rightArmY,
                      A.arm.hand_width, A.arm.hand_length * 0.6f, cSkin);
    }

    // --------------------------------------------------------
    // Слой 3: ТАЗ
    // --------------------------------------------------------
    fillEllipseXY(hdc, 0, 0,
                  A.torso.pelvis_width, A.torso.pelvis_depth, cPants);

    // --------------------------------------------------------
    // Слой 4: ТАЛИЯ
    // --------------------------------------------------------
    fillEllipseXY(hdc, 0, 0,
                  A.torso.waist_width, A.torso.waist_depth, cShirt);

    // --------------------------------------------------------
    // Слой 5: ГРУДЬ
    // --------------------------------------------------------
    fillEllipseXY(hdc, 0, 0,
                  A.torso.chest_width, A.torso.chest_depth, cShirt);

    // --------------------------------------------------------
    // Слой 6: ШЕЯ
    // --------------------------------------------------------
    fillEllipseXY(hdc, 0, 0,
                  A.head.neck_width, A.head.neck_width, cSkin);

    // --------------------------------------------------------
    // Слой 7: ГОЛОВА (макушка)
    // Сверху видим волосы.
    // --------------------------------------------------------
    fillEllipseXY(hdc, 0, 0,
                  A.head.width, A.head.depth, cHair);

    // --------------------------------------------------------
    // Индикатор направления взгляда — маленький треугольник
    // на макушке (куда смотрит герой).
    // --------------------------------------------------------
    {
        float fx = 0.0f;
        float fy = A.head.depth * 0.5f + 2.0f;   // чуть впереди головы

        POINT tri[3];
        tri[0] = { SX(fx),       SY(fy) };              // кончик
        tri[1] = { SX(fx - 2.0f), SY(fy - 3.0f) };
        tri[2] = { SX(fx + 2.0f), SY(fy - 3.0f) };

        HBRUSH br = CreateSolidBrush(RGB(220, 60, 60));
        HPEN   pen = CreatePen(PS_SOLID, 1, RGB(220, 60, 60));
        HBRUSH oldBr  = static_cast<HBRUSH>(SelectObject(hdc, br));
        HPEN   oldPen = static_cast<HPEN>(SelectObject(hdc, pen));

        Polygon(hdc, tri, 3);

        SelectObject(hdc, oldBr);
        SelectObject(hdc, oldPen);
        DeleteObject(br);
        DeleteObject(pen);
    }

    // --------------------------------------------------------
    // ИНФО
    // --------------------------------------------------------
    SetBkMode(hdc, TRANSPARENT);

    SetTextColor(hdc, cText);
    wchar_t buf[256];

    const wchar_t* pose_name = L"СТОИТ";
    if (g_state.pose == Pose::WALKING) pose_name = L"ИДЁТ";
    if (g_state.pose == Pose::RUNNING) pose_name = L"БЕЖИТ";

    swprintf_s(buf, L"Body TopDown — %s", pose_name);
    TextOutW(hdc, 10, 10, buf, static_cast<int>(wcslen(buf)));

    swprintf_s(buf, L"Scale: %.1f px/cm", SCALE);
    TextOutW(hdc, 10, 32, buf, static_cast<int>(wcslen(buf)));

    SetTextColor(hdc, cHint);
    swprintf_s(buf, L"1 — стоит   2 — идёт   3 — бежит   ESC — выход");
    TextOutW(hdc, 10, 56, buf, static_cast<int>(wcslen(buf)));

    // Метки размеров
    SetTextColor(hdc, RGB(120, 200, 255));
    swprintf_s(buf, L"плечи:  44 см");
    TextOutW(hdc, 10, WIN_H - 80, buf, static_cast<int>(wcslen(buf)));

    swprintf_s(buf, L"таз:    34 см");
    TextOutW(hdc, 10, WIN_H - 60, buf, static_cast<int>(wcslen(buf)));

    swprintf_s(buf, L"голова: 16 × 20 см");
    TextOutW(hdc, 10, WIN_H - 40, buf, static_cast<int>(wcslen(buf)));

    swprintf_s(buf, L"герой 175 см  |  вид СВЕРХУ");
    TextOutW(hdc, 10, WIN_H - 20, buf, static_cast<int>(wcslen(buf)));
}

// ============================================================
// Win32
// ============================================================
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            drawBodyTopDown(hdc);
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_KEYDOWN:
            if (wParam == VK_ESCAPE) PostQuitMessage(0);
            if (wParam == '1') { g_state.pose = Pose::STANDING;
                                 InvalidateRect(hwnd, nullptr, TRUE); }
            if (wParam == '2') { g_state.pose = Pose::WALKING;
                                 InvalidateRect(hwnd, nullptr, TRUE); }
            if (wParam == '3') { g_state.pose = Pose::RUNNING;
                                 InvalidateRect(hwnd, nullptr, TRUE); }
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int) {
    g_anatomy  = Body::STANDARD_MALE;
    g_skeleton = Body::Skeleton::fromAnatomy(g_anatomy, 0.0f);

    g_state.pose   = Pose::STANDING;
    g_state.facing = Facing::S;

    const char* CLASS_NAME = "BodyTopDownWnd";
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

    HWND hwnd = CreateWindow(CLASS_NAME, "Body Top-Down",
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
