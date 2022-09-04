#ifndef ARCANA2D_EVENTDATA
    #define ARCANA2D_EVENTDATA
    #include "utils/Vector.hpp"
    
    namespace arcana {
        // Used to store event data
        struct EventData {
            // Store window data
            struct WindowData {
                bool wasResized; // Checks if the window has been resized
                bool wasMoved; // Checks if the window has been moved
                bool isMinimized; // Checks if the window is minimized
                bool isMaximized; // Checks if the window is maximized
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