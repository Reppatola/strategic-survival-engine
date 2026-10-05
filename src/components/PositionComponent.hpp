#pragma once
#include "core/include/Component.hpp"

namespace SSE {

struct PositionComponent : public Component {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

} // namespace SSE