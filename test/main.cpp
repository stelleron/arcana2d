#include <iostream> 
#include "Arcana2D.hpp"

using namespace arcana;

class ExampleGame : public Application {
    Image img;
    void config(AppConfig& config) {
        config.halt_while_hidden = true;
    }

    void init(GameContext& ctx) {

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
