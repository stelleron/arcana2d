#ifndef ARCANA2D_SHADER
    #define ARCANA2D_SHADER

    #include <glad/glad.h>
    namespace arcana {
        // Used to create a shader class 
        class Shader {
            private:
                unsigned int id;
                bool is_init;
            public:
                // Different shader constructors 
                Shader();
                Shader(int exclude1, int exclude2);
                Shader(const char* vSource, int exclude);
                Shader(int exclude, const char* fSource);
                Shader(const char* vSource, const char* fSource);
                Shader& operator=(const Shader& shader) {
                    if (is_init) {glDeleteProgram(id);} 
                    id = getID();
                    is_init = true;
                    return *this;
                }

                // Uniform setting functions
                void setBool(const char* name, bool value);  
                void setInt(const char* name, int value);   
                void setFloat(const char* name, float value);

                // Use the shader
                void use();
                
                // Getters
                inline unsigned int getID() {return id;}
                inline bool getInit() {return is_init;}

                // Destructor
                ~Shader();
        };
    }
#endif