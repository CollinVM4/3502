#include <stdlib.h>
#include <stdio.h>



typedef struct Node Node;
typedef struct List List;

struct Node
{
    int data;
    Node * next;
};

struct List
{
    Node * head;
    Node * tail;
};

// pass by reference the list



Node * creatNode(int data)
{
    Node * res = (Node *) malloc(sizeof(Node));
    res->data = data;
    res->next = NULL;

    return res;
}

void insertTail(List * list, int value)
{
    if (list == NULL) return;

    Node * newTail = createNode(value);

    if(list->tail)
    list->tail->next = newTail;
}

void insetHead(List * list, int value)
{

}

int main()
{

    List myList;

    for (int i = 0; i < 10; i++)
    {
        if (i % 2 == 0)
        {
            // tail insertion
            inserTail(&myList, i);
        } else
        {
            // head insertion
            insertHead(&myList, i);
        }
        
    }
    


}