#ifndef SSE_APP_CONFIG_H
#define SSE_APP_CONFIG_H

#include <cstdint>

namespace SSE::Config {

// ============================================================
// ЕДИНАЯ СИСТЕМА МЕР — ПИКСЕЛИ
// ============================================================

// --- Экран (весь, включая UI) ---
constexpr int SCR_W = 1000;
constexpr int SCR_H = 900;

// --- UI-зоны ---
constexpr int UI_TOP_H  = 60;
constexpr int UI_BOT_H  = 140;
constexpr int WORLD_TOP = UI_TOP_H;
constexpr int WORLD_BOT = SCR_H - UI_BOT_H;          // 760
constexpr int WORLD_H   = WORLD_BOT - WORLD_TOP;      // 700

// --- Центр мира (не центр экрана!) ---
constexpr int CXP = SCR_W / 2;
constexpr int CYP = WORLD_TOP + WORLD_H / 2;          // 410

// --- Мир ---
constexpr int CELL_SIZE   = 256;
constexpr int WORLD_CELLS = 24;
constexpr int WORLD_SIZE  = WORLD_CELLS * CELL_SIZE;
constexpr int WORLD_TOTAL = WORLD_CELLS * WORLD_CELLS;

// --- Наблюдатель ---
constexpr float R_CORE = 100.0f;
constexpr float R_FADE = 300.0f;
constexpr float R_LOAD = 1000.0f;

// --- Скорости ---
constexpr float SPEED_WALK  = 140.0f;
constexpr float SPEED_RUN   = 500.0f;
constexpr float SPEED_SNEAK = 50.0f;

// --- Природа ---
constexpr float GRASS_LENGTH_MIN = 2.0f;
constexpr float GRASS_LENGTH_MAX = 3.5f;
constexpr float CELL_DENSITY     = 0.06f;

// --- Стриминг ---
constexpr int LOAD_PER_FRAME_BASE       = 6;
constexpr int LOAD_QUEUE_FAST_THRESHOLD = 50;

} // namespace SSE::Config

#endif
