#include "Gui.hpp"

unsigned char Gui::Bmp::Read(unsigned char read_mode, std::string path, unsigned int x_start, unsigned int y_start){
    unsigned char opStatus = 1;

    switch(read_mode){
        case Gui::Bmp::MONOCHROME:
            opStatus = GUI_ReadBmp(path.c_str(), x_start, y_start);
            break;

        case Gui::Bmp::GRAY_4:
            opStatus = GUI_ReadBmp_4Gray(path.c_str(), x_start, y_start);
            break;

        case Gui::Bmp::GRAY_16:
            opStatus = GUI_ReadBmp_16Gray(path.c_str(), x_start, y_start);
            break;
            
        default:
            break;
    }

    return opStatus;
}