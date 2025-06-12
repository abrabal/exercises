#include <stdio.h>

#define LIMIT 1000

int i = 0;
int j = 0;

void  reverse_string(char src_str[], char rev_str[]){
    if (src_str[i] != '\0'){
        i++;
        reverse_string(src_str, rev_str);
    }
    rev_str[j++] = src_str[--i];
}

int main()
{
    char str_string[LIMIT] = "LOSER";
    char rev_string[LIMIT] = {0};
    reverse_string(str_string, rev_string);
    printf("%s\n", rev_string);

    return 0;
}