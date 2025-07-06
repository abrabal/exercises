#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

int getch(void);
void ungetch(int);

int getfloat(float *pn)
{
    int c, sign;
    while (isspace(c = getch()))
        ;
    if (!isdigit(c) && c != EOF && c != '-')
    {
        ungetch(c); 
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '-'){
        c = getch();
        
        if(!isdigit(c)){
            ungetch(c);
            return 0;
        }
    }
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * (*pn) + (c - '0');
    if (c == '.'){
        c = getch();
        int power = 0;
        for (; isdigit(c); c = getch()){
            power += 10;
            *pn = 10 * (*pn) + (c - '0');
        }
        printf("power = %d\n", power);
        printf("numb = %f\n", *pn);
        *pn = *pn / power;
    }
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}

int main()
{
    float x = 0;

    printf("getint = %d\n", getfloat(&x));
    printf("value of x = %f\n", x);

    return 0;
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c)

{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}