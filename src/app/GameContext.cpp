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
}