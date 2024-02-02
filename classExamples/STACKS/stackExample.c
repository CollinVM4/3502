/*

    Stacks
        * bottom is always the oldest, top is always the newest
        * top is modified when inserting and removing
    
    When is a stack useful?
        * the undo feature of document editors, 
        * the redo feature would be a seperate stack.
    
    Program stack is also a good example
        * LIFO, last in first out 

    Implementation
        * Array List
            - append func can add values (could work as a stack insert (PUSH))
            - entries would be inserted in the last index of the array (top of the stack)
            - removing values -> free the data, decrease array size by 1 (POP)

            How do we access the top?
                - access [size - 1] (because of 0 indexing)

        * Linked List
            - TOP can be head or tail
            - PUSH - insert head, insert tail
            - POP - remove head, remove head
            - req. basic linked list...... (heat/tail, or circular, both need double links)
    


    Expression Parsing
        ex. 3 + (4 + 1 * 3) * 2

        infix exppression, has operators inbetween operands
        postfix expression (reverse polish notation), have operators after operands 
            ex. 3 4 +
            
        infix -     3 * 2 + 1
        postfix -   3 2 * 1 +

    2 steps for evaulating infix
        1. convert to postfix
        2. evaluate postfix

    Loop through expression
        If operant
            Push operand to stack  
        If operator
            operand 1 = top and pop
            operand 2 = top and pop
            push operand 2, operate with operand 1
            
        return top of stack



    Queue Structure 
        Front of queue has been there the longest
        Remove from the front of the queue
        Insertion to the tail



*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h> // DO NOT USE!

typedef struct Node Node;
typedef struct Stack Stack;


struct Node
{
    Node * next;
    int data;
};

struct Stack
{
    int size;
    Node * head;
};

Node * createNode(int value)
{
    Node * res = (Node *)malloc(sizeof(Node));
    res->data = value;
    res->next = NULL;
    return res;
};

Node * insertHead(Node * head, int data)
{
    Node * newHead = createNode(data);
    newHead->next = head;
    return head;
}

Node * removeHead(Node * head)
{
    if (head)
    {
        Node * oldHead = head;
        head = head->next;
        free(oldHead);
    }
    return head;
}

// ^ basic LL functions
// \/ stack operations

void push(Stack * stk, int data)
{
    stk->head = insertHead(stk->head, data);
    stk->size++;
}

void pop(Stack * stk)
{   
    assert(stk->size != 0);
    stk->head = removeHead(stk->head);
    stk->size--;
}

int top(Stack stk)
{
    assert(stk.size != 0);
    return stk.head->data;
}

int isNumber(char * str)
{
    return ('0' <= str[0] && str[0] <= '9' || ('0' <= str[1] && str[1] <= '9'));
}



// evaluate a postfix expression to the resulting number
int main()
{
    Stack operandStack; // stack contains numbers

    // initialize
    operandStack.size = 0;
    operandStack.head = NULL;

    char token[100 + 1];

    // Loop through expression
    while (EOF != scanf("%s", token))
    {
        if (isNumber(token))
        {
            // add to operand stack
            push(&operandStack, atoi(token));
        } 
        else
        {
            int res = 0;
            int a = top(operandStack);
            pop(&operandStack);
            int b = top(operandStack);
            pop(&operandStack);

            if (token[0] == '+') res = a + b;
            else if (token[0] == '-') res = a - b;
            else if (token[0] == '*') res = a * b;
            else if (token[0] == '/') res = a / b;      
            else assert(0);

            push(&operandStack, res);                  
            
        }
        
    }
    




    return 0;
}


