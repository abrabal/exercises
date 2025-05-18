#include <stdio.h>
int main() 
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    printf("\tFAHRENHEIT TO CELSIUS\n\n");

    fahr = lower;
    while (fahr <= upper) {
        celsius = (fahr - 32)/1.8;
        printf("\t%5.0f %8.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
    return 0;
}