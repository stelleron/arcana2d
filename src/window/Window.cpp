#include <glad/glad.h>
#include "window/Window.hpp"
#include "window/Callbacks.hpp"

namespace arcana {
    // WINDOW IMPL.
    Window::Window() {
        glfwDefaultWindowHints();
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        #ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif
    }

    void Window::init(const AppConfig& config) {
        // Set some flags
        glfwWindowHint(GLFW_RESIZABLE, config.resizable);
        glfwWindowHint(GLFW_DECORATED, config.decorated);
        glfwWindowHint(GLFW_MAXIMIZED, config.maximized);
        glfwWindowHint(GLFW_FOCUSED, config.focused);
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, config.transparent);

        // Check if fullscreen enabled before creating the window
        if (config.fullscreen) {
            window = glfwCreateWindow(config.width, config.height, 
                                  config.title.c_str(), glfwGetPrimaryMonitor(), NULL);
        }
        else {
            window = glfwCreateWindow(config.width, config.height, 
                                  config.title.c_str(), NULL, NULL);
        }

        // Set the window to the current context
        glfwMakeContextCurrent(window);

        // Initialise GLAD
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        // And set the OpenGL viewport
        int left, top, right, bottom;
        glfwGetWindowFrameSize(window, &left, &top, &right, &bottom);   
        glViewport(0, 0, right - left, bottom - top);

        // And set the background color
        background_color = config.background_color;

        // And set callbacks
        setCallbacks(window);

        // Finally set vsync
        if (config.vsync) 
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        haltWhileHidden = config.haltWhileHidden;
    }

    void Window::pollEvents() {
        glfwPollEvents();
    }

    bool Window::shouldClose() {
        return glfwWindowShouldClose(window);
    }

    bool Window::isActive() {
        if (haltWhileHidden)
            if (!glfwGetWindowAttrib(window, GLFW_VISIBLE))
                return false;
        return true;
    }

    void Window::fill() {
        glClearColor(COLOR_TO_FLOAT(background_color));
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::swapBuffer() {
        // And swap buffers
        glfwSwapBuffers(window);
    }

    void Window::setData(void* ptr) {
        glfwSetWindowUserPointer(window, ptr);
    }

    void* Window::getData() {
        return glfwGetWindowUserPointer(window);
    }

    void Window::updateTitle(const char* title) {
        glfwSetWindowTitle(window, title);
    }

    Window::~Window() {
        // Destroying for proper practice
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}