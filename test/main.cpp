#include "Arcana2D.hpp"

using namespace arcana;

class UntitledGame : public Application {
    VertexArray vArray = VertexArray(RenderMode::Circles, 37);

    void config(AppConfig& config) {
        
    }

    void init(GameContext& ctx) {
        vArray.add(Circle(Vector2(100.0f, 100.0f), 50.0f), 0);
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
