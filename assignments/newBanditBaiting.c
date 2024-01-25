#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct LocationList LocationList;
typedef struct Location Location;
typedef struct Placement Placement;


struct Placement
{
    long long int ID;
    long long int prevFoodLevel;
    long long int foodLevel;
    long long int individualAmountStolen;
};

struct Location
{
    char **arr;
    int size, cap;    
    char *name;
    int totalFoodTaken;    
    Placement *placementList;
};

struct LocationList 
{
    Location *arr;
    int size, cap;
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


void initializeLocation(Location *location, char *name)
{
    location->size = 0;
    location->cap = 0;
    location->totalFoodTaken = 0;
    
    //allocate space for an an array of strings
    location->arr = (char **)malloc(sizeof(char *) * location->cap);
    location->name = strdup(name); // copy location name

    // dynamically allocate the array of Placement structs
    location->placementList = (Placement *)malloc(sizeof(Placement));
}


// function to add to arrayList & expand if necessary
void append(LocationList *list, char *name)
{

    // if list is full, expand
    if (list->size == list->cap)
    {
        list->cap *= 2;
        list->arr = (Location*)realloc(list->arr, sizeof(Location) * list ->cap);
    }

    // TO DO, ADD INFO TO STRUCT 
}


// function goes through the list and finds if name exists
Location *findLocation(LocationList *list, char *name)
{
    // Linear search
    for (int i = 0; i < list->size; i++)
    {
        //check if the name matches
        if (strcmp(name, list->arr[i].name) == 0)
        {
            return &(list->arr[i]);
        }
    }
    // TODO return
}






void printList(Location * list)
{
    for (int i = 0; i < list->size; i++)
    {
        printf("%s\n", list->arr[i]);
    }
}


void deleteList(Location *list)
{
    free(list->arr);
    free(list);
}



int main()
{
    LocationList *mainList = createLocationList();

    char locationName[100 + 1];








    return(0);
}
