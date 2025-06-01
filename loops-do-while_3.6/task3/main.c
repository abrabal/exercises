#include <stdio.h>
#include <string.h>
#include <limits.h>

#define LIMIT 1000

void reverse(char s[])
{
int c, i, j;
for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
c = s[i];
s[i] = s[j];
s[j] = c;
}
}

void num_to_string(int n, char string[], int b, int field_width){

    unsigned int numb = 0;
    int i = 0;
    int line_length = 0;
    int space_num = 0;

    if (n < 0){
        numb = -n;
    } else {
        numb = n;
    }

    do {

        if (numb % b < 10){
            string[i++] = numb % b + '0';
        } else {
            string[i++] = ((numb % b) - 10) + 'A';
        }

    } while ((numb /= b) > 0);

    if(n < 0){
        string[i++] = '-';
        string[i] = '\0';
    }

    line_length = strlen(string);

    if (line_length < field_width){
        space_num = field_width - line_length;
        for (int j = 0; j < space_num; i++, j++){
            string[i] = ' ';
        }
    }
    reverse(string);
}

int main()
{
    char string[LIMIT] = {0};
    int n = -255;

    num_to_string(n, string, 2, 20);
    printf("%s\n", string);
    memset(string, 0, sizeof(string));

    num_to_string(n, string, 8, 20);
    printf("%s\n", string);
    memset(string, 0, sizeof(string));

    num_to_string(n, string, 16, 20);
    printf("%s\n", string);
    memset(string, 0, sizeof(string));

    num_to_string(n, string, 10, 20);
    printf("%s\n", string);
    memset(string, 0, sizeof(string));

    return 0;
}