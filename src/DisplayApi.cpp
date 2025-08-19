/**
 * @file    DisplayApi.cpp
 * @brief   Contains the DisplayApi definitions
 */

#include "DisplayApi.hpp"

/// @brief Instantiate the object and init SPI comms
DisplayApi::Display::Display(){
    DEV_Module_Init();
}

/// @brief Initialize the display in the specified mode
/// @param mode 
/// @return Operation status
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

/// @brief Cler the display
void DisplayApi::Display::clear(void) {
    EPD_4IN2_V2_Clear();
}

/// @brief Print an image (from Gui namespace)
///
/// Calls the appropiate driver function
///
/// @param image 
void DisplayApi::Display::print(uint8_t* image) {
    switch(this->initMode){
        case DisplayApi::InitMode::NORMAL:
            EPD_4IN2_V2_Display(image);
        break;

        case DisplayApi::InitMode::GRAY_4:
            EPD_4IN2_V2_Display_4Gray(image);
        break;

        case DisplayApi::InitMode::FAST_1S:
            EPD_4IN2_V2_Display_Fast(image);
        break;

        case DisplayApi::InitMode::FAST_1_5S:
            EPD_4IN2_V2_Display_Fast(image);
        break;
    }
}

/// @brief Use partial print for faster displaying
/// @param image 
/// @param x_position Starting point x coordinate
/// @param y_position Starting point y coordinate
/// @param width 
/// @param length 
void DisplayApi::Display::partialPrint(uint8_t* image, uint16_t x_position, uint16_t y_position, uint16_t width, uint16_t length){
    EPD_4IN2_V2_PartialDisplay(image, x_position, y_position, width, length);
}

/// @brief Set display to sleep mode
void DisplayApi::Display::sleep(void){
    EPD_4IN2_V2_Sleep();
}

/// @brief Set display to sleep and stop SPI
DisplayApi::Display::~Display(){
    this->sleep();
    DEV_Module_Exit();
}

/// @brief Add a delay in miliiseconds
void DisplayApi::delay_ms(uint32_t ms){
    DEV_Delay_ms(ms);
}