#include "Arcana2D.hpp"
using namespace arcana;

class UntitledGame : public Application{
    Font font;
    void config(AppConfig& config) {

    }
    void init(GameContext& ctx) {
        font.load("cache/Pixel Square 10.ttf");
    }
    void update(GameContext& ctx) {

    }
    void render(RenderContext& ctx) {
        ctx.draw(font.fontTex);
    }
    void finish() {
    
    }
};

int main() {
    UntitledGame game;
    build(game);
}