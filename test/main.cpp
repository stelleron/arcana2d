#include <iostream>
#include "Arcana2D.hpp"

class UntitledGame : public arcana::Application {
    arcana::Sprite wall;

    void config(arcana::AppConfig& config) {

    }

    void init() {
        wall.load("cache/wall.jpg");
    }

    void update() {

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