#include <glad/glad.h>
#include "gfx/Shader.hpp"
#include "utils/DebugOnly.hpp"
#include "window/Window.hpp"

// DEBUG ONLY

float vertices[] = {
    -0.5f, -0.5f, 0.0f, // left  
     0.5f, -0.5f, 0.0f, // right 
     0.0f,  0.5f, 0.0f  // top   
}; 

namespace arcana {
    Shader shader;
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

        // DEBUG ONLY
        shader = Shader(0, 0);
    }

    bool Window::shouldClose() {
        return glfwWindowShouldClose(window);
    }

    void Window::fill() {
        glClearColor(COLOR_TO_FLOAT(background_color));
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::swapBuffer() {
        // DEBUG ONLY
        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        shader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);    
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glfwSwapBuffers(window);


    }

    Window::~Window() {
        // Destroying for proper practice
        glfwDestroyWindow(window);
    }
}