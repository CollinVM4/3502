#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main()
{

    // read in the word 
    char word[100 + 1];
    scanf("%s", word);

    // read # of forbiddens
    int numForbid;
    scanf("%d", &numForbid);

    // read in forbiddens
    char badChars[numForbid];
    for (int i = 0; i < numForbid; i++)
    {
        scanf(" ");
        scanf(" %c ", &badChars[i]);

        //printf("[%c]\n", badChars[i]);
    }


    // iterate through all letters in the word 
        // check if the letter ir forbidden 
            // if not forbidden, print the letter out. 

    int length = strlen(word);

    for (int i = 0; i < length; i++)
    {
        int isForbid = 0;
        for (int j = 0; i < numForbid; j++)
        {
            char curLet = word[i];
            int isForbid = 0;
            if (badChars[j] == curLet)
            {
                isForbid = 1;
            }
            

            if (!isForbid)
            {
                printf("%c", curLet);
            }
            
        }
        
    }
    
    



    return(0);
}