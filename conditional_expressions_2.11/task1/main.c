#include <stdio.h>

char to_lower_reg (char c){
    c = (c >= 65 && c <= 90) ? c + 32 : c;
    return c;
}

int main ()
{
    int c;

    while (1){
        c = getchar();
        printf ("%c", to_lower_reg(c));
        if (c == EOF)
        break;
    }

    return 0;
}