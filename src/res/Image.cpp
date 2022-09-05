#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "res/Filesystem.hpp"
#include "res/Image.hpp"

namespace arcana {
    static Filesystem fsys; // Internal filesystem
    Image::Image() {
        data = nullptr;
    }

    Image::Image(const char* path) {
        load(path);
    }

    Image::Image(unsigned char* data, size_t size) {
        load(data, size);
    }

    Image::~Image() {
        if (data)
            stbi_image_free(data);
    }

    void Image::load(const char* path) {
        size_t fsize;
        unsigned char* data = fsys.loadFileData(path, fsize);
        load(data, fsize);
    }

    void Image::load(unsigned char* data, size_t size) {
        stbi_set_flip_vertically_on_load(1);
        this->data = stbi_load_from_memory(data, size, &width, &height, &colorChannels, 0);
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