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
    llint food;
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
void shareFood(Node * cur, int amt);


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


// function with logic for inserting a new raccoon
Node * insertRaccoon(Node * root, int location, int hatSize)
{
    // base case: empty tree (first raccoon)
    if (root == NULL) return createNode(location, hatSize);

    // recursive case: insert raccoon, branch left/right

    if (location <= root->location) //  raccoon < root
    {
        // branch left
        root->left = insertRaccoon(root->left, location, hatSize);
        root->left->parent = root; // set parent to be root 
    }
    else // raccoon > root
    {
        // branch right
        root->right = insertRaccoon(root->right, location, hatSize);
        root->right->parent = root; // set parent to be root 
    }

    // rotations to maintain heirarchy
    root = rotateLeft(root);
    root = rotateRight(root);

    return root; // return the root of tree
}


// function with logic for removing a raccoon 
Node * captureRaccoon(Node * root, int location)
{
    // empty tree
    if (root == NULL) return NULL;

    // find the node 
    Node * targetCapture = findClosest(root, location); 

    // print out food data
    printf("%lld\n", targetCapture->food);

    // no children
    if (targetCapture->left == NULL && targetCapture->right == NULL)
    {
        if (targetCapture->parent != NULL)
        {
            if (targetCapture->parent->left == targetCapture)
            {
                targetCapture->parent->left = NULL;
            }
            else if (targetCapture->parent->right == targetCapture)
            {
                targetCapture->parent->right = NULL;
            }
        }

        free(targetCapture); // free the memory
        return NULL; // return NULL
    }

    // one child
    else if (targetCapture->left == NULL || targetCapture->right == NULL)
    {
        Node * temp;
        if (targetCapture->left != NULL)    // left
        {
            temp = targetCapture->left;
        } 
        else                                // right
        {   
            temp = targetCapture->right;
        }
        
        free(targetCapture); // free memory
        return root; // return the original root
    }

    // two children
    else
    {
        Node * temp = targetCapture->right; // set temp to the right child
        while (temp->left != NULL) // find the leftmost child
        {
            temp = temp->left;
        }

        // perform data swap
        int tempLocation = temp->location; // save the location
        targetCapture->location = temp->location; 
        targetCapture->hat = temp->hat; 
        targetCapture->food = temp->food; 

        // temp parent is not being captured 
        if (temp->parent != targetCapture)
        {
            temp->parent->left = temp->right;
        }

        // temp parent is being captured
        else
        {
            targetCapture->right = temp->right;
        }

        // temp has right cild
        if (temp->right != NULL)
        {
            temp->right->parent = temp->parent;
        }

        free(temp); // free the memory
        return root; // return the root
    }
}


// function with logic for changing a raccoon's hat 
Node * changeHat(Node * current, int hatSize)
{
    // empty tree
    if (current == NULL) return NULL;

    // change hat if new hat is better
    if (hatSize > current->hat)
    {
        current->hat = hatSize; // change the hat size
    }

    return current; // return current node
}


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

        // update if closer 
        if (distance < minDistance)
        {
            minDistance = distance;
            closest = cur;
        }

        // move to left or right child based on location
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


// function with logic for stealing food
void stealFood(Node * root, int location, int amt)
{
    // empty tree
    if (root == NULL) return;

    // find the closest raccoon
    Node * closest = findClosest(root, location);

    // Check if closest is NULL
    if (closest == NULL) return;

    // share the food
    shareFood(closest, amt);
}


// function with logic for sharing food
void shareFood(Node * cur, int amt)
{
    // no raccoon :C
    if (cur == NULL) return;

    // if top dawg raccoon
    if(cur->parent == NULL)
    {
        cur->food += amt;
        return;
    }

    // cur keeps half of the food ROUNDED DOWN
    int keep = amt / 2;

    // give the remaining half of the food ROUNDED UP
    int give = (int)ceil((double)amt / 2);

    // update the food of the raccoon
    cur->food += keep;

    // share the remaining food with the raccoon's direct leader
    shareFood(cur->parent, give);
}


// function with logic for printing tree data
void printTree(Node * root)
{  
    // empty tree
    if (root == NULL) return;

    // call for left subtree
    printTree(root->left); 

    // print tree data 
    printf("%d %lld\n", root->location, root->food);

    // call for right subtree
    printTree(root->right); // call for right subtree
}


// function with logic for rotating left 
Node * rotateLeft(Node * current)
{
    // empty tree or no right child
    if (current == NULL || current->right == NULL) return current;

    // right child with larger hat size
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


// function with logic for rotating right
Node * rotateRight(Node * current)
{
    // empty tree or no left child
    if (current == NULL || current->left == NULL) return current;

    // left child with larger hat size
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


// main function
int main()
{
    // init root
    Node * root = NULL;  

    // command handling
    char command[20];
    while(1)
    {
        scanf("%s", command); // read command
    
        if (command[0] == 'A') // ADD X H 
        {
            int location, hatSize;
            scanf("%d %d", &location, &hatSize); // read location and hat size
            root = insertRaccoon(root, location, hatSize); // insert raccoon
        }
        else if (command[0] == 'C') // CAPTURE X
        {
            int location;
            scanf("%d", &location); // read location
            captureRaccoon(root, location); // capture raccoon
        }
        else if (command[0] == 'H') // HAT X H 
        {
            int location, hatSize;
            scanf("%d %d", &location, &hatSize); // read location and hat size
            Node * target = findClosest(root, location); // find the node at the location
            target = changeHat(target, hatSize); // change raccoon's hat
        }
        else if (command[0] == 'S') // STEAL X A
        {
            int location, amt;
            scanf("%d %d", &location, &amt); // read location and amount
            stealFood(root, location, amt); // steal food
        }
        else if (command[0] == 'Q') // QUIT 
        {
            break; // break command loop
        }

    }

    // print tree data
    printTree(root);
    
    return 0;
}