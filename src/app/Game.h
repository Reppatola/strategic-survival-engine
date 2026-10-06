#pragma once
#include "world/World.h"
#include "data/objects/Cylinder.h"
#include <cstdint>

namespace SSE {

class Game {
public:
    Game();
    void update(float dt);
    void render(std::uint32_t* buffer, int w, int h);

    Cylinder& cylinder() { return cylinder_; }
    const World& world() const { return world_; }

    float fps() const { return fps_; }

private:
    World world_;
    Cylinder cylinder_;

    float fps_ = 0.0f;
    int   fpsFrames_ = 0;
    float fpsTimer_ = 0.0f;

    void tickFps(float dt);
};

} // namespace SSE
