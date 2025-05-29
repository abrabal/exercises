#include <stdio.h>

int bitcount (unsigned int x){
    int b = 0;

    while (x != 0){
        b++;
        x &= (x-1);
    }

    return b;
}

int main()
{
    printf("num of 1 = %d\n", bitcount(4));
    printf("num of 1 = %d\n", bitcount(17));
    printf("num of 1 = %d\n", bitcount(1335));
    printf("num of 1 = %d\n", bitcount(127));

    return 0;
}