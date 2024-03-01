#include <stdio.h>
#include <stdlib.h>

#define TRIES 1000
#define LEN 100000


// check if a target value is in a sorted array
// return 1 of the tar value is in the array
// return 0 otherwise

int contains(int * arr, int len, int tar)
{

    int lo = 0; // inclusive index
    int hi = len; // exculsive index

    // repeatedly search
    while(lo <= hi)
    {
        int mid = (lo + hi) /  2; // mid index
        if ( arr[mid] == tar) return 1;
        if (arr[mid] < tar) 
        {
            lo = mid + 1;
        } 
        else // mid is larger
        {
            hi = mid;
        }
    }   

    return 0;
}

int main()
{
    int * arr = (int *)malloc(LEN * sizeof(int));
    arr[0] = 0;
    for (int i = 0; i < LEN; i++)
    {
        arr[i] = arr[i-1] + rand() % 100 + 1;
    }
    int max = arr[LEN -1 ];

    for (int i = 0; i < TRIES; i++)
    {
        int val = rand() % (max + 1);
        if (contains(arr, LEN, val))
        {
            printf("Found %d\n", val);
        }
        
    }
    
    



    return 0;
}