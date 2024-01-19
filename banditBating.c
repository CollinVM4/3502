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
    int numEntries = 0; // use in for loop, printing out results

    struct locationOutline locations[30]; // instance of array of structs



    // scan for entries, terminate when "END -1 -1" is entered 
    do
    {
        scanf("%s %lld %lld", locations[i].locationName, &locations[i].placementList[i].ID, &locations[i].placementList[i].foodLevel); // scan for req. info
        i++; numEntries++;
    } while (locations[i - 1].placementList[i - 1].ID != endToken); // will be active until a "-1" is scanned into an ID slot
    


    // print out the results 
    for (int i = 0; i < numEntries - 1; i++) // subtract by 1 so we dont print out the "END -1 -1"
    {
        printf("%s %lld %lld\n", locations[i].locationName, locations[i].placementList[i].ID, locations[i].placementList[i].foodLevel);
    }

    return 0;
}
