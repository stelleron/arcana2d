#ifndef ARCANA2D_APP
    #define ARCANA2D_APP
    // Includes
    #include "engine/EngineConfig.hpp"
    #include "window/Window.hpp"
    #include <functional>

    namespace arcana {
        // Type for user data
        struct UserData {
            void* data;
            UserData& operator= (void* ptr) {
                data = ptr;
            }
        };

        // Macro to convert user data 
        #define GET_USER_DATA(u_data, type) (type*)u_data.data;

        // Redefining types for the application
        using InitFn = std::function<void(EngineConfig&, UserData)>;
        using UpdateFn = std::function<void(UserData)>;
        using RenderFn = std::function<void(UserData)>;
        using FinishFn = std::function<void(UserData)>;

        // Configures the application
        struct AppConfig {
            UserData user_data;
            InitFn init_fn;
            UpdateFn update_fn;
            RenderFn render_fn;
            FinishFn finish_fn;
        };

        // Creates an application
        class App {
            private:
                AppConfig app_config; // Stores the app config functions
                EngineConfig eng_config; // Stores the engine config data
                Window window; // Stores the main window
            public:
                App(); // Constructor

                App& build(const AppConfig& config); // Build the application

                void run(); // Run the application

                ~App();
        };
    }

#endif