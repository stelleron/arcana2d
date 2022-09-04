#include "input/EventData.hpp"
#include "utils/Logger.hpp"

namespace arcana {
    void EventData::reset() {
        // Reset window events
        windowData.wasResized = false;
        windowData.wasMoved = false;

        // Reset keyboard events
        for (int x = 0; x < Key::Menu; x++) {
            keyboardData.keyLastPressed[x] = keyboardData.keyPressed[x];
        }
        for (int x = 0; x < keyboardData.charQueue.size(); x++) {
            keyboardData.charQueue.pop();
        }
    }
}