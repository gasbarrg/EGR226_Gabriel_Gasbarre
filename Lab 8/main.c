#include "msp.h"
#include "Timer_Library.h"
#include "Motor_Library.h"
#include "Keypad_Library.h"
#include "stdio.h"


/*
 * Main.c
 *
 *  Created on: Mar 13, 2021
 *      Author: Gabriel Gasbarre
 *
 *      Basic Motor control program.
 *
 *
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	SysTick_Init();
	Motor_Init();
	Motor_TA_Init();
	Keypad_Init();

	int dutyCycle = 40;

	while (1){

	    //Motor_Sys(dutyCycle);
	    //Motor_TA(dutyCycle);

	    printf("Enter a percentage from 0 - 100: \n");
	    Motor_TA(Keypad_Value());
	    while(Keypad_Read() != 404){}

	}
}
