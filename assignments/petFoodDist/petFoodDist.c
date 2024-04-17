/*
    - Collin Van Meter
    - COP3502C - Assignment 6
    - April 21, 2024
*/


// libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structs
typedef struct Node
{
    int subTrieAmount;
    int myAmount;
    struct Node * children[32];
} Node;

// func prototypes
Node * createNode();
Node * addFamily(Node * root, char * response, int amount);
Node * changeResponse(Node * root, char * oldResponse, char * newResponse);
int minSum(Node * root, char * response);
int maxSum(Node * root, char * response);
int mapCharToIndex(char c);
int getAmount(Node * root, char * response);
int sumAllChildren(Node *root);



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



Node * addFamily(Node * root, char * response, int amount)
{
    printf("inside addFamily amount: %d\n", amount);
    // create root if no root exists
    if (root == NULL)
    {
        root = createNode();
    }

    // increment subTrieAmount for every node in the path
    root->subTrieAmount += amount;

    // string is not empty
    if (response[0] != '\0')
    {
        int index = mapCharToIndex(response[0]); // get index
        root->children[index] = addFamily(root->children[index], response + 1, amount); // add list of children
    }

    // if the response ends at this node, increment myAmount
    if (response[0] == '\0' || response[1] == '\0')
    {
        root->myAmount += amount;
    }

    return root;
}

// change response 
Node * changeResponse(Node * root, char * oldResponse, char * newResponse)
{
    int amount = getAmount(root, oldResponse);
    int negationAmount = -(amount);
    root = addFamily(root, oldResponse, negationAmount); // negate old response
    root = addFamily(root, newResponse, amount); // add new response
    return root;
}

int minSum(Node * root, char * response)
{
    if (root == NULL) return 0;

    if (response[0] == '\0')
    {
        return root->myAmount;
    }

    int index = mapCharToIndex(response[0]);
    return minSum(root->children[index], response + 1);
}

int maxSum(Node * root, char * response)
{
    if (root == NULL) return 0;

    int responseLen = strlen(response);
    int result = 0;


    for (int i = 0; i < responseLen; i++)
    {
        int index = mapCharToIndex(response[i]);
        if (root->children[index] != NULL) 
        {
            result += root->children[index]->myAmount;
            root = root->children[index]; // Move to the next node in the trie
        } 
        else
        {
            return result;
        }
    }
    
    return result;
}


// function that coverts chars to indexes
int mapCharToIndex(char c)
{
    if ('a' <= c && c <= 'z') return c - 'a';
    if ('A' <= c && c <= 'Z') return c - 'A' + 26;
    if ('0' <= c && c <= '9') return c - '0' + 52;
    return -1; // Return -1 for invalid characters
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
    int amount = 0;
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
            scanf("%s %s", oldResponse, newResponse);
            root = changeResponse(root, oldResponse, newResponse);
        }
        else if (command[0] == 'S') // SUM R
        {
            // sum of fams that responded with R
            scanf("%s", response);
            printf("%d %d\n", minSum(root, response), maxSum(root, response));
        }
        else if (command[0] == 'Q') // QUIT
        {
            break; // end of commands
        }

    }
    
    return 0;
}

