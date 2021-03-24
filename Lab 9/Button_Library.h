/*
 * Button_Library.h
 *
 *  Created on: Mar 20, 2021
 *      Author: Gasba
 */

#ifndef BUTTON_LIBRARY_H_
#define BUTTON_LIBRARY_H_

extern volatile int percent;


void Button_Init(void);
void PORT2_IRQHandler(void);
void Motor_Control(int);

#endif /* BUTTON_LIBRARY_H_ */
