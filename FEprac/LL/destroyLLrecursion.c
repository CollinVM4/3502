#include <stdio.h>
#include <stdlib.h>


typedef struct node
{
    struct node *next;
    int data;
} node;

void destroy_list(node *head) 
{
    if(head == NULL) return;

    node * nextNode = head->next;
    free(head);

    destroy_list(nextNode);
}


int main()
{




    return 0;
}