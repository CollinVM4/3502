#include <stdio.h>
#include <stdlib.h>

typedef struct node {
 int data;
 struct node* next;
} node;

void insertAfterN(node* head, int M, int N)
{

    if(head == NULL) return;


    if (head->data == N)
    {
        node * newNode = malloc(sizeof(node));

        newNode->data = M;

        newNode->next = head->next;

        head->next = newNode;
        
        head = newNode;

    }

    insertAfterN(head->next, M, N);

}




int main()
{




    return 0;
}