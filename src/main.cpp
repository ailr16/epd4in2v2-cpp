#include <cstdlib>
#include <csignal>
#include <cstring>

#include "Gui.hpp"

extern "C"{
    #include "DEV_Config.h"
    #include "Debug.h"
    #include <stdlib.h> // malloc() free()
    #include "EPD_4in2_V2.h"
}

int main(void) {
    uint16_t image_size = (EPD_4IN2_V2_WIDTH / 8U) * EPD_4IN2_V2_HEIGHT;
    UBYTE *BlackImage = (UBYTE *)malloc(image_size);

    DEV_Module_Init();
    EPD_4IN2_V2_Init();  // 1-bit BW mode

    //PAINT testPaint;

    Gui::Picture testScreen;

    testScreen.newImage(BlackImage, EPD_4IN2_V2_WIDTH, EPD_4IN2_V2_HEIGHT, 0, WHITE);
    testScreen.setScale(2);
    testScreen.clear(WHITE);

    EPD_4IN2_V2_Display(BlackImage);  // Full clear once

    /*for (int i = 0; i < sizeof(lyrics)/sizeof(lyrics[0]); i+=2) {
        // Clear just the region
        Paint_ClearWindows(10, 120, 400, 192, WHITE);

        // Draw one line
        printf("%s\n", lyrics[i]);
        Paint_DrawString_EN(10, 130, lyrics[i], &Font24, WHITE, BLACK);
        Paint_DrawString_EN(10, 154, lyrics[i+1], &Font24, WHITE, BLACK);

        // Do partial refresh in that region
        EPD_4IN2_V2_Display(BlackImage);
        if(i == 0){
            scanf("%c", &dummy);
        }
        else if(i == 2){
            DEV_Delay_ms(1600);
        }
        else if(i == 4){
            DEV_Delay_ms(2800);
        }
        //EPD_4IN2_V2_PartialDisplay(BlackImage, 10, 120, 280, 50);
        
    }*/
    testScreen.clearWindow(10, 120, 400, 192, WHITE);
    //testScreen.drawString(10, 70, "Temperature is:", &Arial80, WHITE, BLACK);
    //testScreen.drawString(10, 150, "69", &Arial80, WHITE, BLACK);

    //testScreen.drawChar(20, 20, 's', &arial70, BLACK, WHITE);
    //testScreen.drawChar(20, 80, 's', &arial48, BLACK, WHITE);
    //testScreen.drawChar(100, 20, 's', &ComicSansMS69, BLACK, WHITE);
    //testScreen.drawChar(200, 46, 's', &Font24, BLACK, WHITE);

    //testScreen.drawString(20, 160, "abc", &Font24, WHITE, BLACK);
    testScreen.drawString(1, 1, "ABCDEFGHIJKLMNOPQRsTUVWXYZ0123456789!0123456789!()/&,;.-_%$#@*", &arial48, BLACK, WHITE);

    EPD_4IN2_V2_Display(BlackImage);
    EPD_4IN2_V2_Sleep();
    free(BlackImage);
    DEV_Module_Exit();


    return 0;
}
