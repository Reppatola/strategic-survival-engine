#include <iostream>
#include <string>

#include "EventBus.h"

#ifdef _WIN32
#include <windows.h>
#endif

void DummyPublisher(EventBus& eventBus) {
    std::cout << "Publishing TEST_EVENT" << std::endl;
    eventBus.publish("TEST_EVENT", "TEST_EVENT_DATA");
}

SubscriptionId DummySubscriber(EventBus& eventBus) {
    return eventBus.subscribe("TEST_EVENT", [](const std::string& payload) {
        std::cout << "  -> Я получил событие TEST_EVENT! " << payload << std::endl;
    });
}

int main() {
#ifdef _WIN32
    // Включаем UTF-8 в консоли Windows, чтобы кириллица отображалась корректно
    SetConsoleOutputCP(CP_UTF8);
#endif

    EventBus& eventBus = EventBus::getInstance();

    // ============================================================
    // Test 1: Подписка и публикация
    // ============================================================
    std::cout << "=== Test 1: Subscribe and publish ===" << std::endl;
    SubscriptionId id1 = DummySubscriber(eventBus);
    DummyPublisher(eventBus);
    std::cout << "  (ожидалось: 1 подписчик получил событие)" << std::endl;

    // ============================================================
    // Test 2: Отписка по токену
    // ============================================================
    std::cout << "\n=== Test 2: Unsubscribe by token ===" << std::endl;
    eventBus.unsubscribe("TEST_EVENT", id1);  // отписываем подписчика из Test 1
    DummyPublisher(eventBus);
    std::cout << "  (ожидалось: 'Publishing' есть, но никто не получил событие)" << std::endl;

    // ============================================================
    // Test 3: Два подписчика — один отписан, второй остался
    // ============================================================
    std::cout << "\n=== Test 3: Two subscribers ===" << std::endl;
    SubscriptionId idA = DummySubscriber(eventBus);
    SubscriptionId idB = DummySubscriber(eventBus);
    std::cout << "  Подписали двух. Отписываем первого." << std::endl;
    eventBus.unsubscribe("TEST_EVENT", idA);
    DummyPublisher(eventBus);
    std::cout << "  (ожидалось: только один получил событие)" << std::endl;

    // Уборка — отписываем оставшегося
    eventBus.unsubscribe("TEST_EVENT", idB);

    return 0;
}