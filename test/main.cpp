#include "Arcana2D.hpp"
#include <iostream>

using namespace arcana;

class UntitledGame : public Application{
    // Store window dimensions
    Vector2 win_dimensions;


    void config(AppConfig& config) {
        config.resizable = true;
        config.maximized = true;
    }

    void init(GameContext& ctx) {
        win_dimensions = ctx.window.getWindowSize();
        LOG(win_dimensions.x << "," << win_dimensions.y);
    }

    void update(GameContext& ctx) {

    }

    void render(RenderContext& ctx) {

    }

    void finish() {
    
    }
};

int main() {
    UntitledGame game;
    build(game);
}