#include "msp.h"
#include "LED_Library.h"
#include "Button_Library.h"
#include <stdio.h>

/**
 * main.c
 *      EGR 226 902
 *
 *      LAB 4
 *      Digital Inputs and Outputs – Interfacing Switches and LEDs to the MSP432
 *      Author: Gabriel Gasbarre
 *
 *
 *      Function that initializes Red, Green, and Blue LED's along with both input buttons. pressing button on pin 1.4 cycles one color at a time and cannot be held to cycle.
 *          pin 1.1 is able to be held and cycles colors once every second, no faster.
 *
 */
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    LED_init();                                             //LED initialization
    Button_init();                                          //Button initialization

    while(1) {

        if (Port14_Input() == 1) {


            while(Port14_Input() != 1) {}                   //wait for user input
                LED_Blue_OFF();                             //Blue LED off (in case of loop)
                LED_Red_ON();                               //Red LED on
                __delay_cycles(3000000);                    //minimum delay for color switch

           while(Port14_Input() != 1) {}                    //wait for user input
                LED_Red_OFF();                              //Red LED off
                LED_Green_ON();                             //Green LED on
                __delay_cycles(3000000);                    //minimum delay for color switch

           while(Port14_Input() != 1) {}                    //wait for user input
                LED_Green_OFF();                            //Green LED off
                LED_Blue_ON();                              //Blue LED on
                __delay_cycles(3000000);                    //minimum delay for color switch


        }

        else if (Port1_Input() == 1){

            while(Port1_Input() != 1) {}                        //wait for user input
                     if (Port1_Input() == 1){
                             LED_Blue_OFF();                    //LBlue LED off (in case of loop)
                             LED_Red_ON();                      //Red LED on, first color
                             while(Port1_Input() == 1){}        //delay next function if button held
                     }

                while(Port1_Input() != 1){}                     //wait for user input
                    if (Port1_Input() == 1){
                            LED_Red_OFF();                      //Red LED off
                            LED_Green_ON();                     //Green LED on
                            while(Port1_Input() == 1){}         //delay next function if button held
                    }
                while(Port1_Input() != 1){}                     //wait for user input
                    if(Port1_Input() == 1){
                            LED_Green_OFF();                    //Green LED off
                            LED_Blue_ON();                      //Blue LED on
                            while(Port1_Input() == 1){}         //delay next function if button held

        }

        }

        }


}
