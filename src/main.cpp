#include <csignal>
#include <cstring>

#include "Gui.hpp"
#include "DisplayApi.hpp"

int main(void) {
    DisplayApi::Display display;
    Gui::Picture picture;

    display.init(DisplayApi::InitMode::FAST_1_5S);

    picture.newImage(EPD_4IN2_V2_WIDTH, EPD_4IN2_V2_HEIGHT, 0, WHITE);

    picture.setScale(2);

    picture.clear(WHITE);

    display.print(picture.getImage());

    DisplayApi::delay_ms(3000);
    picture.drawString(0, 0, "Hello", &BebasNeue66, BLACK, WHITE);
    //display.print(picture.getImage());
    display.partialPrint(picture.getImage(), 0, 0, EPD_4IN2_V2_WIDTH, EPD_4IN2_V2_HEIGHT);
    picture.clearWindow(0, 0, 160, 62, WHITE);
    picture.drawString(0, 0, "ailr16", &BebasNeue66, BLACK, WHITE);
    DisplayApi::delay_ms(1000);
    display.partialPrint(picture.getImage(), 0, 0, EPD_4IN2_V2_WIDTH, EPD_4IN2_V2_HEIGHT);
    picture.clearWindow(0, 0, 160, 62, WHITE);
    picture.drawString(0, 0, "bye!", &BebasNeue66, BLACK, WHITE);
    DisplayApi::delay_ms(1000);
    display.partialPrint(picture.getImage(), 0, 0, EPD_4IN2_V2_WIDTH, EPD_4IN2_V2_HEIGHT);

    display.clear();
    display.sleep();

    return 0;
}
