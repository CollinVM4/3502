/*
    - Collin Van Meter
    - COP 3502C - Assignment 5
    - 3/31/2024
*/

// libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// definitions
#define llint long long int
#define MEGA_NUM 1000000000

// structs
typedef struct Node 
{
    struct Node * left, * right, * parent;
    int hat;
    int location;
    llint food; // llint = long long int
} Node;


// function prototypes
Node * createNode(int location, int hatSize);
Node * insertRaccoon(Node * root, int location, int hatSize);
Node * captureRaccoon(Node * root, int location);
Node * changeHat(Node * current, int hatSize);
void stealFood(Node * root, int location, int amt);
Node * findClosest(Node * root, int location);
Node * rotateLeft(Node * current);
Node * rotateRight(Node * current);
void printTree(Node * root);
void shareFood(Node * raccoon, int amt);


// WORKS :D
// function to add a new node to the tree
Node * createNode(int location, int hatSize)
{
    // malloc memory for new node
    Node * newNode = (Node *) malloc(sizeof(Node));

    // set node data
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    newNode->hat = hatSize;
    newNode->location = location;
    newNode->food = 0;

    return newNode; // return resulting node
}

// WORKS :D 
// function with logic for inserting a new raccoon
Node * insertRaccoon(Node * root, int location, int hatSize)
{
    // base case: empty tree (first raccoon)
    if (root == NULL) return createNode(location, hatSize);

    // recursive case: insert raccoon 
    if (location < root->location) //  raccoon < root
    {
        // branch left
        root->left = insertRaccoon(root->left, location, hatSize);
        root->left->parent = root; // set parent to be root 
    }
    else if (location > root->location) // raccoon > root
    {
        // branch right
        root->right = insertRaccoon(root->right, location, hatSize);
        root->right->parent = root; // set parent to be root 
    }

    // Perform rotations to maintain hat size hierarchy
    root = rotateLeft(root);
    root = rotateRight(root);

    return root; //returns the root of the tree
}

// WORKS :D maybe 
// function with logic for removing a raccoon AKA "Node Removal"
Node * captureRaccoon(Node * root, int location)
{
    // base case: empty tree
    if (root == NULL) return NULL;

    // recursive case: capture raccoon

    // left subtree
    if (location < root->location)
    {
        // capture left
        root->left = captureRaccoon(root->left, location);
    }
    // right subtree
    else if (location > root->location) 
    {
        // capture right
        root->right = captureRaccoon(root->right, location);
    }
    // location == root
    else 
    {
        printf("%lld\n", root->food); // print food level upon capture
        // no children :C
        if (root->left == NULL && root->right == NULL)
        {
            free(root); // free root memory
            return NULL; // return NULL
        }
        // only one child (left/right)
        else if (root->left == NULL) // (no left node)
        {
            Node * temp = root->right; // temporarily store
            free(root); // free root memory
            return temp; // return right child
        }
        else if (root->right == NULL) // (no right node)
        {
            Node * temp = root->left; // temporarily store
            free(root); // free root memory
            return temp; // return left child
        }
        // for two children
        else
        {
            Node * temp = findClosest(root->right, root->location); // store closest 
            root->location = temp->location; // swap the nodes
            root->right = captureRaccoon(root->right, temp->location); // delete 
        }
    }

    // Perform rotations to maintain hat size hierarchy
    if (root != NULL)
    {
        root->food = 0; // reset food
        root = rotateLeft(root);
        root = rotateRight(root);
    }

    return root;
}


// WORKS :D 
// function with logic for changing a raccoon's hat 
Node * changeHat(Node * current, int hatSize)
{
    // base case: empty tree
    if (current == NULL) return NULL;

    // recursive case: change hat

    // left subtree
    if (hatSize < current->hat)
    {
        // change left hat
        current->left = changeHat(current->left, hatSize);
    }
    // right subtree
    else if (hatSize > current->hat) 
    {
        // change right hat
        current->right = changeHat(current->right, hatSize);
    }

    // change hat if new hat is better
    if (hatSize > current->hat)
    {
        current->hat = hatSize; // change the hat size
    }

    return current; // return current node
}


// WORKS :D
// function with logic for finding the closest raccoon
Node * findClosest(Node * root, int location)
{
    Node * closest = NULL;
    Node * currcurent = root;

    int minDistance = MEGA_NUM; // init and set to mega num (very very big)

    Node * cur = root;
    // iterate through the tree
    while (cur != NULL)
    {
        // calculate distance from current node to location
        int distance = abs(cur->location - location);

        // update closest node if distance is less than minDistance and not the node itself
        if (distance < minDistance && cur->location != location)
        {
            minDistance = distance;
            closest = cur;
        }

        // move to the left or right child based on the location
        if (location < cur->location)
        {
            cur = cur->left;
        }
        else
        {
            cur = cur->right;
        }
    }

    return closest;
}


// need to test
// function with logic for stealing food
void stealFood(Node * root, int location, int amt)
{
    // base case: empty tree
    if (root == NULL) return;

    // find the closest raccoon
    Node * closest = findClosest(root, location);

    // share the food
    shareFood(closest, amt);
}


// need to test
// function with logic for sharing food
void shareFood(Node * raccoon, int amt)
{
    // base case: no raccoon
    if (raccoon == NULL) return;

    // raccoon keeps half of the food (rounded down)
    int keep = amt / 2;

    // the remaining half of the food (rounded up) is passed to the raccoon's direct leader
    int pass = (int)ceil((double)amt / 2);

    // update the food of the raccoon
    raccoon->food += keep;

    // share the remaining food with the raccoon's direct leader
    shareFood(raccoon->parent, pass);
}


// WORKS :D 
// function with logic for printing tree data
void printTree(Node * root)
{  
    // base case: empty tree
    if (root == NULL) return;

    // call for left subtree
    printTree(root->left); 

    // print tree data 
    printf("%d %lld\n", root->location, root->food);

    // call for right subtree
    printTree(root->right); // call for right subtree
}


// NEED TO TEST
// function with logic for rotating left 
Node * rotateLeft(Node * current)
{
    // base case: empty tree or no right child
    if (current == NULL || current->right == NULL) return current;

    // Check if the right child has a larger hat size
    if (current->right->hat > current->hat)
    {
        // rotate left
        Node * temp = current->right;
        current->right = temp->left;
        temp->left = current;
        return temp; // return new root
    }

    return current; // return current node if no rotation happened
}


// NEED TO TEST
// function with logic for rotating right
Node * rotateRight(Node * current)
{
    // base case: empty tree or no left child
    if (current == NULL || current->left == NULL) return current;

    // Check if the left child has a larger hat size
    if (current->left->hat > current->hat)
    {
        // rotate right
        Node * temp = current->left;
        current->left = temp->right;
        temp->right = current;
        return temp; // return new root
    }

    return current; // return current node if no rotation happened
}


// end of function definitions


// main function
// int main()
// {
//     // init root
//     Node * root = NULL;  

//     // command handling
//     char command[5];
//     while(1)
//     {
//         scanf("%s", command); // read command
    
//         if (command[0] == 'A') // ADD X H 
//         {
//             int location, hatSize;
//             scanf("%d %d", &location, &hatSize); // read location and hat size
//             root = insertRaccoon(root, location, hatSize); // insert raccoon
//         }
//         else if (command[0] == 'C') // CAPTURE X
//         {
//             int location;
//             scanf("%d", &location); // read location
//             root = captureRaccoon(root, location); // capture raccoon
//         }
//         else if (command[0] == 'H') // HAT X H 
//         {
//             int location, hatSize;
//             scanf("%d %d", &location, &hatSize); // read location and hat size
//             Node * node = findClosest(root, location); // find the node at the location
//             if (node != NULL) {
//                 node = changeHat(node, hatSize); // change raccoon's hat
//             }
//         }
//         else if (command[0] == 'S') // STEAL X A
//         {
//             int location, amt;
//             scanf("%d %d", &location, &amt); // read location and amount
//             stealFood(root, location, amt); // steal food
//         }
//         else if (command[0] == 'Q') // QUIT 
//         {
//             break; // break command loop
//         }

//     }

//     printf("hat [%d]\n", root->right->hat); 

//     // print tree data
//     printTree(root);

//     return 0;
// }

int main()
{
    // init root
    Node * root = NULL;  

    // Add nodes
    root = insertRaccoon(root, 10, 5); // Add raccoon at location 10 with hat size 5
    root = insertRaccoon(root, 5, 3); // Add raccoon at location 5 with hat size 3
    root = insertRaccoon(root, 11, 7); // Add raccoon at location 15 with hat size 7


    Node * node = findClosest(root, 10); // find the node at the location 10

    // Print tree data before changing hat
    printf("Before changing hat:\n");
    printf("node [%d] hat [%d]\n",node->location, node->hat);
    // Change hat size
    if (node != NULL) {
        node = changeHat(node, 8); // change raccoon's hat to size 8
    }

    // Print tree data after changing hat
    printf("After changing hat:\n");
    printf("node [%d] hat [%d]\n",node->location, node->hat);
    return 0;
}


