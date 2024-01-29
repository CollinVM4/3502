/*
    Circular Linked List
        * works by forcing the tail to tell us the head
        * tail points to the head
        * pass in the tail, return what the resulting tail is
*/


#include<stdlib.h>
#include<stdio.h>

typedef struct Node Node;

struct Node
{
    int data;
    Node * next;
};

// create a node of a circular linked list and return it 
Node * createNode(int value) 
{
    Node * res = (Node *) malloc(sizeof(Node));
    res->data = value;
    res->next = res;

    return res;
}

Node * insertHead(Node * tail, int data)
{
    Node * newHead = createNode(data);

    if(!tail)
    {
        // TAIL IS NULL, LIST IS EMPTY
        return newHead;
    }

    newHead->next = tail->next;
    tail->next = newHead; // tail points to head of the list

    return tail;
}

Node * insertTail(Node * tail, int data)
{
    return insertHead(tail, data)->next;
}




int main()
{



    return(0);
}