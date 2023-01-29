#include "Arcana2D.hpp"
using namespace arcana;

class UntitledGame : public Application{

    bool a;

    void config(AppConfig& config) {
        
    }
    void init(GameContext& ctx) {
        ctx.audio.init();
        a = false;
    }
    void update(GameContext& ctx) {
        if (!a) {
            ctx.audio.play();
            a = true;
        }
    }
    void render(RenderContext& ctx) {
        for (int x = 0; x < 100; x++) {
            ctx.draw(Point(Vector2{random::generateNum(0, 800), random::generateNum(0, 600)}));
        }
    }
    void finish() {
    
    }
};

int main() {
    UntitledGame game;
    build(game);
}