#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <time.h>



// get a prime: https://www.bigprimes.net/archive/prime/8/
#define PRIME 5477

// alphabet size is the base
#define BASE 256


/* prints n chars on a single line with no newline at the end. */
void printn(int n, char c)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%c",c);
}


/*
This function takes a string as input. It processes the string four bytes at a time, 
and interprets each of the four-byte chunks as a single long integer value. 
The integer values for the four-byte chunks are added together. 
In the end, the resulting sum is converted to the range 0 to M-1 using the modulus operator.

Folding on a string, summed 4 bytes.
Curtesy of https://research.cs.vt.edu/AVresearch/hashing/strings.php
*/
unsigned 
hash_fold_div(const char* key, unsigned m)
{
    int intlength = strlen(key) / 4;
    long sum = 0;
    long mult = 1;

    int j;
    int k;
    //printf("%s\n", key);
    for (j = 0; j < intlength; j++)
    {
        printn(j*4, ' ');
        for (k = j*4; k < j*4 + 4; k++)
        {
            sum += key[k] * mult;
            mult *= BASE;
            //printf("%c", key[k]);
        }
        mult = 1;
        //printf("\n");
    }

    //printf("sum before last for-loop: %ld\n", sum);
    /*
    for (int k = 0; k < intlength*4; k++)
    {
        sum += key[k] * mult;
        mult *= 256;
    }
    */
    //printf("sum after last for-loop: %ld\n", sum);
    return abs(sum) % PRIME;
}


char lower(char val)
{
    return 0xF & val;
}


char upper(char val)
{
    return val >> 4;
}


void get_random_str(char* str, int length)
{
    char c;
    int i;
    for (i = 0; i < length; i++)
    {
       c = ' ' + (rand() % 126);
       str[i] = c;
    }
}
    
int main()
{
    int table4[PRIME]; // counts the nuber of collisions - 1 of the hash;
    int table8[PRIME]; // counts the nuber of collisions - 1 of the hash;
    int table16[PRIME]; // counts the nuber of collisions - 1 of the hash;
    int table32[PRIME]; // counts the nuber of collisions - 1 of the hash;
    int i;
    // init the tables to zero
    for(i = 0; i < PRIME; i++) 
    {
        table4[i] = 0;
        table8[i] = 0;
        table16[i] = 0;
        table32[i] = 0;
    }
    char* str4 = calloc(5, sizeof(char));
    char* str8 = calloc(9, sizeof(char));
    char* str16 = calloc(17, sizeof(char));
    char* str32 = calloc(33, sizeof(char));

    // seed rand()
    unsigned int seed = time(NULL);
    srand(seed);
   
    // test hashing function
    for (i = 0; i < 1000; i++)
    {
        get_random_str(str4, 4);
        table4[hash_fold_div(str4, PRIME)]++;
        //printf("i = %d: h(%s) = %u\n", i, str4, hash_fold_div(str4, PRIME));
    }
    for (i = 0; i < PRIME; i++)
        printf("%d %u\n", i, table4[i]);

    return 0;    
}

