#include "DisplayApi.hpp"

DisplayApi::Display::Display(){
    DEV_Module_Init();
}

uint8_t DisplayApi::Display::init(uint8_t mode) {
    uint8_t opStatus = 0;
    this->initMode = mode;

    switch(mode){
        case DisplayApi::InitMode::NORMAL:
            EPD_4IN2_V2_Init();
        break;
        
        case DisplayApi::InitMode::GRAY_4:
            EPD_4IN2_V2_Init_4Gray();
        break;

        case DisplayApi::InitMode::FAST_1S:
            EPD_4IN2_V2_Init_Fast(Seconds_1S);
        break;

        case DisplayApi::InitMode::FAST_1_5S:
            EPD_4IN2_V2_Init_Fast(Seconds_1_5S);
        break;

        default:
            opStatus = 1;
        break;
    }

    return opStatus;
}

void DisplayApi::Display::clear(void) {
    EPD_4IN2_V2_Clear();
}

void DisplayApi::Display::print(uint8_t* frame) {
    switch(this->initMode){
        case DisplayApi::InitMode::NORMAL:
            EPD_4IN2_V2_Display(frame);
        break;

        case DisplayApi::InitMode::GRAY_4:
            EPD_4IN2_V2_Display_4Gray(frame);
        break;

        case DisplayApi::InitMode::FAST_1S:
            EPD_4IN2_V2_Display_Fast(frame);
        break;

        case DisplayApi::InitMode::FAST_1_5S:
            EPD_4IN2_V2_Display_Fast(frame);
        break;
    }
}

void DisplayApi::Display::partialPrint(uint8_t* frame, uint16_t x_position, uint16_t y_position, uint16_t width, uint16_t length){
    EPD_4IN2_V2_PartialDisplay(frame, x_position, y_position, width, length);
}

void DisplayApi::Display::sleep(void){
    EPD_4IN2_V2_Sleep();
}

DisplayApi::Display::~Display(){
    this->sleep();
    DEV_Module_Exit();
}

void DisplayApi::delay_ms(uint32_t ms){
    DEV_Delay_ms(ms);
}