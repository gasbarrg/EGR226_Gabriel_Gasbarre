/*
 * LCD_Library.c
 *
 *  Created on: Feb 27, 2021
 *      Author: Gasba
 */
#include "msp.h"
#include "Timer_Library.h"

#define clearDisplay   0x01
#define cursorHome  0x02
#define Line2 0xC0
#define Line3 0x90
#define Line4 0xD0
#define DisplayShiftOn 0b0111
#define DisplayShiftOff 0b0110

//PINS:
    //RS = 4.0
    //R/W = 4.1
    //E = 4.2
    //D4 = 4.4
    //D5 = 4.5
    //D6 = 4.6
    //D7 = 4.7

void SetPorts(void){
    //INITIALIZE ALL PINS
    P4 -> SEL0 &=~ (BIT0 | BIT1 | BIT2 | BIT4 |BIT5 | BIT6 | BIT7);
    P4 -> SEL1 &=~ (BIT0 | BIT1 | BIT2 | BIT4 |BIT5 | BIT6 | BIT7);
    //ALL PINS OUTPUT
    P4 -> DIR |= (BIT0 | BIT1 | BIT2 | BIT4 |BIT5 | BIT6 | BIT7);

    delay_ms(60);
}

void PulseEnablePin(void) {
    P4 -> OUT &=~BIT2;              // make sure pulse starts out at 0V
    delay_micro(10);
    P4 -> OUT |=BIT2;               //High
    delay_micro(10);
    P4 -> OUT &=~BIT2;              //Low
    delay_micro(10);
}

void pushNibble (uint8_t nibble){

    P4 -> OUT &=~ (BIT3 | BIT4 |BIT5 | BIT6 | BIT7);                 // clear P4.4-P4.7
    P4 -> OUT |=  (nibble & 0x0F) << 4 ;

    PulseEnablePin();
}

void pushByte(uint8_t byte){
    uint8_t nibble;

    nibble = (byte & 0xF0) >> 4;
    pushNibble(nibble);

    nibble = (byte & 0x0F);
    pushNibble(nibble);
    delay_micro(100);

}

void commandWrite (uint8_t command){
    P4 -> OUT &=~(BIT0);    //RS line 0 for command
    P4 -> OUT &=~(BIT1);    //R/w line 0 for write
    pushByte(command);

}

void dataWrite(uint8_t data){
    P4 -> OUT |= (BIT0);    //RS line 1 for data
    P4 -> OUT &=~(BIT1);    //R/w line 0 for write
    delay_micro(100);
    pushByte(data);
}


void LCD_Init(void){
    commandWrite(3);
    delay_ms(10);
    commandWrite(3);
    delay_micro(200);
    commandWrite(3);
    delay_ms(10);

    //Setting 4-bit mode
    commandWrite(2);
    delay_micro(100);


    //2 lines 5x7 format
    commandWrite(0x28);
    delay_micro(100);

    //display ON cursor ON blinking
    commandWrite(0x0F);
    delay_micro(100);

    //Clear display, move cursor to home pos.
    commandWrite(0x1);
    delay_micro(100);

    //increment cursor
    commandWrite(0x6);
    delay_micro(100);
}
void LCD_Reset(void){
    //Clear display, move cursor to home pos.
    commandWrite(0x1);
    delay_micro(100);

    //increment cursor
    commandWrite(0x6);
    delay_micro(100);
}


void writeString(char str[]){

    int i = 0;

    for(i = 0; str[i] != 0 ; i++){
        if (i == 16){
            commandWrite(0x06);
            delay_micro(100);
        }
        dataWrite(str[i]);
        delay_micro(100);
    }


}

void printName(void){

    char FirstName[] = "Gabriel";
    char LastName[] = "Gasbarre";
    char EGR[] = "EGR";
    char EGR2[] = "226";

    writeString(FirstName);
    delay_micro(100);
    commandWrite(Line2);
    delay_micro(100);

    writeString(LastName);
    delay_micro(100);
    commandWrite(Line3);
    delay_micro(100);

    writeString(EGR);
    delay_micro(100);
    commandWrite(Line4);
    delay_micro(100);

    writeString(EGR2);
    delay_micro(100);

}

void scroll (void){
    char message[] = "LABORATORY OVER";
    int i;

    commandWrite(0x10);                         //cursor home
    delay_micro(100);

    //increment cursor
    commandWrite(0x6);
    delay_micro(100);    //increment cursor


    writeString(message);
    delay_micro(100);



    commandWrite(DisplayShiftOn);                       //display shift on
    delay_micro(100);

    for (i=0; i<16; i++){
        delay_ms(1000);
        commandWrite(0b00011000);               //Display shift left
    }

}
