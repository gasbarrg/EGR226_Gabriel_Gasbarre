#include "msp.h"
#include "LCD_Library.h"
#include "Timer_Library.h"
#include "stdio.h"

/**
 * main.c
 */



void main(void)
{

    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    SysTick_Init();
    SetPorts();
    LCD_Init();
    delay_micro(100);

    LCD_Reset();
    delay_micro(100);


    while (1){
       //Wait 5 seconds to display initialization function
       delay_ms(5000);
       //Print name for 5 seconds
       printName();
       delay_ms(5000);
       //Clear screen for next function
       LCD_Reset();
       delay_micro(100);
       //Display scroll message
       scroll();


       LCD_Reset();
       delay_ms(500);

    }
}
