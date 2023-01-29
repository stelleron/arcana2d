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

    }
    void finish() {
    
    }
};

int main() {
    UntitledGame game;
    build(game);
}