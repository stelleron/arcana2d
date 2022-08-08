#include "engine/App.hpp"
#include "utils/DebugOnly.hpp"

namespace arcana {
    // APP IMPL.
    App::App() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        #ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif
    }

    App& App::build(const AppConfig& config) {
        app_config = config;
        return *this;
    }

    void App::run() {
        // 1. INIT STAGE
        // First call the init function
        app_config.init_fn(eng_config, app_config.user_data);
        // And use it to initialise the window
        window.init(eng_config);
        // Also intialise the render context
        render_ctx.init();
        
        // 2. LOOP STAGE
        // Then loop over the update and render functions
        while( !window.shouldClose() ) { // If the game should be closed, simply set the window to close
            // Update func
            glfwPollEvents(); // Poll events before
            app_config.update_fn(app_config.user_data);

            // Render func
            window.fill();
            render_ctx.useDefault();
            app_config.render_fn(render_ctx, app_config.user_data);
            window.swapBuffer();
        }

        // 3. CLEANUP STAGE
        // Simply call the finish function; the destructor handles the rest
        app_config.finish_fn(app_config.user_data);
    }

    App::~App() {
        glfwTerminate();
    }
}