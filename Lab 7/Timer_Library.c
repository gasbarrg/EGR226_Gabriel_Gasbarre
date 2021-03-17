/*
 * Timer_Library.c
 *
 *  Created on: Feb 24, 2021
 *      Author: gasbarrg
 */
#include "msp.h"

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
