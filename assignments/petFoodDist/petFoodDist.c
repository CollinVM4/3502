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
    Node * children[32];
} Node;

// definitions


// func prototypes


// func definitions



int main()
{
    // delcare and init max/min match values
    int minMatches, maxMatches = 0;







    // command handling
    char command[20];
    while (1)
    {
        scanf("%s", command);

        if (command[0] == 'A') // ADD R A
        {
            // addFamily(Recieving R, Food A)
        }
        else if (command[0] == 'C') // CHANGE R N
        {
            // change(response R, question N)
        }
        else if (command[0] == 'S') // SUM R
        {
            // sum of fams that responded with R

            // printf("%d %d", minMatches, maxMatches);
        }
        else if (command[0] == 'Q') // QUIT
        {
            break; // end of commands
        }

    }
    


    return 0;
}