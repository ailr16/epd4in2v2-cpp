extern "C"{
    #include <stdlib.h>     //exit()
    #include <signal.h>     //signal()
    #include <string.h>

    #include "DEV_Config.h"
    #include "GUI_Paint.h"
    #include "GUI_BMPfile.h"
    #include "Debug.h"
    #include <stdlib.h> // malloc() free()
    #include "EPD_4in2_V2.h"
}


int main(void) {
    DEV_Module_Init();
    EPD_4IN2_V2_Init();  // 1-bit BW mode

    UWORD Imagesize = (EPD_4IN2_V2_WIDTH / 8) * EPD_4IN2_V2_HEIGHT;
    UBYTE *BlackImage = (UBYTE *)malloc(Imagesize);

    Paint_NewImage(BlackImage, EPD_4IN2_V2_WIDTH, EPD_4IN2_V2_HEIGHT, 0, WHITE);
    Paint_SetScale(2); // Monochrome
    Paint_Clear(WHITE);
    EPD_4IN2_V2_Display(BlackImage);  // Full clear once

    const char* lyrics[] = {
        "now that you're mine",
        " ",
        "we'll find a way",
        "of chasing the sun",
        "let me be the one",
        "who shines with you",
        "in the morning",
        "we don't know what to do"
    };

    char dummy = ' ';

    for (int i = 0; i < sizeof(lyrics)/sizeof(lyrics[0]); i+=2) {
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
        
    }

    EPD_4IN2_V2_Sleep();
    free(BlackImage);
    DEV_Module_Exit();
    return 0;
}
