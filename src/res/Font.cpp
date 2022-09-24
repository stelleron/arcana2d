#define STB_RECT_PACK_IMPLEMENTATION
#include "stb_rect_pack.h"
#define STBTT_STATIC
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h" 
#include "res/Font.hpp"
#include "res/Filesystem.hpp"
#include "utils/Logger.hpp"

namespace arcana {
    Font::Font() {

    }

    Font::Font(const char* path, int fontsize) {
        load(path, fontsize);
    }

    Font::Font(unsigned char* data, size_t size, int fontsize) {
        load(data, size, fontsize);
    }

    Font::~Font() {

    }

    void Font::load(const char* path, int fontsize) {
        size_t fsize;
        unsigned char* data = filesystem::loadFileData(path, fsize);
        std::string extension = filesystem::getFileExtension(path);
        if (extension == "otf" && extension == "ttf")
            load(data, fsize, fontsize);
        else 
            LOG("Font: Font type not supported!");
    }

    void Font::load(unsigned char* data, size_t size, int fontsize) {
        fontSize = fontsize;
    }
}