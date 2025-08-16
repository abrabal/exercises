#include <stdio.h>

#define ILLEGALMONTH -1
#define ILLEGALDAY -2


static char daytab[2][13] = {
{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int get_day_of_year(int year, int month, int day){
    if (month > 12 || month < 1){
        return ILLEGALMONTH;
    }

    int leap;
    leap = ((year%4 == 0 && year%100 != 0) || year%400 == 0) ? 1 : 0;
    char *daynum = *(daytab + leap);

    if (day > *(daynum + month)){
        return ILLEGALDAY;
    }

    for (int i = 0; i < month; i++){
        day += *(daynum + i);
    }
    return day;

}

int get_month (int year, int day, int *p_month, int *p_day){
    int leap;
    leap = ((year%4 == 0 && year%100 != 0) || year%400 == 0) ? 1 : 0;

    if (leap == 1 && day > 366){
        return ILLEGALDAY;
    }
    if (leap == 0 && day > 365){
        return ILLEGALDAY;
    }
    char *daynum = *(daytab + leap);
    daynum += 1;
    int i;

    for (i = 1; day > *daynum; daynum++){
        day -= *daynum;
        i++;
    }

    *p_month = i;
    *p_day = day;

    return 0;
}

int main()
{
    int year = 1993;
    //int month = 6;
    int day = 305;

    int day_of_year = 0;
    int month_of_year = 0;

    //day = get_day_of_year(year, month, day);
    day = get_month(year, day, &month_of_year, &day_of_year);

    if (day == ILLEGALMONTH){
        printf("there is no such month\n");
        return 0;
    }
    if (day == ILLEGALDAY){
        printf("too many days\n");
        return 0;
    }

    //printf("%d day of yhe year\n", day);
    printf("%d.%d.%d\n", day_of_year, month_of_year, year);


    return 0;
}