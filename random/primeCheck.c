#include <stdio.h>
#include <stdlib.h>




int isPrime(int x)
{
    for (int factor = 2; factor * factor <= x ; factor++)
    {
        if(x % factor == 0) return 0;
    }
    return 1;
}

// determine how many insertion can happen at the same location
// before a insertion is no longer possible
int testQuad(int size)
{
    int empty[size];

    for (int i = 0; i < size; i++)
    {
        empty[i] = 1;
    }

    int ans = 0;

    for (int i = 0; i < size; i++)
    {
        int index = (i * i) % size;
        if (empty[index])
        {
            ans++;
            empty[index] = 0;
        }
    }
    return ans;

}


int main()
{

    for (int i = 2; i < 100; i++)
    {
        if(isPrime(i))
        {
            printf("%d can insert %d values at same hash.\n", i, testQuad(i));
        }
    }


    return 0;
}