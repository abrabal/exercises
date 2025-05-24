#include <stdio.h>

#define TAB 2

int main()
{
    int c;

    while ((c = getchar())){
        if (c == '\t'){
            for(int i = 0; i < TAB; i++){
                putchar(' ');
            }
        } else if (c == EOF){
            break;
        } else {
            putchar(c);
        }
    }

    return 0;
}