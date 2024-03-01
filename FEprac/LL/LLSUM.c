#include <stdio.h>
#include <stdlib.h>


typedef struct Node 
{
    int value;
    Node * next;
} Node;



int sum (Node * head)
{
    int res = 0;


    if (head == NULL) return 0;

    while (head != NULL)
    {
        res += head->value;
        head = head->next;
    }

    return res;
}


int main()
{




    return 0;
}