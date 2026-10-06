#ifndef SSE_APP_GAME_H
#define SSE_APP_GAME_H

#include "world/World.h"
#include "data/character/Character.h"
#include <cstdint>

namespace SSE {

class Game {
public:
    Game();
    void update(float dt);
    void render(std::uint32_t* buffer, int w, int h);

    Character& character() { return character_; }
    const World& world() const { return world_; }

    float fps() const { return fps_; }

private:
    World world_;
    Character character_;

    float fps_ = 0.0f;
    int   fpsFrames_ = 0;
    float fpsTimer_ = 0.0f;

    void tickFps(float dt);
};

} // namespace SSE

#endif
