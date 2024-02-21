#include <stdio.h>
#include <stdlib.h>


struct Stack 
{
    int *array;
    int top;
    int capacity;
};


void grow_stack(struct Stack *s, int increase) 
{
    int newCap = s->capacity + increase;

    int *hold = s->array;

    s->capacity = malloc(sizeof(int) * newCap);

    for (int i = 0; i < s->top; i++)
    {
        s->array[i] = hold[i]; 
    }
    
    free(hold);

    s->capacity = newCap;
}


int main()
{




    return 0;
}