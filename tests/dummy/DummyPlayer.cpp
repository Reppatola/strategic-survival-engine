#include "DummyPlayer.h"

namespace SSE {

DummyPlayer::DummyPlayer(EventBus& eventBus) : bus(eventBus), noisePerStep(5.0f) {}

void DummyPlayer::walk(int steps) {
    for (int i = 1; i <= steps; ++i) {
        std::cout << "  [Player] Step " << i << ": made noise" << std::endl;
        bus.publish("NOISE_GENERATED", std::to_string(noisePerStep));
    }
}

}  // namespace SSE