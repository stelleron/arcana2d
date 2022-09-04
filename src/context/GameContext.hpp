#ifndef ARCANA2D_GAME_CONTEXT
    #define ARCANA2D_GAME_CONTEXT

    #include "utils/Logger.hpp"
    #include "camera/Camera.hpp"
    #include "window/Window.hpp"
    #include "input/EventData.hpp"
    #include "utils/Random.hpp"

    namespace arcana {
        // Used to communicate with the application logic
        class GameContext {
            private:
                Window* win_pointer;
                Camera* curr_camera;
                EventData event_data;
                Random randNumGen;
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
                // If the mouse button was just pressed
                inline bool isMouseButtonPressed(MouseButton button) {
                    if (event_data.mouseData.buttonPressed[button - 1] && !event_data.mouseData.buttonLastPressed[button - 1]) {
                        return true;
                    }
                    return false;
                }

                // If the mouse button was just released
                inline bool isMouseButtonReleased(MouseButton button) {
                    if (!event_data.mouseData.buttonPressed[button - 1] && event_data.mouseData.buttonLastPressed[button - 1]) {
                        return true;
                    }
                    return false;
                }

                // If the mouse button was being held
                inline bool isMouseButtonHeld(MouseButton button) {
                    if (event_data.mouseData.buttonPressed[button - 1] && event_data.mouseData.buttonLastPressed[button - 1]) {
                        return true;
                    }
                    return false;
                }

                // If the mouse button is up
                inline bool isMouseButtonUp(MouseButton button) {
                    if (!event_data.mouseData.buttonPressed[button - 1] && !event_data.mouseData.buttonLastPressed[button - 1]) {
                        return true;
                    }
                    return false;
                }

                // Get mouse position 
                inline Vector2 getMousePos() {return event_data.mouseData.mousePos;}

                // Get mouse delta
                inline Vector2 getMouseDelta() {return Vector2(event_data.mouseData.mousePos.x - event_data.mouseData.mouseLastPos.x, 
                                                event_data.mouseData.mousePos.y - event_data.mouseData.mouseLastPos.y);}

                // Get vertical scroll
                inline float getVerticalScroll() {return event_data.mouseData.mScrollV;}

                // Get scroll vector
                inline Vector2 getScroll() {return Vector2(event_data.mouseData.mScrollH, event_data.mouseData.mScrollV);}

                // == Keyboard input functions
                // If the key was just pressed
                inline bool isKeyPressed(Key key) {
                    if (event_data.keyboardData.keyPressed[key - 1] && !event_data.keyboardData.keyLastPressed[key - 1]) {
                        return true;
                    }
                    return false;
                }

                // If the key was just released
                inline bool isKeyReleased(Key key) {
                    if (!event_data.keyboardData.keyPressed[key - 1] && event_data.keyboardData.keyLastPressed[key - 1]) {
                        return true;
                    }
                    return false;
                }

                // If the key is being held down
                inline bool isKeyHeld(Key key) {
                    if (event_data.keyboardData.keyPressed[key - 1] && event_data.keyboardData.keyLastPressed[key - 1]) {
                        return true;
                    }
                    return false;
                }

                // If the key isn't being pressed at all
                inline bool isKeyUp(Key key) {
                    if (!event_data.keyboardData.keyPressed[key - 1] && !event_data.keyboardData.keyLastPressed[key - 1]) {
                        return true;
                    }
                    return false;
                }

                // Get typed characters one at a time
                inline unsigned char getCharPressed() {
                    if (event_data.keyboardData.charQueue.size() > 0) {
                        unsigned char val = event_data.keyboardData.charQueue.front();
                        event_data.keyboardData.charQueue.pop();
                        return val;
                    }
                    else {
                        return 0;
                    }
                }

                // == Random functions
                inline void setSeed(unsigned int seed) {randNumGen.setSeed(seed);}
                inline int generateNum(int min, int max) {return randNumGen.generateNum(min, max);}

                // == Gamepad input functions
        };
    }
#endif