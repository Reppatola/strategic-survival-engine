#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include <any>

// ============================================================
// КОНТРАКТ 1: EventBus
// Все события, передаваемые между системами, ДОЛЖНЫ
// быть зарегистрированы здесь с явной структурой Payload.
// ============================================================

namespace SSE {

// --- Структуры Payload для событий ---

struct MovementIntentPayload {
    int entityId;
    float directionX, directionY, directionZ;
    float speed;
};

struct NoiseGeneratedPayload {
    int sourceId;
    float intensity;     // L0 в формуле шума
    float decayFactor;   // k в формуле шума
};

struct PositionUpdatedPayload {
    int entityId;
    float x, y, z;
};

// --- Шина событий ---
class EventBus {
public:
    using Handler = std::function<void(const std::any&)>;

    void subscribe(const std::string& eventType, Handler handler);
    void publish(const std::string& eventType, const std::any& payload);

private:
    std::unordered_map<std::string, std::vector<Handler>> subscribers_;
};

} // namespace SSE