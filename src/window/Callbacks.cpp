#include "window/Callbacks.hpp"
#include "utils/Logger.hpp"
#include "app/GameContext.hpp"

namespace arcana {
    void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
        GameContext* ctx = (GameContext*)glfwGetWindowUserPointer(window);
        glViewport(0, 0, width, height);
        // Modify window data
        (ctx->getEventData()).windowData.wasResized = true;
    }

    void windowMoveCallback(GLFWwindow* window, int xpos, int ypos) {
        GameContext* ctx = (GameContext*)glfwGetWindowUserPointer(window);
        // Modify window data
        (ctx->getEventData()).windowData.wasMoved = true;
        (ctx->getEventData()).windowData.windowPos = {xpos, ypos};
    }

    void setCallbacks(GLFWwindow* window) {
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
        glfwSetWindowPosCallback(window, windowMoveCallback);
    }
}