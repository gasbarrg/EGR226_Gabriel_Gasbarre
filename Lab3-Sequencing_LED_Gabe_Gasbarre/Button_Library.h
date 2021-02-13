/*
 * Button_Library.h
 *
 *  Created on: Feb 10, 2021
 *      Author: Gabriel Gasbarre
 *
 *      All button function declarations. Includes Pins 1.1 and 1.4 initialization and input debouncing detection.
 */

#ifndef BUTTON_LIBRARY_H_
#define BUTTON_LIBRARY_H_

void Button_init();
int Port1_Input(void);
int Port14_Input(void);

#endif /* BUTTON_LIBRARY_H_ */
