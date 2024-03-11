/*
    - Collin Van Meter
    - COP3502C, Business Buyout
    - 3/5/24
*/


#include <stdio.h>
#include <stdlib.h>


// stack struct
typedef struct Stack
{
    long long int* shops;
    long long int top;
} Stack;


// stack functions 

// initialize stack (for shop arrays)
void initStack(Stack* stack, long long int* shops, long long int shopCount) 
{
    stack->shops = shops;
    stack->top = shopCount;
}

// add shop
void push(Stack* stack, long long int shop) 
{
    stack->shops[stack->top] = shop;
    stack->top++;
}

// remove shop 
long long int pop(Stack* stack) 
{
    stack->top--;
    return stack->shops[stack->top];
}

// grab top of stack
long long int top(Stack* stack) 
{
    return stack->shops[stack->top - 1];
}


// quick sort from webcourses :)
void quick_sort(long long int *arr, long long int len) 
{
    // Base Case
    if (len <= 1) 
    {
        return;
    }

    // Split the array based on the pivot (arr[0])
    int fptr = 1;
    int bptr = len - 1;

    for (int i = 1; i < len; i++) 
    {
        if (arr[0] < arr[fptr]) 
        {
            int tmp = arr[fptr]; // move to back
            arr[fptr] = arr[bptr];
            arr[bptr] = tmp;
            bptr--; // adjust the back pointer
        } 
        else 
        {
            fptr++; // stay in front
        }
    }

    // Move pivot into location
    int tmp = arr[0];
    arr[0] = arr[fptr - 1];
    arr[fptr - 1] = tmp;

    // sort the 2 parts
    quick_sort(arr, fptr - 1);
    quick_sort(arr + fptr, len - fptr);

}


int main()
{
    // declare and init starting vars
    long long int numShops = 0;
    long long int btsWealth = 0;
    long long int isWealthiest = -1;
    long long int numEaten = 0;


    // scan in starting wealth, number of shops
    scanf("%lld %lld", &numShops, &btsWealth);


    // declare and scan buyout amounts
    long long int* shopCostArr = (long long int*)malloc(numShops * sizeof(long long int));
    for (long long int i = 0; i < numShops; i++)
    {
        scanf("%lld", &shopCostArr[i]);
    }
    

    // split into smallerShops and largerShops

    // declare and init arrays
    long long int* smallerShops = (long long int*)malloc(numShops * sizeof(long long int));
    long long int* largerShops = (long long int*)malloc(numShops * sizeof(long long int));
    for (long long int i = 0; i < numShops; i++) 
    {
        smallerShops[i] = 0;
        largerShops[i] = 0;
    }

    // declare and init counters
    long long int numSmall = 0;
    long long int numLarge = 0;

    // split into smaller/larger arrays
    for (long long int i = 0; i < numShops; i++)
    {
        if (btsWealth > shopCostArr[i]) // smaller than BTS
        {
            smallerShops[numSmall] = shopCostArr[i];
            numSmall++;
        }
        else if (btsWealth <= shopCostArr[i]) // larger than or equal to BTS
        {
            largerShops[numLarge] = shopCostArr[i];
            numLarge++;
        }
    }


    // quick sort each smaller/larger array
    quick_sort(smallerShops, numSmall);
    quick_sort(largerShops, numLarge);


    // put arrays into stacks
    Stack smallerStack; 
    Stack largerStack;
    initStack(&smallerStack, smallerShops, numSmall);
    initStack(&largerStack, largerShops, numLarge);


    // pre-check if BTS is already largest
    if(numLarge == 0 || btsWealth > top(&largerStack))
    {
        isWealthiest = 1;
    }   

    // buyout shop logic 
    while(isWealthiest == -1)
    {
        // break conditions

        // if biggest, success
        if(btsWealth > top(&largerStack))
        {
            isWealthiest = 1;
            break;
        }
        // if BTS equal to largest, fail
        if(btsWealth == top(&largerStack))
        {
            break;
        }

        
        // eat the largest shop from smallerStack
        if(numSmall > 0)
        {
            // buyout the largest consumable shop
            btsWealth += top(&smallerStack);
            numEaten++;
            pop(&smallerStack);
            numSmall--;
        }


        // check if you can now eat a previously uneatable shop
        for (long long int i = largerStack.top - 1; i >= 0; i--)
        {
            if (largerStack.shops[i] <= btsWealth)
            {
                // transfer from largerShops to smallerShops
                push(&smallerStack, largerStack.shops[i]);
                numSmall++;
                numLarge--;

                // remove the shop
                for (long long int j = i; j < largerStack.top - 1; j++)
                {
                    largerStack.shops[j] = largerStack.shops[j + 1];
                }
                largerStack.top--;

                break;
            }
        }

        // break if there are no consumable shops
        if(numSmall == 0)
        {
            break;
        }
    }


    // print -1 if mission failed, 
    // print num of eaten shops if successful

    if(isWealthiest == 1) 
    {
        printf("%lld\n", numEaten);
    }
    else
    {
        printf("-1");
    }

    // free arrays 
    free(shopCostArr);
    free(smallerShops);
    free(largerShops);

    return 0;
}