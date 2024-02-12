/*
    - Collin Van Meter
    - COP3502
    - Optimal Cozy Levels
*/

/*
    Assignment Outline

    note: MUST USE RECURSION

    hint: use recursion class examples for help 

    important advice: 
    no structs, only recursive function and main, use global memory to hold arrays and answers, 
    account for negative answers, base case: make sure each hose has a cat assigned


    input:
        1st line: num of cats
        
        N lines: each cat receives 3 cozy level ints (?) 

        N lines: more input corresponding to the cozy levels of cats with families (?)
    
    output:
        2 ints on the same line, 
            1. max coziness sum possible
            2. coziness of least cozy cat under least possible cozy combo




    SAMPLE INPUT: 

        4           <- num of cats 

        1 2 3       <- ? 
        4 5 6
        7 8 9
        1 2 3

        0 3 -3 2    <- ?
        10 0 -6 4
        5 2 0 8
        0 0 0 0

    SAMPLE OUTPUT: 

        31 3 <- sum, least possible level

*/

#include <stdio.h>
#include <stdlib.h>


// function prototype
















int main()
{

    int numCats, p1, p2, p3 = 0;

    // read in the num of cats 
    scanf("%d", &numCats);

    // based on num of cats, read in 3 cozy levels for each 
    for (int i = 0; i < numCats; i++)
    {
        scanf("%d %d %d", &p1, &p2, &p3);
    }
    


    return 0;
}