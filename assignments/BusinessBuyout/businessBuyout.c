/*
    - Collin Van Meter
    - Business Buyout Assignment 4
    - 3/5/24
*/


/*

    a4 layout

    quicksort 
    merge?
    


*/

#include <stdio.h>
#include <stdlib.h>


// Quick sort function
void quick_sort(int *arr, int len) 
{
    // Base Case
    if (len <= 1) 
    {
        return;
    }

    // Split the array based on the pivot (arr[0])
    int fptr = 1;
    int bptr = len - 1;

    for (int i = 1; i < len; i++) 
    {
        if (arr[0] < arr[fptr]) 
        {
            int tmp = arr[fptr]; // move to back
            arr[fptr] = arr[bptr];
            arr[bptr] = tmp;
            bptr--; // adjust the back pointer
        } 
        else 
        {
            fptr++; // stay in front
        }
    }

    // Move pivot into location
    int tmp = arr[0];
    arr[0] = arr[fptr - 1];
    arr[fptr - 1] = tmp;

    // sort the 2 parts
    quick_sort(arr, fptr - 1);
    quick_sort(arr + fptr, len - fptr);

}




// Function to print the values of an array
void print(int *arr, int len) 
{
    for (int i = 0; i < len; i++) 
    {
        printf("%2d ", arr[i]);
    }

    printf("\n");
}


int main()
{




    return 0;
}