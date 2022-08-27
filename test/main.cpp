#include <iostream>
#include "Arcana2D.hpp"

class UntitledGame : public arcana::Application {
    arcana::Image logo;
    arcana::Sprite wall;
    arcana::AudioContext audio_ctx;


    void config(arcana::AppConfig& config) {
        config.resizable = true;
        config.vsync = false;
    }

    void init(arcana::GameContext& ctx) {
        logo.load("cache/wall.jpg");
        wall.load(logo);
    }

    void update(arcana::GameContext& ctx) {

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