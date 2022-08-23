#include <iostream>
#include "Arcana2D.hpp"

class UntitledGame : public arcana::Application {
    arcana::VertexBuffer vBuffer = arcana::VertexBuffer(arcana::RenderMode::Triangles, 1);

    void config(arcana::AppConfig& config) {

    }

    void init() {
        arcana::Triangle tri(
            arcana::Vector2(50.0, 50.0), 
            arcana::Vector2(150.0, 50.0), 
            arcana::Vector2(50.0, 150.0)
        );
        vBuffer.add(tri);
    }

    void update() {

    }

    void render(arcana::RenderContext& ctx) {
        ctx.draw();
    }

    void finish() {

    }
};

int main() {
    UntitledGame game;
    arcana::build(game);
}