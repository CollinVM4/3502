#include <stdio.h>
#include <stdlib.h>



typedef struct Node
{
    int flag;
    struct Node * children[26];
} Node; 


// prototypes
int countQs1(Node * root);
int countQs2(Node * root);
Node * insert(Node * root, char * word);
int valid(char * word);

// go down q edge 
int countQs1(Node * root)
{
    if(root == NULL) return 1;

    return countQs2(root->children['q' - 'a']);
}

// explore the full true 
// traversal (pre-order)
int countQs2(Node * root)
{
    // base case
    if (root == NULL) return 0;

    int ans = 0;
    if(root->flag == 1) ans++;

    for (int i = 0; i < 26; i++)
    {
        ans += countQs2(root->children[i]);
    }
    


    return ans;
}

Node * insert(Node * root, char * word)
{
    if (root == NULL)
    {
        root = (Node * ) calloc(1, sizeof(Node));
    }


    // base:
    if (word[0] == '\0')
    {
        root->flag++;
        return root;
    }
    

    // recursive case
    int index = word[0] - 'a'; // in range 0 to 25
    root->children[index] = insert(root->children[index], &(word[1]));
    
}

int valid(char * word)
{
    for (int i = 0; i < word[i]; i++)
    {
        if (word[i] < 'a' || word[i] > 'z')
        {
            return 0;
        }
        return 1;
    }
    
}



int main()
{

    FILE * ifp;
    Node * root = NULL;

    ifp = fopen("words.txt", "r");
    char word[1000];

    while (EOF != fscanf(ifp, "%s", word))
    {
        root = insert(root, word);
    }
    
    printf("");

    countQs1(root);

    return 0;
}