#pragma once
#include <windows.h>
#include <cstdint>

namespace SSE::Platform {

class Win32Window {
public:
    bool create(HINSTANCE hInst, int w, int h, const char* title);
    bool pumpMessages();

    std::uint32_t* beginFrame(int w, int h);
    void endFrame();

    HWND handle() const { return hwnd_; }
    HDC memDC() const { return memDC_; }

    float moveX() const;
    float moveY() const;

private:
    HWND hwnd_ = nullptr;
    HDC memDC_ = nullptr;
    HBITMAP dibBmp_ = nullptr;
    void* dibBits_ = nullptr;
    int dibW_ = 0, dibH_ = 0;

    bool ensureDIB(HDC hdc, int w, int h);
};

} // namespace SSE::Platform
