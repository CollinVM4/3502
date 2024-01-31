/*
    Doubly Linked List
        * prev and next pointers on all nodes
        * also can be circular, as in this example
*/

#include<stdlib.h>
#include<stdio.h>

typedef struct Node Node;

struct Node
{
    int data;
    Node * next;
    Node * prev;
};

// create a node of a circular linked list and return it 
Node * createNode(int value) 
{
    Node * res = (Node *) malloc(sizeof(Node));
    res->data = value;

    // Make the node circular
    res->next = res;
    res->prev = res;

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

    // Make the old nodes point to the new node first
    Node * oldHead = tail->next;
    Node * oldTail = tail;
    oldTail->next = newHead;
    oldHead->prev = newHead;

    newHead->next = oldHead;
    oldHead->prev = newHead;

    newHead->next = oldHead; // point to the old head
    newHead->prev = tail; // must point back to the tail

    return oldTail;
}

Node * insertTail(Node * tail, int data)
{
    return insertHead(tail, data)->next;
}

Node * removeHead(Node * tail)
{
    // empty list
    if (tail == NULL)
    {
        return NULL;
    }
    
    // one node case
    if (tail->next == tail)
    {
        free(tail);
        return NULL;
    }

    // more than one node case
    Node * oldHead = tail->next;
    Node * newHead = oldHead->next;

    free(oldHead);

    newHead->prev = tail;
    tail->next = newHead;
    
    return tail;
}

Node * removeTail(Node * tail)
{
    return removeHead(tail)->prev;
}

int main()
{



    return(0);
}