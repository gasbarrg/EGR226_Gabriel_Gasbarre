#include "msp.h"
#include "stdio.h"
#include "SysTick_Library.h"
#include "LCD_Library.h"
#include "Keypad_Library.h"
#include "Motor_Library.h"
#include "LED_Library.h"

/*
 * Arm_Library.c
 *
 *  Created on: Apr 14, 2021
 *      Author: Gasba
 */

int indicator = 0;
void Potentiometer_Init(void)
{
    /*-----------------------------------------------------------------------
     |  Function Potentiometer_Init
     |
     |  Purpose:  Initializes all Potentiometers,
                     Both LCD Potentiometers
                     all 3 Robotic arm potentiometers
     |
     |  Parameters:     N/A
     |
     |
     |  Returns:        N/A
     *-------------------------------------------------------------------*/
    //LCD POTENTIOMETER
    // configure pin 6.0 for A15 input
    P6-> SEL0 |= BIT0;
    P6-> SEL1 |= BIT0;
    P6-> DIR &=~ BIT0;
    //Set pin 6.0 ADC input = A15
    ADC14-> CTL0  &=~ ADC14_CTL0_ENC;   // disable ADC converter during initialization
    ADC14-> CTL0 |=   0x04230290;      // S/H pulse mode, SMCLK, 16 sample clocks, Multi sample
    ADC14-> CTL1  =   0x00000000;      // 8 bit resolution
    ADC14-> CTL1 |=   0x00000000;      // convert for mem0 register (start adress)
    ADC14-> MCTL[15]= 0x0000000F;      // ADC14INCHx = 15 for mem[15]
    //ADC14-> IER0 |=   BIT15; //Interrupt on 15


    //**POTENTIOMETERS**//
    //Arm Servo Controllers: P5.0, P5.4, P5.5 (ADC)
    //ARM P1
    // configure pin 5.0 for A5 input
    P5-> SEL0 |= ( BIT0 | BIT4 | BIT5 );
    P5-> SEL1 |= ( BIT0 | BIT4 | BIT5 );
    P5-> DIR &=~ ( BIT0 | BIT4 | BIT5 );
    //Set pin 5.0 ADC input = A5 , P5.4 = A1, P5.5= A0
    ADC14-> MCTL[5]=  0x00000005;       // ADC14INCHx = 5 for mem[5]
    ADC14-> MCTL[1]=  0x00000001;       // ADC14INCHx = 1 for mem[1]
    ADC14-> MCTL[0]=  0x00000000;       // ADC14INCHx = 0 for mem[0]
    ADC14-> CTL0 |=   ADC14_CTL0_ENC;   // enable ADC14ENC, Starts the ADC after confg.
}



void Servo_Init(void)
{
    /*-----------------------------------------------------------------------
     |  Function Servo_Init
     |
     |  Purpose:  Initialize all 4 Robotic arm Servos
     |
     |  Parameters:     N/A
     |
     |
     |  Returns:        N/A
     *-------------------------------------------------------------------*/
    //******SERVOS******//
    //P2.4- P2.7 = MG902S (PWM)
    // Configure Pin 2.4 GPIO for PWM output
    P2->SEL0 |= (BIT4 | BIT5 | BIT6 | BIT7);
    P2->SEL1 &=~(BIT4 | BIT5 | BIT6 | BIT7);           // P2.4 set TA0.1
    P2->DIR  |= (BIT4 | BIT5 | BIT6 | BIT7);           //Output

    TIMER_A0->CCR[0]  = 60000;                          // PWM Period (# cycles of clock)
    TIMER_A0->CCR[1]  = 0;                              // CCR2 PWM duty cycle
    TIMER_A0->CCR[2]  = 0;                              // CCR2 PWM duty cycle
    TIMER_A0->CCR[3]  = 0;                              // CCR2 PWM duty cycle
    TIMER_A0->CCR[4]  = 0;                              // CCR2 PWM duty cycle
    TIMER_A0->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;         // CCR1 reset/set mode 7
    TIMER_A0->CCTL[2] = TIMER_A_CCTLN_OUTMOD_7;         // CCR1 reset/set mode 7
    TIMER_A0->CCTL[3] = TIMER_A_CCTLN_OUTMOD_7;         // CCR1 reset/set mode 7
    TIMER_A0->CCTL[4] = TIMER_A_CCTLN_OUTMOD_7;         // CCR1 reset/set mode 7
    TIMER_A0->CTL     = 0b0000001000010100;             // SMCLK, Up Mode, clear TAR to start
}

void Button_Init(void)
{
    /*-----------------------------------------------------------------------
     |  Function Button_Init
     |
     |  Purpose:  Initialize all Buttons
                   Claw, DC Motor E stop, and LED Toggle
     |
     |  Parameters:     N/A
     |
     |
     |  Returns:        N/A
     *-------------------------------------------------------------------*/
    //******CLAW BUTTON****//
    //P3.6 pull up resistor
    //******DC E STOP******//
    //P1.7  E STOP (pull up)
    //P1.6 -    LED TOGGLE (pull up)

    //CONFIGURE PIN 3.6 INTERNAL PULL UP RESISTORS
    P3->SEL0 &=~ (BIT6);
    P3->SEL1 &=~ (BIT6);
    P3->DIR  &=~ (BIT6);
    P3->REN  |=  (BIT6);      // Enable Internal  resistor
    P3->OUT  |=  (BIT6);      // Enable pull-up resistor (P3.6 output high)
    P3->IES  |=  (BIT6);      //Set pin interrupt to trigger when it goes from high to low
    P3->IE   |=  (BIT6);      // Enable interrupt for P3.6
    P3->IFG   = 0;            // Clear all P3 interrupt flags

    //CONFIGURE PIN 1.6, 1.7 INTERNAL PULL UP RESISTORS
    P1->SEL0 &=~ (BIT6 | BIT7);
    P1->SEL1 &=~ (BIT6 | BIT7);
    P1->DIR  &=~ (BIT6 | BIT7);
    P1->REN  |=  (BIT6 | BIT7);      // Enable Internal  resistor
    P1->OUT  |=  (BIT6 | BIT7);      // Enable pull-up resistor (P1.6 output high)
    P1->IES  |=  (BIT6 | BIT7);      //Set pin interrupt to trigger when it goes from high to low
    P1->IE   |=  (BIT6 | BIT7);      // Enable interrupt for P1.6
    P1->IFG   = 0;                   // Clear all P1 interrupt flags

}

void UpdateArmPos (void)
{
    /*-----------------------------------------------------------------------
     |  Function UpdateArmPos
     |
     |  Purpose:  Reads the stored ADC values and convers them to a duty cycle between 1-2ms for each of the
                     servos for the robotic arm.
     |
     |  Parameters:     N/A
     |
     |
     |  Returns:        N/A
     *-------------------------------------------------------------------*/
    float baseVar = ADC14->MEM[5];
    float arm1 = ADC14->MEM[1];
    float arm2 =ADC14->MEM[0];
    TIMER_A0->CCR[1]  = (baseVar / 256) * 6000;
    TIMER_A0->CCR[2]  = (arm1 / 256) * 6000;
    TIMER_A0->CCR[3]  = (arm2 / 256) * 6000;
}


void PORT3_IRQHandler (void)
{
    /*-----------------------------------------------------------------------
     |  Function Port3_IRQHandler
     |
     |  Purpose:  Activates function when a port 3 interrupt is recieved
     |              Toggles the Claw position between open/ closed and the green / Red
     |              LED between on / off.
     |
     |  Parameters:     N/A
     |
     |
     |  Returns:        N/A
     *-------------------------------------------------------------------*/
    SysTick_delay_ms(100); //Wait for low
    //P6.5 RED LED
    //P6.4 GREEN LED
    if (P3->IFG  & BIT6)
    {
        if (indicator == 0 )
        {
            TIMER_A0->CCR[4]  = 6000;
            P6 -> OUT &=~ BIT5;     //RED LED OFF
            P6 -> OUT |= BIT4;      //GREEN LED ON
            indicator = 1;
        }
        else if (indicator == 1)
        {
            TIMER_A0->CCR[4]  = 3000;
            P6 -> OUT |= BIT5;     //RED LED OFF
            P6 -> OUT &=~ BIT4;      //GREEN LED ON
            indicator =0;
        }
    }
    P3->IFG   = 0;                   // Clear all P3 interrupt flags
}
