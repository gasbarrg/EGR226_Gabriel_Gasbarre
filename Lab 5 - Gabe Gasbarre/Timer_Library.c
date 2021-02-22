/*
 * Timer_Library.c
 *
 *  Created on: Feb 21, 2021
 *      Author: Gasba
 *
 *      SysTick clock initialization and delay functions.
 *      Currently has SysTick Delay clock with each delay value = 1msecond
 *
 */
#include "msp.h"

void SysTick_Init (void)                        //initialization of systic timer
  {
    SysTick -> CTRL  = 0;                        // disable SysTick During step
    SysTick -> LOAD = 0x00FFFFFF;                // max reload value
    SysTick -> VAL     = 0;                      // any write to current clears it
    SysTick -> CTRL  = 0x00000005;               // enable systic, 3MHz, No Interrupts
  }

void SysTdelay (uint16_t delay)                             // Systick delay function
  {
    SysTick -> LOAD = ((delay * 3000) - 1);                 //delay for 1 msecond per delay value
    SysTick -> VAL     = 0;                                 // any write to CVR clears it
    while ( (SysTick -> CTRL  &  0x00010000) == 0) {}        // wait for flag to be SET
  }


