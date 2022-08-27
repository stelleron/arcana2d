#ifndef ARCANA2D_APPCONFIG
    #define ARCANA2D_APPCONFIG
    // Includes
    #include <string>
    #include "utils/Color.hpp"

    namespace arcana {
        struct AppConfig {
            int width;
            int height;
            std::string title;
            Color background_color;

            bool resizable; 
            bool maximized; 
            bool fullscreen;
            bool decorated;
            bool vsync;
            bool transparent;
            bool focused;
            bool haltWhileHidden; // Set whether the app will pause while hidden

            // Framerate cap
            int fps_cap;

            // Default constructor
            AppConfig();
        };
    }
#endif