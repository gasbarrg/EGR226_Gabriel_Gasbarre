/*
 * Button_Library.c
 *
 *  Created on: Feb 10, 2021
 *      Author: Gabriel Gasbarre
 *
 *
 *      Button initialization function library. Current functions include initializng pins 1.1 and 1.4
 *          Function also has debouncing for each input.
 */

#include "msp.h"

void Button_init(){

    P1-> SEL0 &=~(BIT1 | BIT4);
    P1-> SEL1 &=~(BIT1 | BIT4);         //configureP1.4 and P1.1as GPIO
    P1-> DIR &=~(BIT1 | BIT4);          //make P1.1 and P1.4 inputs
    P1-> REN |=(BIT1 | BIT4);           //enable pull resistors on P1.1 and P1.4
    P1-> OUT |=(BIT1 | BIT4);           //P1.1 and P1.4 are pull down

}


int Port1_Input(void){
/*    Desc: Simple debounce function that detects input and ensures button cannot input many singnals in a short amount of time
 *      Pin(s): 1.4
 * */

    if ((P1->IN & BIT4 ) == 0 ){        //If button being pressed
        __delay_cycles(45000);          //delay 15ms
        if ((P1->IN & BIT4 ) == 0 )     //if button still pressed
            return(1);                  //return positibe button press
    }
    else
        return(0);
}

int Port14_Input(void){
    /*    Desc: Simple debounce function that detects input and ensures button cannot input many singnals in a short amount of time
     *
     *    Pin(s): Pin 1.1
     * */
    if ((P1->IN & BIT1 ) == 0 ){
        __delay_cycles(45000);
        if ((P1->IN & BIT1 ) == 0 )
            return(1);
    }
    else
        return(0);

}
