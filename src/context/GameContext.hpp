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


                // == Window functions
                inline bool wasWindowResized() {return event_data.windowData.wasResized;} // Was the window resized last frame?
                inline bool wasWindowMoved() {return event_data.windowData.wasMoved;} // Was the window moved last frame?
                inline bool isWindowMinimized() {return event_data.windowData.isMinimized;} // Is the window minimized?
                inline bool isWindowMaxmized() {return event_data.windowData.isMaximized;} // Is the window maximized?
                inline Vector2 getWindowPos() {return event_data.windowData.windowPos;} // Gets the window position

                Vector2 getWindowSize();
                void setMinWindowSize(int min_width, int min_height);
                void setMaxWindowSize(int max_width, int max_height);
                void setWindowPos(int x, int y);
                void setWindowPos(Vector2 pos);
                void restoreWindow();
                void minimizeWindow();
                void maximizeWindow();

                void updateTitle(const char* title); // Set a new title for the game window during runtime
                // void setWindowIcon(const Image& image); // Set a icon

                // == Time functions
                inline float getDeltaTime() {return dt;}
                inline int getFPS() {return (int)1.0f/dt;}

                // == Mouse input functions

                // == Keyboard input functions
                // If the key was just pressed
                inline bool isKeyPressed(Key key) {
                    if (event_data.keyboardData.keyPressed[key] && !event_data.keyboardData.keyLastPressed[key]) {
                        return true;
                    }
                }

                // If the key was just released
                inline bool isKeyReleased(Key key) {
                    if (!event_data.keyboardData.keyPressed[key] && event_data.keyboardData.keyLastPressed[key]) {
                        return true;
                    }
                }

                // If the key is being held down
                inline bool isKeyHeld(Key key) {
                    if (event_data.keyboardData.keyPressed[key] && event_data.keyboardData.keyLastPressed[key]) {
                        return true;
                    }
                }

                // == Gamepad input functions
        };
    }
#endif