#include <stdio.h>
#include <limits.h>

#define LIMIT 1000

void convert_to_string(int n, char str[]){
    unsigned numb = 0;
    static int i = 0;

    if (n < 0){
        str[i] = '-';
        i++;
        numb = -n;
    } else {
        numb = n;
    }
     
    if (numb / 10){
        convert_to_string((numb / 10), str);
    }

    str[i++] = (numb % 10 + '0');

}

int main()
{
    char number[LIMIT] = {0};
    int n = INT_MIN;

    convert_to_string(n, number);
    printf("%s\n", number);

    return 0;
}