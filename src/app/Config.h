#ifndef SSE_APP_CONFIG_H
#define SSE_APP_CONFIG_H

#include <cstdint>

namespace SSE::Config {

// ============================================================
// ЕДИНАЯ СИСТЕМА МЕР — ПИКСЕЛИ
// ============================================================

// --- Экран ---
constexpr int SCR_W = 1000;
constexpr int SCR_H = 900;
constexpr int CXP = SCR_W / 2;
constexpr int CYP = SCR_H / 2;

// --- Мир ---
constexpr int CELL_SIZE   = 256;      // 256 px — тело 175 влезает
constexpr int WORLD_CELLS = 24;       // 24 × 24 = 576 ячеек
constexpr int WORLD_SIZE  = WORLD_CELLS * CELL_SIZE;  // 6144 px
constexpr int WORLD_TOTAL = WORLD_CELLS * WORLD_CELLS;

// --- Наблюдатель ---
constexpr float R_CORE = 80.0f;       // зона чёткости
constexpr float R_FADE = 500.0f;      // граница размытия
constexpr float R_LOAD = 900.0f;      // буфер загрузки

// --- Скорости передвижения (px/сек) ---
constexpr float SPEED_WALK  = 140.0f;
constexpr float SPEED_RUN   = 500.0f;
constexpr float SPEED_SNEAK = 50.0f;

// --- Природа ---
constexpr float GRASS_LENGTH_MIN = 8.0f;   // 8 px
constexpr float GRASS_LENGTH_MAX = 15.0f;  // 15 px
constexpr float CELL_DENSITY     = 0.015f; // травинок на пиксель ячейки

// --- Стриминг ---
constexpr int LOAD_PER_FRAME_BASE       = 6;
constexpr int LOAD_QUEUE_FAST_THRESHOLD = 50;

} // namespace SSE::Config

#endif
