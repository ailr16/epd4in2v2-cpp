#include "Gui.hpp"

namespace Gui{
    void Screen::newImage(UBYTE *image, UWORD width, UWORD height, UWORD rotate, UWORD color){
        Paint_NewImage(&this->screenHandler, image, width, height, rotate, color);
    }

    void Screen::setScale(UBYTE scale){
        Paint_SetScale(&this->screenHandler, scale);
    }

    void Screen::clear(UWORD color){
        Paint_Clear(&this->screenHandler, color);
    }

    void Screen::clearWindow(UWORD x_start, UWORD y_start, UWORD x_end, UWORD y_end, UWORD color){
        Paint_ClearWindows(&this->screenHandler, x_start, y_start, x_end, y_end, color);
    }

    void Screen::drawString(UWORD x_start, UWORD y_start, const char * pString, sFONT* font, UWORD color_foreground, UWORD color_background){
        Paint_DrawString_EN(&this->screenHandler, x_start, y_start, pString, font, color_foreground, color_background);
    }

    unsigned char Bmp::read(Screen &targetScreen, unsigned char read_mode, std::string path, unsigned int x_start, unsigned int y_start){
        unsigned char opStatus = 1;

        switch(read_mode){
            case Gui::Bmp::MONOCHROME:
                opStatus = GUI_ReadBmp(&targetScreen.screenHandler, path.c_str(), x_start, y_start);
                break;

            case Gui::Bmp::GRAY_4:
                opStatus = GUI_ReadBmp_4Gray(&targetScreen.screenHandler, path.c_str(), x_start, y_start);
                break;

            case Gui::Bmp::GRAY_16:
                opStatus = GUI_ReadBmp_16Gray(&targetScreen.screenHandler, path.c_str(), x_start, y_start);
                break;
                
            default:
                break;
        }

        return opStatus;
    }
}


