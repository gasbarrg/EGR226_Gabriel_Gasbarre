/**************************************************************************************
* Author: Gabriel Gasbarre
* Course: EGR 226
* Date: 01/20/2021
* Project: Lab 1 Part 1 : Resistor Analysis Tool
* File: Lab1
* Description: This program accepts an integer input that represents the ohms desired for a resistor.
* The program accepts the input and will display the resulting 3 bands that equate to the resistor
* with the same ohm reading.
**************************************************************************************/




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void prompt(void);
void calcResistorColors(int);
int getIntBetween();
int resistorVal;


int main()
{
    char repeat;

    do {
    prompt();
    calcResistorColors(resistorVal);

    printf("\n\nWould you like to input another resistor?\n\t Y/N?\n\n");
    scanf(" %c", &repeat );

    }   while (repeat == 'y' || repeat == 'Y' );

    return 0;
}




void prompt (void) {
/****| Prompt | *****************************************
* Brief: Displays Ohm values for resistors and asks what resistor
* value the user would like to input.
* param: resistorVal
*
* return: void
*
*************************************************************/

    printf("---------------Resistor Codes-----------------\n");
    printf("|Character| Color | Band 1 & 2 | Band 3      |\n");
    printf("|    K    | Black |     0      | *1          |\n");
    printf("|    N    | Brown |     1      | *10         |\n");
    printf("|    R    | Red   |     2      | *100        |\n");
    printf("|    O    | Orange|     3      | *1,000      |\n");
    printf("|    Y    | Yellow|     4      | *10,000     |\n");
    printf("|    G    | Green |     5      | *100,000    |\n");
    printf("|    B    | Blue  |     6      | *1,000,000  |\n");
    printf("|    V    | Violet|     7      | *10,000,000 |\n");
    printf("|    E    | Grey  |     8      |             |\n");
    printf("|    W    | White |     9      |             |\n");
    printf("|    D    | Gold  |            |             |\n");
    printf("|    S    | Silver|            |             |\n");
    printf("---------------------------------------------\n\n");

    resistorVal = getIntBetween();

}

int getIntBetween() {
    int val;

    printf("\nWhat resistance should be color coded?\n");
    scanf("%d", &val);

    if (val < 99000000 && val > 0) {
        printf("Valid Integer = %d Ohms\n", val);
    }
    else {
        do{
            printf("invalid Integer, try again\n");
            scanf(" %d", &val);
        }while ( !(val < 99000000 && val > 0));
    }

    return(val);
}

void calcResistorColors(int val){
    int i=1;
    int j;
    int k;


    while(val > 100) {
        val = val / 10;
        i = i * 10;
    }
    while (val>=10){
        val = val - 10;
        k= k + 1 ;
    }
    while (val >0 ) {
        val = val - 1;
        j = j + 1;
    }


    printf("\nBand 1 = ");
        if (k == 0 )
            printf("Black");
        else if(k == 1 )
            printf("Brown");
        else if(k == 2 )
            printf("Red");
        else if(k == 3 )
            printf("Orange");
        else if(k == 4 )
            printf("Yellow");
        else if(k == 5 )
            printf("Green");
        else if(k == 6 )
            printf("Blue");
        else if(k == 7 )
            printf("Violet");
        else if(k == 8 )
            printf("Grey");
        else if(k == 9 )
            printf("white");
        else if(k == 10 ) {
            i = i * 10;
            printf("Brown");
        }

        printf("\tBand 2 = ");
        if (j == 0 )
            printf("Black");
        else if(j == 1 )
            printf("Brown");
        else if(j == 2 )
            printf("Red");
        else if(j == 3 )
            printf("Orange");
        else if(j == 4 )
            printf("Yellow");
        else if(j == 5 )
            printf("Green");
        else if(j == 6 )
            printf("Blue");
        else if(j == 7 )
            printf("Violet");
        else if(j == 8 )
            printf("Grey");
        else if(j == 9 )
            printf("white");


    printf("\tBand 3 = ");
        if (i == 1 )
            printf("Black");
        else if(i == 10 )
            printf("Brown");
        else if(i == 100 )
            printf("Red");
        else if(i == 1000 )
            printf("Orange");
        else if(i == 10000 )
            printf("Yellow");
        else if(i == 100000 )
            printf("Green");
        else if(i == 1000000 )
            printf("Blue");
        else if(i == 10000000 )
            printf("Violet");



}







