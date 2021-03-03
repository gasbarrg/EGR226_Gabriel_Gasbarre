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
        commandWrite(0b0110);                       //reset display shift
        delay_micro(100);
        //printName();
        //delay_ms(500);

        LCD_Reset();
        delay_micro(100);

        scroll();
        commandWrite(0b0110);                       //reset display shift
        delay_micro(100);

        LCD_Reset();
        delay_ms(500);

    }
}
