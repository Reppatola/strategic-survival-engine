#pragma once
#include "world/World.h"
#include "data/objects/Cylinder.h"
#include <cstdint>

namespace SSE::Render {

void renderWorld(std::uint32_t* buffer,
                 int width,
                 int height,
                 const World& world,
                 const Cylinder& cyl);

} // namespace SSE::Render
