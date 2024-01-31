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


Node * removeHead(Node * tail)
{
    if (!tail) return NULL;
    if (tail->next == tail) 
    {
        free(tail);
        return NULL;
    }

    Node * newHead = tail->next->next;
    free(tail->next);
    tail->next = newHead;

    return tail;
}


Node * insertTail(Node * tail, int data)
{
    if (!tail) return NULL;
    return insertHead(tail, data)->next;
}

void printList(Node * tail)
{
    // empty list case
    if(tail == NULL) printf("NULL\n"); return;

    // print all the nodes starting at the head 
    Node * cur = tail->next;
    do
    {
        printf("%d -> ", cur->data);
        cur = cur->next;
    } while (cur != tail->next);
    
    printf("\n");
}



int main()
{

    Node * tail = NULL;

    // head insert 
    for (int i = 0; i < 10; i++)
    {
        tail = insertHead(tail, i);

    }
    //head remove
    for (int i = 0; i < 11; i++)
    {
        printList(tail);
        tail = removeHead(tail, i);
    }
    
    


    return(0);
}