/*
 * Timer_Library.c
 *
 *  Created on: Feb 24, 2021
 *      Author: Gabriel Gasbarre
 *
 *      Systic initialization function
 *      Systick w/ interrupts initialization
 *      Systick micro-second delay function
 *      Systick millisecond delay function
 *      Systick interrupt handler
 */
#include "msp.h"
#include "Timer_Library.h"
volatile int count;




void SysTick_Init(void)                        //initialization of systic timer
  {
    SysTick -> CTRL  = 0;                        // disable SysTick During step
    SysTick -> LOAD = 0x00FFFFFF;                // max reload value
    SysTick -> VAL     = 0;                      // any write to current clears it
    SysTick -> CTRL  = 0x00000005;               // enable systic, 3MHz, No Interrupts
  }

void delay_micro (uint16_t delay){                          // Systick delay function
    SysTick -> LOAD = ((delay * 3) - 1);                    //delay for 1 microsecond per delay value
    SysTick -> VAL     = 0;                                 // any write to CVR clears it
    while ( (SysTick -> CTRL  &  0x00010000) == 0) {}       // wait for flag to be SET
  }


void delay_ms (uint16_t ms){
    SysTick -> LOAD = ((ms * 3000) - 1);                 //delay for 1 msecond per delay value
    SysTick -> VAL     = 0;                                 // any write to CVR clears it
    while ( (SysTick -> CTRL  &  0x00010000) == 0) {}        // wait for flag to be SET
}

void SysTick_Init_interrupt (void)                  //initialization of systic timer
  {
    SysTick -> CTRL = 0;                           // disable SysTick During step
    SysTick -> LOAD = 3000000;                     //reload value for 1s interrupts
    SysTick -> VAL = 0;                            // any write to current clears it
    SysTick -> CTRL =  0x00000007;                 // enable SysTick, 3MHz,   with Interrupts
  }

void SysTick_Handler(void) {                            //SysTick interrupt handler
    count = count + 1;
    if (count == 10)
        count = 0;
}


void TimerA0_Init(void)
{
    P2->SEL0 |= BIT4;
    P2->SEL1 &=~BIT4;
    P2->DIR |=  BIT4;                  // P2.4 set TA0.1

    TIMER_A0->CTL |= TIMER_A_CTL_SSEL__SMCLK;      // SMCLK
    TIMER_A0->CTL |= TIMER_A_CTL_MC__UP;          // Up mode
    TIMER_A0->CTL |= TIMER_A_CTL_CLR;            //Clear timer
    TIMER_A0->CTL |= BIT6 | BIT7;               //Divide clock by 8

    TIMER_A0->CCR[0] = 37500;                  // 10 Hz
    TIMER_A0->CCR[1] = 37500 / 2;
    TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;


}

void TimerA02_Init(void)
{
    //6.6 = t2.3
    P6->SEL0 |= BIT6;
    P6->SEL1 &=~ BIT6;       // P6.6
    P6->DIR  &=~ BIT6;       //Set 6.6 as input


    TIMER_A2->CTL |= TIMER_A_CTL_TASSEL_2;              // Use SMCLK as clock source,
    TIMER_A2->CTL |= TIMER_A_CTL_MC__UP;            // Start timer in CONTINUOUS mode
    TIMER_A2->CTL |= TIMER_A_CTL_ID_3;                  // divide by 8  375KHz to capture 10 & 14 Hz
    TIMER_A2->CTL |= TIMER_A_CTL_CLR;                   // clear TA0R


    TIMER_A2->CCTL[3] |= TIMER_A_CCTLN_CM_1;            // Capture rising edge,
    TIMER_A2->CCTL[3] |= TIMER_A_CCTLN_CCIS_0;            // Use CCI2A=ACLK,
    TIMER_A2->CCTL[3] |= TIMER_A_CCTLN_CCIE;            // Enable capture interrupt
    TIMER_A2->CCTL[3] |= TIMER_A_CCTLN_CAP;            // Enable capture mode,
    TIMER_A2->CCTL[3] |= TIMER_A_CCTLN_SCS;               // Synchronous capture

    TIMER_A2->CCR[0] = 65535;


}








/*
 *
 *
 *     if ( ( 35635 <period ) && ( period < 39375 ) )    // within 5% of 10Hz period
            detect10Hz=1;


 * P2->SEL0 |=  BIT5;                 // TA0.CCI2A input capture pin, second function
    P2->SEL1 &=~ BIT5;                // TA0.CCI2A input capture pin, second function
    P2->DIR  &=~ BIT5;

    TIMER_A0->CTL |=  0b0000001011010100;

    TIMER_A0->CCTL[2] |= TIMER_A_CCTLN_CM_1;            // Capture rising edge,
    TIMER_A0->CCTL[2] |= TIMER_A_CCTLN_CCIS_0;            // Use CCI2A=ACLK,
    TIMER_A0->CCTL[2] |= TIMER_A_CCTLN_CCIE;            // Enable capture interrupt
    TIMER_A0->CCTL[2] |= TIMER_A_CCTLN_CAP;            // Enable capture mode,
    TIMER_A0->CCTL[2] |= TIMER_A_CCTLN_SCS;               // Synchronous capture
 */


