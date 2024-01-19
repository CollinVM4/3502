#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NAME_SIZE 20
#define LOCATION_COUNT 3
#define PLACEMENT_COUNT 5


struct locationOutline 
{
    char locationName;
    long long int* placementList;
    long long int totalAmountStolen;
};

struct placementOutline
{
    int ID;
    long long int foodLevel;
    long long int prevFoodLevel;
    long long int individualAmountStolen;
};


int main() 
{

    long long int d,f;
    char n[NAME_SIZE];
    int i = 0;
    int endToken = -1;



    collectLocationInfo(n, &d, &f);

    printf("%s %lld %lld\n", n, d, f);


    struct locationOutline locations[30];

    struct placementOutline placements[30];


    do
    {
        scanf("%s %lld %lld", locations[i].locationName, placements[i].ID, placements[i].foodLevel);
        i++;

    } while (endToken != placements[i].ID);
    



    return 0;
}