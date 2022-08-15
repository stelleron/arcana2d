#ifndef ARCANA2D_SHADER
    #define ARCANA2D_SHADER

    #include <glad/glad.h>
    #include <glm/glm.hpp>

    namespace arcana {
        // Used to create a shader class 
        class Shader {
            private:
                bool is_init;
                unsigned int id;
            public:
                // Different shader constructors 
                Shader();
                Shader(int exclude1, int exclude2);
                Shader(const char* vSource, int exclude);
                Shader(int exclude, const char* fSource);
                Shader(const char* vSource, const char* fSource);

                // Uniform setting functions
                void setBool(const char* name, bool value);  
                void setInt(const char* name, int value);   
                void setFloat(const char* name, float value);
                void setMat4(const char* name, glm::mat4 matrix);

                // Use the shader
                void use();

                // Getters
                inline const unsigned int getID() {return id;}
                inline const bool getInit() {return is_init;}

                // Setters
                void deInit() { is_init = false;}

                // Copy assignment operator
                Shader& operator=(Shader& shader) {
                    if (is_init) {glDeleteProgram(id);} 
                    id = shader.getID();
                    shader.deInit();
                    is_init = true;
                    return *this;
                }

                // Destructor
                ~Shader();
        };
    }
#endif