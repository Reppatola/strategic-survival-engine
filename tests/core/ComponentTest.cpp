#include <iostream>

#include "Component.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace SSE;

struct HealthComponent : public Component {
    float hp = 100.0f;
};

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    HealthComponent healthComponent;
    healthComponent.owner = 42;
    healthComponent.typeName = "Health";

    std::cout << "Owner: " << healthComponent.owner << ", Type: " << healthComponent.typeName
              << ", HP: " << healthComponent.hp << std::endl;
    std::cout << "Size of HealthComponent: " << sizeof(HealthComponent) << std::endl;

    return 0;
}
