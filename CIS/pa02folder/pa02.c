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


/*
    Outline: 

    1. Collect the command line input arguments and print them to the console. Remember to
    remove or comment out this test code when running the testing scripts.
    2. Read the file and print it out to the console.
    3. Adjust the output to print 80 characters per line.
    4. Calculate the 8 bit checksum. Remember that the checksum is a running total with no
    overflow.
    5. Resolve the calculations and padding for both 16 and 32 bit checksums.

*/


#include <stdio.h>
#include <stdlib.h>


// globals
int checkSumSize; 
int characterCnt = 0;
int checkSum = 0;


void checkSumFunction(int character)
{
    // calculate the checksum
    checkSum += character; // add ASCII value of character to checksum

    // apply bitwise AND based on checksum size
    if (checkSumSize == 8) checkSum &= 0xFF; // for 8-bit checksum
    else if (checkSumSize == 16) checkSum &= 0xFFFF; // for 16-bit checksum
    else if (checkSumSize == 32) checkSum &= 0xFFFFFFFF; // for 32-bit checksum
}


int main(int argc, char **argv)
{
    printf("\n");
    // collect command line args 
    char *fileName = argv[1];
    checkSumSize = atoi(argv[2]);

    // validate checkSumSize
    if (checkSumSize != 8 && checkSumSize != 16 && checkSumSize != 32)
    {
        fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
        return 1;
    }

    // open the file provided
    FILE *mainFile = fopen(fileName, "r");

    // read and perform checkSum on the file
    while(1)
    {
        int character = fgetc(mainFile); // grab current character
        if(character == EOF) break; // break if end of file

        printf("%c", character); // echo character
        characterCnt++; // increment character count
        checkSumFunction(character); // call checkSum

        // format to 80 chars per line
        if(characterCnt % 80 == 0) printf("\n");
    }

    // calculate the number of padding characters needed
    int padding = 0;
    if (checkSumSize == 16) padding = (2 - characterCnt % 2) % 2;
    else if (checkSumSize == 32) padding = (4 - characterCnt % 4) % 4;

    // add padding characters
    for (int i = 0; i < padding; i++) 
    {
        printf("X"); // print pad
        checkSumFunction('X'); // call checkSum
        characterCnt++; // increment character count
        if(characterCnt % 80 == 0) printf("\n");
    }

    // print ending data
    if (characterCnt % 80 != 0) printf("\n");
    printf("%2d bit checksum is %8lx for all %4d chars\n", checkSumSize, (unsigned long)checkSum, characterCnt);

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