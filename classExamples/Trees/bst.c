/*
    binary search tree
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node 
{
    char * data;
    struct Node * left;
    struct Node * right;
} Node;


Node * createNode(char * data)
{
    Node * res = (Node *) malloc(sizeof(Node));
    res->left = NULL;
    res->right = NULL;
    res->data = strdup(data);

    return res;
}

// return the root of the BST
Node * insertName(Node * root, char * name)
{
    // base case: empty tree
    if (root == NULL)
    {
        return createNode(name);
    }

    // use strcmp to determine direction
    int res = strcmp(root->data, name);
    if (res > 0)
    {
        // go left
        root->left = insertName(root->left, name);
    }
    if (res < 0)
    {
        // go right
        root->right = insertName(root->right, name);
    }

    return root;
}


// returns 1 if a name is in the tree, 0 otherwise
int contains(Node * root, char * name)
{
    if (root == NULL)
    {
        printf("not in tree\n"); 
        return 0; // empty tree
    } 

    int res = strcmp(root->data, name);

    // base case
    if (res == 0) 
    {
        printf("is in tree\n"); 
        return 1;
    }

    // go left
    if (res > 0 )
    {
        return contains(root->left, name);
    }

    // go right
    if (res < 0 )
    {
        return contains(root->right, name);
    }

}


int main()
{
    Node * root = NULL;

    root = insertName(root, "alice");
    root = insertName(root, "alex");
    contains(root, "alice");
    root = insertName(root, "ali");
    contains(root, "fred");
    root = insertName(root, "carol");
    root = insertName(root, "bob");
    root = insertName(root, "david");
    contains(root, "alice");
    root = insertName(root, "erik");
    contains(root, "al");






    return 0;
}