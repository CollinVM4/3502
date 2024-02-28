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
#define MEGA_NUM 1e9

// globals
int numCats = 0;
int maxCozySum = -MEGA_NUM;
int leastCozyCat = -MEGA_NUM;
int baseLevels[MAX_CATS][MAX_FAMS];
int catFriendship[MAX_CATS][MAX_CATS];
int assignedFamily[MAX_CATS];


int cozyCombo(int catIndex) 
{
    if (catIndex == numCats) 
    {
        // declare and init vars
        int thisCozySum = 0;
        int minCozyCat = MEGA_NUM;

        // declare and init array to hold family cat count
        int familyCatCounter[MAX_FAMS];

        for (int i = 0; i < numCats; i++) 
        {
            familyCatCounter[assignedFamily[i]]++;
        }

        // make sure each family has a cat
        for (int i = 0; i < MAX_FAMS; i++) 
        {
            if (familyCatCounter[i] == 0) 
            {
                return 0;
            }
        }

        // loop through each cat
        for (int i = 0; i < numCats; i++) 
        {
            int curCozy = baseLevels[i][assignedFamily[i]]; // grab base coziness 

            // check for cats assigned in fam, add friendship (+/-)
            for (int j = 0; j < numCats; j++) 
            {
                // if not itself and in same family
                if (j != i && assignedFamily[j] == assignedFamily[i]) 
                {
                    curCozy += catFriendship[i][j]; // add friendship
                }
            }

            // check for min cozy cat
            if (curCozy < minCozyCat) 
            {
                minCozyCat = curCozy;
            }

            thisCozySum += curCozy; // update sum
        }

        // update max cozy if needed 
        if (thisCozySum > maxCozySum) 
        {
            maxCozySum = thisCozySum;
        }

        // update the least cozy cat if needed
        if (minCozyCat > leastCozyCat)
        {
            leastCozyCat = minCozyCat;
        }

        return 0;
    }

    // try each family
    for (int i = 0; i < MAX_FAMS; i++) 
    {
        assignedFamily[catIndex] = i;
        cozyCombo(catIndex + 1);
    }

    return 0;
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

    // initial  call
    cozyCombo(0);

    // print max cozy sum and least cozy cat
    printf("%d %d\n", maxCozySum, leastCozyCat);

    return 0;
}