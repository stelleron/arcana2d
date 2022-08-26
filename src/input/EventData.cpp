#include "input/EventData.hpp"
#include "utils/Logger.hpp"

namespace arcana {
    void EventData::reset() {
        // Reset window events
        windowData.wasResized = false;
        windowData.wasMoved = false;
        windowData.windowPos = {0.0, 0.0};
    }
}