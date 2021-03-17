/*
 * Keypad_Library.h
 *
 *  Created on: Feb 24, 2021
 *      Author: gasbarrg
 */

#ifndef KEYPAD_LIBRARY_H_
#define KEYPAD_LIBRARY_H_

void Keypad_Init(void);
int Keypad_Read(void);
int Keypad_Pin(void);
void Key_Entry(void);
char compareArray(int a[],int b[]);
int Keypad_Value(void);
#endif /* KEYPAD_LIBRARY_H_ */
