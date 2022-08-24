#include <iostream>
#include "Arcana2D.hpp"

class UntitledGame : public arcana::Application {
    arcana::VertexBuffer vBuffer = arcana::VertexBuffer(arcana::RenderMode::Quads, 12);

    void config(arcana::AppConfig& config) {

    }

    void init() {
        arcana::Rectangle square(arcana::Vector2(50.0, 50.0), 100);
        vBuffer.add(square, 0);
        vBuffer[0].color = BLUE;
        vBuffer[1].color = RED;
        vBuffer[2].color = GREEN;
        vBuffer[3].color = YELLOW;
    }

    void update() {

    }

    void render(arcana::RenderContext& ctx) {
        ctx.draw(vBuffer);
    }

    void finish() {

    }
};

int main() {
    UntitledGame game;
    arcana::build(game);
}