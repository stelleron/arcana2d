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
        unsigned char* data = filesystem::loadFileData(path, fsize);
        std::string extension = filesystem::getFileExtension(path);
        if (extension == "otf" || extension == "ttf")
            load(data, fsize, fontsize);
        else 
            LOG("Font: Font type not supported!");
        delete[] data;
    }

    void Font::load(unsigned char* data, size_t size, int fontsize) {
        this->fontSize = fontsize;
        // First load the font
        stbtt_fontinfo ftData = {0};
        if (!stbtt_InitFont(&ftData, data, 0)) {
            LOG("Font: Could not process the font data!");
            return;
        }

        // Then get font data
        float scaleFactor = stbtt_ScaleForPixelHeight(&ftData, fontSize);
        int ascent, descent, lineGap;
        stbtt_GetFontVMetrics(&ftData, &ascent, &descent, &lineGap);
        GlyphData* glyphs = new GlyphData[NUM_CHARS];

        // Now load the data for each character to be put into a bitmap
        fontRecs = new Rectangle[NUM_CHARS];
        float imgArea = 0;

        for (int i = START_CHAR; i < END_CHAR; i++) {
            int xCharDim, yCharDim;
            int index = i - START_CHAR;
            glyphs[index].charValue = i;

            if (i != 32) {
                glyphs[index].image.data = stbtt_GetCodepointBitmap(&ftData, scaleFactor, scaleFactor, i, &xCharDim, &yCharDim, 
                                                                    &glyphs[index].xOffset, &glyphs[index].yOffset);
                stbtt_GetCodepointHMetrics(&ftData, i, &glyphs[index].advance, NULL);

                glyphs[index].advance = (int)( (float)glyphs[index].advance * scaleFactor);
                // Set image data
                glyphs[index].image.width = xCharDim;
                glyphs[index].image.height = yCharDim;
                glyphs[index].image.format = GRAYSCALE;
                glyphs[index].yOffset += (int)((float)ascent*scaleFactor);
            }
            else {
                stbtt_GetCodepointHMetrics(&ftData, i, &glyphs[index].advance, NULL);
                glyphs[index].advance = (int)( (float)glyphs[index].advance * scaleFactor);
                glyphs[index].xOffset = 0;
                glyphs[index].yOffset = 0;
                glyphs[index].image.data = new unsigned char[glyphs[index].advance * fontSize];
                glyphs[index].image.width = glyphs[index].advance;
                glyphs[index].image.height = fontSize;
                glyphs[index].image.format = GRAYSCALE;
            }

            imgArea += glyphs[index].image.height * glyphs[index].image.width;
        }

        // Now generate the bitmap
        float guessSize = sqrtf(imgArea) * 1.4f;
        int imageSize = (int)powf(2, ceilf(logf((float)guessSize)/logf(2))); 
        Image fontAtlas;
        fontAtlas.width = imageSize;
        fontAtlas.height = imageSize;
        fontAtlas.data = new unsigned char[imageSize * imageSize];
        fontAtlas.format = GRAYSCALE;

        // And store each glyph in the font atlas
        Vector2 atlasOffset = {0, 0};
        for (int i = 0; i < NUM_CHARS; i++) {
            for (int y = 0; y < glyphs[i].image.height; y++)
            {
                for (int x = 0; x < glyphs[i].image.width; x++)
                {
                    fontAtlas.data[((int)atlasOffset.y + y) * fontAtlas.width + ((int)atlasOffset.y + x)] = glyphs[i].image.data[y * glyphs[i].image.width + x];
                }
            }
            fontRecs[i].point = atlasOffset;
            fontRecs[i].width = glyphs[i].image.width;
            fontRecs[i].height = glyphs[i].image.height;

            atlasOffset.x += glyphs[i].image.width;
            

            if (atlasOffset.x >= fontAtlas.width - glyphs[i].image.width) {
                atlasOffset.x = 0;
                atlasOffset.y += glyphs[i].image.height;
                if (atlasOffset.y > fontAtlas.height - glyphs[i].image.height) {
                    for (int j = i + 1; j < NUM_CHARS; j++) {
                        fontRecs[j].point = {0, 0};
                        fontRecs[j].width = 0;
                        fontRecs[j].height = 0;
                    }
                    ERROR("Font: Failed to package some characters!");
                    return;
                }
            }
        }
        
        // Convert from grayscale to gray alpha
        /* 
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
        */

       #define DEBUG_NUM 0

        unsigned char *dataGrayAlpha = new unsigned char[glyphs[DEBUG_NUM].image.width * glyphs[DEBUG_NUM].image.height * 2]; 

        for (int i = 0, k = 0; i < glyphs[DEBUG_NUM].image.width*glyphs[DEBUG_NUM].image.height; i++, k += 2)
        {
            dataGrayAlpha[k] = 255;
            dataGrayAlpha[k + 1] = glyphs[DEBUG_NUM].image.data[i];
        }

        delete[] glyphs[DEBUG_NUM].image.data;
        glyphs[DEBUG_NUM].image.data = dataGrayAlpha;
        glyphs[DEBUG_NUM].image.format = GRAY_ALPHA;
        
        // And finally convert it to a texture
        fontTex.load(glyphs[DEBUG_NUM].image);
        

        // Delete glyphs
        delete[] glyphs;
    }
}