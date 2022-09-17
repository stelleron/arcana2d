#include "Arcana2D.hpp"

using namespace arcana;

class UntitledGame : public Application {
    VertexArray vArray = VertexArray(RenderMode::Quads, 4);

    void config(AppConfig& config) {

    }

    void init(GameContext& ctx) {
        
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
