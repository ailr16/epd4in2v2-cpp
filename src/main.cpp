#include <csignal>
#include <cstring>

#include "Gui.hpp"
#include "DisplayApi.hpp"


int main(void) {
    DisplayApi::Display display;
    Gui::Picture picture;
    Cursor cursor = {0};

    display.init(DisplayApi::InitMode::FAST_1_5S);

    picture.newImage(EPD_4IN2_V2_WIDTH, EPD_4IN2_V2_HEIGHT, 0, WHITE);

    picture.setScale(2);

    picture.clear(WHITE);

    display.print(picture.getImage());

    DisplayApi::delay_ms(3000);
    picture.drawChar(0, 0, 'a', &BebasNeue66, BLACK, WHITE);
    //display.print(picture.getImage());
    display.partialPrint(picture.getImage(), 0, 0, EPD_4IN2_V2_WIDTH, EPD_4IN2_V2_HEIGHT);
    picture.clearWindow(0, 0, 30, 62, WHITE);
    cursor = picture.drawString(0, 0, "bc", &BebasNeue66, BLACK, WHITE);
    DisplayApi::delay_ms(1000);

    display.partialPrint(picture.getImage(), 0, 0, EPD_4IN2_V2_WIDTH, EPD_4IN2_V2_HEIGHT);
    picture.clearWindow(cursor.x_point - cursor.last_width,
                        cursor.y_point,
                        cursor.x_point,
                        cursor.last_height,
                        WHITE
    );

    cursor = picture.drawString(cursor.x_point - cursor.last_width,
                                cursor.y_point,
                                "E",
                                &BebasNeue66,
                                BLACK,
                                WHITE
    );
                             
    DisplayApi::delay_ms(1000);

    display.partialPrint(picture.getImage(), 0, 0, EPD_4IN2_V2_WIDTH, EPD_4IN2_V2_HEIGHT);

    display.clear();
    display.sleep();

    return 0;
}
