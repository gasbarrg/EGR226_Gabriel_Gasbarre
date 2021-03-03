/*
 * Keypad_Library.c
 *
 *  Created on: Feb 24, 2021
 *      Author: Gabriel Gasbarre
 *      Course: EGR 226 - 902
 *      Contains current keypad functions:
 *
 *          void Keypad_Init(void) - - - initializes all rows and columns for reading keypad
 *          int Keypad_Read(void)  - - - Reads keypad and returns a number 0 - 11 depending on button pressed
 *          void Keypad_Pin(void)  - - - Stores the last 4 numbers entered as a pin.
 *          void Key_Entry(void)   - - - Stores 2 pins and checks if they are equal
 *
 *
 */
#include "msp.h"
#include "Timer_Library.h"
#include "stdio.h"


void Keypad_Init(void){
    /****| Keypad_Init | *****************************************
    * Brief: Initializes all rows and columns
    * param: N/A
    *
    * return:
    * N/A
    *************************************************************/
    //Pins:
        //rows: 5.6 , 6.6 , 6.7 2.3
        //Columns:  5.1 3.5 3.7

    //INITIALIZE KEYPAD ROW 5.6:
    P5 -> SEL0 &=~ (BIT6);
    P5 -> SEL1 &=~ (BIT6);      //INITIALIZE PIN5.6
    P5 -> DIR &=~ (BIT6);       //PIN 5.6 IS INPUT
    P5 -> REN |= (BIT6);        //ENABLE INTERNAL RESISTORS
    P5 -> OUT |= (BIT6);        //P5.6 IS PULL UP

    //INITIALIZE KEYPAD ROW 6.6 AND 6.7:
    P6 -> SEL0 &=~ (BIT6 | BIT7);
    P6 -> SEL1 &=~ (BIT6 | BIT7);      //INITIALIZE PIN5.6
    P6 -> DIR &=~ (BIT6 | BIT7);       //PIN 5.6 IS INPUT
    P6 -> REN |= (BIT6 | BIT7);        //ENABLE INTERNAL RESISTORS
    P6 -> OUT |= (BIT6 | BIT7);        //P5.6 IS PULL UP

    //INITIALIZE KEYPAD ROW 2.3:
    P2 -> SEL0 &=~ (BIT3);
    P2 -> SEL1 &=~ (BIT3);      //INITIALIZE PIN5.6
    P2 -> DIR &=~ (BIT3);       //PIN 5.6 IS INPUT
    P2 -> REN |= (BIT3);        //ENABLE INTERNAL RESISTORS
    P2 -> OUT |= (BIT3);        //P5.6 IS PULL UP

}
int Keypad_Read(void){
    /****| Keypad_Read | *****************************************
    * Brief:  Sets a colum to output while other 2 colums remain input to read one entire row at a time.
    * param: N/A
    *
    * return:
    * Int value between 0 and 11 depending on the button pressed.
    *************************************************************/
    //Columns:  5.1 3.5 3.7
    //set all colums to inputs
    P5 -> DIR &=~ (BIT1);       //PIN5.1 INPUT
    P3 -> DIR &=~ (BIT5);       //PIN 3.5 INPUT
    P3 -> DIR &=~ (BIT7);       //PIN 3.7 INPUT

    //SET COL 1 TO LOW OUTPUT (P5.1)
    P5 -> DIR |= (BIT1);        //OUTPUT
    P5 -> OUT &=~(BIT1);        //LOW

    //READ ALL ROWS IN COL 1
    if ((P5 -> IN & BIT6) == 0){        //ROW1
        SysTdelay(15);
        if ((P5 -> IN & BIT6) == 0){
            return(1);
        }
    }
    if ((P6 -> IN & BIT6) == 0){        //ROW 2
        SysTdelay(15);
        if ((P6 -> IN & BIT6) == 0){
            return(4);
        }
    }
    if ((P6 -> IN & BIT7) == 0){        //ROW 3
        SysTdelay(15);
        if ((P6 -> IN & BIT7) == 0){
            return(7);
        }
    }
    if ((P2 -> IN & BIT3) == 0){        //ROW 4
        SysTdelay(15);
        if ((P2 -> IN & BIT3) == 0){
            return(10);
        }
    }



    //SET COL1 INPUT, COL2 LOW OUTPUT (P6.6)
    P5 -> DIR &=~ (BIT1);       //PIN5.1 INPUT
    P3 -> DIR |= (BIT5);        //OUTPUT P6.6
    P3 -> OUT &=~(BIT5);        //LOW

    //READ ALL ROWS IN COL2
    if ((P5 -> IN & BIT6) == 0){        //ROW1
        SysTdelay(15);
        if ((P5 -> IN & BIT6) == 0){
            return(2);
        }
    }
    if ((P6 -> IN & BIT6) == 0){        //ROW 2
        SysTdelay(15);
        if ((P6 -> IN & BIT6) == 0){
            return(5);
        }
    }
    if ((P6 -> IN & BIT7) == 0){        //ROW 3
        SysTdelay(15);
        if ((P6 -> IN & BIT7) == 0){
            return(8);
        }
    }
    if ((P2 -> IN & BIT3) == 0){        //ROW 4
        SysTdelay(15);
        if ((P2 -> IN & BIT3) == 0){
            return(0);
        }
    }

    //SET COL2 INPUT, COL3 LOW OUTPUT (P6.6)
    P3 -> DIR &=~ (BIT5);       //PIN5.1 INPUT
    P3 -> DIR |= (BIT7);        //OUTPUT P6.6
    P3 -> OUT &=~(BIT7);        //LOW

    //READ ALL ROWS IN COL 3
    if ((P5 -> IN & BIT6) == 0){        //ROW1
        SysTdelay(15);
        if ((P5 -> IN & BIT6) == 0){
            return(3);
        }
    }
    if ((P6 -> IN & BIT6) == 0){        //ROW 2
        SysTdelay(15);
        if ((P6 -> IN & BIT6) == 0){
            return(6);
        }
    }
    if ((P6 -> IN & BIT7) == 0){        //ROW 3
        SysTdelay(15);
        if ((P6 -> IN & BIT7) == 0){
            return(9);
        }
    }
    if ((P2 -> IN & BIT3) == 0){        //ROW 4
        SysTdelay(15);
        if ((P2 -> IN & BIT3) == 0){
            return(11);
        }
    }


    //SET ALL COLUMNS TO INPUTS
    P5 -> DIR &=~ (BIT1);       //PIN5.1 INPUT
    P3 -> DIR &=~ (BIT5);       //PIN 3.5 INPUT
    P3 -> DIR &=~ (BIT7);       //PIN 3.7 INPUT

    return(404);  //Null return value (no key pressed)
}



void Keypad_Pin(void) {
    /****| Keypad_Pin | *****************************************
    * Brief:  Remeber all that junk from before? No more!
    * This function stores the last 4 numbers entered as a pin. for example, typing "12345678" return "5678"
    *
    * param: N/A
    *
    * return:
    * N/A
    *************************************************************/
    int i;
    int pin[4] = {800815, 800815, 800815, 800815};

    do {
        //Wait for user input
        while(Keypad_Read() == 404);
        //Print current PIN if user presses #
        if ((Keypad_Read() == 11) & (pin[3] == 800815 || pin[2] == 800815 || pin[1] == 800815) ){
            printf("Please enter at least 4 digits.\n\n");
            //Wait for end of keystroke
            while(Keypad_Read() != 404);
        }
        else if (Keypad_Read() == 11 ){
            printf(" %d, %d, %d, %d\n", pin[3], pin[2], pin[1], pin[0]);
            //Wait for end of keystroke
            while(Keypad_Read() != 404);
        }
        //If any other number is pressed, move all variables down one position and import new keystroke
        else {
            for( i = 3; i > 0; i-- ){
                pin[i] = pin [i-1];
            }
            pin[0] = Keypad_Read();
            //Wait for end of keystroke
            while(Keypad_Read() != 404);
        }
    }while (pin[0] != 10 );     //Exit when * is pressed
}

char compareArray(int a[],int b[]) {
    /****| compareArray | *****************************************
    * Brief: Function to compare the 2 pins provided. (Will be used for below function)
    *
    * param: pin1 and pin1 as integer arrays
    *
    * return:
    * Returns 1 if Pins are unequal
    * Returns 0 if pins are equal
    *************************************************************/
    int i;
    for(i=0;i<4;i++){
        if(a[i]!=b[i])
            return 1;
    }
    return 0;
}


void Key_Entry(void) {
    /****| Key_Entry | *****************************************
    * Brief: Reads in 2 pins and compares them to see if they are equal. Each pin also only stores the last 4 numbers.
    *
    * param: N/A
    *
    * return:
    * N/A
    *************************************************************/
    int i;
    int pin[4] = {800815, 800815, 800815, 800815};
    int pin1[4] = {800815, 800815, 800815, 800815};

    while (Keypad_Read() != 11 ){
        //Wait for user input
        while(Keypad_Read() == 404);
        do {
            for( i = 3; i > 0; i-- ){
                pin[i] = pin [i-1];
            }
            pin[0] = Keypad_Read();
            //Wait for end of keystroke
            while(Keypad_Read() != 404);
            //Wait for user input
            while(Keypad_Read() == 404);
        }while(Keypad_Read() != 11);
    }

    printf(" %d, %d, %d, %d\n", pin[3], pin[2], pin[1], pin[0]);
    while(Keypad_Read() != 404);
    printf("Re-Enter your Pin to confirm, followed by a #.\n");
    while (Keypad_Read() != 11 ){
        //Wait for user input
        while(Keypad_Read() == 404);
        do {
            for( i = 3; i > 0; i-- ){
                pin1[i] = pin1[i-1];
            }
            pin1[0] = Keypad_Read();
            //Wait for end of keystroke
            while(Keypad_Read() != 404);
            //Wait for user input
            while(Keypad_Read() == 404);
        }while(Keypad_Read() != 11);
    }
    printf(" %d, %d, %d, %d\n", pin1[3], pin1[2], pin1[1], pin1[0]);

    if (compareArray(pin, pin1) == 0){
        printf("Pins are equal\n");
    }
    else
        printf("Pins are not equal.\n");
}


