#include <iostream>
#include "Arcana2D.hpp"

class UntitledGame : public arcana::Application {
    arcana::VertexBuffer vBuffer = arcana::VertexBuffer(arcana::RenderMode::Triangles, 6);

    void config(arcana::AppConfig& config) {

    }

    void init() {
        arcana::Triangle triangle({50.0, 50.0}, 100, 100);
        vBuffer.add(arcana::makeDrawable(triangle, RED), 0);
        triangle = arcana::Triangle ({75.0, 75.0}, 100, 100);
        vBuffer.add(arcana::makeDrawable(triangle, BLUE), 3);
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