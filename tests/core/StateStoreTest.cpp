#include <iostream>

#include "StateStore.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace SSE;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    StateStore& store = StateStore::getInstance();

    // ============================================================
    // Test 1: Начальное состояние
    // ============================================================
    std::cout << "=== Test 1: Initial state ===" << std::endl;
    std::cout << "  AlertLevel = " << store.getAlertLevel() << std::endl;
    std::cout << "  GlobalNoiseLevel = " << store.getGlobalNoiseLevel() << std::endl;
    std::cout << "  LastKnownPosition = (" << store.getLastKnownPosition().x << ", "
              << store.getLastKnownPosition().y << ", " << store.getLastKnownPosition().z << ")"
              << std::endl;

    // ============================================================
    // Test 2: Запись и чтение AlertLevel
    // ============================================================
    std::cout << "\n=== Test 2: Set/Get AlertLevel ===" << std::endl;
    store.setAlertLevel(3.5f);
    std::cout << "  После записи AlertLevel = " << store.getAlertLevel() << std::endl;

    // ============================================================
    // Test 3: Запись и чтение GlobalNoiseLevel
    // ============================================================
    std::cout << "\n=== Test 3: Set/Get GlobalNoiseLevel ===" << std::endl;
    store.setGlobalNoiseLevel(12.7f);
    std::cout << "  После записи GlobalNoiseLevel = " << store.getGlobalNoiseLevel() << std::endl;

    // ============================================================
    // Test 4: Запись и чтение LastKnownPosition
    // ============================================================
    std::cout << "\n=== Test 4: Set/Get LastKnownPosition ===" << std::endl;
    Vec3 pos{10.0f, 0.0f, -5.0f};
    store.setLastKnownPosition(pos);
    Vec3 got = store.getLastKnownPosition();
    std::cout << "  После записи LastKnownPosition = (" << got.x << ", " << got.y << ", " << got.z
              << ")" << std::endl;

    // ============================================================
    // Test 5: Singleton — тот же экземпляр
    // ============================================================
    std::cout << "\n=== Test 5: Singleton check ===" << std::endl;
    StateStore& store2 = StateStore::getInstance();
    std::cout << "  Два вызова getInstance() дают один и тот же объект? "
              << (&store == &store2 ? "ДА" : "НЕТ") << std::endl;

    return 0;
}