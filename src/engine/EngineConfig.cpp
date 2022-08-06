#include "EngineConfig.hpp"
namespace arcana {
    // ENGINE CONFIG IMPL.
    EngineConfig::EngineConfig() {
        win_config.width = 800;
        win_config.height = 600;
        win_config.title = "Untitled Game";
        win_config.background_color = Color(20, 20, 20, 255);
    }
}