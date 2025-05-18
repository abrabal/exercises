#include <stdio.h>

int main()
{
    int c, nss;

    nss = 0;

    while ((c = getchar()) != EOF){

        if (c == ' ' || c == '\t' || c == '\n'){
            ++nss;
        }

    }

    printf("number of special symbols = %d\n", nss);
    

    return 0;
}