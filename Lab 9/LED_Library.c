/*
 * LED_Library.c
 *
 *  Created on: Mar 20, 2021
 *      Author: Gabe Gasbarre
 *
 *      7-Segement Display initialization function
 *      Display function that accepts integer 0 to 9 and displays that number
 *
 */
#include "msp.h"
#include "Timer_Library.h"


void LED_Init(void){
    //initialize all LED Pins:
    //A= 5.0
    //B=3.5
    //C=3.7
    //D=3.6
    //E=5.2
    //F=5.1
    //G=1.7

    //PORT 3
    P3-> SEL0 &=~(BIT5 | BIT6| BIT7);
    P3-> SEL1 &=~(BIT5 | BIT6| BIT7);
    P3-> DIR |=(BIT5 | BIT6| BIT7);
    P3-> OUT &=~(BIT5 | BIT6| BIT7);

    //PORT5
    P5-> SEL0 &=~(BIT0 | BIT1 | BIT2);
    P5-> SEL1 &=~(BIT0 | BIT1 | BIT2);
    P5-> DIR  |=(BIT0 | BIT1 | BIT2);
    P5-> OUT  &=~(BIT0 | BIT1 | BIT2);

    //PORT 1
    P1-> SEL0 &=~(BIT7);
    P1-> SEL1 &=~(BIT7);
    P1-> DIR  |=(BIT7);
    P1-> OUT  &=~(BIT7);

}

void display(int num){

    if (num == 1){
    //B and C on all else off
    P5->OUT &=~(BIT0);  //A
    P3->OUT |=(BIT5);  //B
    P3->OUT |=(BIT7);  //C
    P3->OUT &=~(BIT6);  //D
    P5->OUT &=~(BIT2);  //E
    P5->OUT &=~(BIT1);  //F
    P1->OUT &=~(BIT7);  //G
    }

    if (num == 2){
        P5->OUT |=(BIT0);  //A
        P3->OUT |=(BIT5);  //B
        P3->OUT &=~(BIT7);  //C
        P3->OUT |=(BIT6);  //D
        P5->OUT |=(BIT2);  //E
        P5->OUT &=~(BIT1);  //F
        P1->OUT |=(BIT7);  //G
    }
    if (num == 3){
        P5->OUT |=(BIT0);  //A
        P3->OUT |=(BIT5);  //B
        P3->OUT |=(BIT7);  //C
        P3->OUT |=(BIT6);  //D
        P5->OUT &=~(BIT2);  //E
        P5->OUT &=~(BIT1);  //F
        P1->OUT |=(BIT7);  //G
    }
    if (num ==4){
        P5->OUT &=~(BIT0);  //A
        P3->OUT |=(BIT5);  //B
        P3->OUT |=(BIT7);  //C
        P3->OUT &=~(BIT6);  //D
        P5->OUT &=~(BIT2);  //E
        P5->OUT |=(BIT1);  //F
        P1->OUT |=(BIT7);  //G
    }
    if (num ==5){
        //A,F,G,C,D
        P5->OUT |=(BIT0);  //A
        P3->OUT &=~(BIT5);  //B
        P3->OUT |=(BIT7);  //C
        P3->OUT |=(BIT6);  //D
        P5->OUT &=~(BIT2);  //E
        P5->OUT |=(BIT1);  //F
        P1->OUT |=(BIT7);  //G
    }
    if (num ==6){
        //A,F,G,E,C,D
        P5->OUT |=(BIT0);  //A
        P3->OUT &=~(BIT5);  //B
        P3->OUT |=(BIT7);  //C
        P3->OUT |=(BIT6);  //D
        P5->OUT |=(BIT2);  //E
        P5->OUT |=(BIT1);  //F
        P1->OUT |=(BIT7);  //G
    }
    if (num ==7){
        //A,B,C
        P5->OUT |=(BIT0);  //A
        P3->OUT |=(BIT5);  //B
        P3->OUT |=(BIT7);  //C
        P3->OUT &=~(BIT6);  //D
        P5->OUT &=~(BIT2);  //E
        P5->OUT &=~(BIT1);  //F
        P1->OUT &=~(BIT7);  //G
    }
    if (num ==8){
        //A,B,C,D,E,F
        P5->OUT |=(BIT0);  //A
        P3->OUT |=(BIT5);  //B
        P3->OUT |=(BIT7);  //C
        P3->OUT |=(BIT6);  //D
        P5->OUT |=(BIT2);  //E
        P5->OUT |=(BIT1);  //F
        P1->OUT |=(BIT7);  //G
    }
    if (num ==9){
        //A,B,C,G,F
        P5->OUT |=(BIT0);  //A
        P3->OUT |=(BIT5);  //B
        P3->OUT |=(BIT7);  //C
        P3->OUT &=~(BIT6);  //D
        P5->OUT &=~(BIT2);  //E
        P5->OUT |=(BIT1);  //F
        P1->OUT |=(BIT7);  //G
    }
    if (num ==0){
        //F,A,B,C,D,E
        P5->OUT |=(BIT0);  //A
        P3->OUT |=(BIT5);  //B
        P3->OUT |=(BIT7);  //C
        P3->OUT |=(BIT6);  //D
        P5->OUT |=(BIT2);  //E
        P5->OUT |=(BIT1);  //F
        P1->OUT &=~(BIT7);  //G
    }
}






