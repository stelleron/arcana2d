#include "input/EventData.hpp"
#include "utils/Logger.hpp"

namespace arcana {
    void EventData::reset() {
        windowData.wasResized = false;
        windowData.wasMoved = false;
    }
}