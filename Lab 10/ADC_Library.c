/*
 * ADC_Library.c
 *
 *  Created on: Mar 24, 2021
 *      Author: gasbarrg
 */
#include "msp.h"
#include "stdio.h"
#include "Timer_Library.h"

void ADC14_init (void)
{
  ADC14-> CTL0  &=~ ADC14_CTL0_ENC;   // disable ADC converter during initialization
  ADC14-> CTL0 |=   0x04200210;      // S/H pulse mode, SMCLK, 16 sample clocks
  ADC14-> CTL1  =   0x00000030;      // 14 bit resolution
  ADC14-> CTL1 |=   0x00000000;      // convert for mem0 register
  ADC14-> MCTL[0] = 0x00000000;      // ADC14INCHx = 0 for mem[0]
  ADC14-> CTL0 |=   ADC14_CTL0_ENC;  // enable ADC14ENC, Starts the ADC after confg.
 }


void PotentiometerADC_init (void)
 {
    P5-> SEL0 |= BIT5;  // configure pin 5.5 for A0 input
    P5-> SEL1 |= BIT5;
    P5-> DIR &=~ BIT5;
}

float display_temp(void)
{
    int result;
    float nADC, tempC, tempF;
    //start conversation
    ADC14->CTL0 |= ADC14_CTL0_SC;

    //wait for conversation to complete
    while ( (!ADC14->IFGR0 & BIT0) );

    // get the value from the ADC
    result = ADC14->MEM[0];

    //solve for voltage
    nADC = (result * 3.3) / 16384;

    //solve for temperatures
    tempC = ((nADC*1000) - 500) /10;
    tempF = (tempC * ((float)9/5) + 32);

    //Return Values
    printf("Temp in C:\t%.2f\nTemp in F: \t%.2f\n\n", tempC, tempF );
    delay_ms(500);

    return tempC;
}
