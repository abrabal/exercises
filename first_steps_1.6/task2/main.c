#include <stdio.h>

int main()
{
    int c;

    int freq[94] = {0};

    while ((c = getchar()) != EOF){
        if (c >= ' ' && c <= '~'){
            ++freq[c - ' '];
        }
    }

    for (int i = 0; i < 94; i++){
        printf("%c: ", i + ' ');
        for(int j = 0; j < freq[i]; j++){
            printf("#");
        }
        printf("\n");
    }

    return 0;
}