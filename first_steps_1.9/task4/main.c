#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int getlinelength (char line[], int maxline, char flag[]);
void reverseline (char from[], char to[], int len);

int main ()
{
    char line[MAXLINE] = {0};
    char revline[MAXLINE] = {0};
    char flag[1] = {0};
    int len = 0;

    while (1){
        len = getlinelength(line, MAXLINE, flag);
        fprintf(stderr, "%s", line);
        reverseline(line, revline, len);
        printf("%s", revline);
        memset(line, 0, sizeof(line));
        memset(revline, 0, sizeof(revline));
        if (flag[0] == 1){
            break;
        }

    }

    return 0;
}

int getlinelength (char s[], int lim, char EOFflag[])
{
    int c, i;

    for (i = 0; i < lim; i++){
        c = getchar();
        if ( c == EOF){
            EOFflag[0] = 1;
            return i;
        } else if ( c == '\n'){
            break;
        }
        s[i] = c;
    }

    return i;
}

void reverseline (char from[], char to[], int len){
    for (int i = 0; i < len; i++){
        to[i] = from[len - 1 - i];
    }
    to[len] = '\n';
    to[len+1] = '\0';
}