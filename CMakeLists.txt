cmake_minimum_required(VERSION 3.25)
project(StrategicSurvivalEngine VERSION 0.1.0 LANGUAGES CXX)

# ========== Глобальные настройки ==========
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ========== Пресеты сборки ==========
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# ========== Rust-крейт (био-матрицы) ==========
# Интеграция через Corrosion — автоматический импорт Cargo-крейтов[reference:3]
find_package(Corrosion QUIET)
if(Corrosion_FOUND)
    corrosion_import_crate(MANIFEST_PATH "${CMAKE_SOURCE_DIR}/rust-bio/Cargo.toml")
endif()

# ========== C++ Ядро ==========
add_subdirectory(src/core)
add_subdirectory(src/systems)
add_subdirectory(tests)

# ========== C# Скрипты ==========
# Вызов dotnet build как custom target
add_custom_target(scripts ALL
    COMMAND dotnet build "${CMAKE_SOURCE_DIR}/src/scripts/StrategicSurvival.csproj"
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/src/scripts"
    COMMENT "Building C# scripts..."
)

# ========== Порядок сборки ==========
add_dependencies(engine-core scripts)

# ============================================================
# SSE Prototype — C++ окно с землёй + травой + цилиндром
# ============================================================
add_executable(sse_prototype WIN32
    src/main.cpp
    src/world/Patch.cpp
    src/world/Observer.cpp
)
target_include_directories(sse_prototype PRIVATE src)
target_link_libraries(sse_prototype PRIVATE user32 gdi32)
