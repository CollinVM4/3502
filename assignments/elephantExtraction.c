
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
    // if not empty
    if (stk->head != NULL) 
    {
        *row_ptr = stk->head->row;
        *col_ptr = stk->head->column;
    }
    else
    {
        // handle the case where the stack is empty
        *row_ptr = -1;
        *col_ptr = -1;
    }
}

// add bait to grid
void addBait(int ** grid, int row, int col, int amt)
{
    grid[row][col] += amt;
}

// eat bait from grid
int eatBait(int ** grid, int row, int col)
{
    // make sure there is bait to eat
    if (grid[row][col] > 0)
    {
        grid[row][col]--;
        return 1;
    }
    return 0; // failed to eat bait
}

// move the elephant
void move(Elephant * ele_ptr, int ** grid)
{
    int row, col;
    top(&ele_ptr->memory, &row, &col); // get the current location of the elephant

    if (row > 0) // prevent seg fault if elephant is on the top edge of the grid
    {
        // the if statement checks if eatbait was successful, if so, push the new location onto the stack
        if (eatBait(grid, row - 1, col))
        {
            push(&ele_ptr->memory, row - 1, col); 
            return;
        }
    }
    if (row < 499) // prevent seg fault if elephant is on the bottom edge of the grid
    {
        if (eatBait(grid, row + 1, col))
        {
            push(&ele_ptr->memory, row + 1, col);
            return;
        }
    }
    if (col > 0) // prevent seg fault if elephant is on the left edge of the grid
    {
        if (eatBait(grid, row, col - 1))
        {
            push(&ele_ptr->memory, row, col - 1);
            return;
        }
    }
    if (col < 499) // prevent seg fault if elephant is on the right edge of the grid
    {
        if (eatBait(grid, row, col + 1))
        {
            push(&ele_ptr->memory, row, col + 1);
            return;
        }
    }

    pop(&ele_ptr->memory);  // if elephant unable to move, pop the top of the stack
}

// eat bait
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

// progress the hour
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
    return eaten; // return the num of watermelons eaten so we can print it
}

/*

    assignment layout

    input: 
        1st line: number of elephants (1 <= N <= 10,000)
        following "N" lines: row and column of each elephant (1-500)
        afterwards: 3 commands 
            1. "BAIT R C A" (row, column, amount to add to the grid)
            2. "HOUR" (passing of 1 hour)
            3. "QUIT" (end of commands)

    output:
        upon "HOUR" print num of watermelons consumed within the hour   
        following "QUIT" print elephant location in order the were input 
    
    stack usage 
        * individual stack for each elephant 
            modify:
                if elephant backtracks, pop prev. location from stack
                if elephant travels tonew location, push onto the stack

            do not modify:
                if elephant is in initial location
                if elephant eats at their location

    grid usage
        2D int array [x][y]
        will hold the num of watermelons at each position
    

    plan:
        1. create a 2D array of size 100x100 (double pointer method)
        2. create an array of elephants (for loop to init)
        3. read in the number of elephants (for loop)
        4. read in the location of each elephant (for loop)
        5. read in the commands (while loop)
        6. execute the commands (switch statement)
        7. print the output (for loop)

    TODO
        - figure out how to scan in until QUIT is reached  (DONE)
        - implement the double pointer method for the grid... (DONE)
        - fix stack for each indv. elephant




*/


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
        ele_arr[i].memory.head = NULL; // Initialize the head of the stack to NULL
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
                printf("%d %d\n", row, col);
            }
            break;
        }
    }


    for (int i = 0; i < 500; i++)
    {
        free(grid[i]);
    }
    free(grid);

    return(0);
}