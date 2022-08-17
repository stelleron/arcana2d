#include <iostream>
#include "Arcana2D.hpp"

struct GameData {
    arcana::VertexBuffer vBuffer = arcana::VertexBuffer(arcana::RenderMode::Triangles, 4);
    arcana::VertexBuffer rectBuffer = arcana::VertexBuffer(arcana::RenderMode::Quads, 4);
};

void init(arcana::EngineConfig& config, arcana::UserData user_data) {
    // Setting the title 
    config.win_config.title = "Hello World!";

    // Storing some data
    GameData* gdata = GET_USER_DATA(user_data, GameData);

    // Adding a triangle
    arcana::Triangle triangle{{100.0, 100.0}, {100.0, 200.0}, {200.0, 200.0}};
    gdata->vBuffer << makeDrawable(triangle, arcana::Color(80, 70, 185, 255));

    // Adding a square
    arcana::Rectangle rect{{0.0, 0.0}, 800, 600};
    gdata->rectBuffer << rect;
}

void update(arcana::UserData user_data) {
    GameData* data = GET_USER_DATA(user_data, GameData);
}

void render(arcana::RenderContext& ctx, arcana::UserData user_data) {
    GameData* gdata = GET_USER_DATA(user_data, GameData);
    ctx.draw(gdata->vBuffer);
    ctx.draw(gdata->rectBuffer);
}

void finish(arcana::UserData user_data) {
    std::cout << "Closing application!\n";
}

int main() {
    GameData data;
    arcana::AppConfig config = {
        .user_data = &data,
        .init_fn = init,
        .update_fn = update,
        .render_fn = render,
        .finish_fn = finish,
    };
    arcana::App().build(config).run();
}