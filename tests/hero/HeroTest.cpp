#include <iostream>
#include <windows.h>
#include "data/characters/hero1/hero1.h"

using namespace SSE::Hero1;

// ============================================================
// Макрос — печатает информацию о части
// ============================================================
#define PRINT_PART(ns, name)                                        \
    std::cout << "\n=== " << name << " ===\n";                      \
    std::cout << "  H-срезов: " << ns::H_SLICES_COUNT << "\n";      \
    std::cout << "  V-срезов: " << ns::V_SLICES_COUNT << "\n";      \
    {                                                                \
        const auto& top = ns::H_SLICES[0];                          \
        std::cout << "  Верх:  z=" << top.z                         \
                  << "  w=" << top.width                             \
                  << "  d=" << top.depth << "\n";                    \
    }                                                                \
    {                                                                \
        const auto& bot = ns::H_SLICES[ns::H_SLICES_COUNT - 1];     \
        std::cout << "  Низ:   z=" << bot.z                         \
                  << "  w=" << bot.width                             \
                  << "  d=" << bot.depth << "\n";                    \
    }

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "=== ГЕРОЙ 01 — ВСЕ ЧАСТИ ТЕЛА ===\n";

    PRINT_PART(Head,       "Голова");
    PRINT_PART(TorsoUpper, "Верх торса");
    PRINT_PART(TorsoLower, "Низ торса");
    PRINT_PART(ArmLeft,    "Левая рука");
    PRINT_PART(ArmRight,   "Правая рука");
    PRINT_PART(LegLeft,    "Левая нога");
    PRINT_PART(LegRight,   "Правая нога");
    PRINT_PART(FootLeft,   "Левая стопа");
    PRINT_PART(FootRight,  "Правая стопа");

    std::cout << "\n=== ГОТОВО ===\n";
    return 0;
}
