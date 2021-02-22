/*
 * Timer_Library.h
 *
 *  Created on: Feb 21, 2021
 *      Author: Gabriel Gasbarre
 *
 *      SysTick clock initialization and delay functions declarations.
 */
#include "msp.h"

#ifndef TIMER_LIBRARY_H_
#define TIMER_LIBRARY_H_

void SysTick_Init (void);
void SysTdelay (uint16_t delay);

#endif /* TIMER_LIBRARY_H_ */
