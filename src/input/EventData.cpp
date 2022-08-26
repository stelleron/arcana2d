#include "input/EventData.hpp"

namespace arcana {
    void EventData::reset() {
        // Reset window events
        windowData.wasResized = false;
    }
}