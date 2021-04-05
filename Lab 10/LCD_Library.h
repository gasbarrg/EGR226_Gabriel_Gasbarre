/*
 * LCD_Library.h
 *
 *  Created on: Feb 27, 2021
 *      Author: Gasba
 */

#ifndef LCD_LIBRARY_H_
#define LCD_LIBRARY_H_

void LCD_Init(void);
void PulseEnablePin(void);
void pushNibble (uint8_t nibble);
void pushByte(uint8_t byte);
void commandWrite (uint8_t command);
void dataWrite(uint8_t data);
void LCD_Reset(void);
void writeString(char str[]);
void printName(void);
void scroll (void);
void printTemp(float C);

#define clearDisplay   0x01
#define cursorHome  0x02
#define nextLine 0xC0




#endif /* LCD_LIBRARY_H_ */
