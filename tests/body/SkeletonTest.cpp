#include <iostream>
#include <iomanip>
#include <windows.h>
#include "data/body/Anatomy.h"
#include "data/body/Skeleton.h"

using namespace SSE;

void printPoint(const char* name, const Body::Point3& p) {
    std::cout << "  " << std::setw(14) << std::left << name
              << "  x=" << std::setw(7) << std::right << p.x
              << "  y=" << std::setw(7) << p.y
              << "  z=" << std::setw(7) << p.z
              << " cm\n";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "=== Skeleton Test — STANDARD_MALE ===\n\n";

    const auto& A = Body::STANDARD_MALE;
    std::cout << "Height: " << A.total_height << " cm\n\n";

    auto sk = Body::Skeleton::fromAnatomy(A, 0.0f);

    std::cout << "--- Точки скелета (стоит, лицом на юг) ---\n";
    printPoint("head_top",     sk.head_top);
    printPoint("head_center",  sk.head_center);
    printPoint("head_base",    sk.head_base);
    printPoint("shoulder_L",   sk.shoulder_left);
    printPoint("shoulder_R",   sk.shoulder_right);
    printPoint("chest",        sk.chest);
    printPoint("waist",        sk.waist);
    printPoint("pelvis",       sk.pelvis);
    printPoint("hip_L",        sk.hip_left);
    printPoint("hip_R",        sk.hip_right);
    printPoint("knee_L",       sk.knee_left);
    printPoint("knee_R",       sk.knee_right);
    printPoint("ankle_L",      sk.ankle_left);
    printPoint("ankle_R",      sk.ankle_right);

    std::cout << "\n--- Руки ---\n";
    printPoint("elbow_L",      sk.elbow_left);
    printPoint("wrist_L",      sk.wrist_left);

    return 0;
}
