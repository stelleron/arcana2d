#include "Arcana2D.hpp"

using namespace arcana;

class UntitledGame : public Application {
    VertexArray triArray = VertexArray(RenderMode::Triangles, 6);

    void config(AppConfig& config) {

    }

    void init(GameContext& ctx) {
        triArray.add(drawable::make(
            Triangle(
                Vector2(20.0f, 20.0f),
                130.0f,
                130.0f
            ),
            Color::HexRGB(0x00FA3D),
            12
        ), 0);
        triArray.add(drawable::make(
            Triangle(
                Vector2(40.0f, 40.0f),
                130.0f,
                130.0f
            ),
            Color::HexRGB(0x0AA3D),
            6
        ), 3);
    }

    void update(GameContext& ctx) {

    }

    void render(RenderContext& ctx) {
        ctx.draw(triArray);
    }

    void finish() {

    }
};

int main() {  
    UntitledGame game;
    build(game);
}
