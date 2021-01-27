#include "stats_lib.h"
#define MAXCHAR 1000
#include <math.h>


float maximum(float nums[], int n) {
    int i = 0;
    float max;

    for (i; i < (n-1); i++) {

            if (max < nums[i]) {
                max = nums[i];
            }
    }

    return(max);
}

float minimum(float nums[ ], int n) {
    int i = 0 ;
    float min = 100000;

    for (i; i < (n-1); i++) {
            if (nums[i] < min)
                min = nums[i];

    }
    return(min);
}

float mean(float nums[ ], int n) {
    int i=0;
    float mean;

    for(i; i < (n-1); i++) {
        mean = mean + nums[i];
    }
    mean = (mean / i);

    return(mean);
}

float median(float nums[ ], int n) {
    int temp;
    int i, j;

    //swaps values in array[] to put them in ascending order for median calculation
    for(i=0; i<n-1; i++) {
        for(j=i+1; j<n-1; j++) {
            if(nums[j] < nums[i]) {

                temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }
        }
    }

    if(i%2==0) {

        return((nums[n/2] + nums[i/2 - 1]) / 2.0);
    } else {

        return nums[i/2];
    }
}



float variance(float nums[ ], int n) {
    int i=0;
    float sum, variance;



        for(i = 0; i < (n-1); i++) {
        sum = sum + pow((nums[i] - mean(nums, n)) , 2 );

        }

        variance = (sum / (n-2));

    return(variance);
}


float standard_deviation(float nums[], int n) {
       float SD;

       SD = pow( (variance(nums, n)) , .5);

    return(SD);
}



