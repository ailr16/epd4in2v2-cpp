#ifndef GUI_HPP
#define GUI_HPP

#include <string>

extern "C"{
    #include "GUI_BMPfile.h"
    #include "GUI_Paint.h"
}

namespace Gui {
    class Screen {
        private:
        PAINT screenHandler;

        public:
        Screen(){}
        friend class Bmp;
        void newImage(UBYTE *image, UWORD width, UWORD height, UWORD rotate, UWORD color);
        void setScale(UBYTE scale);
        void clear(UWORD color);
        void clearWindow(UWORD x_start, UWORD y_start, UWORD x_end, UWORD y_end, UWORD color);
        void drawString(UWORD x_start, UWORD y_start, const char * pString, sFONT* font, UWORD color_foreground, UWORD color_background);

    };

    class Bmp {
        public:
        enum ReadMode : unsigned char {
            MONOCHROME,
            GRAY_4,
            GRAY_16 
        };

        Bmp(){}
        unsigned char read(Screen &targetScreen, unsigned char read_mode, std::string path, unsigned int x_start, unsigned int y_start);
    };
}

#endif