/*
Suppose we have a linked list implemented with the structure below. Write a function that will take in a
pointer to the head of a list and inserts a node storing -1 after each even value in the list. If the list is empty
or there are no even values in the list, no modifications should be made to the list. (For example, if the
initial list had 2, 6, 7, 1, 3, and 8, the resulting list would have 2, -1, 6, -1, 7, 1, 8, -1.)
*/


#include <stdio.h>
#include <stdlib.h>


typedef struct node 
{
    int data;
    struct node* next;
} node;


void markEven(node *head) 
{

    node * newNode = head;

    if(head == NULL) return;

    while (head != NULL)
    {
        if (head->data % 2 == 0)
        {
            /* code */
        }
        
    }
    




}


int main()
{




    return 0;
}