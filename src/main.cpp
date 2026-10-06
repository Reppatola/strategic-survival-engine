// ============================================================
// SSE Prototype — ШАР + кэш ячеек + DIB Section (60 FPS)
// ============================================================
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <vector>
#include <map>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <chrono>
#include <cstdio>
#include <algorithm>

#include "core/Color.h"
#include "core/Screen.h"
#include "core/Random.h"
#include "data/grass/GrassType.h"
#include "data/grass/GrassBlade.h"
#include "data/objects/Cylinder.h"

using namespace SSE;

constexpr int SCR_W = 1000;
constexpr int SCR_H = 900;
constexpr int CXP = SCR_W / 2;
constexpr int CYP = SCR_H / 2;

// --- ШАР ---
constexpr int CELL_SIZE    = 64;
constexpr int WORLD_CELLS  = 48;
constexpr int WORLD_SIZE   = WORLD_CELLS * CELL_SIZE;

// --- Радиусы ---
constexpr float R_CORE = 180.0f;
constexpr float R_FADE = 380.0f;
constexpr float R_LOAD = 450.0f;

// --- Плотность травы ---
constexpr float CELL_DENSITY = 0.06f;

// ============================================================
// ХЕЛПЕРЫ ШАРА
// ============================================================
inline float wrapFloat(float v) {
    v = std::fmod(v, static_cast<float>(WORLD_SIZE));
    if (v < 0) v += WORLD_SIZE;
    return v;
}
inline int wrapCell(int i) {
    i %= WORLD_CELLS;
    if (i < 0) i += WORLD_CELLS;
    return i;
}
inline float wrapDelta(float d) {
    d = std::fmod(d + WORLD_SIZE * 0.5f, static_cast<float>(WORLD_SIZE));
    if (d < 0) d += WORLD_SIZE;
    return d - WORLD_SIZE * 0.5f;
}

// ============================================================
// FADE MASK — таблица затухания (считается ОДИН РАЗ)
// ============================================================
std::uint8_t g_fade_mask[SCR_W * SCR_H];

void buildFadeMask() {
    const float r_core_sq = R_CORE * R_CORE;
    const float r_fade_sq = R_FADE * R_FADE;
    const float inv_range = 1.0f / (R_FADE - R_CORE);

    for (int y = 0; y < SCR_H; ++y) {
        float dy = static_cast<float>(y - CYP);
        float dy2 = dy * dy;
        std::uint8_t* row = &g_fade_mask[y * SCR_W];

        for (int x = 0; x < SCR_W; ++x) {
            float dx = static_cast<float>(x - CXP);
            float sq = dx * dx + dy2;

            if (sq >= r_fade_sq) {
                row[x] = 0;
            } else if (sq <= r_core_sq) {
                row[x] = 255;
            } else {
                float d = std::sqrt(sq);
                float a = 1.0f - (d - R_CORE) * inv_range;
                if (a < 0) a = 0;
                row[x] = static_cast<std::uint8_t>(a * 255.0f);
            }
        }
    }
}

// ============================================================
// КЭШ ЯЧЕЙКИ
// ============================================================
struct CachedCell {
    std::vector<std::uint32_t> pixels;
    int min_x = 0, min_y = 0, max_x = 0, max_y = 0;
    std::uint8_t has_data = 0;
};

std::map<std::pair<int,int>, CachedCell> g_cells;
GrassType g_grassType = GrassType::meadow();
Cylinder g_cyl;

// ============================================================
// УТИЛИТЫ
// ============================================================
inline void putPixelBGRA(std::uint32_t* buf, int w, int h,
                         int x, int y, std::uint32_t color) {
    if (static_cast<unsigned>(x) >= static_cast<unsigned>(w)) return;
    if (static_cast<unsigned>(y) >= static_cast<unsigned>(h)) return;
    buf[y * w + x] = color;
}

inline std::uint32_t colorFromRGB(std::uint8_t r, std::uint8_t g, std::uint8_t b) {
    return (0xFFu << 24)
         | (static_cast<std::uint32_t>(r) << 16)
         | (static_cast<std::uint32_t>(g) << 8)
         | static_cast<std::uint32_t>(b);
}

void drawLineToBuffer(std::uint32_t* buf, int w, int h,
                      int x1, int y1, int x2, int y2,
                      std::uint32_t color) {
    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        putPixelBGRA(buf, w, h, x1, y1, color);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx)  { err += dx; y1 += sy; }
    }
}

// ============================================================
// СОЗДАНИЕ ЯЧЕЙКИ
// ============================================================
void loadCell(int ix, int iy) {
    int wix = wrapCell(ix);
    int wiy = wrapCell(iy);
    auto key = std::make_pair(wix, wiy);
    if (g_cells.find(key) != g_cells.end()) return;

    std::uint32_t seed =
        static_cast<std::uint32_t>(wix * 73856093) ^
        static_cast<std::uint32_t>(wiy * 19349663) ^ 0x9e3779b9u;
    Random rng(seed);

    CachedCell cell;
    cell.pixels.assign(CELL_SIZE * CELL_SIZE, 0);
    cell.has_data = 1;

    int min_x = CELL_SIZE, min_y = CELL_SIZE;
    int max_x = -1, max_y = -1;

    int count = static_cast<int>(CELL_SIZE * CELL_SIZE * CELL_DENSITY);

    for (int i = 0; i < count; ++i) {
        float bx = rng.floatRange(0.0f, static_cast<float>(CELL_SIZE - 1));
        float by = rng.floatRange(0.0f, static_cast<float>(CELL_SIZE - 1));

        GrassBlade blade = GrassBlade::create(0, 0, g_grassType, rng);
        int bxi = static_cast<int>(bx);
        int byi = static_cast<int>(by);

        for (const auto& leaf : blade.leaves) {
            int tip_x = bxi + static_cast<int>(
                std::cos(leaf.angle_rad) * leaf.length_px);
            int tip_y = byi + static_cast<int>(
                std::sin(leaf.angle_rad) * leaf.length_px);

            std::uint32_t col = colorFromRGB(leaf.color.r,
                                             leaf.color.g,
                                             leaf.color.b);
            drawLineToBuffer(cell.pixels.data(), CELL_SIZE, CELL_SIZE,
                             bxi, byi, tip_x, tip_y, col);

            int lx = std::min(bxi, tip_x);
            int ly = std::min(byi, tip_y);
            int rx = std::max(bxi, tip_x);
            int ry = std::max(byi, tip_y);
            if (lx < min_x) min_x = lx;
            if (ly < min_y) min_y = ly;
            if (rx > max_x) max_x = rx;
            if (ry > max_y) max_y = ry;
        }
    }

    if (max_x < min_x || max_y < min_y) {
        cell.has_data = 0;
    } else {
        cell.min_x = std::max(0, min_x);
        cell.min_y = std::max(0, min_y);
        cell.max_x = std::min(CELL_SIZE - 1, max_x);
        cell.max_y = std::min(CELL_SIZE - 1, max_y);
    }

    g_cells[key] = std::move(cell);
}

// ============================================================
// СТРИМИНГ
// ============================================================
void streamWorld() {
    float cx = static_cast<float>(g_cyl.x);
    float cy = static_cast<float>(g_cyl.y);

    int ccx = static_cast<int>(std::floor(cx / CELL_SIZE));
    int ccy = static_cast<int>(std::floor(cy / CELL_SIZE));

    int r_cells = static_cast<int>(R_LOAD / CELL_SIZE) + 1;
    float load_r2 = (R_LOAD + CELL_SIZE * 2.0f) * (R_LOAD + CELL_SIZE * 2.0f);

    for (int dy = -r_cells; dy <= r_cells; ++dy) {
        for (int dx = -r_cells; dx <= r_cells; ++dx) {
            int wix = wrapCell(ccx + dx);
            int wiy = wrapCell(ccy + dy);
            float cell_cx = (wix + 0.5f) * CELL_SIZE;
            float cell_cy = (wiy + 0.5f) * CELL_SIZE;
            float ddx = wrapDelta(cell_cx - cx);
            float ddy = wrapDelta(cell_cy - cy);
            if (ddx * ddx + ddy * ddy < load_r2) {
                loadCell(ccx + dx, ccy + dy);
            }
        }
    }

    float unload_r2 = (R_LOAD * 1.4f) * (R_LOAD * 1.4f);
    std::vector<std::pair<int,int>> to_remove;
    for (auto& kv : g_cells) {
        float cell_cx = (kv.first.first + 0.5f) * CELL_SIZE;
        float cell_cy = (kv.first.second + 0.5f) * CELL_SIZE;
        float ddx = wrapDelta(cell_cx - cx);
        float ddy = wrapDelta(cell_cy - cy);
        if (ddx * ddx + ddy * ddy > unload_r2) {
            to_remove.push_back(kv.first);
        }
    }
    for (auto& k : to_remove) g_cells.erase(k);
}

// ============================================================
// БЛИТ
// ============================================================
void blitCell(std::uint32_t* screen_buf,
              const CachedCell& cell,
              int dst_x, int dst_y) {
    int sx0 = dst_x + cell.min_x;
    int sy0 = dst_y + cell.min_y;
    int sx1 = dst_x + cell.max_x;
    int sy1 = dst_y + cell.max_y;

    int x0 = std::max(0, sx0);
    int y0 = std::max(0, sy0);
    int x1 = std::min(SCR_W - 1, sx1);
    int y1 = std::min(SCR_H - 1, sy1);
    if (x0 > x1 || y0 > y1) return;

    int cx0 = x0 - dst_x;
    int cy0 = y0 - dst_y;
    int cx1 = x1 - dst_x;
    int cy1 = y1 - dst_y;

    for (int y = cy0; y <= cy1; ++y) {
        const std::uint32_t* src = cell.pixels.data() + y * CELL_SIZE + cx0;
        std::uint32_t* dst = screen_buf + (dst_y + y) * SCR_W + x0;
        const std::uint8_t* fade_row = &g_fade_mask[(dst_y + y) * SCR_W + x0];

        for (int x = cx0; x <= cx1; ++x) {
            std::uint32_t c = *src++;
            std::uint8_t a8 = static_cast<std::uint8_t>(c >> 24);

            if (a8) {
                std::uint8_t fade = *fade_row;
                if (fade) {
                    std::uint32_t final_a =
                        (static_cast<std::uint32_t>(a8) * fade) >> 8;

                    if (final_a >= 250) {
                        *dst = c | 0xFF000000u;
                    } else if (final_a) {
                        std::uint32_t bg = *dst;
                        std::uint32_t inv = 255 - final_a;
                        std::uint32_t r = ((((c >> 16) & 0xFF) * final_a
                                          + ((bg >> 16) & 0xFF) * inv) >> 8);
                        std::uint32_t g = ((((c >>  8) & 0xFF) * final_a
                                          + ((bg >>  8) & 0xFF) * inv) >> 8);
                        std::uint32_t b = ((( c        & 0xFF) * final_a
                                          + ( bg        & 0xFF) * inv) >> 8);
                        *dst = 0xFF000000u | (r << 16) | (g << 8) | b;
                    }
                }
            }
            ++dst;
            ++fade_row;
        }
    }
}

// ============================================================
// FPS
// ============================================================
float g_fps_value = 0.0f;

// ============================================================
// РЕНДЕР
// ============================================================
void renderWorld(Screen& screen) {
    std::uint32_t* sbuf = reinterpret_cast<std::uint32_t*>(
        const_cast<Color*>(screen.data().data()));

    const std::uint32_t bg_color = colorFromRGB(45, 32, 22);
    std::fill(sbuf, sbuf + SCR_W * SCR_H, bg_color);

    float cx = static_cast<float>(g_cyl.x);
    float cy = static_cast<float>(g_cyl.y);

    // --- Ячейки ---
    for (const auto& kv : g_cells) {
        const CachedCell& cell = kv.second;
        if (!cell.has_data) continue;

        int wix = kv.first.first;
        int wiy = kv.first.second;

        float cell_world_x = static_cast<float>(wix * CELL_SIZE);
        float cell_world_y = static_cast<float>(wiy * CELL_SIZE);

        float dx = wrapDelta(cell_world_x - cx);
        float dy = wrapDelta(cell_world_y - cy);

        int dst_x = CXP + static_cast<int>(dx);
        int dst_y = CYP + static_cast<int>(dy);

        if (dst_x + cell.max_x < 0 || dst_x + cell.min_x >= SCR_W) continue;
        if (dst_y + cell.max_y < 0 || dst_y + cell.min_y >= SCR_H) continue;

        blitCell(sbuf, cell, dst_x, dst_y);
    }

    // --- Метка старта (0,0) ---
    {
        float dx = wrapDelta(0.0f - cx);
        float dy = wrapDelta(0.0f - cy);
        int sx = CXP + static_cast<int>(dx);
        int sy = CYP + static_cast<int>(dy);

        auto fadeAt = [](int x, int y) -> std::uint8_t {
            if (static_cast<unsigned>(x) >= SCR_W) return 0;
            if (static_cast<unsigned>(y) >= SCR_H) return 0;
            return g_fade_mask[y * SCR_W + x];
        };

        auto blend = [](std::uint8_t r, std::uint8_t g, std::uint8_t b,
                        std::uint8_t fade) {
            std::uint32_t inv = 255 - fade;
            return colorFromRGB(
                static_cast<std::uint8_t>((r * fade + 45 * inv) >> 8),
                static_cast<std::uint8_t>((g * fade + 32 * inv) >> 8),
                static_cast<std::uint8_t>((b * fade + 22 * inv) >> 8));
        };

        for (int t = 0; t < 360; t += 4) {
            float a = t * 3.14159f / 180.0f;
            int px = sx + static_cast<int>(std::cos(a) * 22);
            int py = sy + static_cast<int>(std::sin(a) * 22);
            std::uint8_t f = fadeAt(px, py);
            if (f && static_cast<unsigned>(px) < SCR_W &&
                static_cast<unsigned>(py) < SCR_H) {
                sbuf[py * SCR_W + px] = blend(255, 60, 60, f);
            }
        }

        for (int i = -14; i <= 14; ++i) {
            int px = sx + i, py = sy;
            std::uint8_t f = fadeAt(px, py);
            if (f && static_cast<unsigned>(px) < SCR_W &&
                static_cast<unsigned>(py) < SCR_H)
                sbuf[py * SCR_W + px] = blend(255, 220, 100, f);

            px = sx; py = sy + i;
            f = fadeAt(px, py);
            if (f && static_cast<unsigned>(px) < SCR_W &&
                static_cast<unsigned>(py) < SCR_H)
                sbuf[py * SCR_W + px] = blend(255, 220, 100, f);
        }

        for (int oy = -3; oy <= 3; ++oy)
            for (int ox = -3; ox <= 3; ++ox)
                if (ox*ox + oy*oy <= 9) {
                    int px = sx + ox, py = sy + oy;
                    std::uint8_t f = fadeAt(px, py);
                    if (f && static_cast<unsigned>(px) < SCR_W &&
                        static_cast<unsigned>(py) < SCR_H)
                        sbuf[py * SCR_W + px] = blend(255, 255, 255, f);
                }
    }

    // --- Цилиндр ---
    const int r = g_cyl.radius_px;
    auto putCircle = [sbuf](int ccx, int ccy, int rr, std::uint32_t col) {
        for (int oy = -rr; oy <= rr; ++oy) {
            for (int ox = -rr; ox <= rr; ++ox) {
                if (ox*ox + oy*oy <= rr*rr) {
                    int px = ccx + ox, py = ccy + oy;
                    if (static_cast<unsigned>(px) < SCR_W &&
                        static_cast<unsigned>(py) < SCR_H)
                        sbuf[py * SCR_W + px] = col;
                }
            }
        }
    };
    putCircle(CXP + 3, CYP + 4, r, colorFromRGB(15, 10, 10));
    putCircle(CXP, CYP + g_cyl.wall_height_px, r,
              colorFromRGB(g_cyl.color_side.r, g_cyl.color_side.g,
                           g_cyl.color_side.b));
    putCircle(CXP, CYP, r,
              colorFromRGB(g_cyl.color_top.r, g_cyl.color_top.g,
                           g_cyl.color_top.b));
    putCircle(CXP, CYP - r / 2, 3,
              colorFromRGB(g_cyl.color_marker.r, g_cyl.color_marker.g,
                           g_cyl.color_marker.b));
}

// ============================================================
// DIB SECTION — быстрый вывод
// ============================================================
HDC     g_memDC   = nullptr;
HBITMAP g_dibBmp  = nullptr;
void*   g_dibBits = nullptr;
int     g_dibW    = 0;
int     g_dibH    = 0;

bool initDIB(HDC hdc, int w, int h) {
    if (g_dibBits && g_dibW == w && g_dibH == h) return true;

    if (g_dibBmp) { DeleteObject(g_dibBmp); g_dibBmp = nullptr; }
    if (g_memDC)  { DeleteDC(g_memDC); g_memDC = nullptr; }

    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth       = w;
    bmi.bmiHeader.biHeight      = -h;
    bmi.bmiHeader.biPlanes      = 1;
    bmi.bmiHeader.biBitCount    = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    g_dibBmp = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS,
                                &g_dibBits, nullptr, 0);
    if (!g_dibBmp) return false;

    g_memDC = CreateCompatibleDC(hdc);
    SelectObject(g_memDC, g_dibBmp);

    g_dibW = w;
    g_dibH = h;
    return true;
}

void presentToWindow(HWND hwnd, Screen& screen) {
    const int w = screen.width();
    const int h = screen.height();

    HDC hdc = GetDC(hwnd);
    if (!initDIB(hdc, w, h)) { ReleaseDC(hwnd, hdc); return; }

    const auto& data = screen.data();
    std::memcpy(g_dibBits, data.data(),
                static_cast<std::size_t>(w) * h * sizeof(std::uint32_t));

    BitBlt(hdc, 0, 0, w, h, g_memDC, 0, 0, SRCCOPY);

    // --- HUD ---
    float cx = static_cast<float>(g_cyl.x);
    float cy = static_cast<float>(g_cyl.y);
    float mdx = wrapDelta(0.0f - cx);
    float mdy = wrapDelta(0.0f - cy);
    float mdist = std::sqrt(mdx * mdx + mdy * mdy);

    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(255, 255, 255));

    wchar_t buf[256];
    swprintf_s(buf,
        L"Pos: %.0f, %.0f  |  Start dist: %.0f px  |  Cells: %zu  |  FPS: %.1f",
        cx, cy, mdist, g_cells.size(), g_fps_value);
    TextOutW(hdc, 10, 10, buf, static_cast<int>(wcslen(buf)));

    SetTextColor(hdc, RGB(160, 160, 160));
    swprintf_s(buf, L"WASD — move  |  ESC — quit");
    TextOutW(hdc, 10, 32, buf, static_cast<int>(wcslen(buf)));

    ReleaseDC(hwnd, hdc);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_KEYDOWN:
            if (wParam == VK_ESCAPE) PostQuitMessage(0);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    const char* CLASS_NAME = "SSEPrototypeWnd";
    WNDCLASS wc = {};
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
    wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
    RegisterClass(&wc);

    RECT rect = {0, 0, SCR_W, SCR_H};
    AdjustWindowRect(&rect,
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, FALSE);

    HWND hwnd = CreateWindow(CLASS_NAME, "SSE — ШАР (DIB Section)",
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT,
        rect.right - rect.left, rect.bottom - rect.top,
        nullptr, nullptr, hInstance, nullptr);
    if (!hwnd) return 1;

    ShowWindow(hwnd, nCmdShow);
    SetFocus(hwnd);

    buildFadeMask();

    g_cyl.x = 0;
    g_cyl.y = 0;
    g_cyl.radius_px = 12;

    Screen screen(SCR_W, SCR_H);

    auto last = std::chrono::steady_clock::now();
    auto fps_last = last;
    int  fps_frames = 0;
    float speed = 400.0f;

    MSG msg;
    while (true) {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) return 0;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        auto now = std::chrono::steady_clock::now();
        float dt = std::chrono::duration<float>(now - last).count();
        last = now;
        if (dt > 0.1f) dt = 0.1f;

        fps_frames++;
        float fps_elapsed = std::chrono::duration<float>(now - fps_last).count();
        if (fps_elapsed >= 0.5f) {
            g_fps_value = fps_frames / fps_elapsed;
            fps_frames = 0;
            fps_last = now;
        }

        float mx = 0.0f, my = 0.0f;
        if (GetAsyncKeyState('W') & 0x8000) my -= 1.0f;
        if (GetAsyncKeyState('S') & 0x8000) my += 1.0f;
        if (GetAsyncKeyState('A') & 0x8000) mx -= 1.0f;
        if (GetAsyncKeyState('D') & 0x8000) mx += 1.0f;

        if (mx != 0.0f || my != 0.0f) {
            float len = std::sqrt(mx * mx + my * my);
            g_cyl.x += static_cast<int>(mx / len * speed * dt);
            g_cyl.y += static_cast<int>(my / len * speed * dt);
            g_cyl.x = static_cast<int>(wrapFloat(static_cast<float>(g_cyl.x)));
            g_cyl.y = static_cast<int>(wrapFloat(static_cast<float>(g_cyl.y)));
        }

        streamWorld();
        renderWorld(screen);
        presentToWindow(hwnd, screen);

        Sleep(16);
    }
    return 0;
}
