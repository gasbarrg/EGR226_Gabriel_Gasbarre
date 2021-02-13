/*
 * LED_Library.h
 *
 *  Created on: Feb 10, 2021
 *      Author: Gabriel Gasbarre
 *
 *      All LED function declarations. LED initialization and individual Red, Green, and Blue LED control (On/Off)
 */

#ifndef LED_LIBRARY_H_
#define LED_LIBRARY_H_

void LED_init(void);

void LED_Red_ON (void);
void LED_Red_OFF(void);
void LED_Green_ON(void);
void LED_Green_OFF(void);
void LED_Blue_ON(void);
void LED_Blue_OFF(void);

#endif /* LED_LIBRARY_H_ */
