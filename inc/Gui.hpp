/**
 * @file    Gui.hpp
 * @brief   Contains the Gui namespace, bringing interfaces to draw on a picture
 *
 * Features:
 * - Allocate memory for handling the image specifying width and height
 * - Retrieve the array with the image and draw in display using the Api
 * - Rotate and mirror the image
 * - Set the size of points and image color scale (B/W or 4-gray)
 * - Clear the entire image or just a window
 * - Draw primitives (dot, line, rectangle, circle)
 * - Draw characters and strings with a specific font (monospaced and variable-width)
 * - Read BMPs
 * - Handling cursor with last-character drew data and start point for new drawings (ONLY FOR 
 *   VARIABLE-WIDTH fonts)
 * 
 * To Do:
 * - Add character handling for monospaced fonts
 * - Add a method to draw non-ASCII characters
 * - Add support for allocating memory for 4-gray scale image
 */

#ifndef GUI_HPP
#define GUI_HPP

#include <string>
#include <cstdlib>
#include <string_view>

extern "C"{
    #include "GUI_BMPfile.h"
    #include "GUI_Paint.h"
}

/**
 * @namespace Gui
 * @brief Groups enumerations and the class Picture
 */
namespace Gui {
    /**
     * @enum DotSize
     * @brief Size of drawing point
     *
     * Consider that the point is a nxn square. Example, DOT6 = 6x6 pixel square
     */
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

    /**
     * @enum DotStyle
     * @brief  Style of drawing point
     */
    enum DotStyle : uint8_t {
        FILL_AROUND = 1,
        FILL_RIGHTUP 
    };

    /**
     * @enum LineStyle
     * @brief Style of drawing line
     */
    enum LineStyle : uint8_t {
        SOLID = 1,
        DOTTED
    };

    /**
     * @enum GeometryFill
     * @brief Enable/disable filling for drew figures
     */
    enum GeometryFill : uint8_t {
        VOID,
        FULL
    };

    /**
     * @enum BmpReadMode
     * @brief Color scale for reading BMPs
     */
    enum BmpReadMode : unsigned char {
        MONOCHROME = 0,
        GRAY_4 = 1
    };

    /**
     * @class Picture
     * @brief Handles drawing in a picture and retrieving data from it
     */
    class Picture {
        private:
        PAINT screenHandler;
        uint8_t *image;

        public:
        Picture(){}
        ~Picture();

        void newImage(uint16_t width, uint16_t height, uint16_t rotate, uint16_t color, uint8_t mode);
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

        Cursor drawChar(uint16_t x_position, uint16_t y_position, const char ascii_char, sFONT* Font, uint16_t color_foreground, uint16_t color_background);
        Cursor drawString(uint16_t x_position, uint16_t y_position, std::string_view pString, sFONT* font, uint16_t color_foreground, uint16_t color_background);
        void drawFloatNum(uint16_t x_position, uint16_t y_position, double number, sFONT* font, uint16_t digit, uint16_t color_foreground, uint16_t color_background);

        unsigned char readBmp(unsigned char read_mode, std::string path, unsigned int x_start, unsigned int y_start);
    };
}

#endif