#ifndef DUMMY_NOISE_SYSTEM_H
#define DUMMY_NOISE_SYSTEM_H

#include <iostream>
#include <string>

#include "EventBus.h"
#include "StateStore.h"

namespace SSE {

class DummyNoiseSystem {
   public:
    DummyNoiseSystem(EventBus& eventBus);
    ~DummyNoiseSystem();
    void update();

   private:
    EventBus& bus;
    SubscriptionId subId;
};

}  // namespace SSE

#endif