#ifndef ARCANA2D_EVENTDATA
    #define ARCANA2D_EVENTDATA
    #include "utils/Vector.hpp"
    
    namespace arcana {
        // Used to store event data
        struct EventData {
            // Store window data
            struct WindowData {
                bool isResized; // Checks if the window has been resized
                bool isMoved; // Checks if the window has been moved
                bool isIconified; // Checks if the window is iconified
                Vector2 windowPos; // Stores the window position
            };
            
            // Store mouse events
            struct MouseData {

            };

            // Store keyboard events
            struct KeyboardData {
            
            };

            // Store gamepad data
            struct GamepadData {

            };

            WindowData windowData;
            KeyboardData keyboardData;
            MouseData mouseData;
            GamepadData gamepadData;

            // Reset event data
            void reset();
        };
    };
#endif