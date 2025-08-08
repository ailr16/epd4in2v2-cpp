#include "Gui.hpp"

namespace Gui{
    void Screen::newImage(uint8_t *image, uint16_t width, uint16_t height, uint16_t rotate, uint16_t color){
        Paint_NewImage(&this->screenHandler, image, width, height, rotate, color);
    }

    void Screen::selectImage(uint8_t *image){
        Paint_SelectImage(&this->screenHandler, image);
    }

    void Screen::setRotate(uint16_t rotate){
        Paint_SetRotate(&this->screenHandler, rotate);
    }

    void Screen::setMirroring(uint8_t mirror){
        Paint_SetMirroring(&this->screenHandler, mirror);
    }

    void Screen::setPixel(uint16_t x_position, uint16_t y_position, uint16_t color){
        Paint_SetPixel(&this->screenHandler, x_position, y_position, color);
    }

    void Screen::setScale(uint8_t scale){
        if(scale == 2 || scale == 4){
            Paint_SetScale(&this->screenHandler, scale);
        }
    }

    void Screen::clear(uint16_t color){
        Paint_Clear(&this->screenHandler, color);
    }

    void Screen::clearWindow(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color){
        Paint_ClearWindows(&this->screenHandler, x_start, y_start, x_end, y_end, color);
    }

    void Screen::drawDot(uint16_t x_position, uint16_t y_position, uint16_t color, uint8_t dot_size, uint8_t dot_style){
        Paint_DrawPoint(&this->screenHandler, x_position, y_position, color, static_cast<DOT_PIXEL>(dot_size), static_cast<DOT_STYLE>(dot_style));
    }

    void Screen::drawString(uint16_t x_start, uint16_t y_start, const char * pString, sFONT* font, uint16_t color_foreground, uint16_t color_background){
        Paint_DrawString_EN(&this->screenHandler, x_start, y_start, pString, font, color_foreground, color_background);
    }

    unsigned char Bmp::read(Screen &targetScreen, unsigned char read_mode, std::string path, unsigned int x_start, unsigned int y_start){
        unsigned char opStatus = 1;

        switch(read_mode){
            case Gui::BmpReadMode::MONOCHROME:
                opStatus = GUI_ReadBmp(&targetScreen.screenHandler, path.c_str(), x_start, y_start);
                break;

            case Gui::BmpReadMode::GRAY_4:
                opStatus = GUI_ReadBmp_4Gray(&targetScreen.screenHandler, path.c_str(), x_start, y_start);
                break;

            case Gui::BmpReadMode::GRAY_16:
                opStatus = GUI_ReadBmp_16Gray(&targetScreen.screenHandler, path.c_str(), x_start, y_start);
                break;
                
            default:
                break;
        }

        return opStatus;
    }
}


