#include <stdio.h>
#include <stdlib.h>


typedef struct dataTOD
{
    int seconds; // seconds since midnight
    double data; // data sample
    char * dataName; // data name (optional)
} dataTOD;

dataTOD * init_dataTOD(int sec, double val, char* name)
{

	dataTOD* newEntry = (dataTOD*) malloc(sizeof(dataTOD));

    if(newEntry == NULL) return NULL;

    newEntry->data = val;
    newEntry->seconds = sec;

    newEntry->dataName = malloc((strlen(name) + 1) * sizeof(char));
    strcpy(newEntry->dataName, name);

    return newEntry;
}

void free_dataTOD(dataTOD *zapThis)
{
    free(zapThis->dataName);
    free(zapThis);
}

int main()
{




    return 0;
}