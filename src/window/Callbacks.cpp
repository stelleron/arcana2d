#include <GLFW/glfw3.h>
#include "window/Callbacks.hpp"
#include "utils/Logger.hpp"
#include "context/GameContext.hpp"

namespace arcana {
    void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    void windowSizeCallback(GLFWwindow* window, int width, int height) {
        GameContext* ctx = (GameContext*)glfwGetWindowUserPointer(window);
        // Resize the camera
        (ctx->getCamera())->setDim(width, height);
        // Modify window data
        (ctx->getEventData()).windowData.isResized = true;
    }

    void windowPosCallback(GLFWwindow* window, int xpos, int ypos) {
        GameContext* ctx = (GameContext*)glfwGetWindowUserPointer(window);
        // Modify window data
        (ctx->getEventData()).windowData.isMoved = true;
        (ctx->getEventData()).windowData.windowPos = {xpos, ypos};
    }

    void windowIconifyCallback(GLFWwindow* window, int iconified) {
        GameContext* ctx = (GameContext*)glfwGetWindowUserPointer(window);
        (ctx->getEventData()).windowData.isIconified = iconified;
    }

    void setCallbacks(GLFWwindow* window) {
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
        glfwSetWindowSizeCallback(window, windowSizeCallback);
    }
}