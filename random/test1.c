#include <stdio.h>
#include <stdlib.h>


typedef struct Node Node;

struct Node
{
    Node * next;
    int value;
};


Node * removeTail(Node * head)
{

    if(head==NULL) return;
    if(head->next==NULL) return;

    Node * nextNode = head->next;

    if(nextNode->next == NULL)
    {
        free(nextNode);
    }
    removeTail(head->next);
}


int main()
{




    return 0;
}