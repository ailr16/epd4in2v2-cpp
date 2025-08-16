#include <csignal>
#include <cstring>

#include "Gui.hpp"
#include "DisplayApi.hpp"

int main(void) {
    DisplayApi::Display display;
    Gui::Picture picture;
    Gui::Picture picture2;

    display.init(DisplayApi::InitMode::NORMAL);

    picture.newImage(EPD_4IN2_V2_WIDTH, EPD_4IN2_V2_HEIGHT, 0, WHITE);
    picture2.newImage(EPD_4IN2_V2_WIDTH, EPD_4IN2_V2_HEIGHT, 0, WHITE);

    picture.setScale(2);
    picture2.setScale(2);

    picture.clear(WHITE);
    picture2.clear(WHITE);

    display.print(picture.getImage());

    //picture.drawString(20, 160, "abc", &Font24, BLACK, WHITE);
    picture.drawString(10, 48, "This is", &arial48, BLACK, WHITE);
    picture.drawString(10, 100, "a test!", &arial48, BLACK, WHITE);
    

    display.print(picture.getImage());
    DisplayApi::delay_ms(3000);
    display.print(picture2.getImage());
    picture2.drawString(120, 120, "ailr16", &BebasNeue66, BLACK, WHITE);
    display.print(picture2.getImage());

    display.sleep();

    return 0;
}
