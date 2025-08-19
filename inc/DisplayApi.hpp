/**
 * @file    DisplayApi.hpp
 * @brief   Contains the DisplayApi namespace, bringing interfaces to control a Display
 *
 * Features:
 * - Init the display
 * - Clear the entire display
 * - Print an image
 * - Print an image in fast mode (partial print)
 * - Enable sleep mode
 * - Delay for nmilliseconds
 */

#ifndef DISPLAY_API_HPP
#define DISPLAY_API_HPP

extern "C"{
    #include "EPD_4in2_V2.h"
    #include "DEV_Config.h"
}

 /// @namespace DisplayApi
 /// @brief Groups the class Picture and related enums
namespace DisplayApi {
    /// @enum InitMode
    /// @brief Mode to initialize the display
    enum InitMode : uint8_t {
        NORMAL,
        GRAY_4,
        FAST_1S,
        FAST_1_5S
    };

    /// @class Display
    /// @brief Encapsulate Display operations and add a logic layer to inteface with low-level
    class Display {
        private:
            uint8_t initMode;

        public:
            Display();
            ~Display();
            uint8_t init(uint8_t mode);
            void clear(void);
            void print(uint8_t* image);
            void partialPrint(uint8_t* image, uint16_t x_position, uint16_t y_position, uint16_t width, uint16_t length);
            void sleep(void);
    };

    void delay_ms(uint32_t ms);
}

#endif