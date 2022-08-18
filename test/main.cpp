#include <iostream>
#include "Arcana2D.hpp"

struct GameData {
    arcana::Sprite sprite;
    arcana::VertexBuffer vBuffer;

    // Constructor 
    GameData() : vBuffer(arcana::RenderMode::Triangles, 4)
    {
        
    }
};

void config(arcana::EngineConfig& config, arcana::UserData user_data) {
    // Setting the title 
    config.win_config.title = "Hello World!";
}

void init(arcana::UserData user_data) {
    // Storing some data
    GameData* gdata = GET_USER_DATA(user_data, GameData);
    gdata->sprite.load("build/pepe-sad.png");
    gdata->vBuffer << arcana::Triangle{{0.0, 0.0},  {400.0, 0.0}, {0.0, 100.0}};
}

void update(arcana::UserData user_data) {
    GameData* data = GET_USER_DATA(user_data, GameData);
}

void render(arcana::RenderContext& ctx, arcana::UserData user_data) {
    GameData* gdata = GET_USER_DATA(user_data, GameData);
    // Render the sprite
    ctx.draw(gdata->sprite);
    ctx.draw(gdata->vBuffer);
}

void finish(arcana::UserData user_data) {
    std::cout << "Closing application!\n";
}

int main() {
    GameData data;
    arcana::AppConfig app_config = {
        .user_data = &data,
        .config_fn = config,
        .init_fn = init,
        .update_fn = update,
        .render_fn = render,
        .finish_fn = finish,
    };
    arcana::App().build(app_config).run();
}