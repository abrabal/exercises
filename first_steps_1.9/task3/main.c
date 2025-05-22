#include <stdio.h>

#define MAXLINE 1000

int getlinelength (char line[], int maxline);

int main()
{
    char line[MAXLINE];
    int len;

    while(len = getlinelength(line, MAXLINE)){
        for (int i = (len - 2); i > 0; i--){
            if (line[i] == '\t' || line[i] == ' '){
                    line[i] = 0;
            } else {
                line[i+1] = '\n';
                line[i+2] = '\0';
                break;
            }
        }
        if (len > 1){
            printf("%s", line);
            for (int j = 0; j < len; j++){
                line[j] = 0;
            }
        } 
    }

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