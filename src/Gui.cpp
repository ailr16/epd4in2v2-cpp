#include "Gui.hpp"

namespace Gui{
    Picture::~Picture(){
        free(this->image);
    }

    void Picture::newImage(uint16_t width, uint16_t height, uint16_t rotate, uint16_t color){
        uint16_t image_size = (width / 8U) * height;

        this->image = (uint8_t*)malloc(image_size);
        if(this->image == NULL) {
            return;
        }

        Paint_NewImage(&this->screenHandler, this->image, width, height, rotate, color);
    }

    uint8_t* Picture::getImage(void){
        return this->image;
    }

    void Picture::setRotate(uint16_t rotate){
        Paint_SetRotate(&this->screenHandler, rotate);
    }

    void Picture::setMirroring(uint8_t mirror){
        Paint_SetMirroring(&this->screenHandler, mirror);
    }

    void Picture::setPixel(uint16_t x_position, uint16_t y_position, uint16_t color){
        Paint_SetPixel(&this->screenHandler, x_position, y_position, color);
    }

    void Picture::setScale(uint8_t scale){
        if(scale == 2 || scale == 4){
            Paint_SetScale(&this->screenHandler, scale);
        }
    }

    void Picture::clear(uint16_t color){
        Paint_Clear(&this->screenHandler, color);
    }

    void Picture::clearWindow(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color){
        Paint_ClearWindows(&this->screenHandler,
                           x_start, y_start,
                           x_end, y_end,
                           color
                           );
    }

    void Picture::drawDot(uint16_t x_position, uint16_t y_position, uint16_t color, uint8_t dot_size, uint8_t dot_style){
        Paint_DrawPoint(&this->screenHandler,
                        x_position, y_position,
                        color,
                        static_cast<DOT_PIXEL>(dot_size),
                        static_cast<DOT_STYLE>(dot_style)
                        );
    }

    void Picture::drawLine(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color, uint8_t dot_size, uint8_t line_style){
        Paint_DrawLine(&this->screenHandler,
                        x_start, y_start,
                        x_end, y_end,
                        color,
                        static_cast<DOT_PIXEL>(dot_size),
                        static_cast<LINE_STYLE>(line_style)
                        );
    }

    void Picture::drawRectangle(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color, uint8_t dot_size, uint8_t geometry_fill){
        Paint_DrawRectangle(&this->screenHandler,
                            x_start, y_start,
                            x_end, y_end,
                            color,
                            static_cast<DOT_PIXEL>(dot_size),
                            static_cast<DRAW_FILL>(geometry_fill)
                            );
    }

    void Picture::drawCircle(uint16_t x_center, uint16_t y_center, uint16_t radius, uint16_t color, uint8_t dot_size, uint8_t geometry_fill){
        Paint_DrawCircle(&this->screenHandler,
                         x_center, y_center,
                         radius, color,
                         static_cast<DOT_PIXEL>(dot_size),
                         static_cast<DRAW_FILL>(geometry_fill)
                        );
    }

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

    unsigned char Picture::readBmp(unsigned char read_mode, std::string path, unsigned int x_start, unsigned int y_start){
        unsigned char opStatus = 1;

        switch(read_mode){
            case Gui::BmpReadMode::MONOCHROME:
                opStatus = GUI_ReadBmp(&this->screenHandler, path.c_str(), x_start, y_start);
                break;

            case Gui::BmpReadMode::GRAY_4:
                opStatus = GUI_ReadBmp_4Gray(&this->screenHandler, path.c_str(), x_start, y_start);
                break;

            case Gui::BmpReadMode::GRAY_16:
                opStatus = GUI_ReadBmp_16Gray(&this->screenHandler, path.c_str(), x_start, y_start);
                break;
                
            default:
                break;
        }

        return opStatus;
    }
}


