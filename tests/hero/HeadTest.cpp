#include <iostream>
#include <windows.h>
#include "data/characters/hero1/head.h"

using namespace SSE::Hero1;

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "=== HERO1 — ГОЛОВА ===\n\n";

    std::cout << "Крепление:   Z = " << Head::ATTACH_Z << " см\n";
    std::cout << "Горизонтальных срезов: " << Head::H_SLICES_COUNT << "\n";
    std::cout << "Вертикальных срезов:   " << Head::V_SLICES_COUNT   << "\n\n";

    std::cout << "--- Горизонтальные срезы (сверху вниз) ---\n";
    std::cout << "   z      width  depth  off_x  off_y\n";
    for (int i = 0; i < Head::H_SLICES_COUNT; ++i) {
        const auto& s = Head::H_SLICES[i];
        std::cout << "  " << s.z
                  << "    " << s.width
                  << "   " << s.depth
                  << "    " << s.offset_x
                  << "     " << s.offset_y << "\n";
    }

    std::cout << "\n--- Вертикальные срезы (слева направо) ---\n";
    std::cout << "   x     height  depth  off_z  off_y\n";
    for (int i = 0; i < Head::V_SLICES_COUNT; ++i) {
        const auto& s = Head::V_SLICES[i];
        std::cout << "  " << s.x
                  << "    " << s.height
                  << "   " << s.depth
                  << "    " << s.offset_z
                  << "     " << s.offset_y << "\n";
    }

    std::cout << "\n--- Материал ---\n";
    std::cout << "Кожа:   RGB("
              << (int)Head::MATERIAL.primary.r   << ","
              << (int)Head::MATERIAL.primary.g   << ","
              << (int)Head::MATERIAL.primary.b   << ")\n";
    std::cout << "Волосы: RGB("
              << (int)Head::MATERIAL.secondary.r << ","
              << (int)Head::MATERIAL.secondary.g << ","
              << (int)Head::MATERIAL.secondary.b << ")\n";

    return 0;
}
