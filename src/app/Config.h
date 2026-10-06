#pragma once
#include <cstdint>

namespace SSE::Config {

// --- Экран ---
constexpr int SCR_W = 1000;
constexpr int SCR_H = 900;
constexpr int CXP = SCR_W / 2;
constexpr int CYP = SCR_H / 2;

// --- Мир (шар) ---
constexpr int CELL_SIZE   = 64;
constexpr int WORLD_CELLS = 48;
constexpr int WORLD_TOTAL = WORLD_CELLS * WORLD_CELLS;
constexpr int WORLD_SIZE  = WORLD_CELLS * CELL_SIZE;

// --- Восприятие наблюдателя ---
constexpr float R_CORE = 40.0f;
constexpr float R_FADE = 420.0f;
constexpr float R_LOAD = 800.0f;

// --- Трава ---
constexpr float CELL_DENSITY = 0.06f;

// --- Стриминг ---
constexpr int LOAD_PER_FRAME_BASE = 12;
constexpr int LOAD_QUEUE_FAST_THRESHOLD = 100;

} // namespace SSE::Config
