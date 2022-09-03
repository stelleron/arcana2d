#ifndef ARCANA2D_GAME_CONTEXT
    #define ARCANA2D_GAME_CONTEXT

    #include "camera/Camera.hpp"
    #include "window/Window.hpp"
    #include "input/EventData.hpp"

    namespace arcana {
        // Used to communicate with the application logic
        class GameContext {
            private:
                Window* win_pointer;
                Camera* curr_camera;
                EventData event_data;
                float dt;
            public:
                // Constructor
                GameContext();
                // Destructor
                ~GameContext();

                // SETTERS
                // =======
                void setCamera(Camera& camera);
                void setWindow(Window& window);
                void setDeltaTime(float dt);

                // GETTERS
                // =======
                Camera* getCamera();
                EventData& getEventData();

                // FUNCTIONS
                // =========
                void resetEvents(); // Reset the event data buffer


                // Window functions
                inline bool isWindowResized() {return event_data.windowData.isResized;} // Was the window resized 
                inline bool isWindowMoved() {return event_data.windowData.isMoved;} // Was the window moved 
                inline bool isWindowIconified() {return event_data.windowData.isIconified;} // Is the window iconified
                inline Vector2 getWindowPos() {return event_data.windowData.windowPos;} // Gets the window position

                Vector2 getWindowSize();
                void setMinWindowSize(int min_width, int min_height);
                void setMaxWindowSize(int max_width, int max_height);
                void setWindowPos(int x, int y);
                void setWindowPos(Vector2 pos);
                void restoreWindow();
                void iconifyWindow();

                inline float getDeltaTime() {return dt;}
                inline int getFPS() {return (int)1.0f/dt;}

                void updateTitle(const char* title); // Set a new title for the game window during runtime
                // void setWindowIcon(const Image& image); // Set a icon
        };
    }
#endif