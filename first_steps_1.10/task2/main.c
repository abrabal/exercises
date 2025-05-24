#include <stdio.h>
#include <string.h>

#define TAB 2
#define LIM 1000

int main()
{
    char str[LIM] = {0};
    char newStr[LIM] = {0};
    int emptyCheck, len;

    emptyCheck = 1;
    len = 0;

    while(fgets(str, sizeof(str), stdin)){
        len = strlen(str);
        for (int i = 0; i < len - 1; i++){
            if (str[i] != ' '){
                emptyCheck--;
                break;
            }
        }
        if (emptyCheck){
            int tlim = (len - 1) / TAB;
            int slim = (len - 1) % TAB;
            int i, j;
            i = j = 0;
            for (i = 0; i < tlim; i++){
                newStr[i] = 't';
            }
            for (int j = 0; j < slim; j++){
                newStr[i + j] = 's';
            }
            printf("%s\n", newStr);
            memset(newStr, 0, sizeof(newStr));
        } else {
            printf("%s", str);
            emptyCheck = 1;
        }
    }

    return 0;
}