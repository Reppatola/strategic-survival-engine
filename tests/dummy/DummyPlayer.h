#ifndef DUMMY_PLAYER_H
#define DUMMY_PLAYER_H

#include <iostream>
#include <string>

#include "EventBus.h"

namespace SSE {

class DummyPlayer {
   public:
    DummyPlayer(EventBus& eventBus);
    void walk(int steps);

   private:
    EventBus& bus;
    float noisePerStep;
};

}  // namespace SSE

#endif