/*
    - Collin Van Meter
    - COP3502C - Assignment 6
    - April 21, 2024
*/


// libraries
#include <stdio.h>
#include <stdlib.h>

// structs
typedef struct Node
{
    int subTrieAmount;
    int myAmount;
    struct Node * children[32];
} Node;

typedef struct Sum 
{
    int minSum;
    int maxSum;
} Sum;


// definitions
#define MAX_FOOD_AMOUNT 1000

// func prototypes
Node * createNode();
Node * addFamily(Node * root, char * response, int amount);
Node * changeResponse(Node * root, char * oldResponse, char * newResponse);
Sum sum(Node * root, char * response);
int mapCharToIndex(char c);
int getAmount(Node * root, char * response);


// func definitions

// Function to create a node
Node * createNode() 
{
    // allocate memory for new node
    Node * res = (Node *) malloc(sizeof(Node));

    // init values to 0
    res->myAmount = 0;
    res->subTrieAmount = 0;

    // init children to NULL
    for (int i = 0; i < 32; i++)
    {
        res->children[i] = NULL;
    }

    return res;
}


// Function that inserts a word into a trie and returns the resulting root of the trie
Node * addFamily(Node * root, char * response, int amount)
{
    // create root if no root exists
    if(root == NULL)
    {
        root = createNode();
    }

    // increment subTrieAmount, add amount to myAmount
    root->subTrieAmount++;
    root->myAmount += amount;

    // string is not empty
    if(response[0] != '\0')
    {
        int index = mapCharToIndex(response[0]); // get index
        root->children[index] = addFamily(root->children[index], response + 1, amount); // add list of children
    }

    return root;
}


// change response 
Node * changeResponse(Node * root, char * oldResponse, char * newResponse)
{
    root = addFamily(root, newResponse, getAmount(root, oldResponse)); // add new response
    root = addFamily(root, oldResponse, -(getAmount(root, oldResponse))); // negate old response
    return root;
}


// function that gets the sum of responses
Sum sum(Node * root, char * response) {
    Sum result;
    if (root == NULL) {
        result.minSum = 0;
        result.maxSum = 0;
        return result;
    }

    // empty string
    if (response[0] == '\0') {
        result.minSum = root->myAmount;
        result.maxSum = root->subTrieAmount * MAX_FOOD_AMOUNT;
        return result;
    }

    // not empty string
    int index = mapCharToIndex(response[0]);
    Sum childSum = sum(root->children[index], response + 1);
    result.minSum = childSum.minSum + root->myAmount;
    result.maxSum = childSum.maxSum + root->myAmount;
    return result;
}


// function that coverts chars to indexes
int mapCharToIndex(char c)
{
    return c - 'A';
}


// function that grabs amount corresponding with a response
int getAmount(Node * root, char * response)
{
    if (root == NULL) return 0;

    if (response[0] == '\0')
    {
        return root->myAmount;
    }

    int index = mapCharToIndex(response[0]);
    return getAmount(root->children[index], response + 1);
}



int main()
{
    // delcare and init max/min match values
    int minMatches, maxMatches, amount = 0;
    char * response = (char *) malloc(32 * sizeof(char));
    char * oldResponse = (char *) malloc(32 * sizeof(char));
    char * newResponse = (char *) malloc(32 * sizeof(char));

    // create initial root node
    Node * root = NULL;

    // command handling
    char command[20];
    while (1)
    {
        scanf("%s", command);

        if (command[0] == 'A') // ADD R A
        {
            scanf("%s %d", response, &amount);
            root = addFamily(root, response, amount);
        }
        else if (command[0] == 'C') // CHANGE R N
        {
            scanf("%s %d", response, &amount);
            root = changeResponse(root, oldResponse, newResponse);
        }
        else if (command[0] == 'S') // SUM R
        {
            // sum of fams that responded with R
            scanf("%s", response);
            Sum result = sum(root, response);
            printf("%d %d\n", result.minSum, result.maxSum);
        }
        else if (command[0] == 'Q') // QUIT
        {
            break; // end of commands
        }

    }
    
    return 0;
}