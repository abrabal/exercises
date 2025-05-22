#include <stdio.h>

#define MAXLINE 1000

int getlinelength (char line[], int maxline);



int main ()
{
    int len;
    char line[MAXLINE];

    while (len = getlinelength(line, MAXLINE)){
        if( len > 80){
            printf("%s", line);
        }
    }

    printf("\n");

    return 0;
}

int getlinelength (char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; i++){
        s[i] = c;
    }
    if (c == '\n'){
        s[i] = c;
        i++;
    }
        
    s[i] = '\0';
    return i;
}