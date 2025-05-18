#include <stdio.h>
main ()
{
    float celsius, fahr;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    printf("\tCELSIUS TO FAHRENHEIT\n\n");

    celsius = lower;
    while (celsius <= upper) {
        fahr = (celsius * (9.0/5.0)) + 32.0;
        printf("\t%5.0f \t%8.1f\n", celsius, fahr);
        celsius = celsius + step;
    }
    return 0;
}