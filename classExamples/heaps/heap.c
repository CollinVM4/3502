#include <stdio.h>
#include <stdlib.h>


#define PARENT(x) ((x)-1)/2

typedef struct Heap Heap;
struct Heap 
{
    int size, cap;
    int * arr;
};


void insert(Heap * h, int value);
void printHeap(Heap * h);
void * deleteHeap(Heap * h);
Heap * createHeap();
void percolateUp(Heap * h, int index);
void append(Heap * h, int value);


void append(Heap * h, int value)
{
    if (h->size == h->cap)
    {
        h->cap *= 2;
        h->arr = (int *) realloc(h->arr, h->cap * sizeof(int));
    }

    h->arr[h->size] = value;
    h->size++;
}

void percolateUp(Heap * h, int index)
{
    while(index != 0 && h->arr[index] > h->arr[PARENT(index)])
    {
        int parentIndex = PARENT(index);

        int tmp = h->arr[parentIndex];
        h->arr[parentIndex] = h->arr[index];
        h->arr[index] = tmp;

        index = parentIndex;
    }
}



void printHeap(Heap * h)
{
    for (int i = 0; i < h->size; i++)
    {
        printf("%d ", h->arr[i]);
    }
    printf("\n");
}


void insert(Heap * h, int value) 
{
    // insert value at end of heap
    append(h, value);


    // percolate up
    percolateUp(h, value);
}


Heap * createHeap()
{
    Heap * res;
    res = (Heap *) calloc(1, sizeof(Heap));

    res->cap = 1;
    res->arr = (int *) malloc(sizeof(int) * res->cap);

    return res;
}


void * deleteHeap(Heap * h)
{
    free(h->arr);
    free(h);
}


int main()
{




    return 0;
}