#include "window/Callbacks.hpp"
#include "utils/Logger.hpp"

namespace arcana {
    void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
        LOG("Framebuffer resized!");
    }

    void setCallbacks(GLFWwindow* window) {
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    }
}