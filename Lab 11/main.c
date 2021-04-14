#include "msp.h"
#include "ADC_Library.h"
#include "Timer_Library.h"
#include "stdio.h"
/**
 * main.c
 */

volatile unsigned short period, result;
volatile int detect10Hz;
unsigned short lastedge, currentedge;
int count1;
void main(void)
 {
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer

	SysTick_Init();
	TimerA0_Init();
	TimerA02_Init();
	P1->DIR = BIT0;

    NVIC->ISER[1] = 1 << ((PORT6_IRQn) & 31);       // Enable interrupt in NVIC vector
    NVIC->ISER[0] = 1 << ((TA2_N_IRQn) & 31);
    __enable_irq();                                 // Enable global interrupt


	while(1)
	{

	    if ( (detect10Hz == 1) ){
            P1-> OUT |=BIT0;
	        }

	    else if (detect10Hz == 0){
	        P1-> OUT &=~BIT0;}

	   count1++;
	   if ((count1 > 10000))
	       detect10Hz =0;
	}
}





void TA2_N_IRQHandler(void)             // Timer A0 interrupt service routine
 {

    TIMER_A2->CCTL[3] &=~ BIT0;         // Clear the interrupt flag
    currentedge = (TIMER_A2->CCR[3]);
    period = currentedge - lastedge;
    lastedge = currentedge;
    count1 = 0;
    if ( ( 35635 <period ) && ( period < 39375 ) ){
        detect10Hz =1;
    }
    else if ( !( 35635 <period ) && ( period < 39375 ) )
        detect10Hz= 0;




 }
