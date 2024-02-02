/*
    First Assignment Notes 


    Hill Cipher
    
    * Invented in 1926 by Lester Hill
    * uses Linear Algebra (matrix manipulation)
    * Letters are encoded as numbers modulo 26
    * blocks are interpreted as vectors
    * key is a random matrix of same dimension as vectors
    

    Vectors

    * vector is an ordered set of nums
    * the dot product of two vectors is the sum of the products of each component
    ex. 
    [1,5,4] * [4,2,6] = (1)(4) + (5)(2) + (4)(6)
    4 + 10 + 24 = 48

    Matrices
    
    * rectangular arrangement of numerical values 
    * similar to a vector, just an ordered arrangmenet

    How to cipher
    * key vector * plaintext vector, output mod 26 = ciphertext 




    Covered Hints in class
        * read in key file
        * read in plaintext file
        * note * every thing graded on Eustis 
        * output the processed inout to the screen
        * output the ciphertext

        * first character in key file is the dimension of the matrix, ex. if 4, read in 4 lines 
        * delete any whitespace, punctuaction in input (everything except letters)
        * 80 character rows, seperated by newline
*/



/*============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Hill cipher
|
| Author: Collin Van Meter
| Language: c, c++, Java, go, python
|
| To Compile: javac pa01.java
| gcc -o pa01 pa01.c
| g++ -o pa01 pa01.cpp
| go build pa01.go
|
| To Execute: java -> java pa01 kX.txt pX.txt
| or c++ -> ./pa01 kX.txt pX.txt
| or c -> ./pa01 kX.txt pX.txt
| or go -> ./pa01 kX.txt pX.txt
| or python -> python3 pa01.py kX.txt pX.txt
| where kX.txt is the keytext file
| and pX.txt is plaintext file
| Note:
| All input files are simple 8 bit ASCII input
| All execute commands above have been tested on Eustis
|
| Class: CIS3360 - Security in Computing - Fall 2023
| Instructor: McAlpin
| Due Date: per assignment
+===========================================================================*/




#include <stdlib.h>
#include <stdio.h>


int main()
{








    return(0);
}




/*=============================================================================
| I [Collin Van Meter] ([co149144]) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/