/*
 * LCD_Library.c
 *
 *  Created on: Feb 27, 2021
 *      Author: Gasba
 */
#include "msp.h"
#include "Timer_Library.h"
#include "stdio.h"


//Certain define functions. initialized here because of occastional issues when initialized in header file.
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



void PulseEnablePin(void) {
    // make sure pulse starts out at 0V
    P4 -> OUT &=~BIT2;
    delay_micro(10);

    //High
    P4 -> OUT |=BIT2;
    delay_micro(10);

    //Low
    P4 -> OUT &=~BIT2;
    delay_micro(10);
}

void pushNibble (uint8_t nibble){
    // clear P4.4-P4.7
    P4 -> OUT &=~ (BIT3 | BIT4 |BIT5 | BIT6 | BIT7);
    //Push values of MSB
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
    //INITIALIZE ALL PINS
    P4 -> SEL0 &=~ (BIT0 | BIT1 | BIT2 | BIT4 |BIT5 | BIT6 | BIT7);
    P4 -> SEL1 &=~ (BIT0 | BIT1 | BIT2 | BIT4 |BIT5 | BIT6 | BIT7);
    //ALL PINS OUTPUT
    P4 -> DIR |= (BIT0 | BIT1 | BIT2 | BIT4 |BIT5 | BIT6 | BIT7);
    delay_ms(60);


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

    //display ON cursor ON blinking OFF
    commandWrite(0x0E);
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
      //Optional code to go to next line while printing. (NOTE: DOES NOT GO IN ORDER. GOES LINE 1 > 3 > 2 > 4)
       if (i == 16){
           commandWrite(0xC0);
            delay_micro(100);
        }
        dataWrite(str[i]);
        delay_micro(100);
    }
}

void printTemp(float C)
{
    char ch=0b11011111;
    char str[30];
    char str2[10];
    float F = (C *((float)9/5) +32);

    //Print temp in C
    sprintf(str, "Current Temp is     %.2f%cC ",C,ch);
    writeString(str);
    delay_micro(100);
    commandWrite(0x90);
    delay_micro(100);

    sprintf(str2,"    %.2f%cF" ,F,ch);
    writeString(str2);
    delay_micro(100);
    commandWrite(cursorHome);
    delay_micro(100);
}


void printName(void){

    char FirstName[] = "    Gabriel";
    char LastName[] = "    Gasbarre";
    char EGR[] = "      EGR";
    char EGR2[] = "      226";

    //Print first name, move to next line
    writeString(FirstName);
    delay_micro(100);
    commandWrite(Line2);
    delay_micro(100);

    //print lastname, move to next line
    writeString(LastName);
    delay_micro(100);
    commandWrite(Line3);
    delay_micro(100);

    //Print "EGR" move to next line
    writeString(EGR);
    delay_micro(100);
    commandWrite(Line4);
    delay_micro(100);
    //Print "226" move to next line
    writeString(EGR2);
    delay_micro(100);

}

void scroll (void){
    char *message[] = {"L","A","B","O","R","A","T","O","R","Y", " ", "O","V","E","R", " "," "," "," "," "," "," "," "," "," "," "," "," "," "," "," ",};
    int i= 0;
    int j = 0;
    int k = 0;

    //increment cursor
    commandWrite(0x6);
    delay_micro(100);

    for (i=0; i<16; i++){
        //Reset LED after each message print
        LCD_Reset();
        delay_micro(100);
        //Print 15 characters, while "dropping" the first character after each loop.
        for (j=0; j < 15; j++){
        writeString(message[j+i]);
        delay_micro(100);
        delay_micro(100);
        }
        delay_ms(1000);

    }
    //Reset LED and J variable
    j = 0;
    LCD_Reset();

    //Print 16 spaces, then 15 spaces and one character, then 14 spaces and 2 characters and so on to give the appearance of scrolling riight to left.
        for(i=0; i < 15; i++){
            for (j=i; j < 16; j++){
                writeString(message[10]);   //mesage[10] variable is a space
                    delay_micro(100);
            }


            for (k=0; k <= i; k++){
                writeString(message[k]);
                delay_micro(100);
            }
            delay_ms(1000);
            LCD_Reset();
        }
}

