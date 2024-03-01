#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main()
{

    FILE *file = fopen("input2.txt", "r");
    if (file == NULL) {
        printf("Could not open file\n");
        return 1;
    }
    char seq1[100000 + 1];
    char seq2[100000 + 1];

    if (fscanf(file, "%s %s", seq1, seq2) != 2) {
        printf("Could not read data from file\n");
        return 1;
    }
    int answer = 0;

    // brute force all possible starting points
    for (int i = 0; seq1[i]; i++) // if not null terminator
    {
        for (int j = 0; seq2[j]; j++) // if not null terminator
        {
            int ind1 = i;
            int ind2 = j;
            int len = 0;

            // walk until we find a difference
            while (seq1[ind1] == seq2[ind2] && seq2[ind2] != '\0') 
            {
                len++;
                ind1++;
                ind2++;
            }
            
            if (len > answer)
            {
                answer = len;
            }
        }
    }
    
    printf("%d\n", answer);


    fclose(file);
    return 0;
}