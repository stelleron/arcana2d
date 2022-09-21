#include "Arcana2D.hpp"

using namespace arcana;

class UntitledGame : public Application {
    Sprite sprite;
    void config(AppConfig& config) {
        
    }

    void init(GameContext& ctx) {
        sprite.load("cache/wall.jpg");
    }

    void update(GameContext& ctx) {

    }

    void render(RenderContext& ctx) {
        sprite.scale = {0.5, 0.5};
        ctx.draw(sprite);        
    }

    void finish() {

    }
};

int main() {  
    UntitledGame game;
    build(game);
}
