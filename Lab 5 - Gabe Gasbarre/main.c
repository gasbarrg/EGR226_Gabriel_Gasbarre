#include "msp.h"
#include "LED_Library.h"
#include "Button_Library.h"
#include "Timer_Library.h"
/**
 * main.c
 *
 *   Created on: Feb 17, 2021
 *      Author: Gabriel Gasbarre
 *
 *      Main function
 *
 *      This function is designed to have 3 buttons each with their own functionality.
 *          Button 1 allows for the cycling of colors (forward only) without any input delay other than that the button cannot be held down. It must be pressed each time in order to cycle the colors
 *          Button 2 allows for the cycling of colors (forward) on a one second loop. This button can be held down.
 *          Button 3 allows for the cycling of colors (backward) on a one second loop. This button can be held down.
 */


void main(void) {
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    LED_init();
    Button_init();
    SysTick_Init();

    int i=0;
    while (1){

        if(Button1() == 1){

            while (Button1() == !1 ) {}                 //Wait while Button1 is not being pressed
            Red_LED_OFF();                              //Turn off Red LED in case of loop
            Green_LED_ON();                             //Turn on green LED
            while (Button1() == 1 ) {}                  //Wait for button 1 to be pressed

            while (Button1() == !1 ) {}                 //Loop above lines with different LED colors.
            Green_LED_OFF();
            Yellow_LED_ON();
            while (Button1() == 1 ) {}
            while (Button1() == !1 ) {}
            Yellow_LED_OFF();
            Red_LED_ON();
            while (Button1() == 1 ) {}

        }


        else if((Button2() == 1) || (Button3() == 1)){                  //Function section for if forward/ backward button is being pressed.
            while((Button2() == !1) && (Button3() == !1)){}             //Wait for either button to be pressed

            if(i == 0){                                                 //initial position i = 0
                Green_LED_ON();
                Yellow_LED_OFF();
                Red_LED_OFF();
                while((Button2() == !1) && (Button3() == !1)){}         //Wait for either button to be pressed
                if (Button2() == 1)                                     //If forward button is pressed, move to next section i = 1
                    i = 1;
            }
            else if (Button3() == 1){                               //If backwards button is pressed, move backwards to i = 2
                i = 2;
            }
            SysTdelay(100);                                         //Delay 100ms between inputs.
        }

        if(i == 1){                                                //Same section of code as above but for i = 1 where the Yellow LED is on
            Green_LED_OFF();
            Yellow_LED_ON();
            Red_LED_OFF();
            while ((Button2() == !1) && (Button3() == !1)){}
            if (Button2() == 1){
                i = 2;
            }
            else if (Button3() == 1){
                i = 0;
            }
            SysTdelay(100);
        }
        if(i == 2){                                               //Same section of code as above but for i = 2 where the Red LED is on
            Green_LED_OFF();
            Yellow_LED_OFF();
            Red_LED_ON();
            while((Button2() == !1) && (Button3() == !1)){}
            if (Button2() == 1){
                i = 0;
            }
            else if (Button3() == 1){
                i = 1;
            }
            SysTdelay(100);
        }
    }
}

