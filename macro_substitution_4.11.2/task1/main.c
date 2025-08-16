#include <stdio.h>

#define SWAP(t, x, y) { \
    t temp = x;         \
    x = y;              \
    y = temp;           \
}

int main()
{
    int x = 1;
    int y = 2;

    SWAP(int, x, y);

    printf("x = %d\n", x);
    printf("y = %d\n", y);

    return 0;
}