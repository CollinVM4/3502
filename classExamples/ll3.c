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



Node * createNode(int data)
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

    if(list->tail) // this tail comes after the old
    list->tail->next = newTail; // this is the new tail 
}

void insertHead(List * list, int value)
{
    // make sure list is aight
    if (list == NULL)
    {
        return;
    }

    // create the new head
    Node * newHead = createNode(value);

    // Connect the newHead next to the head of the list
    newHead->next = list->head;

    // Make the enw node the head of the list
    list->head = newHead;

    // Maintain invariant that head and tail agree on emptiness
    if (list->tail == NULL)
    {
        list->tail = newHead;
    }
}

void printList(List myList)
{
    Node * cur = myList.head;
    while (cur) {
        printf("%d -> ", cur->data);
        cur = cur->next;
    }    
}

void removeHead(List * list)
{
    if (list == NULL) return; // NO LIST
    if (list->head == NULL) return; // EMPTY LIST

    Node * tmp = list->head->next;
    free(list->head);
    list->head = tmp;

    // Maintain invariant: list becomes empty
    if (list->head == NULL)
    {
        // DO NOT FREE THE TAIL (tail was head -> double free)
        list->tail = NULL;
    }
}

int main()
{

    List myList;

    // initialize the list
    myList.head = myList.tail =  NULL; // right most assignment, basically first, myList.tail = NULL, then myList.head = myList.tail

    for (int i = 0; i < 10; i++)
    {
        if (i % 2 == 0)
        {
            // tail insertion
            insertTail(&myList, i);
        } else
        {
            // head insertion
            insertHead(&myList, i);
        }
    }
    
    printList(myList);
    printf("\n");

}