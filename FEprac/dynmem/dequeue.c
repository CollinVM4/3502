#include <stdio.h>
#include <stdlib.h>


typedef struct node 
{
    int data;
    struct node* next, *prev;
} node;

typedef struct queue 
{
    int size;
    struct node *head, *tail;
} queue;

int dequeue(queue *thisQ) 
{
    if (thisQ == NULL) return 0;

    if(thisQ->size == 0) return 0;
        

    int retval = thisQ->head->data; 

    node *temp = thisQ->head; 

    thisQ->head = thisQ->head->next; 

    if (thisQ->size > 1) 
        thisQ->head->prev = NULL;
    else
        thisQ->tail = NULL;

    free(temp); // Grading – 2pts

    thisQ->size--; // Grading – 1 pt



 return retval; 
}


int main()
{




    return 0;
}