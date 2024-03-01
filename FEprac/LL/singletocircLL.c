#include <stdio.h>
#include <stdlib.h>


struct node 
{
    int num;
    struct node* next;
};


struct node* make_circle(struct node* head) 
{
    if(head == NULL) return NULL;

    node * tail = head;

    while (head != NULL)
    {
        tail = head->next;

        if (tail->next == NULL)
        {
            tail->next = head;
        }

    }

    return tail;
} 


int main()
{




    return 0;
}