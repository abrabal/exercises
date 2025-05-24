#include <stdio.h>

#define MAXLENGTH 10

int main()
{
    int c, i;

    i = 0;

    while (1){
        c = getchar();
        if (c == EOF){
            break;
        }
        if (c != ' ' && c != '\t'){
            putchar(c);
        }
        if (i == MAXLENGTH -1){
            putchar('\n');
            i = 0;
        } 
        i++;
    }

    return 0;
} 