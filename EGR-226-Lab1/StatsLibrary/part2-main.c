#include <stdio.h>
#include <stdlib.h>
#include "stats_lib.h"
#define MAXCHAR 1000



int main() {
    // Reads file and saves to array[]
    FILE *fp;
    float str[MAXCHAR];
    float array[MAXCHAR];
    char* filename = "data.txt";
    int i=0;

    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }
    for ( i; !feof(fp); i++){
        fscanf(fp, "%f", &array[i]);

    }
    fclose(fp);

    //prints the functions from stats_lib.c to the console

    printf("Number of elements: %d\n\n",i);
    printf("Maximum = %f\n", maximum(array, i));
    printf("Minimum = %f\n", minimum(array, i));
    printf("Mean = %f\n", mean(array, i));
    printf("Median = %f\n", median(array, i));
    printf("Variance = %f\n", variance(array, i));
    printf("Standard Deviation = %f\n", standard_deviation(array, i));
    return 0;
}
