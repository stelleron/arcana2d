#include "app/GameContext.hpp"

namespace arcana {
    GameContext::GameContext() {

    }

    GameContext::~GameContext() {

    }

    void GameContext::setCamera(Camera& camera) {
        curr_camera = &camera;
    }

    void GameContext::setWindow(Window& window) {
        win_pointer = &window;
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

    void GameContext::updateTitle(const char* title) {
        win_pointer->updateTitle(title);
    }

    void GameContext::setWindowIcon(const Image& image) {
        win_pointer->setIcon(image.width, image.height, image.data);
    }
}