#include "Arcana2D.hpp"
using namespace arcana;

class UntitledGame : public Application{

    void config(AppConfig& config) {
        
    }
    void init(GameContext& ctx) {
        ctx.audio.init();
    }
    void update(GameContext& ctx) {
        ctx.audio.play();
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