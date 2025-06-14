#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define LIMIT 1000

double atof(char s[])
{
    double val, power;
    int i, sign;
    int power_sign = 1;

    for (i = 0; isspace(s[i]); i++) 
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++)
    {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }
    val = val / power;

    if (s[i] == 'e'){
        i++;
       switch(s[i]){
            case '+':
                i++;
                break;
            case '-':
                i++;
                power_sign = -1;
                break;
            default:
                break;
       }
       for (power = 0; isdigit(s[i]); i++){
            power = 10 * power + (s[i] - '0');
       }
       power = power_sign * power;
       val = (pow(10, power) * val);
    }

    return sign * val;
}

int main()
{
    char string[LIMIT] = {0};
    double result = 0;

    while (1){
        if (fgets(string, sizeof(string), stdin) == NULL){
            break;
        }
        result = atof(string);
        printf("%f\n", result);
    }

    return 0;
}