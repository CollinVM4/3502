/*
    - Collin Van Meter
    - COP3502C, Spring 2024
    - Assignment 1, BanditBaiting [DMA]
*/


// libraries used
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// structs
typedef struct LocationList LocationList;
typedef struct Location Location;
typedef struct Placement Placement;

struct Placement
{
    long long int ID, foodLevel;
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


// function prototypes
LocationList *createLocationList();
void initializeLocation(Location *location);
void addLocation(LocationList *locationList);
void printLocation(Location *location);
void freeMemory(LocationList *locationList);


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
    location->size = 0; location->cap = 10; location->totalStolen = 0; location->placementSize = 0;

    location->name = (char *)malloc(sizeof(char) * 100 + 1); // allocate memory for the name
    location->placementList = (Placement *)malloc(sizeof(Placement) * location->cap); // allocate memory for the placement list

    location->placementList->foodLevel = 0; location->placementList->ID = 0;
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

    // variables to temporarily hold scanned in entries
    char name[100 + 1]; long long int ID; long long int foodLevel;

    // Use scanf to input entry data 
    scanf("%s %lld %lld", name, &ID, &foodLevel);
    
    // linear search through locations
    for (int i = 0; i < locationList->size; i++)
    {
        // check if the new entry matches an existing location/placement
        if (strcmp(name, locationList->arr[i].name) == 0)
        {
            // if location exists, linear search through specific location's placements
            bool foundPlacement = false;
            for (int j = 0; j < locationList->arr[i].placementSize; j++) 
            {
                if (ID == locationList->arr[i].placementList[j].ID) // existing placement
                {
                    foundPlacement = true; 
                    // if food has been added or same amount
                    if (foodLevel >= locationList->arr[i].placementList[j].foodLevel)
                    {
                        printf("0\n"); 
                    }
                    // if food was stolen
                    else if (foodLevel < locationList->arr[i].placementList[j].foodLevel)
                    {
                        // determine and update the amount stolen
                        long long int leastAmountStolen = locationList->arr[i].placementList[j].foodLevel - foodLevel;
                        printf("%lld\n", leastAmountStolen);
                        locationList->arr[i].totalStolen += leastAmountStolen; // update the location's total stolen
                        locationList->arr[i].placementList[j].foodLevel = leastAmountStolen;
                    }
                    break;
                } 
            }
            // if placement is new
            if (!foundPlacement)
            {
                // avoid printing New placement. for the end sequence
                if (strcmp(locationList->arr[i].name, "END") != 0)
                {
                    printf("New placement.\n");
                }

                // check if the placementList array needs to be expanded
                if (locationList->arr[i].placementSize >= locationList->arr[i].cap) 
                {
                    locationList->arr[i].cap *= 2;
                    locationList->arr[i].placementList = (Placement *)realloc(locationList->arr[i].placementList, sizeof(Placement) * locationList->arr[i].cap);
                }

                // add the new placement at the end of the placementList array
                locationList->arr[i].placementList[locationList->arr[i].placementSize].ID = ID;
                locationList->arr[i].placementList[locationList->arr[i].placementSize].foodLevel = foodLevel;
                locationList->arr[i].placementSize++; // increment the size of the placementList for the specific location
            }
            return;
        } 
    }

    // expand list if it meets capacity
    if (locationList->size >= locationList->cap) 
    {
        locationList->cap *= 2;
        locationList->arr = (Location *)realloc(locationList->arr, sizeof(Location) * locationList->cap);
    }

    // initialize the new location
    initializeLocation(&locationList->arr[locationList->size]);

    int initialSize = 10; // initial size of the placementList array
    locationList->arr[locationList->size].placementList = malloc(sizeof(Placement) * initialSize); 

    // assign data to the main list
    strcpy(locationList->arr[locationList->size].name, name); 
    locationList->arr[locationList->size].placementList[0].ID = ID;
    locationList->arr[locationList->size].placementList[0].foodLevel = foodLevel;

    locationList->arr[locationList->size].placementSize++; // increment the size of the placementList for the specific location
    locationList->size++; // increase size of the main list

    // avoid printing for end sequence
    if (strcmp(name, "END") != 0)
    {
        printf("New placement.\n");
    }   
}

// function to print out each location's name and total food stolen
void printLocation(Location *location)
{
    // avoid printing the end sequence
    if (strcmp(location->name, "END") == 0)
    {
        return;
    }

    printf("%s ", location->name);
    printf("%lld\n", location->totalStolen);    
}

void freeMemory(LocationList *locationList)
{
    // loop through and free each individual location
    for (int i = 0; i < locationList->size; i++)
    {
        // free the name and placement list for each location
        free(locationList->arr[i].name);
        free(locationList->arr[i].placementList);
    }
    // free the array of locations
    free(locationList->arr);
    // free the outermost chunk
    free(locationList);
}

int main()
{
    // create the main list
    LocationList *mainList = createLocationList(); 

    do
    {
        // check for end sequence
        if (mainList->arr[mainList->size - 1].placementList[0].ID == -1)
        {
            break; // will break the do/while loop if "END -1 -1" is scanned
        }

        // function for and adding in entries, determining if it's new, and performing the food stolen logic
        addLocation(mainList);

    } while (1);
    
    // print out location name, and corresponding total food stolen
    for (int i = 0; i < mainList->size; ++i)
    {
        printLocation(&mainList->arr[i]);
    }

    // free the memory used >:D
    freeMemory(mainList);

    return(0);
}