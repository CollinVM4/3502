#include <stdio.h>
#include <stdlib.h>


int fib(int n)
{   
    // base case
    if (n==0) return 0;
    if (n==1) return 1;

    // recursive case
    return fib(n-1) + fib(n-2);
}


int main()
{
    for (int i = 0; i < 25; i++)
    {
        printf("%d\n", fib(i));
    }

    return 0;
}