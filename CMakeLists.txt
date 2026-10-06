# ============================================================
# Strategic Survival Engine — корневой CMakeLists
# ============================================================
cmake_minimum_required(VERSION 3.25)
project(StrategicSurvivalEngine VERSION 0.1.0 LANGUAGES CXX)

# ============================================================
# Глобальные настройки
# ============================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Флаги Release — максимальная оптимизация
set(CMAKE_CXX_FLAGS_RELEASE "/O2 /Oi /Ot /GL /DNDEBUG /MD")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "/LTCG /OPT:REF /OPT:ICF /INCREMENTAL:NO")

# Корень include-путей — все модули видят друг друга
include_directories(${CMAKE_SOURCE_DIR}/src)

# Группировка в Solution Explorer
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# ============================================================
# 1. ЯДРО — engine-core (EventBus, StateStore)
# ============================================================
add_library(engine-core STATIC
    src/core/src/EventBus.cpp
    src/core/src/StateStore.cpp
    # src/core/src/GameLoop.cpp    # раскомментировать, когда будет готов
)
target_include_directories(engine-core PUBLIC
    ${CMAKE_SOURCE_DIR}/src/core/include
    ${CMAKE_SOURCE_DIR}/src
)
set_target_properties(engine-core PROPERTIES FOLDER "core")

# ============================================================
# 2. РЕАЛЬНЫЙ ПРОТОТИП МИРА — sse_prototype (Win32 окно)
# ============================================================
add_executable(sse_prototype WIN32
    src/main.cpp
    src/app/Game.cpp
    src/world/World.cpp
    src/world/Observer.cpp
    src/world/Patch.cpp
    src/render/FadeMask.cpp
    src/render/Renderer.cpp
    src/platform/Win32Window.cpp
)
target_include_directories(sse_prototype PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(sse_prototype PRIVATE
    user32
    gdi32
)
set_target_properties(sse_prototype PROPERTIES FOLDER "apps")

# ============================================================
# 3. C# СКРИПТЫ (PlayerController, AIStateLogic)
# ============================================================
add_custom_target(scripts ALL
    COMMAND dotnet build
            "${CMAKE_SOURCE_DIR}/src/scripts/StrategicSurvival.csproj"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/src/scripts"
    COMMENT "Building C# scripts..."
)
set_target_properties(scripts PROPERTIES FOLDER "scripts")

# ============================================================
# 4. ТЕСТЫ — модульные тесты ядра
# ============================================================
enable_testing()

add_executable(eventbus_test   tests/core/EventBusTest.cpp)
add_executable(statestore_test tests/core/StateStoreTest.cpp)
add_executable(component_test  tests/core/ComponentTest.cpp)

add_executable(dummy_noise_test
    tests/dummy/DummyNoiseTest.cpp
    tests/dummy/DummyPlayer.cpp
    tests/dummy/DummyNoiseSystem.cpp
)
target_include_directories(dummy_noise_test PRIVATE
    ${CMAKE_SOURCE_DIR}/tests/dummy
    ${CMAKE_SOURCE_DIR}/src/core/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(eventbus_test    PRIVATE engine-core)
target_link_libraries(statestore_test  PRIVATE engine-core)
target_link_libraries(component_test   PRIVATE engine-core)
target_link_libraries(dummy_noise_test PRIVATE engine-core)

set_target_properties(eventbus_test    PROPERTIES FOLDER "tests")
set_target_properties(statestore_test  PROPERTIES FOLDER "tests")
set_target_properties(component_test   PROPERTIES FOLDER "tests")
set_target_properties(dummy_noise_test PROPERTIES FOLDER "tests")

add_test(NAME eventbus_test   COMMAND eventbus_test)
add_test(NAME statestore_test COMMAND statestore_test)
add_test(NAME component_test  COMMAND component_test)
add_test(NAME dummy_noise     COMMAND dummy_noise_test)

# ============================================================
# 5. ПОРЯДОК СБОРКИ
# ============================================================
add_dependencies(sse_prototype scripts)

add_executable(anatomy_test tests/body/AnatomyTest.cpp)
target_include_directories(anatomy_test PRIVATE ${CMAKE_SOURCE_DIR}/src)
set_target_properties(anatomy_test PROPERTIES FOLDER "tests")

add_executable(skeleton_test tests/body/SkeletonTest.cpp)
target_include_directories(skeleton_test PRIVATE ${CMAKE_SOURCE_DIR}/src)
set_target_properties(skeleton_test PROPERTIES FOLDER "tests")

add_executable(skeleton_view WIN32 tests/body/SkeletonView.cpp)
target_include_directories(skeleton_view PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(skeleton_view PRIVATE user32 gdi32)
set_target_properties(skeleton_view PROPERTIES FOLDER "tests")

add_executable(body_view WIN32 tests/body/BodyView.cpp)
target_include_directories(body_view PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(body_view PRIVATE user32 gdi32)
set_target_properties(body_view PROPERTIES FOLDER "tests")

add_executable(character_test tests/body/CharacterTest.cpp)
target_include_directories(character_test PRIVATE ${CMAKE_SOURCE_DIR}/src)
set_target_properties(character_test PROPERTIES FOLDER "tests")

add_executable(body_topdown WIN32 tests/body/BodyTopDown.cpp)
target_include_directories(body_topdown PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(body_topdown PRIVATE user32 gdi32)
set_target_properties(body_topdown PROPERTIES FOLDER "tests")
