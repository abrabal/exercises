#include <stdio.h>
#define IN 1
#define OUT 0

int main()
{
    int c, state, wl;
    int wlength[11] = {0};

    state = OUT;
    wl = 0;

    while (1){
        c = getchar();
        if (c == ' ' || c == '\t' || c == '\n' || c == EOF){
            if (wl > 0){
                if ( wl > 10){
                    ++wlength[10];
                } else {
                    ++wlength[wl];
                    wl = 0;
                }
            }
            state = OUT;
        } else if (state == OUT){
            state = IN;
            ++wl;
        } else {
                ++wl;
            
        }
        if(c == EOF){
            break;
        }
    }

    for(int i = 0; i <= 10; i++){
        if (i == 10){
            printf("%d+: ", i);
        } else {
            printf("%d: ", i);
        }
        for(int j = 0; j < wlength[i]; j++){
            printf("#");
        }
        printf("\n");

    }

    return 0;
}