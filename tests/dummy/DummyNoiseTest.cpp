#include <iostream>

#include "DummyNoiseSystem.h"
#include "DummyPlayer.h"
#include "EventBus.h"
#include "StateStore.h"

#ifdef _WIN32
#include <windows.h>
#endif

using namespace SSE;

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    EventBus& bus = EventBus::getInstance();
    StateStore& store = StateStore::getInstance();

    store.setGlobalNoiseLevel(0.0f);

    DummyNoiseSystem noiseSystem(bus);
    DummyPlayer player(bus);

    std::cout << "=== Test: Player walks 3 steps ===" << std::endl;
    player.walk(3);

    std::cout << "=== Final state ===" << std::endl;
    noiseSystem.update();

    return 0;
}