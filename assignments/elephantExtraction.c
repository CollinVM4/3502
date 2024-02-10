/*
    - Collin Van Meter
    - COP 3502C 
    - Elephant Extraction 
*/


#include <stdio.h>
#include <stdlib.h>


typedef struct Node 
{
    int row, column;
    struct Node * next;
} Node;

typedef struct Stack 
{
    Node * head;
} Stack;

typedef struct Elephant 
{
    Stack memory;
} Elephant;


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
    // if not empty
    if (stk->head != NULL) 
    {
        *row_ptr = stk->head->row;
        *col_ptr = stk->head->column;
    }
    else // empty :(
    {
        *row_ptr = -1;
        *col_ptr = -1;
    }
}

// add bait to grid
void addBait(int ** grid, int row, int col, int amt)
{
    grid[row][col] += amt; // increment rather than set to new given value
}

// eat bait from grid
int eatBait(int ** grid, int row, int col)
{
    int eaten = 0;
    // make sure there is bait to eat
    if (grid[row][col] > 0)
    {
        while (grid[row][col] > 0)
        {
            printf("amount of food while eating: %d\n", grid[row][col]);    
            grid[row][col]--;
            eaten += 1;
        }
        printf("amount of food after eating: %d\n", grid[row][col]);
        return eaten; // success :D
    }
    return 0; // failed :(
}

void move(Elephant * ele_ptr, int ** grid)
{
    int row, col;
    top(&ele_ptr->memory, &row, &col); // get the current location of the elephant

    // Initialize maxBait to -1 to find a cell with any amount of bait
    int maxBait = 0;
    int maxRow = row;
    int maxCol = col;

    // search in cells around the elephant (up, down, left, right)
    if (row > 0 && grid[row - 1][col] > maxBait) // bait is in the cell above
    {
        maxBait = grid[row - 1][col];
        maxRow = row - 1;
        maxCol = col;
    }
    if (row < 499 && grid[row + 1][col] > maxBait) // bait is in the cell below
    {
        maxBait = grid[row + 1][col];
        maxRow = row + 1;
        maxCol = col;
    }
    if (col > 0 && grid[row][col - 1] > maxBait) // bait is in the cell to the left
    {
        maxBait = grid[row][col - 1];
        maxRow = row;
        maxCol = col - 1;
    }
    if (col < 499 && grid[row][col + 1] > maxBait) // bait is in the cell to the right
    {
        maxBait = grid[row][col + 1]; 
        maxRow = row;
        maxCol = col + 1;
    }

    // no bait in adjacent cells
    if (maxBait == 0)
    {
        // make sure its not 
        if (ele_ptr->memory.head != NULL && ele_ptr->memory.head->next != NULL)
        {
            pop(&ele_ptr->memory);
        }

        // Get the new top of the stack
        if (ele_ptr->memory.head != NULL)        
        {
            top(&ele_ptr->memory, &row, &col);
            printf("no bait, BACKTRACKING to [%d, %d]\n", row + 1, col + 1);
        }
    }
    // bait found in adjacent cells
    else
    {
        printf("found bait, moving to [%d, %d]\n", maxRow + 1, maxCol + 1);
        // Move to the cell with the most bait
        push(&ele_ptr->memory, maxRow, maxCol);
    }
}

// eat bait
int eat(Elephant * ele_ptr, int ** grid)
{
    int row, col;
    top(&ele_ptr->memory, &row, &col);
    return (eatBait(grid, row, col));
}

// progress the hour
int progress_hour(Elephant * ele_arr, int num_ele, int ** grid)
{
    int i, totalEaten = 0;

    // First loop: all elephants move if they need to
    for (i = 0; i < num_ele; i++)
    {
        int row, col;
        top(&ele_arr[i].memory, &row, &col);
        if (grid[row][col] == 0) // If no bait at current location, move the elephant
        {
            move(&ele_arr[i], grid);
        }
    }

    // Second loop: all elephants eat
    for (i = 0; i < num_ele; i++)
    {
        totalEaten += eat(&ele_arr[i], grid);
    }
    
    return totalEaten; // return the total number of baits eaten
}


int main()
{
    // create and init grid
    int **grid = malloc(500 * sizeof(int *)); // "double pointer method" discussed in lab
    for (int i = 0; i < 500; i++)
    {
        grid[i] = malloc(500 * sizeof(int));
        for (int j = 0; j < 500; j++)
        {
            grid[i][j] = 0;
        }
    }

    // declare vars
    int num_ele, i, j, row, col, amt;

    // read in the number of elephants
    scanf("%d", &num_ele);

    // create array of elephants
    Elephant * ele_arr;
    ele_arr = (Elephant *) malloc(num_ele * sizeof(Elephant));

    // init each elephant's stack
    for (int i = 0; i < num_ele; i++) 
    {
        ele_arr[i].memory.head = NULL; 
    }


    // read in the location of each elephant
    for (i = 0; i < num_ele; i++)
    {
        scanf("%d %d", &row, &col); 
        push(&ele_arr[i].memory, row - 1, col - 1);
    }
    
    // read in the commands
    char command[5];
    while (scanf("%s", command) != EOF) 
    {
        if (command[0] == 'B') // BAIT
        {
            // read bait's Row Column Amount
            scanf("%d %d %d", &row, &col, &amt);
            addBait(grid, row - 1, col - 1, amt);
        } else if (command[0] == 'H') // HOUR
        {
            printf("%d\n", progress_hour(ele_arr, num_ele, grid));
        } else if (command[0] == 'Q') // QUIT
        {
            // print each elephant's location (in order they were typed in)
            for (i = 0; i < num_ele; i++)
            {
                top(&ele_arr[i].memory, &row, &col);
                printf("%d %d\n", row + 1, col + 1); // debug
            }
            break;
        }
    }


    // free memory
    for (int i = 0; i < 500; i++)
    {
        free(grid[i]);
    }
    free(grid);

    return(0);
}