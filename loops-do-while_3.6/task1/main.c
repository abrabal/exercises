// CODE WAS COPIED FROM DA BOOK, ALL QUESTIONS TO THE AUTHORS!

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

void itoa(int n, char s[])
{
    int i, sign;
    unsigned int numb;
    if ((sign = n) < 0)
    {
        numb = -n;
    }
    else
    {
        numb = n;
    } /* record sign */

    /* make n positive */
    i = 0;
    do
    {
        /* generate digits in reverse order */
        s[i++] = numb % 10 + '0'; /* get next digit */
    } while ((numb /= 10) > 0);
    /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int main()
{
    char string_numb[LIMIT] = {0};
    int numb = INT_MIN;

    itoa(numb, string_numb);

    printf("%s\n", string_numb);

    return 0;
}