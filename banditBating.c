#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NAME_SIZE 20


struct locationOutline 
{
    char* locationName;
    long long int* placementList;
    long long int totalAmountStolen;
};

struct placementOutline
{
    int ID;
    long long int prevFoodLevel;
    long long int individualAmountStolen;
};

void collectStarterInfo(char *n, long long int *d, long long int *f) //name, ID, food level
{
    scanf("%s %lld %lld", n, d, f);
}








int main() 
{

    long long int d,f;
    char n[NAME_SIZE];



    collectStarterInfo(n, &d, &f);

    printf("%s %lld %lld\n", n, d, f);

    return 0;
}