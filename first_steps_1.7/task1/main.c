#include <stdio.h>

float fahrtocels (float fahrenheit);

int main()
{
    int upper, step;
    
    upper = 300;
    step = 20;

    for (float fahr = 0; fahr <= upper; fahr = fahr + step){
        printf("F: %.0f\tC: %.1f\n", fahr, fahrtocels(fahr));
    }

    return 0;
}

float fahrtocels (float fahr)
{
    float c;

    c = (fahr - 32.0)/1.8;

    return c;
}