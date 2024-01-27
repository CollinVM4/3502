#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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
    int size, cap;
    char *name;
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

    location->name = (char *)malloc(sizeof(char) * 100 + 1);

    location->placementList = (Placement *)malloc(sizeof(Placement) * location->cap);
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

    // Use scanf to input data
    scanf("%s %lld %lld", locationList->arr[locationList->size].name,
            &locationList->arr[locationList->size].placementList[0].ID,
            &locationList->arr[locationList->size].placementList[0].foodLevel);

    locationList->size++;
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