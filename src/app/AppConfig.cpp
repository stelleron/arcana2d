#include "app/AppConfig.hpp"
namespace arcana {
    AppConfig::AppConfig() {
        width = 800;
        height = 600;
        title = "Untitled Game";
        background_color = Color::RGB(20, 20, 20);

        resizable = false;
        fullscreen = false;
        decorated = true;
        maximized = false;
        vsync = true;
        transparent = false;
        focused = true;
        haltWhileHidden = true;

        fps_cap = 60;
    }
}