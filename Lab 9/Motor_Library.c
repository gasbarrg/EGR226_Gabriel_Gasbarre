/*
 * Motor_Library.c
 *
 *  Created on: Mar 13, 2021
 *      Author: Gabriel Gasbarre
 *
 *      Basic Motor control functions.
 *          Motor_Sys : PWM motor control using SysTick timer.
 *          Motor_TA  : PWM motor control using TimerA
 */
#include "msp.h"
#include "Timer_Library.h"

//Initialize pin for PWM using SysTick
void Motor_Init(void){
    P4 -> SEL1 &=~ BIT1;
    P4 -> SEL0 &=~ BIT1;
    P4 -> DIR |= BIT1;      //Output
}

void Motor_Sys(int cycle) {
    int on, off;
    on = (20 * cycle) / 100;
    off = 20 - on;              //off remainder of time

    P4 -> OUT |= BIT1;
    delay_ms(on);
    P4 -> OUT &=~ BIT1;
    delay_ms(off);

}

void Motor_TA_Init(void){
    // Configure GPIO for PWM output
    // Pin 2.4

   P2->SEL0 |= BIT4;
   P2->SEL1 &= ~BIT4;
   P2->DIR |= BIT4;         // P2.4 set TA0.1


   TIMER_A0->CCR[0]  = 60000;                         // PWM Period (# cycles of clock)
   TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;        // CCR1 reset/set mode 7
   TIMER_A0->CCR[1]  = 30000;                         // CCR1 PWM duty cycle

   TIMER_A0->CTL = 0b0000001000010100;     // SMCLK, Up Mode, clear TAR to start


}
void Motor_TA(int cycle){
    int period;
    period = (60000 * cycle) / 100;

    TIMER_A0 -> CCR[1] = period;
}
