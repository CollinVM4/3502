/*============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Hill cipher
|
| Author: Collin Van Meter
| Language: c
|
| To Compile: gcc -o pa01 pa01.c
| To Execute: c -> ./pa01 kX.txt pX.txt
| where kX.txt is the keytext file
| and pX.txt is plaintext file
| Note:
| All input files are simple 8 bit ASCII input
| All execute commands above have been tested on Eustis
|
| Class: CIS3360 - Security in Computing - Fall 2023
| Instructor: McAlpin
| Due Date: 2/25/2024
+===========================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


#define MAX_TEXT_SIZE 10000


// encrypt using hill cipher
void hillCipher(int size, int** key, char* text, char* cipher) 
{
    int i, j, k = 0; // init loop vars

    // loop through the plaintext
    while (text[k] != '\0') 
    {
        // loop through the key matrix
        for(i = 0; i < size && text[k + i] != '\0'; i++)
        {
            int cipherVal = 0;

            // loop through the text
            for(j = 0; j < size; j++) 
            {
                cipherVal += key[i][j] * (text[k+j] - 'a');
            }

            cipherVal = cipherVal % 26;

            if (cipherVal < 0) // handle negative values
            {
                cipherVal += 26;
            }

            cipher[k+i] = cipherVal + 'a'; // add back 'a' to ensure correct ascii value
        }

        k += size;  
    }

    cipher[k] = '\0'; // null terminator to end of ciphertext
}


int main(int argc, char **argv) 
{
    FILE *keyFile, *textFile;

    int size; // size of the key matrix
    int **key; // key matrix

    char plainText[MAX_TEXT_SIZE], cipher[MAX_TEXT_SIZE]; // plaintext and ciphertext

    // open key and plaintext files
    keyFile = fopen(argv[1], "r");
    textFile = fopen(argv[2], "r");

    fscanf(keyFile, "%d", &size); // read in size of the key

    // allocate memory for the key matrix
    key = malloc(size * sizeof(int *));
    for(int i = 0; i < size; i++) 
    {
        key[i] = malloc(size * sizeof(int));
    }

    // read in key
    for(int i = 0; i < size; i++) 
    {
        for(int j = 0; j < size; j++) 
        {
            fscanf(keyFile, "%d", &key[i][j]);
        }
    }

    // read in the plaintext
    int i = 0;
    char curChar; // current char being read from the plaintext

    while((curChar = fgetc(textFile)) != EOF && i < MAX_TEXT_SIZE) 
    {
        // validate the character, make sure its not a space or punctuation
        if(isalpha(curChar)) 
        {
            plainText[i++] = tolower(curChar);
        }
    }
    // pad the plaintext with 'x' until its length is a multiple of the size of the key matrix
    while(i % size != 0) 
    {
        plainText[i++] = 'x';
    }
    plainText[i] = '\0'; // add null terminator to the end of plaintext


    // call encryption on the plaintext
    hillCipher(size, key, plainText, cipher);


    // print resulting key, origianl plain text, and cipher text
    printf("\nKey matrix:\n");
    for(int i = 0; i < size; i++) 
    {
        for(int j = 0; j < size; j++) 
        {
            printf("  %d  ", key[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Plaintext:\n");
    for(int i = 0; plainText[i] != '\0'; i++) 
    {
        putchar(plainText[i]);
        if((i + 1) % 80 == 0) 
        {
            putchar('\n');
        }
    }
    printf("\n\n");

    printf("Ciphertext:\n");
    for(int i = 0; cipher[i] != '\0'; i++) 
    {
        putchar(cipher[i]);
        if((i + 1) % 80 == 0) 
        {
            putchar('\n');
        }
    }
    printf("\n");

    // close files
    fclose(keyFile);
    fclose(textFile);

    for(int i = 0; i < size; i++) 
    {
        free(key[i]);
    }
    free(key);

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