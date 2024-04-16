
// This program demonstrates
//  * a trie that can store words
//  * how to insert into a trie
//  * how to remove from a trie
//  * how to check if a word is in a trie

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define MAX_NAMES 1000

// Alias
typedef struct Node Node;

// Trie node struct definition
struct Node {
    Node * children[26];
    int flag; // 1 if word ending at is contained; 0 otherwise
};

// Prototypes
Node * insertWord(Node * root, char * word);
void removeWord(Node * root, char * word);
int containsWord(Node * root, char * word);
void swap(Node * root, char a, char b);
int getKth(Node * root, int k, char * res);

// Function to insert a word into a trie
Node * insert(Node * root, char * word) {

    if(root == NULL)
    {
        root = createNode();
    }
    root->subTrieCount++;
    if (word[0] == "\0")
    {
        root->flag++;
        return root;
    }
    root->children[word[0]- 'a'] = insert(root->children[word[0] - 'a'], word + 1);
    return root;
}

// Function to remove a word from a trie
void removeWord(Node * root, char * word) {
    // If root does not exist
    if (!root) {
        // Cannot remove word
        return;
    }

    // If word is at end
    if (word[0] == '\0') {
        root->flag = 0;
    } else {
        // Determine child index
        int index = word[0] - 'a';

        // Remove word without first letter from child's trie
        removeWord(root->children[index], &word[1]);
    }
}

// Function to check if a word is in a trie
// Returns 1 if the word is in the root
// Returns 0 otherwise
int containsWord(Node * root, char * word) {
    // If root does not exist
    if (!root) {
        return 0;
    }

    // If word is at end
    if (word[0] == '\0') {
        // The flag stores if the word is contained
        return root->flag;
    } else {
        // Determine child index
        int index = word[0] - 'a';

        // Check containment in child with first letter of word removed
        return containsWord(root->children[index], &word[1]);
    }
}

// Function to delete a trie
void deleteTrie(Node * root) {
    // If trie is empty stop
    if (root == NULL) return;

    // Delete all the children
    for (int i = 0; i < 26; i++) {
        deleteTrie(root->children[i]);
    }

    // Delete the root last (post order)
    free(root);
}

void swap(Node * root, char a, char b)
{
    if(!root) return; 
    Node * tmp = root->children[a - 'a'];
    root->children[a - 'a'] = root->children[b - 'a'];
    root->children[b - 'a'] = tmp;
    for (int i = 0; i < 26; i++)
    {
        swap(root->children[i], a, b);
    }
    
}


int getKth(Node * root, int k, char * res)
{
    if (k <= 0 && root->flag) return k;
    else return 0;
}




int main(int argc, char *argv[]) {
    Node * root = NULL;

    // Check if the path to MED_3_CIPHER.txt is provided
    if (argc < 2) {
        printf("Please provide the path to MED_3_CIPHER.txt as a command line argument.\n");
        return 1;
    }

    // Open MED_3_DICT.txt to read names
    FILE *file = fopen("MED_3_DICT.txt", "r");
    if (file == NULL) {
        printf("Failed to open MED_3_DICT.txt\n");
        return 1;
    }

    char * names[MAX_NAMES];
    int num_names = 0;
    char buffer[MAX_NAME_LENGTH];

    // Read names from MED_3_DICT.txt
    while (fgets(buffer, MAX_NAME_LENGTH, file) != NULL) {
        // Remove newline character
        buffer[strcspn(buffer, "\n")] = 0;

        // Allocate memory and copy the name
        names[num_names] = malloc(strlen(buffer) + 1);
        strcpy(names[num_names], buffer);
        num_names++;
    }

    fclose(file);

    // Open MED_3_CIPHER.txt to read operations
    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Failed to open %s\n", argv[1]);
        return 1;
    }

    char operation[MAX_NAME_LENGTH];
    char name[MAX_NAME_LENGTH];

    // Perform operations from MED_3_CIPHER.txt
    while (fscanf(file, "%s %s", operation, name) == 2) {
        if (strcmp(operation, "insert") == 0) {
            printf("Inserting %s...\n", name);
            root = insertWord(root, name);
        } else if (strcmp(operation, "remove") == 0) {
            printf("Removing %s...\n", name);
            removeWord(root, name);
        }

        for (int j = 0; j < num_names; j++) {
            int cont = containsWord(root, names[j]);
            if (cont) {
                printf("  %s is contained.\n", names[j]);
            } else {
                printf("  %s is NOT containted.\n", names[j]);
            }
        }
    }

    fclose(file);

    // Delete trie
    deleteTrie(root);

    // Free names
    for (int i = 0; i < num_names; i++) {
        free(names[i]);
    }

    return 0;
}
