


#include <stdio.h>
#include <stdlib.h>


typedef struct Node Node;

struct Node
{
    int data;
    Node * next;
};

Node * createNode(int value) 
{
    Node * res = (Node *) malloc(sizeof(Node));
    res->data = value;
    res->next = NULL;

    return res;
}


int main()
{




    return 0;
}