/*
scan and subtract from previous location if existing.
if new print new placement 
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NAME_SIZE 100


// struct for individual placements 
struct Placement
{
    long long int ID;
    long long int foodLevel;
};


// struct for locations
struct Location 
{
    char locationName[NAME_SIZE + 1];
    struct placementOutline *placementList[];
};






int main()
{

    struct Location* locationList[] = malloc();




    do
    {
        /* code */
    } while (/* condition */);
    












    return(0);
}