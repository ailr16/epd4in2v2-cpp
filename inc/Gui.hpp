#ifndef GUI_HPP
#define GUI_HPP

#include <string>
#include <cstdlib>

extern "C"{
    #include "GUI_BMPfile.h"
    #include "GUI_Paint.h"
}

namespace Gui {
    enum DotSize : uint8_t {
        DOT_1 = 1,
        DOT_2,
        DOT_3,
        DOT_4,
        DOT_5,
        DOT_6,
        DOT_7,
        DOT_8
    };

    enum DotStyle : uint8_t {
        FILL_AROUND = 1,
        FILL_RIGHTUP 
    };

    enum LineStyle : uint8_t {
        SOLID = 1,
        DOTTED
    };

    enum GeometryFill : uint8_t {
        VOID,
        FULL
    };

    enum BmpReadMode : unsigned char {
        MONOCHROME,
        GRAY_4,
        GRAY_16 
    };

    class Picture {
        private:
        PAINT screenHandler;
        uint8_t *image;

        public:
        Picture(){}
        ~Picture();

        void newImage(uint16_t width, uint16_t height, uint16_t rotate, uint16_t color);
        uint8_t* getImage(void);

        void setRotate(uint16_t rotate);
        void setMirroring(uint8_t mirror);
        void setPixel(uint16_t x_position, uint16_t y_position, uint16_t color);
        void setScale(uint8_t scale);

        void clear(uint16_t color);
        void clearWindow(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color);

        void drawDot(uint16_t x_position, uint16_t y_position, uint16_t color, uint8_t dot_size, uint8_t dot_style);
        void drawLine(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color, uint8_t dot_size, uint8_t line_style);
        void drawRectangle(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color, uint8_t dot_size, uint8_t geometry_fill);
        void drawCircle(uint16_t x_center, uint16_t y_center, uint16_t radius, uint16_t color, uint8_t dot_size, uint8_t geometry_fill);

        void drawChar(uint16_t x_position, uint16_t y_position, const char ascii_char, sFONT* Font, uint16_t color_foreground, uint16_t color_background);
        void drawString(uint16_t x_position, uint16_t y_position, const char * pString, sFONT* font, uint16_t color_foreground, uint16_t color_background);
        void drawFloatNum(uint16_t x_position, uint16_t y_position, double number, sFONT* font, uint16_t digit, uint16_t color_foreground, uint16_t color_background);

        unsigned char readBmp(unsigned char read_mode, std::string path, unsigned int x_start, unsigned int y_start);
    };
}

#endif