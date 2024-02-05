#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// prototypes
int front(ArrayList * list);
void listRemove(ArrayList * list);
void append(ArrayList * list, int value);




// basic arrayList code
typedef struct ArrayList ArrayList;

struct ArrayList
{
    int size, cap;
    int begin, end;
    int * arr;
};

ArrayList * createArrayList()
{
    ArrayList * res = (ArrayList *) malloc(sizeof(ArrayList));
    res->size = 0;
    res->cap = 4;
    res->begin = 0;
    res->end = 0;
    res->arr = (int *) malloc(sizeof(int) * res->cap);
    return res;
}

void append(ArrayList * list, int value)
{
    if (list->size == list->cap)
    {

        ArrayList tmp;
        tmp.cap = list->cap * 2;
        tmp.size = 0;
        tmp.begin = 0;
        tmp.end = 0;
        tmp.arr = (int *) malloc(sizeof(int) * tmp.cap);

        while (list->size)
        {
            append(&tmp, front(list));
            listRemove(list);
        }

        list->cap *=2;
        free(list->arr);
        list->arr = tmp.arr;
        list->arr = (int *) realloc(list->arr, sizeof(int) * list->cap);
    }
    list->arr[list->end] = value;

    if (list->end == list->cap) // wrap around
    {
        list->end = 0;
    }

    list->size++;
}

int front(ArrayList * list)
{
    assert(list->size != 0);
    return list->arr[list->begin];
}


void listRemove(ArrayList * list)
{
    assert(list->size != 0);
    list->size--;
    list->begin++;
    if (list->begin == list->cap) // wrap around
    {
        list->begin = 0;
    }
}

// need to adapt this code to work with the stack (FIFO)

// According to original array list...
// when removing a value, we need to shift all the values to the left

// Adapt ArrayList to allow empty spots at the beggining
// Aka "Circular Buffer"
// need to track end, begining, a




int main()
{

    ArrayList * list = createArrayList();

    int cur = 0;
    for (int i = 0; i < 100; i++)
    {
        if (rand() % 4 < 3)
        {
            append(list, cur);
            printf("Inserted %d\n", cur);
            cur++;
        }
        else
        {
            int value = front(list);
            printf("removed %d\n", value);
            listRemove(list);
        }
        
    }
    


    return 0;
}