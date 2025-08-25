/**
 * @file    Gui.cpp
 * @brief   Contains the Gui::Picture class definitions
 */

#include "Gui.hpp"

namespace Gui{
    
    ///@brief Free allocated memory
    Picture::~Picture(){
        free(this->image);
    }
    /// @brief Insantiate a Picture object 
    /// Allocates required memory and associates it with the low-level driver
    /// @param width 
    /// @param height 
    /// @param rotate 
    /// @param color 
    void Picture::newImage(uint16_t width, uint16_t height, uint16_t rotate, uint16_t color, uint8_t mode){
        uint16_t image_size = ((width / 8U) * (1 + mode))* height;

        this->image = (uint8_t*)malloc(image_size);
        if(this->image == NULL) {
            return;
        }

        Paint_NewImage(&this->screenHandler, this->image, width, height, rotate, color);
    }

    /// @brief Retrieves a pointer to the image data
    uint8_t* Picture::getImage(void){
        return this->image;
    }

    /// @brief Rotates the image
    /// @param rotate Degrees to rotate (90 degrees multiple)
    void Picture::setRotate(uint16_t rotate){
        Paint_SetRotate(&this->screenHandler, rotate);
    }

    /// @brief Mirrors the image
    /// @param mirror Type of mirroring
    void Picture::setMirroring(uint8_t mirror){
        Paint_SetMirroring(&this->screenHandler, mirror);
    }

    /// @brief Set the specified pixel to the specified color
    /// @param x_position X coordinate of point
    /// @param y_position Y coordinate of point
    /// @param color Color
    void Picture::setPixel(uint16_t x_position, uint16_t y_position, uint16_t color){
        Paint_SetPixel(&this->screenHandler, x_position, y_position, color);
    }

    /// @brief Set the color scale
    /// @param scale 2 or 4
    void Picture::setScale(uint8_t scale){
        if(scale == 2 || scale == 4){
            Paint_SetScale(&this->screenHandler, scale);
        }
    }

    /// @brief Clear all the picture
    /// @param color Black or White
    void Picture::clear(uint16_t color){
        Paint_Clear(&this->screenHandler, color);
    }


    /// @brief Fill the specified window with a color
    /// @param x_start Starting point x coordinate
    /// @param y_start Starting point y coordinate
    /// @param x_end Ending point x coordinate
    /// @param y_end Ending point y coordinate
    /// @param color Black or white
    void Picture::clearWindow(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color){
        Paint_ClearWindows(&this->screenHandler,
                           x_start, y_start,
                           x_end, y_end,
                           color
                           );
    }

    /// @brief Draw a dot in the image
    /// @param x_position X coordinate 
    /// @param y_position Y coordinate
    /// @param color Color
    /// @param dot_size Size of dot
    /// @param dot_style Style of dot
    void Picture::drawDot(uint16_t x_position, uint16_t y_position, uint16_t color, uint8_t dot_size, uint8_t dot_style){
        Paint_DrawPoint(&this->screenHandler,
                        x_position, y_position,
                        color,
                        static_cast<DOT_PIXEL>(dot_size),
                        static_cast<DOT_STYLE>(dot_style)
                        );
    }

    /// @brief Draw a line in the image
    /// @param x_position Start point X coordinate 
    /// @param y_position Start point Y coordinate
    /// @param x_end End point X coordinate 
    /// @param y_end End point Y coordinate 
    /// @param color Color
    /// @param dot_size Size of dot
    /// @param line_style Style of dot
    void Picture::drawLine(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color, uint8_t dot_size, uint8_t line_style){
        Paint_DrawLine(&this->screenHandler,
                        x_start, y_start,
                        x_end, y_end,
                        color,
                        static_cast<DOT_PIXEL>(dot_size),
                        static_cast<LINE_STYLE>(line_style)
                        );
    }

    /// @brief Draw a line in the image
    /// @param x_position Start point X coordinate 
    /// @param y_position Start point Y coordinate
    /// @param x_end End point X coordinate 
    /// @param y_end End point Y coordinate 
    /// @param color Color
    /// @param dot_size Size of dot
    /// @param geometry_fill Enable/disbale filling
    void Picture::drawRectangle(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color, uint8_t dot_size, uint8_t geometry_fill){
        Paint_DrawRectangle(&this->screenHandler,
                            x_start, y_start,
                            x_end, y_end,
                            color,
                            static_cast<DOT_PIXEL>(dot_size),
                            static_cast<DRAW_FILL>(geometry_fill)
                            );
    }

    /// @brief Draw a circle in the image
    /// @param x_center X corrdinate of center
    /// @param y_center Y corrdinate of center
    /// @param radius Radius
    /// @param color Color
    /// @param dot_size Size of dot
    /// @param geometry_fill Enable/disable filling
    void Picture::drawCircle(uint16_t x_center, uint16_t y_center, uint16_t radius, uint16_t color, uint8_t dot_size, uint8_t geometry_fill){
        Paint_DrawCircle(&this->screenHandler,
                         x_center, y_center,
                         radius, color,
                         static_cast<DOT_PIXEL>(dot_size),
                         static_cast<DRAW_FILL>(geometry_fill)
                        );
    }

    /// @brief Draw a character in the image
    ///
    /// Automatically detects if the font is monospaced or variable-width
    ///
    /// @param x_position X coordinate to start
    /// @param y_position Y coordinate to start
    /// @param ascii_char ASCII character to draw
    /// @param font Font
    /// @param color_foreground Color for foreground
    /// @param color_background Color for background
    /// @return Cursor with data from last character and start point of new character
    Cursor Picture::drawChar(uint16_t x_position, uint16_t y_position, const char ascii_char, sFONT* font, uint16_t color_foreground, uint16_t color_background){
        Cursor cursor = {0};

        if(font->lut == nullptr){
            /* Monospaced font */
            Paint_DrawChar(&this->screenHandler,
                           x_position, y_position,
                           ascii_char, font,
                           color_foreground,
                           color_background
                           );
        }
        else{
            cursor =  Paint_DrawChar_VariableWidth(&this->screenHandler,
                                         x_position, y_position,
                                         ascii_char,
                                         font,
                                         color_foreground,
                                         color_background
                                        );
        }

        return cursor;
    }

    /// @brief Draw a string in the image
    ///
    /// Automatically detects if the font is monospaced or variable-width
    ///
    /// @param x_position X coordinate to start
    /// @param y_position Y coordinate to start
    /// @param pString String to draw
    /// @param font Font
    /// @param color_foreground Color for foreground
    /// @param color_background Color for background
    /// @return Cursor with data from last character and start point of new character
    Cursor Picture::drawString(uint16_t x_position, uint16_t y_position, std::string_view pString, sFONT* font, uint16_t color_foreground, uint16_t color_background){
        Cursor cursor = {0};
        
        if(font->lut == nullptr){
            /* Monospaced font */
            Paint_DrawString_EN(&this->screenHandler,
                                x_position, y_position,
                                pString.data(),
                                font,
                                color_background,
                                color_foreground
                                );
        }
        else{
            cursor = Paint_DrawString_VariableWidth(&this->screenHandler,
                                                    x_position, y_position,
                                                    pString.data(),
                                                    font,
                                                    color_foreground,
                                                    color_background
            );
        }

        return cursor;
    }

    /// @brief Draw a number with floating point
    ///
    /// NOT FULLY SUPOPRTED RIGHT NOW
    ///
    /// @param x_position X coordinate to start
    /// @param y_position Y coordinate to start
    /// @param number Number to draw
    /// @param font Font
    /// @param digit Digits after point
    /// @param color_foreground Color for foreground
    /// @param color_background Color for background
    void Picture::drawFloatNum(uint16_t x_position, uint16_t y_position, double number, sFONT* font, uint16_t digit, uint16_t color_foreground, uint16_t color_background){
        // Variable-width fonts not supported yet!
        if(font->lut != nullptr){
            return;
        }

        Paint_DrawNumDecimals(&this->screenHandler,
                              x_position, y_position,
                              number,
                              font,
                              digit,
                              color_foreground,
                              color_background
                            );
    }

    /// @brief Read a BMP into the image
    /// @param read_mode Color scale
    /// @param path Path of the file
    /// @param x_position X coordinate to start
    /// @param y_position Y coordinate to start
    /// @return 
    unsigned char Picture::readBmp(unsigned char read_mode, std::string path, unsigned int x_start, unsigned int y_start){
        unsigned char opStatus = 1;

        switch(read_mode){
            case Gui::BmpReadMode::MONOCHROME:
                opStatus = GUI_ReadBmp(&this->screenHandler, path.c_str(), x_start, y_start);
                break;

            case Gui::BmpReadMode::GRAY_4:
                opStatus = GUI_ReadBmp_4Gray(&this->screenHandler, path.c_str(), x_start, y_start);
                break;
                
            default:
                break;
        }

        return opStatus;
    }
}


