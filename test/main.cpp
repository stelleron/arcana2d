#include <iostream>
#include "Arcana2D.hpp"

struct GameData {
    int x = 5;
};

void init(arcana::EngineConfig& config, arcana::UserData user_data) {
    // Setting the title 
    config.win_config.title = "Hello World!";
}

void update(arcana::UserData user_data) {
    GameData* data = GET_USER_DATA(user_data, GameData);
}

void render(arcana::UserData user_data) {

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