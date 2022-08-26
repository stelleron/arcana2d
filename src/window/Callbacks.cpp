#include "window/Callbacks.hpp"
#include "utils/Logger.hpp"
#include "app/GameContext.hpp"

namespace arcana {
    void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
        GameContext* ctx = (GameContext*)glfwGetWindowUserPointer(window);
        glViewport(0, 0, width, height);
    }

    void setCallbacks(GLFWwindow* window) {
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    }
}