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

void removeAll(int value, Node** head)
{
    Node* cur = *head;
    Node* prev = NULL;

    while (cur != NULL)
    {
        if (cur->data == value)
        {
            Node* tmp = cur;
            if (prev == NULL)  // The head is the value to be removed
            {
                *head = cur->next;
            }
            else
            {
                prev->next = cur->next;
            }
            cur = cur->next;
            free(tmp);
        }
        else
        {
            prev = cur;
            cur = cur->next;
        }
    }
}


