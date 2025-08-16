#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LIM 1000

int main(int argc, char *argv[])
{
    int first_col = 0;
    int tab_stop = 0;

    if (argc != 1) {
        for (int i = 1; i < argc; i++){
            first_col = (*argv[i] == '-') ? atoi(argv[i]) : first_col;
            first_col *= (first_col < 0) ? -1 : 1;
            tab_stop = (*argv[i] == '+') ? atoi(argv[i]) : tab_stop;
        }
    } else {
        first_col = 0;
        tab_stop = 4;
    }

    int c;
    int col = 0;
    int next_tab_stop = 0;

    while(1){
        c = getchar();
        if (c == EOF){
            break;
        }
        if (col < first_col){
            putchar(c);
            col++;
        } else if (c == 't' && col >= first_col){
            next_tab_stop = (col - (col % tab_stop)) + tab_stop;
            while (col != next_tab_stop){
                putchar(' ');
                col++;
            }
        } else {
            putchar(c);
            col++;
        }

    }

    return 0;
}