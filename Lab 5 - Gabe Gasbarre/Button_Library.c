/*
 * Button_Library.c
 *
 *  Created on: Feb 17, 2021
 *      Author: Gasbarrg
 *
 *      Button initialization and function library
 *
 *      Library currently has initializations for:
 *          P1 Port1 and Port4 on board buttons
 *          P6 Port4 and Port5 external buttons
 *          P5 Port5 external button
 *
 *
 *     Library currently has input functions with de-bouncing for:
 *          P1 Port4 on board buttons
 *          P6 Port4 and Port5 external buttons
 *          P5 Port5 external button
 *
 *
 */
#include "msp.h"
#include "Timer_Library.h"

void Button_init(){

    //INITIATE ON BOARD BUTTONS FOR DEBUGGING PURPOSES
    P1-> SEL0 &=~(BIT1 | BIT4);
    P1-> SEL1 &=~(BIT1 | BIT4); //configureP1.4 and P1.1as GPIO
    P1-> DIR &=~(BIT1 | BIT4);  //make P1.1 and P1.4 inputs
    P1-> REN |=(BIT1 | BIT4);   //enable pull resistors on P1.1 and P1.4
    P1-> OUT |=(BIT1 | BIT4);  //P1.1 and P1.4 are pull down

    //CONFIGURE PINS 6.4 AND 6.5 AS INTERNAL PULL UP RESISTORS
    P6-> SEL0 &=~(BIT5 | BIT4);
    P6-> SEL1 &=~(BIT5 | BIT4); //configureP6.4 and P6.5 as GPIO
    P6-> DIR &=~(BIT5 | BIT4);  //make P6.5 and P6.4 inputs
    P6-> REN |=(BIT5 | BIT4);   //enable pull resistors on P6.4 and P6.5
    P6-> OUT |=(BIT5 | BIT4);  //P6.4 and P6.5 are pull up

    //CONFIGURE PIN 5.5 AS INTERNAL PULL UP RESISTOR
    P5-> SEL0 &=~(BIT5);
    P5-> SEL1 &=~(BIT5); //configureP5.5 as GPIO
    P5-> DIR &=~(BIT5);  //make P5.5 input
    P5-> REN |=(BIT5);   //enable pull resistors on  P5.5
    P5-> OUT |=(BIT5);  //P5.5 is pull up
}

int Port1_Input(void){                  //On board Pin 1 Port4 input function
    if ((P1->IN & BIT4 ) == 0 ){        //check for input
        SysTdelay(15);                   //De-bounce delay (15Ms
        if ((P1->IN & BIT4 ) == 0 )     //Check again for input
            return(1);                  //Return 1
    }
    else
        return(0);
}

int Button1(void) {                         //External Button 1 (Port6 Pin5) button input

    if ((P6->IN & BIT5 ) == 0 ){
        SysTdelay(15);
        if ((P6->IN & BIT5 ) == 0 )
            return(1);
    }
    else
        return(0);
}

int Button2(void) {                         //External Button 2 (Port6 Pin4) button input

    if ((P6->IN & BIT4 ) == 0 ){
        SysTdelay(15);
        if ((P6->IN & BIT4 ) == 0 )
            return(1);
    }
    else
        return(0);
}

int Button3(void){                          //External Button 3 (Port5 Pin5) button input

    if ((P5->IN & BIT5 ) == 0 ){
        SysTdelay(15);
        if ((P5->IN & BIT5 ) == 0 )
            return(1);
    }
    else
        return(0);
}


