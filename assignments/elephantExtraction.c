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
    if (stk->head != NULL) // make sure stack is not empty
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
        while (grid[row][col] > 0) // eat all bait at location
        {
            grid[row][col]--;
            eaten += 1;
        }
        return eaten; // success :D
    }
    return 0; // failed :(
}

void move(Elephant * ele_ptr, int ** grid)
{
    int row, col;
    top(&ele_ptr->memory, &row, &col); // get the current location of the elephant

    int maxBait = 0; // max bait found so far
    int maxRow = row;
    int maxCol = col;

    // search in cells around the elephant (up, down, left, right)
    if (row > 0 && grid[row - 1][col] > maxBait) // cell above
    {
        maxBait = grid[row - 1][col];
        maxRow = row - 1;
        maxCol = col;
    }
    if (row < 499 && grid[row + 1][col] > maxBait) // cell below
    {
        maxBait = grid[row + 1][col];
        maxRow = row + 1;
        maxCol = col;
    }
    if (col > 0 && grid[row][col - 1] > maxBait) // cell to the left
    {
        maxBait = grid[row][col - 1];
        maxRow = row;
        maxCol = col - 1;
    }
    if (col < 499 && grid[row][col + 1] > maxBait) // cell to the right
    {
        maxBait = grid[row][col + 1]; 
        maxRow = row;
        maxCol = col + 1;
    }

    // no bait in adjacent cells
    if (maxBait == 0)
    {
        // avoid popping initial position
        if (ele_ptr->memory.head != NULL && ele_ptr->memory.head->next != NULL)
        {
            pop(&ele_ptr->memory);
        }

        // get the new top of the stack
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
        push(&ele_ptr->memory, maxRow, maxCol); // move to the cell with the most bait
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

    // first loop: move elephants
    for (i = 0; i < num_ele; i++)
    {
        int row, col;
        top(&ele_arr[i].memory, &row, &col);
        if (grid[row][col] == 0) // first see if bait is at the current location
        {
            move(&ele_arr[i], grid); // if not, move
        }
    }

    // second loop: elephants eat
    for (i = 0; i < num_ele; i++)
    {
        totalEaten += eat(&ele_arr[i], grid);
    }
    
    return totalEaten; // return the total number of bait eaten
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

    // declare variables
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
    char command[5]; // will hold BAIT, HOUR, or QUIT
    while (scanf("%s", command) != EOF) 
    {
        if (command[0] == 'B') // BAIT command 
        {
            // read bait's row, column, amount
            scanf("%d %d %d", &row, &col, &amt);
            addBait(grid, row - 1, col - 1, amt);
        } else if (command[0] == 'H') // HOUR command
        {
            printf("%d\n", progress_hour(ele_arr, num_ele, grid));
        } else if (command[0] == 'Q') // QUIT command
        {
            // print each elephant's location (in order they were typed in)
            for (i = 0; i < num_ele; i++)
            {
                top(&ele_arr[i].memory, &row, &col);
                printf("%d %d\n", row + 1, col + 1); 
            }
            break;
        }
    }

    // free grid's memory
    for (int i = 0; i < 500; i++)
    {
        free(grid[i]); // free each row
    }
    free(grid); // free the grid

    // free each elepahnt's stack
    for (i = 0; i < num_ele; i++) {
        Node *current = ele_arr[i].memory.head;
        while (current != NULL) {
            Node *next = current->next;
            free(current);
            current = next;
        }
    }
    free(ele_arr); // free the array of elephants


    return(0);
}