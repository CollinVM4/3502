#include <stdlib.h>
#include <stdio.h>


typedef struct ArrayList ArrayList;


struct ArrayList 
{
    int * arr;
    int size, cap;
};


ArrayList * createList()
{
    ArrayList * ret;

    ret = (ArrayList *) malloc(sizeof(ArrayList));

    // Initialize
    ret->size = 0;
    ret->cap = 10;
    ret->arr = (int*) malloc(sizeof(int) * ret->cap);

    return ret;
}


void append(ArrayList * list, int value)
{
    // if list full expand
    if (list->size == list->cap)
    {
        list->cap *=2;
        list->arr = (int *) realloc(list->arr,sizeof(int) * list->cap);
    }
    

    list->arr[list->size] = value;
    list->size++;
}


void printList(ArrayList * list)
{
    for (int i = 0; i < list->size; i++)
    {
        printf("%d\n", list->arr[i]);
    }
}


void deleteList(ArrayList * list)
{
    free(list->arr);
    free(list);
}


int main()
{

    ArrayList * myList = createList();
    int value;


    do
    {
        scanf("%d", &value);
        if (value != -1)
        {
            append(myList, value);
        }
        
    } while (value != -1);
    
    printList(myList);


    return 0;
}