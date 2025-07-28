/*****************************************************************************
* | File      	:   EPD_4in2_V2_test.c
* | Author      :   Waveshare team
* | Function    :   4.2inch e-paper V2 test demo
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2023-09-11
* | Info        :
* -----------------------------------------------------------------------------
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "EPD_Test.h"
#include "EPD_4in2_V2.h"
#include <string.h>

#if 0
int EPD_4in2_V2_test(void)
{
    printf("EPD_4IN2_V2_test Demo\r\n");
    if(DEV_Module_Init()!=0){
        return -1;
    }

    printf("e-Paper Init and Clear...\r\n");
    EPD_4IN2_V2_Init();
    EPD_4IN2_V2_Clear();
    DEV_Delay_ms(500);

    //Create a new image cache
    UBYTE *BlackImage;
    /* you have to edit the startup_stm32fxxx.s file and set a big enough heap size */
    //UWORD Imagesize = ((EPD_4IN2_V2_WIDTH % 8 == 0)? (EPD_4IN2_V2_WIDTH / 8 ): (EPD_4IN2_V2_WIDTH / 8 + 1)) * EPD_4IN2_V2_HEIGHT;
    UWORD Imagesize = (EPD_4IN2_V2_WIDTH / 8 ) * EPD_4IN2_V2_HEIGHT;
    if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        return -1;
    }
    printf("Paint_NewImage\r\n");
    Paint_NewImage(BlackImage, EPD_4IN2_V2_WIDTH, EPD_4IN2_V2_HEIGHT, 0, WHITE);   


#if 0
	printf("Partial refresh\r\n");
    Paint_NewImage(BlackImage, 200, 50, 0, WHITE);
	PAINT_TIME sPaint_time;
    sPaint_time.Hour = 12;
    sPaint_time.Min = 34;
    sPaint_time.Sec = 56;
    UBYTE num = 10;
	for (;;) {
		sPaint_time.Sec = sPaint_time.Sec + 1;
		if (sPaint_time.Sec == 60) {
			sPaint_time.Min = sPaint_time.Min + 1;
			sPaint_time.Sec = 0;
			if (sPaint_time.Min == 60) {
				sPaint_time.Hour =  sPaint_time.Hour + 1;
				sPaint_time.Min = 0;
				if (sPaint_time.Hour == 24) {
					sPaint_time.Hour = 0;
					sPaint_time.Min = 0;
					sPaint_time.Sec = 0;
				}
			}
		}
		Paint_Clear(WHITE);
		Paint_DrawTime(20, 10, &sPaint_time, &Font20, WHITE, BLACK);
		EPD_4IN2_V2_PartialDisplay(BlackImage, 80, 200, 200, 50);
		DEV_Delay_ms(500);//Analog clock 1s
		num = num - 1;
		if(num == 0) {
			break;
		}
    }
#endif

#if 1
    EPD_4IN2_V2_Init();
	free(BlackImage);
	BlackImage = NULL;
	Imagesize = (EPD_4IN2_V2_WIDTH / 8 ) * EPD_4IN2_V2_HEIGHT;
    if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        return -1;
    }
	Paint_NewImage(BlackImage, EPD_4IN2_V2_WIDTH, EPD_4IN2_V2_HEIGHT, 0, WHITE);
	Paint_SetScale(2);

    char dummy = ' ';

    printf("PRINTING: we'll find a way\n");
    Paint_Clear(WHITE);
    Paint_DrawString_EN(10, 120, "we'll find a way", &Font24, WHITE, BLACK);
    //EPD_4IN2_V2_PartialDisplay(BlackImage, 10, 240, 390, 50);
    EPD_4IN2_V2_Display(BlackImage);
    scanf("%c", &dummy);

    Paint_Clear(WHITE);
    printf("PRINTING: of chasing the sun\n");
    Paint_DrawString_EN(10, 120, "of chasing the sun", &Font24, WHITE, BLACK);
    EPD_4IN2_V2_PartialDisplay(BlackImage, 10, 10, 390, 280);
    //EPD_4IN2_V2_Display(BlackImage);
    scanf("%c", &dummy);
/*
    Paint_Clear(WHITE);
    Paint_DrawString_EN(10, 120, "let me be the one", &Font24, WHITE, BLACK);
    Paint_DrawString_EN(10, 144, "who sines with you", &Font24, WHITE, BLACK);
	EPD_4IN2_V2_Display(BlackImage);
    scanf("%c", &dummy);

    Paint_Clear(WHITE);
    Paint_DrawString_EN(10, 120, "in the morning", &Font24, WHITE, BLACK);
    Paint_DrawString_EN(10, 144, "we don't know what to do", &Font24, WHITE, BLACK);
	EPD_4IN2_V2_Display(BlackImage);
    scanf("%c", &dummy);
*/

#endif

    EPD_4IN2_V2_Init();
    EPD_4IN2_V2_Clear();
    printf("Goto Sleep...\r\n");
    EPD_4IN2_V2_Sleep();
    free(BlackImage);
    BlackImage = NULL;
    DEV_Delay_ms(2000);//important, at least 2s
    // close 5V
    printf("close 5V, Module enters 0 power consumption ...\r\n");
    DEV_Module_Exit();
    
    return 0;
}
#endif

int EPD_4in2_V2_test(void){
    
}

