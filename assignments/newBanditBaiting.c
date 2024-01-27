#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


typedef struct LocationList LocationList;
typedef struct Location Location;
typedef struct Placement Placement;


struct Placement
{
    long long int ID;
    long long int foodLevel;
};

struct Location
{
    int size, cap, placementSize;
    char *name;
    long long int totalStolen;
    Placement *placementList;
};

struct LocationList 
{
    int size, cap;
    Location *arr;
};


// dynamically create an arraylist
LocationList *createLocationList()
{
    //allocate a single array list
    LocationList *ret;

    // allocate memory for 1 list 
    ret = (LocationList *)malloc(sizeof(LocationList));

    // initialize
    ret->size = 0;
    ret->cap = 10;
    // allocate the array
    ret->arr = (Location *)malloc(sizeof(Location) * ret->cap);

    return ret;
}


// function to initialize a location
void initializeLocation(Location *location)
{
    location->size = 0;
    location->cap = 10;
    location->totalStolen = 0;
    location->placementSize = 0;

    location->name = (char *)malloc(sizeof(char) * 100 + 1);

    location->placementList = (Placement *)malloc(sizeof(Placement) * location->cap);
    location->placementList->foodLevel = 0;
    location->placementList->ID = 0;
    
    
}


// add a location to the list
void addLocation(LocationList *locationList) 
{
    if (locationList->size >= locationList->cap) 
    {
        // expand the array if it meets capacity
        locationList->cap *= 2;
        locationList->arr = (Location *)realloc(locationList->arr, sizeof(Location) * locationList->cap);
    }

    // initialize the new location
    initializeLocation(&locationList->arr[locationList->size]);

     // data to temporarily hold scanned in entries
    char name[100 + 1];
    long long int ID;
    long long int foodLevel;

    // Use scanf to input data
    scanf("%s %lld %lld", name, &ID, &foodLevel);
    
    // linear search through locations
    for (int i = 0; i < locationList->size; i++)
    {
        if (strcmp(name, locationList->arr[i].name) == 0) // checks if two entires are equal
        {
            // if location exists, linear search through specific location's placements
            bool foundPlacement = false;
            for (int j = 0; j < locationList->arr[i].placementSize; j++) 
            {
                if (ID == locationList->arr[i].placementList[j].ID) // existing placement
                {
                    foundPlacement = true; 
                    // if food added/same amount
                    if (foodLevel >= locationList->arr[i].placementList[j].foodLevel)
                    {
                        printf("0\n"); 
                        break;
                    }
                    // if food was stolen
                    if (foodLevel < locationList->arr[i].placementList[j].foodLevel)
                    {
                        long long int leastAmountStolen = locationList->arr[i].placementList[j].ID - foodLevel; // subtract previous food level from current entry
                        printf("%lld", leastAmountStolen);
                        locationList->arr[i].totalStolen += leastAmountStolen; // update location totalStolen
                        break;
                    }
                } 
            }
            // If we've gone through all placements and haven't found a match, it's a new placement
            if (!foundPlacement) // if placement doesnt exist
            {
                printf("SUB New placement.\n");
                locationList->arr[i].placementList[0].ID = ID;
                locationList->arr[i].placementList[0].foodLevel = foodLevel;
                locationList->arr[i].placementSize++; // increment the size of the placementList for the specific location
            }
            return; // We've found the location, no need to keep looking   
        } 
    }

    // If we've gone through all locations and haven't found a match, it's a new location
    if (locationList->size >= locationList->cap) 
    {
        // expand the array if it meets capacity
        locationList->cap *= 2;
        locationList->arr = (Location *)realloc(locationList->arr, sizeof(Location) * locationList->cap);
    }

    // initialize the new location
    initializeLocation(&locationList->arr[locationList->size]);

    int initialSize = 10; // initial size of the array
    locationList->arr[locationList->size].placementList = malloc(sizeof(Placement) * initialSize);

    //assign data to the main list
    strcpy(locationList->arr[locationList->size].name, name); 
    locationList->arr[locationList->size].placementList[0].ID = ID;
    locationList->arr[locationList->size].placementList[0].foodLevel = foodLevel;

    locationList->arr[locationList->size].placementSize++; // increment the size of the placementList for the specific location
    locationList->size++; // increase size 

    printf("TOTALLY New placement.\n");
        
    
}

void printLocation(Location *location)
{
    printf("Name: %s", location->name);
    printf(" ID: %lld, Food Level: %lld\n", location->placementList[0].ID, location->placementList[0].foodLevel);
    
}


int main()
{

    LocationList *mainList = createLocationList();

        do
        {
            // Check if a new location should be added
            if (mainList->arr[mainList->size - 1].placementList[0].ID == -1)
            {
                break;
            }

            addLocation(mainList);

        } while (1);
        

        //  printing both locations
        for (int i = 0; i < mainList->size; ++i)
        {
            printLocation(&mainList->arr[i]);
        }

    return(0);
}




/*
    TODO for tomorrow
    * work on indexing placements
    * determine if new
    * determine how much food since last entry
    * collect amount taken from each placement 
*/