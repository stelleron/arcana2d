#ifndef ARCANA2D_WINDOW
    #define ARCANA2D_WINDOW
    // Includes
    #include <GLFW/glfw3.h>
    #include "engine/EngineConfig.hpp"

    namespace arcana {
        // Used to create a window object
        class Window {
            private: 
                GLFWwindow* window;
                Color background_color;
            public: 
                // Constructor/destructor
                Window();
                ~Window();

                // Window initialiser
                void init(const EngineConfig& config);

                // Check if the window should close
                bool shouldClose();

                // Clear the framebuffer with the stored background color
                void fill();

                // Swap buffers on the window
                void swapBuffer();
        };
    }
#endif