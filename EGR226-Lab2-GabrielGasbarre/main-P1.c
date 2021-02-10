/**************************************************************************************
* Author: Gabriel Gasbarre
* Course: EGR 226
* Date: 01/27/2021
* Project: Lab 2 Part 1 :
* File: Lab1
* Description:
**************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "res_library.h"

void prompt(void);
void calcResistorColors(int);
int getIntBetween();



int main()
{
    char repeat;

    do {
    prompt();


    printf("\n\nWould you like to input another resistor?\n\t Y/N?\n\n");
    scanf(" %c", &repeat);

    }

    while (repeat == 'y' || repeat == 'Y' );

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
    int resistorVal;
    int choice;
    char col1, col2, col3, col4;

    printf("---------------Resistor Codes----------------------------\n");
    printf("|Character| Color | Band 1 & 2 | Band 3      | Band 4   |\n");
    printf("|    K    | Black |     0      | *1          | +/-1%%   |\n");
    printf("|    N    | Brown |     1      | *10         | +/-2%%   |\n");
    printf("|    R    | Red   |     2      | *100        |         |\n");
    printf("|    O    | Orange|     3      | *1,000      |         |\n");
    printf("|    Y    | Yellow|     4      | *10,000     |         |\n");
    printf("|    G    | Green |     5      | *100,000    | +/-0.5%%|\n");
    printf("|    B    | Blue  |     6      | *1,000,000  | +/-0.25%%|\n");
    printf("|    V    | Violet|     7      | *10,000,000 | +/-0.1%%\n");
    printf("|    E    | Grey  |     8      |             | +/-0.05%%|\n");
    printf("|    W    | White |     9      |             |          | \n");
    printf("|    D    | Gold  |            |             | +/-5%    |\n");
    printf("|    S    | Silver|            |             | +/-10%% | \n");
    printf("---------------------------------------------------------\n\n");

    printf("Would you like to \n1.) Determine the color code from a resistance value \nor \n2.)Convert a color code to a resistance?\n\n");
    printf("Enter '1' or '2'\n\n");
    scanf(" %d", &choice);


    if (choice == 1) {
    resistorVal = getIntBetween();
    calcResistorColors(resistorVal);
    }
    else if (choice == 2){
        getColorBands(&col1, &col2, &col3, &col4);
        printf("You entered: %c, %c, %c, %c", col1, col2, col3, col4);
        calcResistance(col1, col2, col3, col4);

    }
    else
        printf("Invalid choice");
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
    int j=0;
    int k;


    while(val > 100) {
        val = val / 10;
        i = i * 10;
    }
    while (val >= 10){
        val = val - 10;
        k= k + 1 ;
    }
    while (val > 0 ) {
        val--;
        j++;
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

