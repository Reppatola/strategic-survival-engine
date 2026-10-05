#include "StateStore.h"

namespace SSE {

StateStore& StateStore::getInstance() {
    static StateStore instance;
    return instance;
}

void StateStore::setAlertLevel(float value) {
    std::lock_guard<std::mutex> lock(mutex);
    alertLevel = value;
}

float StateStore::getAlertLevel() const {
    std::lock_guard<std::mutex> lock(mutex);
    return alertLevel;
}

void StateStore::setGlobalNoiseLevel(float value) {
    std::lock_guard<std::mutex> lock(mutex);
    globalNoiseLevel = value;
}

float StateStore::getGlobalNoiseLevel() const {
    std::lock_guard<std::mutex> lock(mutex);
    return globalNoiseLevel;
}

void StateStore::setLastKnownPosition(const Vec3& pos) {
    std::lock_guard<std::mutex> lock(mutex);
    lastKnownPosition = pos;
}

Vec3 StateStore::getLastKnownPosition() const {
    std::lock_guard<std::mutex> lock(mutex);
    return lastKnownPosition;
}

}  // namespace SSE