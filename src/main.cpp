#include <csignal>
#include <cstring>

#include "Gui.hpp"
#include "DisplayApi.hpp"


int main(void) {
    DisplayApi::Display display;
    Gui::Picture picture;
    Cursor cursor = {0};

    display.init(DisplayApi::InitMode::GRAY_4);

    picture.newImage(EPD_4IN2_V2_WIDTH, EPD_4IN2_V2_HEIGHT, 0, WHITE, Gui::BmpReadMode::GRAY_4);

    picture.setScale(4);

    picture.clear(WHITE);
    display.print(picture.getImage());

    picture.readBmp(Gui::BmpReadMode::GRAY_4,
                    "/home/rpi/git/epd4in2v2-cpp/scripts/fonts/4in2_Scale.bmp",
                    //"/home/rpi/git/epd4in2v2-cpp/scripts/fonts/conv.bmp",
                    //"/home/rpi/git/epd4in2v2-cpp/scripts/fonts/output.bmp",
                    0,
                    0
    );

    picture.drawChar(0, 0, 'a', &Font24, BLACK, WHITE);
    picture.drawChar(366, 0, 'a', &arial48, BLACK, WHITE);
    display.print(picture.getImage());

    #if 0
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
    #endif

    DisplayApi::delay_ms(1000);
    display.clear();
    DisplayApi::delay_ms(100);
    display.sleep();

    return 0;
}
