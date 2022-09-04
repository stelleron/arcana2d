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
        (ctx->getEventData()).windowData.wasResized = true;
    }

    void windowPosCallback(GLFWwindow* window, int xpos, int ypos) {
        GameContext* ctx = (GameContext*)glfwGetWindowUserPointer(window);
        // Modify window data
        (ctx->getEventData()).windowData.wasMoved = true;
        (ctx->getEventData()).windowData.windowPos = {xpos, ypos};
    }

    void windowIconifyCallback(GLFWwindow* window, int iconified) {
        GameContext* ctx = (GameContext*)glfwGetWindowUserPointer(window);
        (ctx->getEventData()).windowData.isMinimized = iconified;
    }

    void windowMaxmizeCallback(GLFWwindow* window, int maximized) {
        LOG("wjsds");
        GameContext* ctx = (GameContext*)glfwGetWindowUserPointer(window);
        (ctx->getEventData()).windowData.isMaximized = maximized;        
    }

    void setCallbacks(GLFWwindow* window) {
        glfwSetWindowIconifyCallback(window, windowIconifyCallback);
        glfwSetWindowMaximizeCallback(window, windowMaxmizeCallback);
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
        glfwSetWindowSizeCallback(window, windowSizeCallback);
    }
}