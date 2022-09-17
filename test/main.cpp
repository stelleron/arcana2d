#include "Arcana2D.hpp"

using namespace arcana;

class UntitledGame : public Application {
    VertexArray triArray = VertexArray(RenderMode::Triangles, 6);

    void config(AppConfig& config) {

    }

    void init(GameContext& ctx) {
        triArray[0] = Vertex(Vector3(150.0f, 50.0f, 25.0f),  Color(255, 0, 0, 255));
        triArray[1] = Vertex(Vector3(50.0f, 150.0f, 25.0f),  Color(0, 255, 0, 255));
        triArray[2] = Vertex(Vector3(150.0f, 150.0f, 25.0f), Color(0, 0, 255, 255));
        triArray[3] = Vertex(Vector3(180.0f, 80.0f, 5.0f),  Color(255, 0, 0, 255));
        triArray[4] = Vertex(Vector3(80.0f, 180.0f, 5.0f),  Color(0, 255, 0, 255));
        triArray[5] = Vertex(Vector3(180.0f, 180.0f, 5.0f), Color(0, 0, 255, 255));
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
