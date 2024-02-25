#include <stdio.h>
#include <stdlib.h>


int isSorted(int* array, int max, int n)
{

    if(n == 0) return 1; 

    if(array[0] > max) return 0;

    if(n > 1 && array[0] > array[1]) return 0;

    return isSorted(array + 1, max, n - 1);
}


int main()
{




    return 0;
}