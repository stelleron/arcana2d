#define STBTT_STATIC
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h" 

#include "utils/Vector.hpp"
#include "res/Image.hpp"
#include "res/Font.hpp"
#include "res/Filesystem.hpp"
#include "utils/Logger.hpp"

#define START_CHAR 32
#define END_CHAR 126
#define NUM_CHARS END_CHAR - START_CHAR + 1

namespace arcana {
    struct GlyphData {
        int charValue;
        int xOffset;
        int yOffset;
        int advance;
        Image image;
    };

    Font::Font() {
        fontRecs = nullptr;
    }

    Font::Font(const char* path, int fontsize) {
        load(path, fontsize);
    }

    Font::Font(unsigned char* data, size_t size, int fontsize) {
        load(data, size, fontsize);
    }

    Font::~Font() {
        if (fontRecs)
            delete[] fontRecs;
    }

    void Font::load(const char* path, int fontsize) {
        size_t fsize;
        // Load file

        // Load file data
        unsigned char* data = filesystem::loadFileData(path, fsize);
        std::string extension = filesystem::getFileExtension(path);
        if (extension == "otf" || extension == "ttf")
            load(data, fsize, fontsize);
        else 
            LOG("Font: Font type not supported!");
        delete[] data;
    }

    void Font::load(unsigned char* data, size_t size, int fontsize) {
        Image fontAtlas;
        this->fontSize = fontsize;
        int xCharDim = 0, yCharDim = 0, xOffset = 0, yOffset = 0;

        // Load the font
        stbtt_fontinfo ftData = {0};
        if (!stbtt_InitFont(&ftData, data, 0)) {
            LOG("Font: Could not process the font data!");
            return;
        }

        // Now create the font atlas
        // First fetch font data
        float scale = stbtt_ScaleForPixelHeight(&ftData, 48 * 2);
        int ascent, descent;
        stbtt_GetFontVMetrics(&ftData, &ascent, &descent, 0);
        int baseline = (int)(ascent * scale);

        // Now get data for each character
        for (int i = START_CHAR; i < END_CHAR; i++) {
            int advance, leftSideBearing;
            stbtt_GetCodepointHMetrics(&ftData, i, &advance, &leftSideBearing);
            fontAtlas.width += advance * scale;
        }


        // Convert GRAYSCALE to GRAY_ALPHA
        unsigned char *dataGrayAlpha = new unsigned char[fontAtlas.width * fontAtlas.height * 2]; 

        for (int i = 0, k = 0; i < fontAtlas.width*fontAtlas.height; i++, k += 2)
        {
            dataGrayAlpha[k] = 255;
            dataGrayAlpha[k + 1] = fontAtlas.data[i];
        }

        delete[] fontAtlas.data;
        fontAtlas.data = dataGrayAlpha;
        fontAtlas.format = GRAY_ALPHA;

        // And finally convert it to a texture
        fontTex.load(fontAtlas);
    }
}