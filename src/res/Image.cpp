#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "res/Image.hpp"
#include "utils/DebugOnly.hpp"

namespace arcana {
    // IMAGE IMPL.
    Image::Image(const char* path) {
        stbi_set_flip_vertically_on_load(1);
        data =  stbi_load(path, &width, &height, &colorChannels, STBI_rgb_alpha); 
    }

    Image::~Image() {
        stbi_image_free(data);
    }

}