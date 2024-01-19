#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NAME_SIZE 20
#define LOCATION_COUNT 3
#define PLACEMENT_COUNT 5

// struct for locations
struct locationOutline 
{
    char locationName[NAME_SIZE];
    long long int placementList;
    long long int totalAmountStolen;
};

// struct for individual placements 
struct placementOutline
{
    long long int ID;
    long long int foodLevel;
    long long int prevFoodLevel;
    long long int individualAmountStolen;
};

int main() 
{
    int i = 0;
    int endToken = -1;
    int numEntries = 0;

    struct locationOutline locations[30];
    struct placementOutline placements[30];

    do
    {
        scanf("%s %lld %lld", locations[i].locationName, &placements[i].ID, &placements[i].foodLevel);
        i++; numEntries++;
    } while (endToken != placements[i].ID);
    
    for (int i = 0; i < numEntries; i++)
    {
        printf("%s\n", locations[i].locationName);
    }

    return 0;
}
