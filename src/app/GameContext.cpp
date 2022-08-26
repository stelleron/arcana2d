#include "app/GameContext.hpp"

namespace arcana {
    GameContext::GameContext() {

    }

    GameContext::~GameContext() {

    }

    void GameContext::setCamera(Camera& camera) {
        curr_camera = &camera;
    }

    Camera* GameContext::getCamera() {
        return curr_camera;
    }

    EventData& GameContext::getEventData() {
        return event_data;
    }

    void GameContext::resetEvents() {
        event_data.reset();
    }
}