#include <stdio.h>
#include <stdlib.h>

// permutation array [0 through max - 1] filled in by preix

// used array [0 or 1] unused or used value 
// Index is the current spot to fill in the perm (start at 0)
// Max is the maximm value

void printArray(int * arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void permute_two(int * perm, int * used, int index, int max)
{
    // Base Case: when index is outside the perm
    if (index == max)
    {
        printArray(perm, max);
        return;
    }
    
    // fill a spot if index = max -1 or less than that value
    for (int v = 0; v < max; v++)
    {
        if (used[v]) continue;
        perm[index] = v; //assign the value at the index
        used[v] = 1;

        permute_two(perm, used, index + 1, max);

        // Unuse the value to use in later loop
        used[v] = 0;
    }
    
}

#define SIZE 8

int main()
{

    int perm[SIZE];
    int used[SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        perm[i] = 0;
        perm[i] = -1;
    }
    
    permute_two(perm, used, 0, SIZE);



    return 0;
}