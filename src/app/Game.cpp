#include "app/Game.h"
#include "app/Config.h"
#include "render/Renderer.h"
#include "world/Sphere.h"
#include <cmath>

namespace SSE {

using namespace Config;

Game::Game() {
    cylinder_.x = 0;
    cylinder_.y = 0;
    cylinder_.radius_px = 12;
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
    float cx = static_cast<float>(cylinder_.x);
    float cy = static_cast<float>(cylinder_.y);
    world_.update(cx, cy);
}

void Game::render(std::uint32_t* buffer, int w, int h) {
    Render::renderWorld(buffer, w, h, world_, cylinder_);
}

} // namespace SSE
