/*
Need to spend max amount of money whilst still being in budget
    chose the subset of items such that the sum of the budget is less than budged and maximal
*/

#include <stdio.h>
#include <stdlib.h>

int gen_combs(int * takes, int index, int numItems, int * itemCost, int budget) 
{
    // base case
    if (index == numItems)
    {
        int curCost = 0;
        for (int i = 0; i < numItems; i++)
        {
            if (takes[i])
            {
                curCost += itemCost[i];
            }
        }

        // check if valod
        if (curCost <= budget)
        {
            return curCost;
        }
        return 0; // if not valid
    }

    // recursive call: buy or dont buy the item
    int result = 0;
    for (int i = 0; i <= 1; i++)
    {
        takes[index] = i;
        int possible_budget = gen_combs(takes, index + 1, numItems, itemCost, budget);

        if (possible_budget > result)
        {
            result = possible_budget;
        }
    }
    return result;
}

#define SIZE 4

int main()
{
    int takes[SIZE];
    int cost[SIZE] = {7,10,3,5};
    for (int budget = 0; budget<=30; budget++)
    {
        printf("Budget: %d, Spend: %d\n", budget, gen_combs(takes, 0, SIZE, cost, budget));
    }




    return 0;
}