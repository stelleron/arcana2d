#include <iostream>
#include "Arcana2D.hpp"

class UntitledGame : public arcana::Application {
    arcana::Sprite wall;
    arcana::AudioContext audio_ctx;

    void config(arcana::AppConfig& config) {
        config.resizable = true;
    }

    void init() {
        wall.load("cache/wall.jpg");
    }

    void update(arcana::GameContext& ctx) {
        if (ctx.wasWindowResized()) {
            std::puts("hello");
        }
        else {
            std::puts("bye");
        }
    }

    void render(arcana::RenderContext& ctx) {
        ctx.draw(wall);
    }

    void finish() {

    }
};

int main() {
    UntitledGame game;
    arcana::build(game);
}