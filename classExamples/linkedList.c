/*

    x Linked List Notes x


    * fracture memory into components "fragmented memory"
    * each node stores where it is supposed to go next
    

    ex.
    * struct Node 
    {
        int x;
        struct Node * next;
        ^ points to next node
    }

    notes: 
    * make your last node point to NULL
    * to access the full list, store the first Node (head)

    int main()
    {
        node * head = createNode(1);
        node * newHead = createNode(2);
        newHead->next = head;
        head = newHead;
        newHead = createNode(3);
        newHead->next = head;
        head = newHead

        // the nodes come out in reverse order, the newest value is always going to be the head of the list
     
    }

    createNode function...

    Node * createNode(int value)
    {
        Node * ret;

        ret = (Node *) malloc(sizeof(Node)); // protects memory?


        return ret;
    }








*/


#include <stdlib.h>
#include <stdio.h>


typedef struct Node Node;

struct Node
{
    int data;
    Node * next;
};

Node * createNode(int data)
{
    Node * ret;

    // allocation
    ret = (Node *) malloc(sizeof(Node));

    //initialization
    ret->data = data;
    ret->data = NULL; // used to avoid dangling pointer

    return ret; // return the init protected block of memory
}


void printList(Node * head)
{
    Node * cur = head;
    while (cur != NULL)
    {
        printf("%d -> ", cur->data);
        cur = cur->next; // moves down the list 1 node
    }
    printf("\n");
}


int main()
{
    Node * head = createNode(1);
    Node * newHead = createNode(2);
    newHead->next = head;
    head = newHead;
    newHead = createNode(3);
    newHead->next = head;
    head = newHead;







    return(0);
}
