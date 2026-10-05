#include "world/Observer.h"

#include <cmath>

namespace SSE {

float Observer::viewX() const {
    return target_player_ ? target_player_->x : own_x_;
}

float Observer::viewY() const {
    return target_player_ ? target_player_->y : own_y_;
}

bool Observer::canSee(float world_x, float world_y) const {
    float dx = world_x - viewX();
    float dy = world_y - viewY();
    float dist_sq = dx * dx + dy * dy;
    return dist_sq <= vision_radius_ * vision_radius_;
}

}  // namespace SSE