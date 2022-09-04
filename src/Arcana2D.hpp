#ifndef ARCANA2D_LIBRARY
    #define ARCANA2D_LIBRARY

    // Includes
    #include <string>
    #include <chrono>
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
        // Used to generate randon numbers
        class Random {
            private:
                static unsigned int seed;
            public:
                // Generate a random number between the two given numbers
                static int generateNum(int min, int max);
                // Set a seed
                static void setSeed(unsigned int nSeed);
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

        // ====== GAMECONTEXT.HPP ======
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

                // FUNCTIONS
                // =========
                inline bool wasWindowResized() {return event_data.windowData.wasResized;}
                inline bool wasWindowMoved() {return event_data.windowData.wasMoved;}

                inline float getDeltaTime() {return dt;}
                inline int getFPS() {return (int)1.0f/dt;}

                void updateTitle(const char* title); // Set a new title for the game window during runtime
                // void setWindowIcon(const Image& image); // Set a icon
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