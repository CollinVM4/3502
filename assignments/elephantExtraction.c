/*
    - Collin Van Meter
    - COP 3502C 
    - Elephant Extraction 
*/
#include <stdio.h>
#include <stdlib.h>


typedef Node Node;
typedef Stack Stack;
typedef Elephant Elephant; 

struct Node 
{
    int row, column;
    Node * next;
};

struct Stack 
{
    Node * head;
};

struct Elephant 
{
    Stack memory;
};




// function prototypes
Node * createNode(int row, int col);
void push(Stack * stk, int row, int col);
void pop(Stack * stk);
void top(Stack * stk, int * row_ptr, int * col_ptr);
void addBait(int ** grid, int row, int col, int amt);
int eatBait(int ** grid, int row, int col);
void move(Elephant * ele_ptr, int ** grid);
int eat(Elephant * ele_ptr, int ** grid);
int progress_hour(Elephant * ele_arr, int num_ele, int ** grid);


// function definitions


// create a new node
Node * createNode(int row, int col)
{
    Node * res = (Node *) malloc(sizeof(Node));
    res->row = row;
    res->column = col;
    res->next = NULL;
    return res;
}

// insert "push" a new node to the top of the stack
void push(Stack * stk, int row, int col)
{
    Node * newHead = createNode(row, col);
    newHead->next = stk->head;
    stk->head = newHead;
}

//  delete "pop" the top of the stack
void pop(Stack * stk)
{
    if (stk->head != NULL) // if the stack is not empty
    {
        Node * oldHead = stk->head;
        stk->head = stk->head->next;
        free(oldHead);
    } else return;
}

// get the top of the stack
void top(Stack * stk, int * row_ptr, int * col_ptr)
{
    if (stk->head != NULL)
    {
        *row_ptr = stk->head->row;
        *col_ptr = stk->head->column;
    }
}

void addBait(int ** grid, int row, int col, int amt)
{
    grid[row][col] += amt;
}

int eatBait(int ** grid, int row, int col)
{
    if (grid[row][col] > 0)
    {
        grid[row][col]--;
        return 1;
    }
    return 0;
}

void move(Elephant * ele_ptr, int ** grid)
{
    int row, col;
    top(&ele_ptr->memory, &row, &col);
    if (row > 0)
    {
        if (eatBait(grid, row - 1, col))
        {
            push(&ele_ptr->memory, row - 1, col);
            return;
        }
    }
    if (row < 99)
    {
        if (eatBait(grid, row + 1, col))
        {
            push(&ele_ptr->memory, row + 1, col);
            return;
        }
    }
    if (col > 0)
    {
        if (eatBait(grid, row, col - 1))
        {
            push(&ele_ptr->memory, row, col - 1);
            return;
        }
    }
    if (col < 99)
    {
        if (eatBait(grid, row, col + 1))
        {
            push(&ele_ptr->memory, row, col + 1);
            return;
        }
    }
    pop(&ele_ptr->memory);
}

int eat(Elephant * ele_ptr, int ** grid)
{
    int row, col;
    top(&ele_ptr->memory, &row, &col);
    if (eatBait(grid, row, col))
    {
        return 1;
    }
    return 0;
}

int progress_hour(Elephant * ele_arr, int num_ele, int ** grid)
{
    int i, eaten = 0;
    for (i = 0; i < num_ele; i++)
    {
        if (eat(&ele_arr[i], grid))
        {
            eaten++;
        } else 
        {
            move(&ele_arr[i], grid);
        }
    }
    return eaten;
}

int main()
{




    return 0;
}