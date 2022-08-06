#include <glad/glad.h>
#include "utils/DebugOnly.hpp"
#include "window/Window.hpp"

namespace arcana {
    // WINDOW IMPL.
    Window::Window() {

    }

    void Window::init(const EngineConfig& config) {
        window = glfwCreateWindow(config.win_config.width, config.win_config.height, 
                                  config.win_config.title.c_str(), NULL, NULL);
        // Set the window to the current context
        glfwMakeContextCurrent(window);

        // Initialise GLAD
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        // And finally set the OpenGL viewport
        glViewport(0, 0, config.win_config.width, config.win_config.height);

        // And set the background color
        background_color = config.win_config.background_color;
    }

    bool Window::shouldClose() {
        return glfwWindowShouldClose(window);
    }

    void Window::fill() {
        glClearColor(COLOR_TO_FLOAT(background_color));
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::swapBuffer() {
        glfwSwapBuffers(window);
    }

    Window::~Window() {
        // Destroying for proper practice
        glfwDestroyWindow(window);
    }
}