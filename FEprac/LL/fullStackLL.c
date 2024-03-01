#include <stdio.h>
#include <stdlib.h>

typedef struct node 
{
    int data;
    struct node* next;
} node;



int isFull(node *stack) 
{

    int nodeCount = 0;
    
    if(stack == NULL) return 0;

    node * tmp = stack;


    while (tmp != NULL)
    {
        nodeCount++;
        tmp = tmp->next;
    }
    

    if(nodeCount >= 20) return 1; else return 0;





}


int main()
{




    return 0;
}