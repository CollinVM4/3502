#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main()
{
    char seq1[10000 + 1];
    char seq2[10000 + 1];
    scanf("%s%s", seq1, seq2);

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

    return 0;
}