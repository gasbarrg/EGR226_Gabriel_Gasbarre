#include "msp.h"
#include "Motor_Library.h"
#include "Timer_Library.h"
#include "Button_Library.h"
#include "LED_Library.h"
#include "stdio.h"

extern volatile int percent;
extern volatile int count;

void main(void)
{
    // stop watchdog timer
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

	//Run Initialization Functions
	SysTick_Init_interrupt();
	Motor_TA_Init();
	Button_Init();
	LED_Init();
	//Enable interrupts
	NVIC->ISER[1] = 1 << ((PORT2_IRQn) & 31);       //Enable port 2 interrupts
	__enable_irq();
	__enable_interrupt();


	while (1) {
	//Begin motor control using pushbutton interrupts
	Motor_TA(percent);
	//Begin 7-segment display using pushbutton interrupts
	display(percent/10);
	//Automatically increment 7-segment display using SysTick interrupts
 	//display(count);
	}
}
