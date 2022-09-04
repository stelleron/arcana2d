#include <iostream> 
#include "Arcana2D.hpp"

using namespace arcana;

class ExampleGame : public Application {
    Filesystem fsys;

    void config(AppConfig& config) {
        config.resizable = true;
        config.halt_while_hidden = false;
    }

    void init(GameContext& ctx) {
        fsys.setDir("cache");
    }

    void update(GameContext& ctx) {

    }

    void render() {

    }

    void finish() {

    }
};

int main() {
    ExampleGame game;
    build(game);
}
