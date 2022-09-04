#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "res/Filesystem.hpp"
#include "res/Image.hpp"

namespace arcana {
    Image::Image() {
        data = nullptr;
    }

    Image::Image(const char* path) {
        load(path);
    }

    Image::Image(unsigned char* data) {
        load(data);
    }

    Image::~Image() {
        if (data)
            stbi_image_free(data);
    }

    void Image::load(const char* path) {
        Filesystem fsys;
        unsigned char* data = fsys.loadFileData(path);
        load(data);
    }

    void Image::load(unsigned char* data) {
        stbi_set_flip_vertically_on_load(1);
        std::string buf = (char*)data;
        this->data = stbi_load_from_memory(data, buf.size(), &width, &height, &colorChannels, 0);
    }

    bool Image::isLoaded() {
        if (data) {
            return true;
        }
        else {
            return false;
        }
    }
}