/*

    4 main functions with linked lists
        * add/remove data (insert/remove)
            via insertHead, removeHead, insertTail, removeTail


    Basic Linked List
        * input will always contain head
        * output will always be resulting head 
        
    Node* insertHead(Node * head, int data);


    Remove Head
        * Node* removeHead(Node* head);

*/

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
    Node * res = (Node *)malloc(sizeof(Node));
    res->data = value;
    res->next = NULL;
    return res;
};

Node * insertHead(Node * head, int data)
{
    Node * newHead = createNode(data);
    newHead->next = head;
    return newHead;
}


Node * removeHead(Node * head)
{    
    /*WHAT FE EXAM EXPECTS*/
    if (head ==NULL)
    {
        return NULL; // in case of empty list 
    }
    
    Node * tmp = head->next; // avoid use after free
    free(head);
    return tmp;
}

Node * insertTail(Node * head, int data)
{

    if (!head) // empty list case
    { 
        return createNode(data); // head and tail are the same
    }
    
    Node * oldTail = head;
    while (oldTail->next) // != NULL
    {
        oldTail = oldTail->next;
    }
    oldTail->next = createNode(data); // connect old tail to new 
    
    return head; // return the head of the list
}


Node * createList()
{
    Node * head = NULL;

    for (int i = 0; i <= 6; i += 2)
    {
        head = insertHead(head, i); // head must be updated
    }

    for (int i = 7; i >= 1; i -= 2)
    {
        head = insertHead(head, i);
    }
    
    return head;
}


void printList(Node * head)
{
    Node * tmp = head;
    while (tmp)
    {
        printf("%d -> ",tmp->data);
        tmp = tmp->next;
    }
    
    printf("NULL\n");

}


void deleteList(Node * head)
{
    while (head)
    {
        head = removeHead(head);
    }
    head = removeHead(head); // check error handling
}



int main()
{

    Node * list = createList();
    printList(list);
    deleteList(list);

    return(0);
}