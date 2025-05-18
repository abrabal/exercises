#include <stdio.h>

#define UPPER 300
#define LOWER 0
#define STEP 20

int main()
{
    int fahr;

    for (fahr = UPPER; fahr >= LOWER; fahr = fahr - STEP){
        printf("F = %3d C = %5.1f\n", fahr, (fahr - 32) * 0.5556);
    }

    return 0;
}