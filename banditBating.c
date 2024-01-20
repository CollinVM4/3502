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



int main() 
{
    int i = 0; // for loop usage 
    long long int endToken = -1; // setting up endToken for do,while loop
    int numEntries, isNew, checkFood = 0; // use in for loop, printing out results


    struct locationOutline locations[30]; // instance of array of structs


    // scan for entries, terminate when "END -1 -1" is entered 
    do
    {
        // scan for req. info
        scanf("%s %lld %lld", locations[i].locationName, &locations[i].placementList[i].ID, 
        &locations[i].placementList[i].foodLevel);

        // increase indexes
        i++; numEntries++;
        

        // walk list to determine if entry is new 
        for (int j = 0; j < numEntries; j++) // loop through all names
        {
            if (strcmp(locations[i].locationName, locations[j].locationName) == 0) // 0 is equal, anything else is not equal
            {
                // now check if new placement
                for (int k = 0; k < numEntries; k++) // loop through all placements
                {
                    if(locations[i].placementList[i].ID == locations[k].placementList[k].ID) // not new 
                    {
                        checkFood = 1; // will run check food block
                        isNew = 0; // will not add to main struct list 
                    }
                }
            } 
        };
        
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
        




    } while (locations[i - 1].placementList[i - 1].ID != endToken); // will be active until a "-1" is scanned into an ID slot
    













    // print out the results 
    for (int i = 0; i < numEntries - 1; i++) // subtract by 1 so we dont print out the "END -1 -1"
    {
        printf("%s %lld %lld\n", locations[i].locationName, locations[i].placementList[i].ID, locations[i].placementList[i].foodLevel);
    }

    return 0;
}
