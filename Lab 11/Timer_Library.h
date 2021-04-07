/*
 * Timer_Library.h
 *
 *  Created on: Feb 24, 2021
 *      Author: gasbarrg
 */

#ifndef TIMER_LIBRARY_H_
#define TIMER_LIBRARY_H_


void SysTick_Init(void);
void SysTick_Init_interrupt (void);
void SysTick_Handler(void);

void delay_micro (uint16_t delay);
void delay_ms (uint16_t ms);


void TimerA0_Init(void);
void TimerA02_Init(void);
void PORT2_IRQHandler (void);
#endif /* TIMER_LIBRARY_H_ */
