#include "app/Game.h"
#include "app/Config.h"
#include "render/Renderer.h"
#include "world/Sphere.h"
#include "data/character/characters/Hero01.h"
#include <cmath>

namespace SSE {

using namespace Config;

Game::Game() {
    character_ = Characters::hero01();
    character_.world_x = 0.0f;
    character_.world_y = 0.0f;
}

void Game::tickFps(float dt) {
    fpsFrames_++;
    fpsTimer_ += dt;
    if (fpsTimer_ >= 0.5f) {
        fps_ = fpsFrames_ / fpsTimer_;
        fpsFrames_ = 0;
        fpsTimer_ = 0.0f;
    }
}

void Game::update(float dt) {
    tickFps(dt);
    world_.update(character_.world_x, character_.world_y);
}

void Game::render(std::uint32_t* buffer, int w, int h) {
    Render::renderWorld(buffer, w, h, world_, character_);
}

} // namespace SSE
