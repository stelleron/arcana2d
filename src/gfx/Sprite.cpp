#include <glad/glad.h>
#include "gfx/Sprite.hpp"
#include "res/Image.hpp"

namespace arcana {
    // SPRITE IMPL.
    Sprite::Sprite() {
        is_init = false;
    }

    Sprite::Sprite(const char* path) {
        load(path);
    }

    void Sprite::load(const char* path) {
        // Load image
        Image image(path);

        // Load texture
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);    
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        width = image.width;
        height = image.height;
        pos = Vector2(0.0, 0.0);
        is_init = true;
    }

    Sprite::~Sprite() {
        if (is_init)
            glDeleteTextures(1, &id);
    }
}