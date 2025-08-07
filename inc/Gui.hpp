#ifndef GUI_HPP
#define GUI_HPP

#include <string>

extern "C"{
    #include "GUI_BMPfile.h"
    #include "GUI_Paint.h"
}

namespace Gui {
    class Bmp {
        public:
            enum ReadMode : unsigned char {
                MONOCHROME,
                GRAY_4,
                GRAY_16 
            };

            Bmp();
            unsigned char Read(unsigned char read_mode, std::string path, unsigned int x_start, unsigned int y_start);
    };

    class Paint {

    };
}

#endif