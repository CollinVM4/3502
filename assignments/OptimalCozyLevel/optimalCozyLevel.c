/*
    - Collin Van Meter
    - COP3502
    - Optimal Cozy Levels
*/


#include <stdio.h>
#include <stdlib.h>

// constants
#define MAX_CATS 15
#define MAX_FAMS 3

// globals
int numCats = 0;
int maxCozySum = 0;
int cozyLevels[MAX_CATS][MAX_FAMS] = {0};
int catFriendship[MAX_CATS][MAX_CATS] = {0};


// function prototype
void cozyCombo(int catIndex);


// function definition 
void cozyCombo(int catIndex) 
{
    // base case: stop when all cats are assigned
    if (catIndex == numCats) return;


    // iterate over each of the 3 families
    for (int i = 0; i < MAX_FAMS; i++) 
    {
        // grab base cozy level 
        int curCozyLevel = cozyLevels[catIndex][i];


        // declare & init max Fship level
        int maxFriendship = 0;
        // iterate over each cat
        for (int j = 0; j < catIndex; j++) 
        {
            // check if the cur Fship level is greater than the maximum
            if (catFriendship[catIndex][j] > maxFriendship)
            {
                // update max Fship level
                maxFriendship = catFriendship[catIndex][j]; 
            }
        }
        // add max Fship level to cur cozy level
        curCozyLevel += maxFriendship;

        // update max cozy sum
        maxCozySum += curCozyLevel;

        // recursive call for next cat
        cozyCombo(catIndex + 1);

    }
}


int main()
{

    // read in the num of cats 
    scanf("%d", &numCats);

    // based on num of cats, read in a cozy level for each 
    for (int i = 0; i < numCats; i++)
    {
        for (int j = 0; j < MAX_FAMS; j++)
        {
            scanf("%d", &cozyLevels[i][j]);
        }
    }
    // based on num of cats, read in cat friendship levels 
    for (int i = 0; i < numCats; i++)
    {
        for (int j = 0; j < numCats; j++)
        {
            scanf("%d", &catFriendship[i][j]);
        }
    }


    // initial recursive call
    cozyCombo(0);

    // print max cozy sum
    printf("Max Cozy Sum [%d]\n", maxCozySum);


    return 0;
}