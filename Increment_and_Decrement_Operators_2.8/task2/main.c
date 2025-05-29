#include <stdio.h>
#include <string.h>

#define LIMIT 1000

int find_first_match(char string1[], char string2[]){
    int string1_length, string2_length;

    string1_length = strlen(string1);
    string2_length = strlen(string2);

    for (int i = 0; i < string1_length - 1; i++){
        for(int j = 0; j < string2_length; j++){
            if (string1[i] == string2[j]){
                return i;
            }
        }
    }
    return -1;
}

int main()
{
    char str1[LIMIT] = {0};
    char str2[LIMIT] = {0};
    int number = 0;

    while (1){
        if (fgets(str1, sizeof(str1), stdin) == NULL){
            break;
        }
        if (fgets(str2, sizeof(str2), stdin) == NULL){
            break;
        }
        number = find_first_match(str1, str2);
        if (number == -1){
            printf("No coincidence\n");
        }else{
            printf("coincidence in %d position\n", number);
        }
    }

    return 0;
}