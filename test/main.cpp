#include "Arcana2D.hpp"
#include <iostream>

using namespace arcana;

class UntitledGame : public Application{

    bool a;

    void config(AppConfig& config) {

    }
    void init(GameContext& ctx) {
        ctx.audio.init();
        a = false;
        Sound sound("cache/pickupCoin.wav");
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