#include "res_library.h"
#include <string.h>
#include <stdio.h>

void getColorBands(char* c1, char* c2, char* c3, char* c4){

    int i=0;
    char errorCheck[24] = {'K', 'k', 'N', 'n', 'R', 'r', 'O', 'o', 'Y', 'y', 'G', 'g', 'B', 'b', 'V', 'v', 'E', 'e', 'W', 'w', 'D', 'd', 'S', 's'};

    printf("Input the four characters for the corresponding band colors\n");
    printf("1.)");
    scanf(" %c", c1);
            while (strchr(errorCheck, *c1) == NULL ) {
                printf("invalid character, please try again.\n");
                scanf(" %c", c1);
            }
    printf("\n2.)");
    scanf(" %c", c2);
            while (strchr(errorCheck, *c2) == NULL ) {
                printf("invalid character, please try again.\n");
                scanf(" %c", c2);
            }
    printf("\n3.)");
    scanf(" %c", c3);
            while (strchr(errorCheck, *c3) == NULL ) {
                printf("invalid character, please try again.\n");
                scanf(" %c", c3);
            }
    printf("\n4.)");
    scanf(" %c", c4);
            while (strchr(errorCheck, *c4) == NULL ) {
                printf("invalid character, please try again.\n");
                scanf(" %c", c4);
            }


}
void calcResistance(char c1, char c2, char c3, char c4) {

    int res=0;


    if (c1 == 'K' || c1 == 'k')
        res = 0;
    else if (c1 == 'N' || c1 == 'n')
        res = 10;
    else if (c1 == 'R' || c1 == 'r')
        res = 20;
    else if (c1 == 'O' || c1 == 'o')
        res = 30;
    else if (c1 == 'Y' || c1 == 'y')
        res = 40;
    else if (c1 == 'G' || c1 == 'g')
        res = 50;
    else if (c1 == 'B' || c1 == 'b')
        res = 60;
    else if (c1 == 'V' || c1 == 'v')
        res = 70;
    else if (c1 == 'E' || c1 == 'e')
        res = 80;
    else if (c1 == 'W' || c1 == 'w')
        res = 90;


    if (c2 == 'K' || c2 == 'k')
        res = res + 0;
    else if (c2 == 'N' || c2 == 'n')
        res = res + 1;
    else if (c2 == 'R' || c2 == 'r')
        res = res + 2;
    else if (c2 == 'O' || c2 == 'o')
        res = res + 3;
    else if (c2 == 'Y' || c2 == 'y')
        res = res + 4;
    else if (c2 == 'G' || c2 == 'g')
        res = res + 5;
    else if (c2 == 'B' || c2 == 'b')
        res = res + 6;
    else if (c2 == 'V' || c2 == 'v')
        res = res + 7;
    else if (c2 == 'E' || c2 == 'e')
        res = res + 8;
    else if (c2 == 'W' || c2 == 'w')
        res = res + 9;


    if (c3 == 'K' || c3 == 'k')
        res = res * 1;
    else if (c3 == 'N' || c3 == 'n')
        res = res * 10;
    else if (c3 == 'R' || c3 == 'r')
        res = res * 100;
    else if (c3 == 'O' || c3 == 'o')
        res = res * 1000;
    else if (c3 == 'Y' || c3 == 'y')
        res = res * 10000;
    else if (c3 == 'G' || c3 == 'g')
        res = res * 100000;
    else if (c3 == 'B' || c3 == 'b')
        res = res * 1000000;
    else if (c3 == 'V' || c3 == 'v')
        res = res * 10000000;

    printf("\n\nResistance: %d     ", res);

    if (c4 == 'K' || c4 == 'k')
        printf("+-1%%");
    else if (c4 == 'N' || c4 == 'n')
          printf("+-2%%");
    else if (c4 == 'G' || c4 == 'g')
        printf("+-0.5%%");
    else if (c4 == 'B' || c4 == 'b')
        printf("+-0.25%%");
    else if (c4 == 'V' || c4 == 'v')
        printf("+-0.1%%");
    else if (c4 == 'E' || c4 == 'e')
        printf("+-0.05%%");
    else if (c4 == 'D' || c4 == 'd')
        printf("+-5%%");
    else if (c4 == 'S' || c4 == 's')
        printf("+-10%%");



}

