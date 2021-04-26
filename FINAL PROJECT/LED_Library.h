/*
 * LED_Library.h
 *
 *  Created on: Apr 13, 2021
 *      Author: Gasba
 */

#ifndef LED_LIBRARY_H_
#define LED_LIBRARY_H_
volatile int dcRed, dcGreen, dcBlue;                     //DutyCycle values for each light

void LED_Init(void);
void BrightnessRed (int percent);
void BrightnessGreen (int percent);
void BrightnessBlue (int percent);
void PORT1_IRQHandler (void);

#endif /* LED_LIBRARY_H_ */
