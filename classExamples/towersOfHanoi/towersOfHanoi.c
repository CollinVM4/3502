#include <stdio.h>
#include <stdlib.h>

int moves(int disks, char * src, char * dest, char * aux)
{

    // base case
    if (disks == 0)
    {
        return 0;
    }





    // recursive call
    int result = 0;
    // move (disks - 1) from src to aux, using dest
    result += moves(disks - 1, src, aux, dest);

    // move the largest disk from src to dest
    printf("Move Disk %d from %s to %s\n", disks, src, dest);
    result++;
    // move (disks -1) from aux to desst using src
    result += moves(disks - 1, aux, dest, src);

    return result;
}

#define SIZE 64

int main()
{

    printf("Number of moves: %d\n", moves(SIZE, "A", "C", "B"));

    return 0;
}