#ifndef ARCANA2D_EVENTDATA
    #define ARCANA2D_EVENTDATA
    #include "utils/Vector.hpp"
    
    namespace arcana {
        // Used to store event data
        struct EventData {
            // Store window data
            struct WindowData {
                bool wasResized; // Checks if the window was resized
                bool wasClosed; // Checks if the window was closed this frame
                bool wasMoved; // Checks if the window was moved
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