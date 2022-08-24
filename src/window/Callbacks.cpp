#include "window/Callbacks.hpp"
#include <iostream>

namespace arcana {
    void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
        std::puts("Framebuffer resized!");
    }

    void setCallbacks(GLFWwindow* window) {
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    }
}