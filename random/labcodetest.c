#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define numFruit 9
#define numBuy 7

void combination(char ** allFruit, char ** basket, int fruitIndex, int basketIndex){
    static int count = 1;
    
    // base case
    if(basketIndex == numBuy) { // filled basket
        printf("%d. ", count);
        for(int i = 0; i < numBuy; i++) {
            printf("%s ", basket[i]);
        }
        count++;
        printf("\n");
        return;
    }

    if(fruitIndex == numFruit) // out of fruit
    {
        return; // no more fruit :[ not enough to fill basket
    }

    for(int i = 0; i <= 2; i++) { // buy 0 to 2 of each fruit
        for(int j = 0; j < i; j++) {
            basket[basketIndex + j] = allFruit[fruitIndex];
        }
        combination(allFruit, basket, fruitIndex + 1, basketIndex + i);
    }
}

int main() {
    char ** allFruit =(char **) malloc(sizeof(char*) * numFruit);
    char ** basket = (char **) malloc(sizeof(char*) * numBuy);

    allFruit[0] = "apple";
    allFruit[1] = "banana";
    allFruit[2] = "cantaloupe";
    allFruit[3] = "lemon";
    allFruit[4] = "limes";
    allFruit[5] = "apricot";
    allFruit[6] = "plum";
    allFruit[7] = "grape";
    allFruit[8] = "cucumber";

    combination(allFruit, basket, 0, 0);

    return 0;
}