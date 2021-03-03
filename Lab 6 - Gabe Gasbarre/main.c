#include "msp.h"
#include "Keypad_Library.h"
#include "stdio.h"
#include "Timer_Library.h"

/*
 *  main.c
 *
 *  Created on: Feb 24, 2021
 *      Author: Gabriel Gasbarre
 *      Course: EGR 226 - 902
 *      Lab 6
 *      Keypad User Input
 *
 *      The keypad program currently cycles between 3 modes.
 *          1.) Display one key at a time instantaneously
 *          2.) Enter 4 keys to be displayed
 *          3.) Enter 2, 4 number pins to be saved and compared if they are equal
 *
 *      Pins:
            Rows: 5.6 , 6.6 , 6.7 2.3
            Columns:  5.1 3.5 3.7
 */


void main(void)
{

    while (1) {
        WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

    //Initialize SysTick Timer
    SysTick_Init();
    //Initialize all Keypad functions
	Keypad_Init();

	//Display one key at a time instantaneously
	printf("Enter a Key to display.\n Press * to exit.\n");
	//Wait for user input
	while(Keypad_Read() == 404);
	//Leave function if * is pressed
	while(Keypad_Read() != 10){

	    //Print Keypad reading
	    printf("%d\n", Keypad_Read());
	    //Wait for end of keystroke
	    while(Keypad_Read() != 404);
	    //Wait for next keystroke
	    while(Keypad_Read() == 404);
	}


	//Enter 4 keys to be displayed
	printf("enter 4 keys\nPress * to Exit. \n");
	//Wait for user input
	while(Keypad_Read() == 404);
	//Collect inputs and display the 4 most recent
	Keypad_Pin();

	//Recieve 2 pins and compare them
	printf("Enter 4 keys to be stored, followed by a #.\n");
	//Wait for user input
	while(Keypad_Read() == 404);
	Key_Entry();
}
}

