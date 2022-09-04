#ifndef ARCANA2D_LIBRARY
    #define ARCANA2D_LIBRARY

    // Includes
    #include <string>
    #include <chrono>
    #include <queue>
    #include <glm/glm.hpp>
    #include <glad/glad.h>
    #include <GLFW/glfw3.h>

    // Exposed library functions and classes
    namespace arcana {
        // ====== COLOR.HPP ======
        // Used to create a color object
        struct Color {
            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a;

            // Constructor options
            Color();
            Color(unsigned char r, unsigned char g, unsigned char b);
            Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

            // Static constructors
            static Color RGB(unsigned char r, unsigned char g, unsigned char b);
            static Color RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
            static Color HSV(float h, float s, float v);
            static Color HSVA(float h, float s, float v, unsigned char a);
            static Color NormalRGB(float r_normal, float g_normal, float b_normal);
            static Color NormalRGBA(float r_normal, float g_normal, float b_normal, float a_normal);
            static Color HexRGB(int hexValue);
            static Color HexRGBA(int hexValue);
        };

        // COLOR MACROS
        #define WHITE arcana::Color::RGB(255, 255, 255)
        #define RED arcana::Color::RGB(255, 0, 0)
        #define GREEN arcana::Color::RGB(0, 255, 0)
        #define YELLOW arcana::Color::RGB(255, 255, 0)
        #define BLUE arcana::Color::RGB(0, 0, 255)
    

        // ====== VECTOR.HPP ======
        // Namespace defines
        // Used to define vectors
        using Vector2 = glm::vec2;
        using Vector3 = glm::vec3;
        using Vector4 = glm::vec4;

        // Used to define matrices
        using Mat2 = glm::mat2;
        using Mat3 = glm::mat3;
        using Mat4 = glm::mat4;

        // ====== TIMER.HPP ======
        using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
        // Used to create a timer object
        class Timer {
            private:
                TimePoint startTime;
            public:
                // Constructor
                Timer();

                // Reset the timer
                void reset();

                // Get the elapsed time
                float getElapsed();

                // Get the elapsed time in milliseconds
                float getElapsedMillis();
        };

        // ====== RANDOM.HPP ======
        // Used to generate random numbers
        class Random {
            private:
                unsigned int seed;
            public:
                // Constructor
                Random();
                Random(unsigned int seed);
                // Generate a random number between the two given numbers
                int generateNum(int min, int max);
                // Set a seed
                void setSeed(unsigned int nSeed);
        };

        // ====== FILESYSTEM.CPP ======
        // Used to create a filesystem
        // Used to create a filesystem
        class Filesystem {
            private:
                std::string currentWorkingDir; // Stores the current working directory to load files from
            public: 
                // Constructor
                Filesystem();

                // Set the working directory
                void setDir(const std::string& dir);
                // Check if directory exists
                bool dirExists(const std::string& dir);
                // Check if file exists
                bool fileExists(const std::string& dir);


                // File loading functions
                std::string loadFileStr(const std::string& fpath); // Load it as a string instead
                char* loadFileText(const std::string& fpath); // Null terminates the file text
                unsigned char* loadFileData(const std::string& path);
                // File unloading functions
                void unloadFileText(char* data);
                void unloadFileData(unsigned char* data);
                // File saving functions
                void saveFileStr(const std::string& path, const std::string& data);
                void saveFileText(const std::string& path, char* data);
                void saveFileData(const std::string& path, unsigned char* data);
        };

        // ====== WINDOW.HPP ======
        // Used to create a window object
        class Window {
            private: 
                GLFWwindow* window;
                Color background_color;
                bool halt_while_hidden;
        }; // Methods hidden for the purpose of hiding window data

        // ====== APPCONFIG.HPP ======
        // Used to configure the application
        struct AppConfig {
            int width;
            int height;
            std::string title;
            Color background_color;

            // Window settings
            bool resizable; 
            bool maximized; 
            bool fullscreen;
            bool decorated;
            bool vsync;
            bool transparent;
            bool focused;
            bool halt_while_hidden; // Set whether the app will pause while hidden

            // Framerate cap
            int fps_cap;
            // Opacity
            float opacity;
            // Min to max size
            Vector2 min_size;
            Vector2 max_size;

            // Default constructor
            AppConfig();
        };

        // ====== CAMERA.HPP ======
        // Used to create a 2D camera
        class Camera {
            private:
                Vector2 dimensions; // Stores the camera dimensions
                Vector2 offset; // Camera offset
                float rotation; // Camera rotation
                float zoom; // Camera zoom
            public:
                // Constructor
                Camera();
                // Destructor 
                ~Camera();

                // Set the camera dimensions
                void setDim(int width, int height);
                // Set the zoom of the camera
                void setZoom(float zoom);

                // Get the projection matrix
                Mat4 getProjectionMatrix();
        };

        // ====== EVENTDATA.HPP ======
        // Current supported keys enum
        enum Key {
            Space = 1,
            Apostrophe,
            Comma,
            Minus,
            Period,
            Slash,
            Zero,
            One,
            Two, 
            Three,
            Four,
            Five,
            Six,
            Seven,
            Eight,
            Nine,
            Semicolon,
            Equal,
            A,
            B,
            C,
            D,
            E,
            F, 
            G,
            H,
            I,
            J,
            K, 
            L,
            M,
            N,
            O,
            P,
            Q,
            R,
            S,
            T,
            U,
            V,
            W,
            X,
            Y,
            Z,
            LeftBracket,
            Backslash,
            RightBracket,
            GraveAccent,
            World1,
            World2,
            Escape,
            Enter,
            Tab,
            Backspace,
            Insert,
            Delete,
            Right,
            Left,
            Down,
            Up,
            PageUp,
            PageDown,
            Home,
            End,
            CapsLock,
            ScrollLock,
            NumLock,
            PrintScreen,
            Pause,
            F1,
            F2,
            F3,
            F4,
            F5,
            F6,
            F7, 
            F8,
            F9,
            F10,
            F11,
            F12,
            F13,
            F14, 
            F15,
            F16,
            F17,
            F18,
            F19,
            F20,
            F21,
            F22,
            F23,
            F24, 
            F25,
            KP0,
            KP1,
            KP2,
            KP3,
            KP4,
            KP5,
            KP6,
            KP7,
            KP8,
            KP9,
            KPDecimal,
            KPDivide,
            KPMultiply,
            KPSubtract,
            KPAdd,
            KPEnter,
            KPEqual,
            LeftShift,
            LeftControl,
            LeftAlt,
            LeftSuper,
            RightShift,
            RightControl,
            RightAlt,
            RightSuper,
            Menu 
        };

        // Current supported buttons enum
        enum MouseButton {
            LeftButton = 1,
            MiddleButton,
            RightButton
        };

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
                Vector2 mousePos; 
                Vector2 mouseLastPos;
                float mScrollH;
                float mScrollV;
                bool buttonPressed[MouseButton::RightButton];
                bool buttonLastPressed[MouseButton::RightButton];
            };

            // Store keyboard events
            struct KeyboardData {
                bool keyPressed[Key::Menu];
                bool keyLastPressed[Key::Menu];
                std::queue<unsigned char> charQueue;
            };

            // Store gamepad data
            struct GamepadData {
                // TODO in a later version
            };

            WindowData windowData;
            KeyboardData keyboardData;
            MouseData mouseData;
            GamepadData gamepadData;

            // Default initialiser
            EventData();

            // Reset event data
            void reset();
        };

        // ====== GAMECONTEXT.HPP ======
        // Used to communicate with the application logic
        class GameContext {
            private:
                Window* win_pointer;
                Camera* curr_camera;
                EventData event_data;
                Random randNumGen;
                float dt;
            public:
                // SETTERS
                // =======
                void setCamera(Camera& camera);

                // GETTERS
                // =======

                // FUNCTIONS
                // =========
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

                // == Gamepad input functions

                // == Random functions
                inline void setSeed(unsigned int seed) {randNumGen.setSeed(seed);}
                inline int generateNum(int min, int max) {return randNumGen.generateNum(min, max);}
        };

        // ====== APPLICATION.HPP ======
        // Used to create the Application class to be extended
        class Application {
            // Application virtual functions
            public:
                virtual void config(AppConfig& config) = 0;
                virtual void init(GameContext& ctx) = 0;
                virtual void update(GameContext& ctx) = 0;
                virtual void render() = 0;
                virtual void finish() = 0;
        };

        // Used to create the application
        void build(Application& app);
    }
#endif