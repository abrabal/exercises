#include <stdio.h>
#include <string.h>

#define LIMIT 1000

int find_occurance(char string_source[], char string_prot[]){
    int source_length = strlen(string_source) - 1;

    int j = 0;
    int k = 0;

    for (int i = source_length; i >= 0; i--){
        for(j = i, k = 0; string_prot[k] != '\0' && string_source[j] == string_prot[k]; j++, k++){

        }
        if ( k > 0 && string_prot[k] == '\0'){
            return i;
        }
    }
    return -1;
}

int main()
{
    char string[LIMIT] = {0};
    char occur_str[LIMIT] = "Lorem";
    int pos = 0;

    while (1){
        if(fgets(string, sizeof(string), stdin) == NULL){
            break;
        }
        pos = find_occurance(string, occur_str);
        if(pos == -1){
            printf("no ocurances\n");
        }else{
            printf("occurance in %d\n", pos);
        }
        
    }

    return 0;
}