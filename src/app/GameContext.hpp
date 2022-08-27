#ifndef ARCANA2D_GAME_CONTEXT
    #define ARCANA2D_GAME_CONTEXT

    #include "utils/Camera.hpp"
    #include "input/EventData.hpp"
    #include "res/Image.hpp"
    #include "window/Window.hpp"

    namespace arcana {
        // Used to communicate with the application logic
        class GameContext {
            private:
                Window* win_pointer;
                Camera* curr_camera;
                EventData event_data;
            public:
                // Constructor
                GameContext();
                // Destructor
                ~GameContext();

                // SETTERS
                // =======
                void setCamera(Camera& camera);
                void setWindow(Window& window);

                // GETTERS
                // =======
                Camera* getCamera();
                EventData& getEventData();

                // FUNCTIONS
                // =========
                void resetEvents(); // Reset the event data buffer

                inline bool wasWindowResized() {return event_data.windowData.wasResized;}
                inline bool wasWindowMoved() {return event_data.windowData.wasMoved;}

                void updateTitle(const char* title); // Set a new title for the game window during runtime
                void setWindowIcon(const Image& image); // Set a icon
        };
    }
#endif