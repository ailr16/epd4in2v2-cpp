#ifndef DISPLAY_API_HPP
#define DISPLAY_API_HPP

extern "C"{
    #include "EPD_4in2_V2.h"
}

namespace DisplayApi {
    enum InitMode : uint8_t {
        NORMAL,
        GRAY_4,
        FAST_1S,
        FAST_1_5S
    };

    class Display {
        private:
            uint8_t initMode;

        public:
            Display(){}

            uint8_t init(uint8_t mode);
            void clear(void);
            void print(uint8_t* frame);
            void partialPrint(uint8_t* frame, uint16_t x_position, uint16_t y_position, uint16_t width, uint16_t length);
            void sleep(void);
    };
}

#endif