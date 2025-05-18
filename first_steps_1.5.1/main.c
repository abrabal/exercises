#include <stdio.h>

int main()
{
    int c;

    while ((c = getchar()) != EOF){
        putchar(c);
        printf("%d\t%d\n", c != EOF, EOF);
    }

    printf("\n%d\n", c != EOF);

    return 0;
}