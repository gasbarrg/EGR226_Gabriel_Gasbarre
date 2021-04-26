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
#include "SysTick_Library.h"

//Initialize pin for PWM using SysTick
void Motor_Init(void){
    P4 -> SEL1 &=~ BIT1;
    P4 -> SEL0 &=~ BIT1;
    P4 -> DIR |= BIT1;      //Output
}

void Motor_Sys(int cycle) {
    //NOT USED FOR FINAL PROJECT
    int on, off;
    on = (20 * cycle) / 100;
    off = 20 - on;              //off remainder of time

    P4 -> OUT |= BIT1;
    SysTick_delay_ms(on);
    P4 -> OUT &=~ BIT1;
    SysTick_delay_ms(off);

}

void Motor_TA_Init(void){
    /*-----------------------------------------------------------------------
     |  Function Motor_TA_Init
     |
     |  Purpose:  Initializes DC motor on TimerA
     |
     |  Parameters:N/A
     |
     |
     |  Returns: N/A
     *-------------------------------------------------------------------*/
   P8->SEL0 |= BIT2;
   P8->SEL1 &= ~BIT2;       // P8.2 set TA3.2
   P8->DIR |= BIT2;         //Output


   TIMER_A3->CCR[0]  = 60000;                           // PWM Period (# cycles of clock)
   TIMER_A3->CCR[2]  = 0;                               // CCR2 PWM duty cycle
   TIMER_A3->CCTL[2] = TIMER_A_CCTLN_OUTMOD_7;          // CCR1 reset/set mode 7


   TIMER_A3->CTL = 0b0000001000010100;     // SMCLK, Up Mode, clear TAR to start


}
void Motor_TA(int cycle){
    /*-----------------------------------------------------------------------
     |  Function Motor_TA
     |
     |  Purpose:  Update the timerA duty cycle for the DC motor
     |
     |  Parameters: cycle
     |      this is the percentage for the duty cycle
     |
     |  Returns: N/A
     *-------------------------------------------------------------------*/
    int period;
    period = (60000 * cycle)/10;

    TIMER_A3 -> CCR[2] = period;
}
