#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "res/Image.hpp"

namespace arcana {
    // IMAGE IMPL.
    Image::Image() {
        data = nullptr;
    }

    Image::Image(const char* path) {
        load(path);
    }

    Image::~Image() {
        if (data)
            stbi_image_free(data);
    }

    void Image::load(const char* path) {
        stbi_set_flip_vertically_on_load(1);
        data =  stbi_load(path, &width, &height, &colorChannels, STBI_rgb_alpha); 
    }
}