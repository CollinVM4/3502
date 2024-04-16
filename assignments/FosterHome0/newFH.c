/*
    - Collin Van Meter
    - 4/15/24
    - Assignment 0, resubmission
*/


// libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// definitions/globals
#define NAME_SIZE 1000    
int adoptionStatus[1000];
int initialWeekChecker = 0;

// family struct
typedef struct fosterFamily
{
    char lastName[NAME_SIZE];
    int positionsToMove;
    int currentPosition;
    int isFostering;
} fosterFamily;


// function to determine how many cages and weeks
void collectStarterInfo(int *numCages, int *numWeeks) 
{
    scanf("%d %d", numCages, numWeeks);
}

// function for adoption logic
void adoptCat(char catNames[1000][NAME_SIZE], fosterFamily *fam, int numCages)
{
    // return family's current cat to shelter 
    if (fam->isFostering == 1)
    {
        // reset flags 
        adoptionStatus[fam->currentPosition] = 0;
        fam->isFostering = 0; 
    }

    // for first week, do not add positionsToMove
    if (initialWeekChecker < 3) 
    {
        // concat last name to cat name
        strcat(catNames[fam->currentPosition], fam->lastName); 

        // update flags
        adoptionStatus[fam->currentPosition] = 1;
        fam->isFostering = 1; 
        initialWeekChecker++; 
    }

    // for subsequent weeks add positionsToMove
    else if (initialWeekChecker >= 3) 
    {
        // mod for circular movement
        fam->currentPosition = (fam->currentPosition + fam->positionsToMove) % numCages; 

        // check if not already adopted
        if (adoptionStatus[fam->currentPosition] == 0) 
        {
            // concat fam's last name to cat name
            strcat(catNames[fam->currentPosition], fam->lastName); 

            // update flags
            adoptionStatus[fam->currentPosition] = 1; 
            fam->isFostering = 1; 
        }
    }
}

int main()
{
    // declare and init variables, arrays
    int numCages, numWeeks = 0;
    char catNames[1000][NAME_SIZE];
    fosterFamily arrFamilies[3];

    // init adoptionStatus array
    for (int i = 0; i < 1000; i++)
    {
        adoptionStatus[i] = 0;
    }


    // init Lee family
    strcpy(arrFamilies[0].lastName, "Lee"); 
    arrFamilies[0].positionsToMove = 2;
    arrFamilies[0].currentPosition = 0;
    arrFamilies[0].isFostering = 0;

    // init Lyn family
    strcpy(arrFamilies[1].lastName, "Lyn"); 
    arrFamilies[1].positionsToMove = 3;
    arrFamilies[1].currentPosition = 1;
    arrFamilies[1].isFostering = 0;

    // init Eve family
    strcpy(arrFamilies[2].lastName, "Eve"); 
    arrFamilies[2].positionsToMove = 5;
    arrFamilies[2].currentPosition = 2;
    arrFamilies[2].isFostering = 0;


    // collect number of cages (num cats) and weeks (duration), then scan names into array 
    collectStarterInfo(&numCages, &numWeeks);
    for (int i = 0; i < numCages; i++)
    {
        scanf("%s", catNames[i]);
    }

    // loop through weeks
    for (int i = 0; i < numWeeks; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            adoptCat(catNames, &arrFamilies[j], numCages);
        }
    }

    // print final cat names
    for (int i = 0; i < numCages; i++)
    {
        // if cat is adopted, print "No Cat Found."
        if (adoptionStatus[i] != 0)
        {
            printf("No cat found.\n");
        }
        if (adoptionStatus[i] == 0)
        {
            printf("%s\n", catNames[i]);
        }
    }
    
    return 0;
}