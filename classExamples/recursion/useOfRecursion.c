/*
    Use of Recursion
        1. Quick Sort
        2. Merge Sort
        3. Brute Force

    Permutations
        Traveling Salesperson Problem
            we know every citr has to be visitied once
            we knoe the travel time between every pair of cities

            find the shortest path to visit all cities in order

            using recursion we can create a number of loops equal to the number of cities
                for
                    for
                        for
                            for
                                for
                                    etc...
            Looper(N)
                for(...) (basecase, if N == 0 return)
                    Looper(N=1)




*/

#include <stdio.h>
#include <stdlib.h>


void printPerm(int * perm, int numLoops, int numCities)
{
    if (numLoops == 0)
    {
        for (int i = 0; i < numLoops; i++)
        {
            printf("%d ", perm[i]);
        }
        return;
    }


    int index = numCities - numLoops;
    for (int i = 0; i < numCities; i++)
    {
        perm[index] = i;

        int validityFlag = 1;
        
        for (int j = 0; j < index; j++)
        {
            if (perm[j] == perm[index])
            {
                validityFlag = 0;
                break;
            }
        }
        
        if (validityFlag)
        {
            printPerm(perm, numLoops - 1, numCities);
        }
        
}

int main()
{

    int array[5];
    printPerm(array, 5, 5);


    return 0;
}