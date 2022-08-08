#include "gfx/Shader.hpp"
#include <string>
#include "utils/DebugOnly.hpp"

namespace arcana {
    const char *vShaderSrc = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    const char *fShaderSrc = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

    // Shader compile functions
    void printErrors(unsigned int id, GLenum cmdType) {
        int success;
        char infoLog[512];
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(id, 512, NULL, infoLog);
            std::string logstr = infoLog;
            LOG(logstr.c_str());
        };
    }

    inline unsigned int compileShader(const char* source, GLenum sType) {
        unsigned int shaderid = glCreateShader(sType);
        glShaderSource(shaderid, 1, &source, NULL);
        glCompileShader(shaderid);
        printErrors(shaderid, GL_COMPILE_STATUS);
        return shaderid;   
    }

    inline unsigned int compileProgram(unsigned int vShader, unsigned int fShader) {
        unsigned int shaderid = glCreateProgram();
        glAttachShader(shaderid, vShader);
        glAttachShader(shaderid, fShader);
        glLinkProgram(shaderid);
        printErrors(shaderid, GL_LINK_STATUS);
        return shaderid;
    }

    // Impl. for shaders
    Shader::Shader() {
        is_init = false;
    }

    Shader::Shader(int exclude1, int exclude2) {
        id = compileProgram(
            compileShader(vShaderSrc, GL_VERTEX_SHADER), 
            compileShader(fShaderSrc, GL_FRAGMENT_SHADER)
        );
        is_init = true;
    }

    Shader::Shader(int exclude, const char* fSource) {
        id = compileProgram(
            compileShader(vShaderSrc, GL_VERTEX_SHADER), 
            compileShader(fSource, GL_FRAGMENT_SHADER)
        );
        is_init = true;
    } 

    Shader::Shader(const char* vSource, int exclude) {
        id = compileProgram(
            compileShader(vSource, GL_VERTEX_SHADER), 
            compileShader(fShaderSrc, GL_FRAGMENT_SHADER)
        );
        is_init = true;
    }

    Shader::Shader(const char* vSource, const char* fSource) {
        id = compileProgram(
            compileShader(vSource, GL_VERTEX_SHADER), 
            compileShader(fSource, GL_FRAGMENT_SHADER)
        );
        is_init = true;        
    }

    void Shader::setBool(const char* name , bool value) {
        if (is_init) {
            glUniform1i(glGetUniformLocation(id, name), (int)value); 
        }
    }

    void Shader::setInt(const char* name, int value)
    { 
        if (is_init) {
            glUniform1i(glGetUniformLocation(id, name), value); 
        } 
    } 

    void Shader::setFloat(const char* name , float value) {
        if (is_init) {
            glUniform1f(glGetUniformLocation(id, name), value); 
        }
    }

    void Shader::use() {
        if (is_init) {
            glUseProgram(id);
        }
    }

    Shader::~Shader() {
        if (is_init) {
            glDeleteProgram(id);
        }
    }
}