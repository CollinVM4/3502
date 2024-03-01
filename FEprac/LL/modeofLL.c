#include <stdio.h>
#include <stdlib.h>



typedef struct node 
{
    int value;
    struct node* next;
} node;

#define MAX 1000

int mode(node* front) 
{
    int freq[MAX], i; // declare vars

    // initilize the array with 0's 
    for (i=0; i<MAX; i++)
        freq[i] = 0;


    while (front != NULL) 
    {
        freq[front->value]++;
        front = front->next;
    }

    // declare and init. res to 0
    int res = 0;

    // loop through the aux array to find the most freq. occuring val
    for (i=1; i<MAX; i++)
        if (freq[i] > freq[res])
            res = i;



    return res;
    






    return mode;
}


int main()
{




    return 0;
}