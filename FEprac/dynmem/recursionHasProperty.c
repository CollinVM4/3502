#include <stdio.h>
#include <stdlib.h>


typedef struct node
{
    char *data;
    struct node *left, *middle, *right;
} node;


int hasProperty(node *root) 
{
    if(root == NULL) return 1;


    else if (root->middle == NULL)
    {
        return hasProperty(root->left) && return hasProperty(root->right);
    }
    






}


int main()
{




    return 0;
}