#include <stdio.h>
#include <assert.h>

int setbit(int x, int p, int n, int y){
    unsigned submask = ~(((1 << n) - 1) << (p - (n-1)));
    int subarg = x & submask;
    int mask = y << ((p - n) + 1);
    int result = subarg | mask;

    return result;
}

// 0b0

// n = 3

// p = 5

// y = 0b111

int main()
{
    assert(setbit(0b0, 5, 3, 0b111) == 0b111000);
    assert(setbit(0b10100, 2, 2, 0b10) == 0b10100);
    assert(setbit(0b11111, 6, 4, 0b0) == 0b111);
    assert(setbit(0b0, 8, 3, 0b111) == 0b111000000);
    return 0;
}



/*x 0 0 1 1
y 0 1 0 1
r 0 1 0 1*/