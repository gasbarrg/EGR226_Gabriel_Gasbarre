#include "msp.h"
#include "Timer_Library.h"
#include "stdio.h"
#include "ADC_Library.h"
#include "LCD_Library.h"

/**
 * main.c
 */

int main(void) {
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	ADC14_init();
	PotentiometerADC_init();
	SysTick_Init();
	LCD_Init();
	delay_micro(100);


	while(1)
	{
	    printTemp(display_temp());
	    delay_ms(500);
	}



}


