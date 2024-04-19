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

Node * addFamily(Node * root, char * response, int amount)
{
    if (root == NULL) return NULL;

    Node * current = root;

    // create subsequent nodes
    for (int i = 0; response[i] != '\0'; i++)
    {
        // map current char to an index
        int index = mapCharToIndex(response[i]); 

        // create a new node if no node exists at the index
        if (current->children[index] == NULL)
        {
            current->children[index] = createNode();
        }

        // move to the child node
        current = current->children[index];
    }

    // add amount to the child node
    current->myAmount += amount;
    current->subTrieAmount += amount; // update subTrieAmount for the added node

    // update subTrieAmount for all ancestors
    current = root;
    for (int i = 0; response[i] != '\0'; i++)
    {
        int index = mapCharToIndex(response[i]);
        if (current->children[index] != current) // avoid updating the added node twice
        {
            current->subTrieAmount += amount;
        }
        current = current->children[index];
    }

    return root;
}


// change response 
Node * changeResponse(Node * root, char * oldResponse, char * newResponse)
{
    if (root == NULL) return NULL;

    Node * current = root;
    int amount = 0;

    // Iterate over the characters in the oldResponse
    for (int i = 0; oldResponse[i] != '\0'; i++)
    {
        // Map the current character to an index
        int index = mapCharToIndex(oldResponse[i]);

        // If no node exists at the index, return root
        if (current->children[index] == NULL) 
        {
            return root; // old response does not exist in the trie
        }

        // Move to the child node
        current = current->children[index];
    }

    // Get the amount from the last node
    amount = current->myAmount;

    // Subtract the amount from the myAmount and subTrieAmount of the nodes in the path of the old response
    current = root;
    for (int i = 0; oldResponse[i] != '\0'; i++)
    {
        int index = mapCharToIndex(oldResponse[i]);
        current->myAmount -= amount;
        current->subTrieAmount -= amount;
        current = current->children[index];
    }

    root = addFamily(root, newResponse, amount); // add new response

    return root;
}

int minSum(Node * root, char * response)
{
    if (root == NULL) return 0;

    Node * current = root;

    // Iterate over the characters in the response
    for (int i = 0; response[i] != '\0'; i++)
    {
        // Map the current character to an index
        int index = mapCharToIndex(response[i]);

        // If no node exists at the index, return 0
        if (current->children[index] == NULL) 
        {
            return 0;
        }

        // Move to the child node
        current = current->children[index];
    }

    // Return the subTrieAmount of the last node
    return current->subTrieAmount;
}


int maxSum(Node * root, char * response)
{
    // no root case
    if (root == NULL) return 0;

    // empty response case
    if (response[0] == '\0') return 0;

    Node * current = root;
    int sum = 0;

    // Iterate over the characters in the response
    for (int i = 0; response[i] != '\0'; i++)
    {
        // Map the current character to an index
        int index = mapCharToIndex(response[i]);

        // If no node exists at the index, return the sum so far
        if (current->children[index] == NULL) 
        {
            break;
        }

        // Add the myAmount of the current node to the sum
        sum += current->myAmount;
        // Move to the child node
        current = current->children[index];

    }

    // Add the subTrieAmount of the last node to the sum
    sum += current->subTrieAmount;

    return sum;
}


// function that coverts chars to indexes
int mapCharToIndex(char c)
{
    if ('a' <= c && c <= 'j') return c - 'a' + 10; 
    if ('k' <= c && c <= 'z') return c - 'k' + 20; 
    if ('A' <= c && c <= 'Z') return c - 'A' + 36; 
    if ('0' <= c && c <= '9') return c - '0'; 
    return -1; //  -1 for invalid characters
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
    char * response = (char *) malloc(1000 * sizeof(char));
    char * oldResponse = (char *) malloc(1000 * sizeof(char));
    char * newResponse = (char *) malloc(1000 * sizeof(char));

    // create initial root node
    Node * root = createNode();

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

