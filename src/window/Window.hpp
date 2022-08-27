#ifndef ARCANA2D_WINDOW
    #define ARCANA2D_WINDOW

    // Includes
    #include <GLFW/glfw3.h>
    #include "app/AppConfig.hpp"

    namespace arcana {
        // Used to create a window object
        class Window {
            private: 
                GLFWwindow* window;
                Color background_color;
                bool haltWhileHidden;
            public: 
                // Constructor/destructor
                Window();
                ~Window();

                // Window initialiser
                void init(const AppConfig& config);

                // Check if the window should close
                bool shouldClose();

                // Check if the window is active
                bool isActive();

                // Poll events
                void pollEvents();

                // Clear the framebuffer with the stored background color
                void fill();

                // Swap buffers on the window
                void swapBuffer();

                // Set the window user data
                void setData(void* ptr);

                // Get the window user data
                void* getData();

                // Set the title of the window
                void updateTitle(const char* title);

                // Set the icon of the window
                void setIcon(int width, int height, unsigned char* data);
        };
    }
#endif