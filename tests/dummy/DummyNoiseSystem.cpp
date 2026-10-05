#include "DummyNoiseSystem.h"

namespace SSE {

DummyNoiseSystem::DummyNoiseSystem(EventBus& eventBus) : bus(eventBus) {
    subId = bus.subscribe("NOISE_GENERATED", [this](const std::string& payload) {
        float noise = std::stof(payload);
        StateStore& store = StateStore::getInstance();
        float total = store.getGlobalNoiseLevel() + noise;
        store.setGlobalNoiseLevel(total);
        std::cout << "  [NoiseSystem] Noise generated: " << noise << ", total: " << total
                  << std::endl;
    });
}

DummyNoiseSystem::~DummyNoiseSystem() {
    bus.unsubscribe("NOISE_GENERATED", subId);
}

void DummyNoiseSystem::update() {
    StateStore& store = StateStore::getInstance();
    std::cout << "  [NoiseSystem] Current global noise level: " << store.getGlobalNoiseLevel()
              << std::endl;
}

}  // namespace SSE