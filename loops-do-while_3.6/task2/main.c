#include <stdio.h>
#include <string.h>
#include <limits.h>

#define LIMIT 1000

void reverse(char s[])
{
    int c, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void num_to_string(int n, char string[], int b)
{

    unsigned int numb = 0;
    int i = 0;

    if (n < 0)
    {
        numb = -n;
    }
    else
    {
        numb = n;
    }

    do
    {

        if (numb % b < 10)
        {
            string[i++] = numb % b + '0';
        }
        else
        {
            string[i++] = ((numb % b) - 10) + 'A';
        }

    } while ((numb /= b) > 0);

    if (n < 0)
    {
        string[i++] = '-';
        string[i] = '\0';
    }

    reverse(string);
}

int main()
{
    char string[LIMIT] = {0};
    int n = INT_MIN;

    num_to_string(n, string, 2);
    printf("binary = %s\n", string);
    memset(string, 0, sizeof(string));

    num_to_string(n, string, 8);
    printf("octal = %s\n", string);
    memset(string, 0, sizeof(string));

    num_to_string(n, string, 16);
    printf("hex = %s\n", string);
    memset(string, 0, sizeof(string));

    num_to_string(n, string, 10);
    printf("hex = %s\n", string);
    memset(string, 0, sizeof(string));

    return 0;
}