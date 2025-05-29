#include <stdio.h>
#include <assert.h>

int invert (int x, int p, int n){
    int submask = ~(((1 << n) - 1) << (p - (n-1)));
    int subarg = ~(x | submask);
    int finarg = x & submask;
    int result = finarg | subarg;
    printf("result = %d\n", result);

    return result;
}

int invert_optimized (int x, int p, int n){
    int mask = (((1 << n) - 1) << (p - (n - 1)));
    int result = x ^ mask;
    printf ("optimized result = %d\n", result);

    return result;
}

int main()
{
    assert(invert(0b0, 5, 3) == 0b111000);
    assert(invert(0b10100, 2, 1) == 0b10000);
    assert(invert(0b11111, 6, 4) == 0b1100111);
    assert(invert(0b111, 8, 3) == 0b111000111);

    //optimized version test

    assert(invert_optimized(0b0, 5, 3) == invert(0b0, 5, 3));
    assert(invert_optimized(0b10100, 2, 1) == invert(0b10100, 2, 1));
    assert(invert_optimized(0b11111, 6, 4) == invert(0b11111, 6, 4));
    assert(invert_optimized(0b111, 8, 3) == invert(0b111, 8, 3));

    return 0;
}
