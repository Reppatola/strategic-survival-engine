// ============================================================
// Win32Window.cpp — окно + DIB (безопасная версия)
// ============================================================
#include "platform/Win32Window.h"
#include <cstring>

namespace SSE::Platform {

// ============================================================
// WndProc
// ============================================================
static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
                                WPARAM wParam, LPARAM lParam)
{
    switch (msg) {
        case WM_ERASEBKGND:
            return 1;   // не стирать фон

        case WM_KEYDOWN:
            if (wParam == VK_ESCAPE) PostQuitMessage(0);
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// ============================================================
// create
// ============================================================
bool Win32Window::create(HINSTANCE hInst, int w, int h, const char* title) {
    const char* CLASS_NAME = "SSEPrototypeWnd";

    WNDCLASS wc = {};
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInst;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
    wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
    RegisterClass(&wc);

    RECT rect = {0, 0, w, h};
    AdjustWindowRect(&rect,
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
        FALSE);

    hwnd_ = CreateWindow(
        CLASS_NAME, title,
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT,
        rect.right - rect.left,
        rect.bottom - rect.top,
        nullptr, nullptr, hInst, nullptr);

    if (!hwnd_) return false;

    ShowWindow(hwnd_, SW_SHOW);
    SetFocus(hwnd_);
    return true;
}

// ============================================================
// pumpMessages
// ============================================================
bool Win32Window::pumpMessages() {
    MSG msg;
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) return false;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return true;
}

// ============================================================
// ensureDIB
// ============================================================
bool Win32Window::ensureDIB(HDC hdc, int w, int h) {
    if (dibBits_ && dibW_ == w && dibH_ == h) return true;

    if (dibBmp_) { DeleteObject(dibBmp_); dibBmp_ = nullptr; }
    if (memDC_)  { DeleteDC(memDC_);      memDC_  = nullptr; }

    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth       = w;
    bmi.bmiHeader.biHeight      = -h;
    bmi.bmiHeader.biPlanes      = 1;
    bmi.bmiHeader.biBitCount    = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    dibBmp_ = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS,
                               &dibBits_, nullptr, 0);
    if (!dibBmp_) return false;

    memDC_ = CreateCompatibleDC(hdc);
    SelectObject(memDC_, dibBmp_);

    dibW_ = w;
    dibH_ = h;
    return true;
}

// ============================================================
// beginFrame
// ============================================================
std::uint32_t* Win32Window::beginFrame(int w, int h) {
    HDC hdc = GetDC(hwnd_);
    bool ok = ensureDIB(hdc, w, h);
    ReleaseDC(hwnd_, hdc);
    if (!ok) return nullptr;
    return reinterpret_cast<std::uint32_t*>(dibBits_);
}

// ============================================================
// endFrame — простой BitBlt без VSync
// ============================================================
void Win32Window::endFrame() {
    HDC hdc = GetDC(hwnd_);
    BitBlt(hdc, 0, 0, dibW_, dibH_, memDC_, 0, 0, SRCCOPY);
    ReleaseDC(hwnd_, hdc);
}

// ============================================================
// Ввод
// ============================================================
float Win32Window::moveX() const {
    float x = 0.0f;
    if (GetAsyncKeyState('A') & 0x8000) x -= 1.0f;
    if (GetAsyncKeyState('D') & 0x8000) x += 1.0f;
    return x;
}

float Win32Window::moveY() const {
    float y = 0.0f;
    if (GetAsyncKeyState('W') & 0x8000) y -= 1.0f;
    if (GetAsyncKeyState('S') & 0x8000) y += 1.0f;
    return y;
}

} // namespace SSE::Platform
