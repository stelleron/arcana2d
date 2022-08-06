#ifndef ARCANA2D_ENGINE_CONFIG
    #define ARCANA2D_ENGINE_CONFIG
    // Includes
    #include <string>
    #include "utils/Color.hpp"

    namespace arcana {
        // Used to configure the game engine
        struct EngineConfig {
            // Structs inside the engine config
            struct WindowConfig {
                int width;
                int height;
                std::string title;
                Color background_color;
            };

            // Properties
            WindowConfig win_config;

            // Constructor
            EngineConfig();
        };
    }
#endif