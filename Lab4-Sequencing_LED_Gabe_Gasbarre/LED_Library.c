/*
 * LED_Library.c
 *
 *  Created on: Feb 10, 2021
 *      Author: Gabriel Gasbarre
 *
 *          LED initialization function library. Currently initializes the pin 2, currently initializes pin 2.0, 2.1, and 2.2 (Red, Green, and Blue on board LED)
 */

#include "msp.h"

void LED_init(void) {

    P2->SEL1 &=~( BIT0 | BIT1 | BIT2 );    //set P2 LED GPIO
    P2->SEL0 &=~( BIT0 | BIT1 | BIT2 );    //set P2 Button GPIO
    P2->DIR |= ( BIT0 | BIT1 | BIT2 );     //turns P2.0 into an output
    P2->OUT &=~( BIT0 | BIT1 | BIT2 );     //Turns off all LED's
}

void LED_Red_ON (void) {
    P2 ->OUT |=BIT0;        //turn red LED on
}

void LED_Red_OFF(void) {
    P2 -> OUT &=~BIT0;      //turn red LED off
}

void LED_Green_ON(void){
    P2 -> OUT |=BIT1;        //turn green LED on

}
void LED_Green_OFF(void){
    P2 -> OUT &=~BIT1;      //Turn green LED off

}
void LED_Blue_ON(void){
    P2 -> OUT |=BIT2;       //Turn blue LED on

}
void LED_Blue_OFF(void){
    P2 -> OUT &=~BIT2;      //Turn blue LED off

}


