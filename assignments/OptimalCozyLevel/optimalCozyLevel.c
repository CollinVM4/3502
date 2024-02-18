/*
    - Collin Van Meter
    - COP3502
    - Optimal Cozy Levels
*/

/*
    Assignment Outline

    note: MUST USE RECURSION

    hint: use combination.c class example for help 

    important advice: 
    no structs, only recursive function and main, use global memory to hold arrays and answers, 
    account for negative answers, base case: make sure each house has a cat assigned



    SAMPLE INPUT: 

        4           <- num of cats 

        1 2 3       <- cozy level for particular cat at each family
        4 5 6
        7 8 9
        1 2 3

        0 3 -3 2    <- the amount each cat will change when with other cats
        10 0 -6 4
        5 2 0 8
        0 0 0 0

    SAMPLE OUTPUT: 

        31 3 <- sum, least possible level

*/

#include <stdio.h>
#include <stdlib.h>


// function prototype
int cozyCombo(foo);


// function definition 
int cozyCombo(foo)
{

    // base case: make sure each family has a cat assigned 
    if (NULL)
    {
       
    


        return 0; // failed
    }
    int cozy = foo;




    // recursive call
    cozyCombo(cozy);


    return cozy;
}












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