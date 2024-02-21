#include <stdio.h>
#include <stdlib.h>


typedef struct Node Node;
typedef struct Queue Queue;

struct Node 
{
    Node * next;
    int value;
};

struct Queue 
{
    Node * head, * tail;
};

void dequeue(Queue * qPtr) 
{

    if(qPtr->head == NULL) return;

    Node * tmp = qPtr->head;
    
    qPtr->head = qPtr->head->next;

    free(tmp);
}


int main()
{




    return 0;
}