/*=============================================================================
| Assignment: pa02 - Calculating an 8, 16, or 32 bit
| checksum on an ASCII input file
|
| Author: Collin Van Meter
| Language: c
|
| To Compile: gcc -o pa02 pa02.c|
| To Execute: c -> ./pa02 inputFile.txt 8
|
| where inputFile.txt is an ASCII input file
| and the number 8 could also be 16 or 32
| which are the valid checksum sizes, all
| other values are rejected with an error message
| and program termination
|
| Note: All input files are simple 8 bit ASCII input
|
| Class: CIS3360 - Security in Computing - Spring 2024
| Instructor: McAlpin
| Due Date: 3/31/2024
|
+=============================================================================*/


#include <stdio.h>
#include <stdlib.h>


// globals
int checkSumSize; 
int characterCnt = 0;
unsigned long checkSum = 0;


// calculates the checksum (8, 16, 32 bit paths) 
void checkSumFunction(int character, int count)
{
    static int shift = 0; // shift variable

    if (checkSumSize == 8) // 8 bit
    {
        checkSum += character;
        checkSum &= 0xFF; // "mask" to 8 bits
    } 
    else 
    {
        // bitwise shift left 8 bits and add the current character
        shift = (shift << 8) + character;

        if (count % (checkSumSize / 8) == 0)
        {
            checkSum += shift;
            shift = 0;

            if (checkSumSize == 16) // 16 bit
            {
                checkSum &= 0xFFFF; // "mask" to 16 bits
            } 
            if (checkSumSize == 32) // 32 bit
            {
                checkSum &= 0xFFFFFFFF; // "mask" to 32 bits
            }
        }
    }
}


int main(int argc, char **argv)
{

    printf("\n"); // formatting


    // collect command line args 
    char *file = argv[1];
    checkSumSize = atoi(argv[2]);


    // validate checkSumSize
    if (checkSumSize != 8 && checkSumSize != 16 && checkSumSize != 32)
    {
        fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
        return 1;
    }


    // open the file provided
    FILE *mainFile = fopen(file, "r");


    // read and perform checkSum on the file
    int count = 0;
    while(1)
    {
        int character = fgetc(mainFile); // grab current character

        if(character == EOF) break; // break if end of file

        printf("%c", character); // echo character

        characterCnt++; 
        count++;
        
        checkSumFunction(character, count); 

        if(characterCnt % 80 == 0) printf("\n"); // format 80 chars per line 
    }


    // add padding if needed
    int padding = 0;
    if (checkSumSize == 16) padding = (2 - characterCnt % 2) % 2; // 16 bit
    if (checkSumSize == 32) padding = (4 - characterCnt % 4) % 4; // 32 bit

    for (int i = 0; i < padding; i++) 
    {
        printf("X"); // print pad
        characterCnt++; 
        checkSumFunction('X', characterCnt); // call checkSum

        if(characterCnt % 80 == 0) printf("\n"); // format to 80 chars per line
    }


    // resolve overflow
    if (checkSumSize == 16)
    {
        checkSum %= 65536;
    }
    if (checkSumSize == 32)
    {
        checkSum %= 4294967296;
    }


    // print ending data
    if (characterCnt % 80 != 0) printf("\n");
    printf("%2d bit checksum is %8lx for all %4d chars\n", checkSumSize, checkSum, characterCnt);


    // close file
    fclose(mainFile);


    return 0;
}


/*=============================================================================
| I [Collin Van Meter] ([co149144]) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/