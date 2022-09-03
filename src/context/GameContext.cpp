#include "context/GameContext.hpp"

namespace arcana {
    GameContext::GameContext() {
        dt = 0;
    }

    GameContext::~GameContext() {

    }

    void GameContext::setCamera(Camera& camera) {
        curr_camera = &camera;
    }

    void GameContext::setWindow(Window& window) {
        win_pointer = &window;
    }

    void GameContext::setDeltaTime(float dt) {
        this->dt = dt;
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

    Vector2 GameContext::getWindowSize() {return win_pointer->getWindowSize();}
    void GameContext::setMinWindowSize(int min_width, int min_height) {win_pointer->setMinSize(Vector2(min_width, min_height));}
    void GameContext::setMaxWindowSize(int max_width, int max_height) {win_pointer->setMaxSize(Vector2(max_width, max_height));}
    void GameContext::setWindowPos(int x, int y) {setWindowPos(Vector2(x, y));}
    void GameContext::setWindowPos(Vector2 pos) {win_pointer->setWindowPos(pos);}
    void GameContext::restoreWindow() {win_pointer->restore();}
    void GameContext::iconifyWindow() {win_pointer->iconify();}


    /* void GameContext::setWindowIcon(const Image& image) {
        win_pointer->setIcon(image.width, image.height, image.data);
    } */
}