#ifndef ARCANA2D_CALLBACKS
    #define ARCANA2D_CALLBACKS
    // Includes
    #include <GLFW/glfw3.h>

    namespace arcana {
        // Callbacks here
        void framebufferSizeCallback(GLFWwindow* window, int width, int height);

        // Function to set callbacks
        void setCallbacks(GLFWwindow* window);
    }
#endif