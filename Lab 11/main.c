#include "msp.h"
#include "ADC_Library.h"
#include "Timer_Library.h"
#include "stdio.h"
/**
 * main.c
 */
extern volatile short period,result;


void main(void)
 {
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	SysTick_Init();
	TimerA0_Init();
	TimerA02_Init();


    NVIC->ISER[1] = 1 << ((PORT2_IRQn) & 31);       // Enable interrupt in NVIC vector
    __enable_irq();                                 // Enable global interrupt


	while(1)
	{
	    if(result ==1 ){
	    printf("period = %d\n", period);
	    result = 0;
	    }

	}
}
