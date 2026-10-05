# Тест EventBus
add_executable(eventbus_test core/EventBusTest.cpp)
target_link_libraries(eventbus_test PRIVATE engine-core)