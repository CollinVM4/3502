#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// hardcoded now, TODO -- will use DMA later.
#define NAME_SIZE 20
#define LOCATION_COUNT 10
#define PLACEMENT_COUNT 15


// struct for individual placements 
struct placementOutline
{
    long long int ID;
    long long int foodLevel;
    long long int prevFoodLevel;
    long long int individualAmountStolen;
};


// struct for locations
struct locationOutline 
{
    char locationName[NAME_SIZE];
    struct placementOutline placementList[PLACEMENT_COUNT];
    long long int totalAmountStolen;
};


struct TEMPlocationOutline 
{
    char locationName[NAME_SIZE];
    struct placementOutline placementList[PLACEMENT_COUNT];
    long long int totalAmountStolen;
};


void addToList(struct TEMPlocationOutline* tempStruct, struct locationOutline* mainStruct)
{
    printf("added to list\n");
    strcpy(mainStruct->locationName, tempStruct->locationName);

    mainStruct->placementList->ID = tempStruct->placementList->ID;
    mainStruct->placementList->foodLevel = tempStruct->placementList->foodLevel;

    printf("%lld\n", mainStruct->placementList->ID);
}


// function that takes in two structs and checks if the names/placements match any existing entries
int compareEntry(struct TEMPlocationOutline* entry1, struct locationOutline* entry2)
{
    /*debug*/printf("entry1[%s] entry2[%s]\n", entry1->locationName, entry2->locationName);

    int match = 0;
    if (strcmp(entry1->locationName, entry2->locationName) != 0 && entry1->placementList->ID != entry2->placementList->ID)
    {
        match = 0; // 0 = new 
        printf("new\n");
    } else
    {
        match = 1; // 1 = existing
        printf("not new \n");
    }
    return match;
}


// function that takes in a struct and checks how much food has been taken/added since last time it was entered
int checkFood(struct locationOutline* curEntry)
{
    /*debug*/printf("checking food func\n");
    int curFoodLevel = curEntry->placementList->foodLevel;
    int prevFoodLevel = curEntry->placementList->prevFoodLevel;
    int maxFoodStolen = 0;

    if (curFoodLevel < prevFoodLevel) // less now than previously
    {
        maxFoodStolen = prevFoodLevel - curFoodLevel;
    } else if (curFoodLevel == prevFoodLevel || curFoodLevel > prevFoodLevel) // more or equal than previously
    {
        maxFoodStolen = 0;
    }

    curEntry->placementList->prevFoodLevel = curFoodLevel;

    return maxFoodStolen;
}



int main() 
{
    int i = 0; // for loop usage 
    long long int endToken = -1; // setting up endToken for do,while loop
    int numEntries = 1; // use in for loop, printing out results
    int matchFound = 0;


    struct locationOutline locations[30] = {0}; // instance of array of structs
    struct TEMPlocationOutline TEMPlocations[30] = {0}; // instance of array of structs


    // scan for entries, terminate when "END -1 -1" is entered 
    do
    {
        // scan for req. info
        scanf("%s %lld %lld", TEMPlocations[i].locationName, &TEMPlocations[i].placementList->ID, 
        &TEMPlocations[i].placementList->foodLevel);

        for (int j = 0; j < numEntries; j++)
        {
            int temp = compareEntry(&TEMPlocations[i], &locations[j]);
            matchFound += temp;
            printf("match found value[%d]\n", matchFound);

            if (matchFound < 1) // 1 = No matches found 
            {
                addToList(&TEMPlocations[i], &locations[i]);
                numEntries++;
                matchFound=0;
                break;
            }

            if (matchFound >= 1)
            {
                checkFood(&locations[i]);
                break;
            }
        }
        
        
    
        

        // increase index
        i++;

    } while (locations[i - 1].placementList->ID != endToken); // will be active until a "-1" is scanned into an ID slot
    





    // print out the results 
    for (int k = 0; k < numEntries - 2; k++) // subtract by 2 so we dont print out the "END -1 -1"
    {
        printf("%s %lld %lld\n", locations[k].locationName, locations[k].placementList[k].ID, locations[k].placementList[k].foodLevel);
    }

    return 0;
}
