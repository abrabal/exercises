#include <stdio.h>
#include <string.h>

#define LIMIT 1000

void string_cat (char *source, char *result){
    int length = strlen(source);
    source += (length - 1);
    while(*result != 0){
        *source = *result;
        source++;
        result++;
    }

}

int main()
{
    char source[LIMIT] = {0};
    char result[LIMIT] = " i am string";

    while(fgets(source, sizeof(source), stdin)){
        string_cat(source, result);
        printf("%s\n", source);
    }

    return 0;
}