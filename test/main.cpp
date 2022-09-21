#include "Arcana2D.hpp"

using namespace arcana;

class UntitledGame : public Application {
    Sprite sprite;
    VertexArray vArray;
    void config(AppConfig& config) {
        
    }

    void init(GameContext& ctx) {
        sprite.load("cache/wall.jpg");
        vArray.create(RenderMode::Circles, 74);
        vArray.add(Circle({50.0f, 50.0f}, 50), 0);
        vArray.add(Circle({150.0f, 150.0f}, 50), 37);
    }

    void update(GameContext& ctx) {

    }

    void render(RenderContext& ctx) {
        ctx.draw(vArray);
    }

    void finish() {

    }
};

int main() {  
    UntitledGame game;
    build(game);
}
