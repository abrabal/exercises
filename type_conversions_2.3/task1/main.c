#include <stdio.h>
#include <string.h>

#define LIMIT 1000

int htoi(char line[]){
    int i = 0;
    int len = strlen(line);
    int result;

    if ((line[0] == '0' && line[1] == 'x') || line[1] == 'X'){
        i = 2;
    }
    for(int j = i; j < len -1; j++){
        if ((line[j] >= '0' && line[j] <= '9')){
            result = 16 * result + line[j] - '0';
        } else if((line[j] >= 'a' && line[j] <= 'f')){
            result = 16 * result + ((line[j] - 'a') + 10);
        } else if((line[j] >= 'A' && line[j] <= 'F')){
            result = 16 * result + ((line[j] - 'A') + 10);
        } else{
            return -1;
        }   
    }
    return result;
}

int main()
{
    char line[LIMIT] = {0};
    int number = 0;

    while(fgets(line, sizeof(line), stdin)){
        number = htoi(line);
        if (number == -1){
            printf("ERROR\n");
            break;
        }
        printf("%s%d\n", line, number);
        memset(line, 0, sizeof(line));
    }

    return 0;
}