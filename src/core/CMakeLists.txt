add_library(engine-core STATIC
    src/EventBus.cpp
    src/StateStore.cpp
    src/GameLoop.cpp
)

target_include_directories(engine-core PUBLIC include)

# Линковка с Rust-крейтом, если он доступен
if(TARGET rust_bio)
    target_link_libraries(engine-core PUBLIC rust_bio)
endif()