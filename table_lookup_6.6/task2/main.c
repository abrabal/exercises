#include <stdio.h>

int main()
{
    int mask = 1;
    int num = 1234;
    int bit_count = 0;
    while (num != 0){
        if ((num & mask) > 0){
            bit_count += 1;
        }
        num = num >> 1;
    }
    printf("%d\n", bit_count);
    return 0;
}