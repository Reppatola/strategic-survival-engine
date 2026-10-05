#ifndef SSE_CORE_SCREEN_H
#define SSE_CORE_SCREEN_H

#include <cstdint>
#include <vector>

#include "Color.h"
#include "Pixel.h"

namespace SSE {

// ============================================================
// ЭКРАН — куда рисуется мир.
// Хранит пиксели. Не знает, ЧТО рисуется.
// Знает только ГДЕ и КАКОГО ЦВЕТА.
// ============================================================
class Screen {
   public:
    Screen(std::int32_t width, std::int32_t height)
        : width_(width), height_(height), pixels_(static_cast<std::size_t>(width) * height) {}

    // Очистить весь экран одним цветом
    void clear(const Color& c) {
        for (auto& p : pixels_) p = c;
    }

    // Поставить один пиксель
    void setPixel(std::int32_t x, std::int32_t y, const Color& c) {
        if (x < 0 || x >= width_ || y < 0 || y >= height_) return;
        pixels_[static_cast<std::size_t>(y) * width_ + x] = c;
    }

    // Положить список пикселей (результат rasterize())
    void putPixels(const std::vector<Pixel>& list) {
        for (const auto& p : list) {
            setPixel(p.x, p.y, p.color);
        }
    }

    // Доступ к данным — для отрисовки через SDL / pygame / win32
    [[nodiscard]] const std::vector<Color>& data() const { return pixels_; }
    [[nodiscard]] std::int32_t width() const { return width_; }
    [[nodiscard]] std::int32_t height() const { return height_; }

   private:
    std::int32_t width_;
    std::int32_t height_;
    std::vector<Color> pixels_;
};

}  // namespace SSE

#endif  // SSE_CORE_SCREEN_H