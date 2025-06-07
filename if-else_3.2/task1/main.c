#include <stdio.h>

int binsearch(int x, int v[], int n)
{
    int low = 0;
    int high = n - 1;
    int mid = (low + high)/2;

    while (low < high && x != v[mid]){

        if (x < v[mid]){
            high = mid - 1;
            mid = (low + high)/2;
        }
        else{
            low = mid + 1;
            mid = (low + high)/2;
        }

    }

    if (x == v[mid]){
        return mid;

    } 

    return -1;
}

int main()
{
    int arr[] = {2, 4, 6, 7, 9, 29, 45, 46, 49, 50, 51};
    printf("%d\n", binsearch(3, arr, 11));


    return 0;
}