#include <iostream>
#include <iomanip>
#include <windows.h>
#include "data/character/characters/Hero01.h"

using namespace SSE;

int main() {
    SetConsoleOutputCP(CP_UTF8);

    Character c = Characters::hero01();

    std::cout << "=== Персонаж: " << c.name << " ===\n\n";

    std::cout << "Рост: " << c.anatomy.total_height << " см\n";
    std::cout << "Вес:  " << c.anatomy.total_weight << " кг\n\n";

    // Голова
    auto* hat = c.hat();
    std::cout << "--- Голова ---\n";
    std::cout << "  Шляпа размер: " << hat->size
              << " (" << hat->label << ")\n";
    std::cout << "  Обхват:       " << hat->circumference << " см\n";
    std::cout << "  Ширина:       " << hat->width  << " см\n";
    std::cout << "  Глубина:      " << hat->depth  << " см\n\n";

    // Торс
    auto* hoodie = c.hoodie();
    std::cout << "--- Толстовка ---\n";
    std::cout << "  Размер:       " << hoodie->size << "\n";
    std::cout << "  Ширина:       " << hoodie->chest_width << " см\n";
    std::cout << "  Длина:        " << hoodie->body_length << " см\n";
    std::cout << "  Рукав:        " << hoodie->sleeve_length << " см\n\n";

    // Ноги
    auto* pants = c.pants();
    std::cout << "--- Брюки ---\n";
    std::cout << "  Размер:       " << pants->size << "\n";
    std::cout << "  Талия:        " << pants->waist_half * 2 << " см\n";
    std::cout << "  Бёдра:        " << pants->hips_half  * 2 << " см\n";
    std::cout << "  Бедро:        " << pants->thigh_half * 2 << " см\n";
    std::cout << "  Длина:        " << pants->length_side << " см\n\n";

    // Обувь
    auto* shoes = c.shoes();
    std::cout << "--- Обувь ---\n";
    std::cout << "  Размер:       " << shoes->size << "\n";
    std::cout << "  Длина стопы:  " << shoes->foot_length << " см\n";
    std::cout << "  Ширина:       " << shoes->foot_width  << " см\n\n";

    // Скелет
    std::cout << "--- Скелет ---\n";
    std::cout << "  head_top z:   " << c.skeleton.head_top.z    << " см\n";
    std::cout << "  shoulder z:   " << c.skeleton.shoulder_left.z << " см\n";
    std::cout << "  waist z:      " << c.skeleton.waist.z       << " см\n";
    std::cout << "  hip z:        " << c.skeleton.hip_left.z    << " см\n";
    std::cout << "  ankle z:      " << c.skeleton.ankle_left.z  << " см\n";

    return 0;
}
