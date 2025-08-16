#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define LIMIT 1000

int match_at_end (char *source, char *match){
    int length_match = strlen(match);
    int length_source = strlen(source);
    
    source += length_source - 1;
    if (*source == '\n'){
        source -= 1;
    }

    match  += (length_match - 1);
    int state = 0;

    length_match -= 1;
    while (*source == *match){
        length_match--;
        source--;
        match--;
        if(length_match == 0){
            break;
        }
    }

    state = (length_match > 0) ? 0 : 1;

    return state;

}

int main()
{
    char source[LIMIT] = {0};
    char match[LIMIT] = "string";

    while (fgets(source, sizeof(source), stdin)){
        printf("occur state = %d\n", match_at_end(source, match));
    }

    return 0;
}