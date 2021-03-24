/*
 * Button_Library.c
 *
 *  Created on: Mar 20, 2021
 *      Author: Gabe Gasbarre
 *
 *      Button initialization using interrupts
 *      Button interrupt handler
 */
#include "msp.h"
#include "Timer_Library.h"
volatile int percent = 0;

void Button_Init(void){

    //CONFIGURE PINS 3.5, 3.6, 3.7 AS INTERNAL PULL UP RESISTORS
    P2->SEL0 &=~ (BIT5 | BIT6 | BIT7);
    P2->SEL1 &=~ (BIT5 | BIT6 | BIT7);
    P2->DIR  &=~ (BIT5 | BIT6 | BIT7);
    P2->REN  |=  (BIT5 | BIT6 | BIT7);      // Enable Internal  resistor
    P2->OUT  |=  (BIT5 | BIT6 | BIT7);      // Enable pull-up resistor (P2.5 output high)
    P2->IES  |=  (BIT5 | BIT6 | BIT7);      //Set pin interrupt to trigger when it goes from high to low
    P2->IE   |=  (BIT5 | BIT6 | BIT7);      // Enable interrupt for P2.5, 2.6, 2.7
    P2->IFG   = 0;                          // Clear all P2 interrupt flags

}

void PORT2_IRQHandler(void){     //Port2 ISR

    if( P2->IFG & BIT7 ){      // If P2.7 had an interrupt (going from high to low
        percent = percent + 10;           //Percent + 10%
        delay_ms(100);
    P2 ->IFG &=~BIT7;           // Reset the interrupt flag
    }

    else if( P2->IFG & BIT5 ){      // If P2.6 had an interrupt (going from high to low
        percent = percent - 10 ;           //Percent - 10%
        delay_ms(100);
    P2 ->IFG &=~BIT5;           // Reset the interrupt flag
    }

    else if( P2->IFG & BIT6 ){      // If P2.5 had an interrupt (going from high to low
        percent = 0;           //Percent = 0
        delay_ms(100);
    P2 ->IFG &=~BIT6;           // Reset the interrupt flag
    }

    //Error handling for LCD display / Motor power
    if (percent > 90){
        percent = 0;
    }
    if (percent < 0){
        percent = 90;
    }
}


