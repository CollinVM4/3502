#include <stdio.h>
#include <stdlib.h>


#define MAX 12


struct stack
{
    int top; /* indicates index of top */
    int nodes[MAX] ;
};

int push(struct stack* s, int value)
{

    if(s->top >= MAX -1) return 0;

    s->nodes[s->top + 1] = value;
    s->top++;

    return 1;
}



int peek(struct stack* s)
{

    if(s->top == -1) return -1;

    return s->nodes[s->top];
}



int main()
{




    return 0;
}