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
void initializeLocation(Location *location, char *name, long long int ID, long long int foodLevel)
{
    location->size = 0;
    location->cap = 10;

    location->name = (char *)malloc(sizeof(char) * 100 + 1);
    strncpy(location->name, name, 100);

    // dynamically allocate the array of Placement structs
    location->placementList = (Placement *)malloc(sizeof(Placement) * location->cap);


     // Set default values for ID and foodLevel for each placement
    for (int i = 0; i < location->cap; ++i) {
        location->placementList[i].ID = ID;
        location->placementList[i].foodLevel = foodLevel;
    }
}


// add a location to the list
void addLocation(LocationList *locationList, char *name, long long int ID, long long int foodLevel) {
    if (locationList->size >= locationList->cap) {
        // Resize the array if necessary
        locationList->cap *= 2;
        locationList->arr = (Location *)realloc(locationList->arr, sizeof(Location) * locationList->cap);
    }

    initializeLocation(&locationList->arr[locationList->size++], name, ID, foodLevel);
}


int main()
{
    LocationList *mainList = createLocationList();

    addLocation(mainList, "Location1", 1, 100);







    return(0);
}
