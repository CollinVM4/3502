#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// hardcoded now, TODO -- will use DMA later.
#define NAME_SIZE 20
#define LOCATION_COUNT 3
#define PLACEMENT_COUNT 5

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



int main() 
{
    int i = 0; // for loop usage 
    long long int endToken = -1; // setting up endToken for do,while loop
    int numEntries = 1; // use in for loop, printing out results
    int isNew = 1, checkFood = 0;


    struct locationOutline locations[30] = {0}; // instance of array of structs
    struct TEMPlocationOutline TEMPlocations[30] = {0}; // instance of array of structs



    // scan for entries, terminate when "END -1 -1" is entered 
    do
    {
        printf("start do while loop\n");

        // scan for req. info
        scanf("%s %lld %lld", TEMPlocations[i].locationName, &TEMPlocations[i].placementList[i].ID, 
        &TEMPlocations[i].placementList[i].foodLevel);



        // fix for before comparing through prev entries 
        // maybe check all locations, make a flag to notify that match, then further check placement

            for (int j = 0; j < numEntries; j++)
            {   /*debug*/printf("tempNAME [%s] bankedNAME [%s]\n", TEMPlocations[i].locationName, locations[j].locationName);

                if (strcmp(TEMPlocations[i].locationName, locations[j].locationName) != 0 
                    || TEMPlocations[i].placementList[i].ID != locations[j].placementList[j].ID)
                {
                    checkFood = 0; isNew = 1;
                } else
                {
                    /*debug*/printf("did not add to main struct\n");
                    checkFood = 1; isNew = 0;
                } 

                    // new entry logic, if yes, assign temp values to main struct 
                    if (isNew == 1)
                    {
                        strcpy(locations[i].locationName, TEMPlocations[i].locationName);
                        locations[i].placementList[i].ID = TEMPlocations[i].placementList[i].ID;
                        locations[i].placementList[i].foodLevel = TEMPlocations[i].placementList[i].foodLevel;
                        numEntries++;
                        printf("added to main struct\n");
                        break;
                    };
            }


        
        
        // check food logic
        if (checkFood == 1) 
        {
            // check if new input food level is less than previous food level, if so, FOOD STOLEN!!! 
            if (locations[i].placementList[i].foodLevel < locations[i].placementList[i].prevFoodLevel)  // if food stolen
            {
                locations[i].placementList[i].individualAmountStolen =
                locations[i].placementList[i].foodLevel - locations[i].placementList[i].prevFoodLevel;
            } else if (locations[i].placementList[i].foodLevel == locations[i].placementList[i].prevFoodLevel) // if no food stolen or added
            {
                locations[i].placementList[i].foodLevel = locations[i].placementList[i].prevFoodLevel;
            } else // if added food
            {
                locations[i].placementList[i].prevFoodLevel = locations[i].placementList[i].foodLevel;
            } 
        }
        
        // increase index
        i++;

    } while (locations[i - 1].placementList[i - 1].ID != endToken); // will be active until a "-1" is scanned into an ID slot
    













    // print out the results 
    for (int i = 0; i < numEntries - 2; i++) // subtract by 2 so we dont print out the "END -1 -1"
    {
        printf("%s %lld %lld\n", locations[i].locationName, locations[i].placementList[i].ID, locations[i].placementList[i].foodLevel);
    }

    return 0;
}
