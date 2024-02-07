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
    Node * newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
};

// insert tail using recursion 
Node * insertTail(Node * head, int data)
{
    if (head == NULL) // empty
    {   
        return createNode(data);
    }

    Node * nextHead = head->next;
    Node * newNextHead = insertTail(nextHead, data);

    head->next = newNextHead;

    // ALWAYS RETURN THE RESULTING HEAD OF THE LIST
    return head; // the head is still the head, bc we inserted at the tail
}


void printList(Node * head)
{
    Node * tmp = head;
    while (tmp)
    {
        printf("%d - > ", tmp->data);
        tmp = tmp->next;
    }
}

int main()
{

    Node * head = NULL;
    for (int i = 0; i < 10; i++)
    {
        head = insertTail(head, i);
        printList(head);
    }
    



    return 0;
}