/*
 * LED_Library.c
 *
 *  Created on: Apr 13, 2021
 *      Author: Gasba
 */
#include "LED_Library.h"
#include "SysTick_Library.h"

        volatile int toggle =0;
    //*****RGB LEDs*****//
    //P7.4 -    (PWM) TA1.4
    //P7.5 -    (PWM) TA1.3
    //P7.6 -    (PWM) TA1.2

void LED_Init(void)
{
    // Configure GPIO for PWM output P7.4 (PWM) TA1.4
    P7->SEL0 |= (BIT4 | BIT5 | BIT6);
    P7->SEL1 &=~(BIT4 | BIT5 | BIT6);           // P7.4 set TA1.4
    P7->DIR  |= (BIT4 | BIT5 | BIT6);           //Output

    TIMER_A1->CCR[0]  = 60000;                           // PWM Period (# cycles of clock)
    TIMER_A1->CCR[4]  = 0;                               // CCR4 PWM duty cycle
    TIMER_A1->CCR[3]  = 0;                               // CCR4 PWM duty cycle
    TIMER_A1->CCR[2]  = 0;                               // CCR4 PWM duty cycle
    TIMER_A1->CCTL[4] = TIMER_A_CCTLN_OUTMOD_7;          // CCR4 reset/set mode 7
    TIMER_A1->CCTL[3] = TIMER_A_CCTLN_OUTMOD_7;          // CCR5 reset/set mode 7
    TIMER_A1->CCTL[2] = TIMER_A_CCTLN_OUTMOD_7;          // CCR6 reset/set mode 7
    TIMER_A1->CTL = 0b0000001000010100;     // SMCLK, Up Mode, clear TAR to start

    //configure indicator LED's
    //P6.5 RED LED
    //P6.4 GREEN LED
    P6-> SEL0 &=~(BIT5 | BIT4 );
    P6-> SEL1 &=~(BIT5 | BIT4 );
    P6-> DIR  |= (BIT5 | BIT4 );

    P6-> OUT |=  BIT5;    //RED LED on
    P6-> OUT &=~ BIT4;    //RED LED on
}

void BrightnessRed (int percent)
{
    int period = (60000 * percent) /100;
    TIMER_A1 -> CCR[4] = period;
}

void BrightnessGreen (int percent)
{
    int period = (60000 * percent) /100;
    TIMER_A1 -> CCR[3] = period;
}

void BrightnessBlue (int percent)
{
    int period = (60000 * percent) /100;
    TIMER_A1 -> CCR[2] = period;
}

void PORT1_IRQHandler (void)
{
    if(P1->IFG & BIT6)  //LED TOGGLE INTERRUPT
    {
        SysTick_delay_ms(100); //Wait for low
        if(toggle==0)
        {
            BrightnessRed(0);
            BrightnessGreen(0);
            BrightnessBlue(0);
            toggle = 1;
        }
        else if(toggle == 1)
        {
            BrightnessRed(dcRed);
            BrightnessGreen(dcGreen);
            BrightnessBlue(dcBlue);
            toggle =0;
        }
    }

    if(P1->IFG & BIT7)  //DC MOTOR E STOP
    {
        TIMER_A3 -> CCR[2] = 0;
    }

    P1->IFG   = 0;                   // Clear all P1 interrupt flags
}

