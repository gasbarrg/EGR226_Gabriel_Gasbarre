/*
 * LED_Library.c
 *
 *  Created on: Feb 17, 2021
 *      Author: Gasbarrg
 *
 *      LED Initialization and functions.
 *
 *      Current LED initializations include
 *          Green LED on Pin6.0
 *          Yellow LED on Pin3.2
 *          Red LED on Pin3.3
 *
 *      Current LED functions include:
 *          Green ON
 *          Green OFF
 *
 *          Yellow ON
 *          Yellow OFF
 *
 *          Red ON
 *          Red OFF
 *
 */
#include "msp.h"

void LED_init(void) {

    //initialize pin 6.0    GREEN LED
    P6->SEL1 &=~(BIT0);
    P6->SEL0 &=~(BIT0);         //Set P6.0 GPIO
    P6->DIR |= (BIT0);          //Set P6.0 DIR = 1 for output
    P6->OUT &=~(BIT0);          //Set P6.0 to 0 for low output

    //initialize pin 3.2    YELLOW LED
    P3->SEL1 &=~(BIT2);
    P3->SEL0 &=~(BIT2);         //Set P3.2 GPIO
    P3->DIR |= (BIT2);          //Set P3.2 DIR = 1 for output
    P3->OUT &=~(BIT2);          //Set P3.2 to 0 for low output

    //initialize pin 3.3    RED LED
    P3->SEL1 &=~(BIT3);
    P3->SEL0 &=~(BIT3);         //Set P3.3 GPIO
    P3->DIR |= (BIT3);          //Set P3.3 DIR = 1 for output
    P3->OUT &=~(BIT3);          //Set P3.3 to 0 for low output

}

void Green_LED_ON (void) {
    P6 -> OUT |= (BIT0);        //Turn on GREEN LED
}
void Green_LED_OFF (void) {
    P6 -> OUT &=~ (BIT0);       //Turn off GREEN LED
}

void Yellow_LED_ON (void){
    P3 -> OUT |= (BIT2);        //Turn on YELLOW LED
}
void Yellow_LED_OFF (void){
    P3 -> OUT &=~ (BIT2);       //Turn off YELLOW LED
}

void Red_LED_ON (void){
    P3 -> OUT |= (BIT3);        //Turn on RED LED
}
void Red_LED_OFF (void){
    P3 -> OUT &=~ (BIT3);       //Turn off RED LED
}
