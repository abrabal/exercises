#include <stdio.h>
#include <assert.h>
#include <limits.h>

unsigned short rightrot(unsigned short x, int n){
    unsigned short mask = ((1 << n) - 1);
    unsigned short subarg = x & mask;
    unsigned short finarg = subarg << (16 - n);
    unsigned short result = finarg | (x >> n);
    printf("result = %hu\n", result);
    return result;
}

int main()
{

    //rightrot(0b10100, 3);

    assert(rightrot(0b0, 5) == 0);
    assert(rightrot(0b10100, 3) == 0b1000000000000010);
    assert(rightrot(0b11111, 6) == 31744);
    assert(rightrot(0b111, 8) == 1792);

    return 0;
}