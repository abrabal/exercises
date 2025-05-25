#include <stdio.h>
#include <string.h>

#define LIMIT 1000

void squeeze(char str1[], char str2[]){
    int line1_length, line2_length, remove, k;
    
    line1_length = strlen(str1);
    line2_length = strlen(str2);
    k = 0;

    for (int i = 0; i < line1_length; i++){
        remove = 0;
        for(int j = 0; j < line2_length; j++){
            if (str1[i] == str2[j]){
                remove = 1;
                break;
            }
        }
        if(remove == 0){
            str1[k] = str1[i];
            k++;
        }
    }
    str1[k] = '\0';
}

int main()
{
    char line1[LIMIT] = {0};
    char line2[LIMIT] = {0};

    while (fgets(line1, sizeof(line1), stdin)){
        fgets(line2, sizeof(line2), stdin);
        squeeze(line1, line2);
        printf("%s\n", line1);
        memset(line1, 0, sizeof(line1));
        memset(line2, 0, sizeof(line2));

    }

    return 0;
}