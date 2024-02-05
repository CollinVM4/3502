/*
    Linked List Worksheet
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
    Node * newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
};

// my solution maybe?
removeAll(int value, struct Node * head)
{
    Node * cur = head;

        while (cur->data != value)
        {
        if (cur->data == value)
        {
            Node * tmp = cur;
            free(tmp);
            cur = cur->next;
            break;
        } else 
        {
            cur = cur->next;
        }
        }






}

int main()
{




    return 0;
}