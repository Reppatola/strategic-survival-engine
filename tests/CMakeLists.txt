add_executable(dummy_noise_test
    dummy/DummyNoiseTest.cpp
    dummy/DummyNoiseSystem.cpp
    dummy/DummyPlayer.cpp
    dummy/DummyNoiseSystem.cpp
)

# Тест EventBus
add_executable(eventbus_test core/EventBusTest.cpp)
target_link_libraries(eventbus_test PRIVATE engine-core)

# Тест StateStore
add_executable(statestore_test core/StateStoreTest.cpp)
target_link_libraries(statestore_test PRIVATE engine-core)

# Тест Component
add_executable(component_test core/ComponentTest.cpp)
target_link_libraries(component_test PRIVATE engine-core)

target_include_directories(dummy_noise_test PRIVATE dummy)
target_link_libraries(dummy_noise_test PRIVATE engine-core)