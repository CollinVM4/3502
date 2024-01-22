/*
    - Collin Van Meter
    - COP3502 
    - not finished, feel abt 70%  of the way there, some variables are still hard coded, commented out unfinished stuff, but hey, it kinda works.
*/

// libraries used 
#include<stdio.h>
#include<string.h>


// constant variables defined 
#define CAT_COUNT 6 
#define FAM_COUNT 3
#define NAME_SIZE 50


// function to determine how many cages (n) and weeks (k)
void collectStarterInfo(int *n, int *k) 
{
    scanf("%d %d", n, k);
}


// void collectCatNames(struct catOutline *catContainer, int catCount) 
// {
//     for (int i = 0; i < catCount; i++) 
//     {
//         scanf("%s", catContainer[i].catName);
//     }
// }    


// struct for families 
struct familyOutline 
{
    char lastName[NAME_SIZE];
    int positionsToMove;
    int startingPosition;
    int currentPosition;
};

// struct for cats
struct catOutline
{
    char catName[CAT_COUNT][NAME_SIZE];
    int adoptionStatus;
};

int main () 
{
    // determine how many cages (n) and weeks (k)
    int n, k, startingCatPlace, chosenCatForWeek, week;
    int initialWeekChecker = 1;

    collectStarterInfo(&n, &k);

    // fill the family struct's with the family data 
    struct familyOutline familyContainer[FAM_COUNT] = 
    {
        {"Lee", 2, 1, 0},
        {"Lyn", 3, 2, 0},
        {"Eve", 5, 3, 0}
    };

    // fill the cat struct's with the cat data 
    struct catOutline catContainer[CAT_COUNT] =
    {
        {"Steve", 0},
        {"CrunchyCatLuna", 0},        
        {"PrincessHoneyLuna", 0},        
        {"Bruce", 0},
        {"TippyToe", 0},
        {"Ili", 0}
    };

    // collectCatNames(catContainer, CAT_COUNT);

    // this is the logic for the first week only!
    if (initialWeekChecker == 1)
    {
        for (int i = 0; i < FAM_COUNT; i++)
        {
            chosenCatForWeek = familyContainer[i-1].startingPosition;
            strcat(catContainer[chosenCatForWeek].catName, familyContainer[i].lastName);
            familyContainer[i].currentPosition = chosenCatForWeek; // updates currentPosition to calculate new position for following weeks
        }
        initialWeekChecker -= 1;
    }
    
    // this is the logic for the weeks following the first 
    for (week = 0; week < k - 1; week++) 
    {

            // will occur each week
            for (int i = 0; i < FAM_COUNT; i++)
            {
                    // determine what cat the family will adopt
                    chosenCatForWeek = familyContainer[i].positionsToMove + familyContainer[i].currentPosition;  // adds each families moves to wherever they left off

                    if (chosenCatForWeek > CAT_COUNT)
                    {
                        chosenCatForWeek = (chosenCatForWeek - 1) % n + 1; // makes sure chosenCatForWeek stays in the 1-6 range
                    }

                    if (catContainer[chosenCatForWeek].adoptionStatus == 0) // logic to do the "No cat found."
                    {
                        strcat(catContainer[chosenCatForWeek].catName, familyContainer[i].lastName);
                        familyContainer[i].currentPosition = chosenCatForWeek; // updates currentPosition to calculate new position for following weeks
                        catContainer[chosenCatForWeek].adoptionStatus = 1;

                    }
                    if (catContainer[chosenCatForWeek].adoptionStatus == 1)
                    {
                        chosenCatForWeek = familyContainer[i].currentPosition - familyContainer[i].positionsToMove; // makes sure family will get same cat next week if adoption fails
                    }
            }

            // logic for returning cats the following week, reset adoption status       
            for (int i = 0; i < FAM_COUNT; i++)
            {
                for (int j = 0; j < CAT_COUNT; j++)
                {
                    catContainer[j].adoptionStatus = 0;
                }
            }
    }    

    // print the updated cat names
    for (int i = 0; i < CAT_COUNT; i++) 
    {
        printf("%s\n", catContainer[i].catName);
    };

return 0;
}