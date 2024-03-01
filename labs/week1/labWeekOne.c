#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Could not open file\n");
        return 1;
    }

    // read in the word 
    char word[4000 + 1];
    fscanf(file, "%s", word);

    // read # of forbiddens
    int numForbid = 7;

    // read in forbiddens
    char badChars[numForbid];
    for (int i = 0; i < numForbid; i++)
    {
        scanf(" ");
        scanf("%c", &badChars[i]);
    }

    // compute the length of the word
    int length = strlen(word);

    // iterate through all letters in the word
    for (int i = 0; i < length; i++)
    {
        char curLet = word[i];

        // check if the letter is forbidden
        int isForbid = 0;
        for (int j = 0; j < numForbid; j++)
        {
            // check if the letter is forbidden
            if (badChars[j] == curLet)
            {
                isForbid = 1;
            }
        }
                    
        if (!isForbid)
        {
            printf("%c", curLet);
        }
    }    
    printf("\n");

    fclose(file);
    return(0);
}