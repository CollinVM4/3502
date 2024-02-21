#include <stdio.h>
#include <stdlib.h>

struct queue 
{
    int *array;
    int num_elements;
    int front;
    int capacity;
};


int dequeue(struct queue * q) 
{

    if (q == NULL) return 0; // null pointer
    if (q->num_elements == 0) return 0; // empty list

    int returnValue = q->array[q->front]; // grab front to dq

    q->front = (q->front + 1) % q->capacity; // circular logic to update new front

    q->num_elements = q->num_elements - 1;

    return returnValue;
}

int main()
{




    return 0;
}