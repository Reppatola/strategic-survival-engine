#pragma once
#include "core/include/Component.hpp"
#include <vector>

namespace SSE {

struct Joint {
    float length = 0.0f;
    float angle = 0.0f;
    int parentId = -1;
};

struct SkeletonComponent : public Component {
    std::vector<Joint> joints;
    float totalMass = 0.0f;
};

} // namespace SSE