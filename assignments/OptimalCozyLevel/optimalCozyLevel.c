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
#define INF 1e9

// globals
int numCats = 0;
int maxCozySum = -INF;
int leastCozyCat = INF;
int cozyLevels[MAX_CATS][MAX_FAMS];
int catFriendship[MAX_CATS][MAX_CATS];
int catFamily[MAX_CATS];


// function prototype
void cozyCombo(int catIndex);


// function definition 
void cozyCombo(int catIndex) 
{
    // base case: stop when all cats are assigned
    if (catIndex == numCats) 
    {
        int totalCozy = 0;
        int minCozy = INF;

        for (int i = 0; i < numCats; i++) 
        {
            totalCozy += cozyLevels[i][catFamily[i]];

            for (int j = i + 1; j < numCats; j++) 
            {
                if (catFamily[i] == catFamily[j]) 
                {
                    totalCozy += catFriendship[i][j];
                }
            }

            if (cozyLevels[i][catFamily[i]] < minCozy) 
            {
                minCozy = cozyLevels[i][catFamily[i]];
            }
        }
        if (totalCozy > maxCozySum) 
        {
            maxCozySum = totalCozy;
            leastCozyCat = minCozy;
        }

        return;
    }

    // try all possible families for the current cat
    for (int i = 0; i < MAX_FAMS; i++) 
    {
        catFamily[catIndex] = i;
        cozyCombo(catIndex + 1);
        catFamily[catIndex] = -1; // unassign the cat from the family
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
    printf("Least Cozy Cat [%d]\n", leastCozyCat);

    return 0;
}