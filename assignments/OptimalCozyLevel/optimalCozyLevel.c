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
int baseLevels[MAX_CATS][MAX_FAMS];
int catFriendship[MAX_CATS][MAX_CATS];
int assignedFamily[MAX_CATS];


// function prototype
void cozyCombo(int catIndex);


// function definition 
void cozyCombo(int catIndex) 
{
    // base case: when all cats assigned
    if (catIndex == numCats) 
    {
        int curCozy = 0;
        int minCozy[MAX_FAMS];

        // init minCozy array
        for (int i = 0; i < MAX_FAMS; i++) 
        {
            minCozy[i] = INF;
        }

        // iterate through each cat
        for (int i = 0; i < numCats; i++) 
        {   
            curCozy += baseLevels[i][assignedFamily[i]]; // grab base cozy level

            for (int j = i + 1; j < numCats; j++) 
            {
                if (assignedFamily[i] == assignedFamily[j]) // if in same family
                {
                    curCozy += catFriendship[i][j]; // calculate friendship level
                }
            }

            if (baseLevels[i][assignedFamily[i]] < minCozy[assignedFamily[i]]) 
            {
                minCozy[assignedFamily[i]] = baseLevels[i][assignedFamily[i]];
            }

            for (int j = i + 1; j < numCats; j++) 
            {
                if (assignedFamily[i] == assignedFamily[j]) // if in same family
                {
                    minCozy[assignedFamily[i]] += catFriendship[i][j]; // calculate friendship level
                }
            }
        }

        int curMin = -1;
        for (int i = 0; i < MAX_FAMS; i++) 
        {
            // if min cozy is less than curMin or curMin has not been set
            if (curMin == -1 || minCozy[i] < curMin)
            {
                curMin = minCozy[i];
            }
        }

        // if curCozy is greater than maxCozySum 
        if (curCozy > maxCozySum)
        {
            maxCozySum = curCozy;
        }
        // if curMin is less than leastCozyCat
        if (curMin < leastCozyCat) 
        {
            leastCozyCat = curMin;
        }

        return;
    }

    // try all possible families for the current cat
    for (int i = 0; i < MAX_FAMS; i++) 
    {
        assignedFamily[catIndex] = i;
        cozyCombo(catIndex + 1);
        assignedFamily[catIndex] = -1; // unassign the cat from the family
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
            scanf("%d", &baseLevels[i][j]);
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