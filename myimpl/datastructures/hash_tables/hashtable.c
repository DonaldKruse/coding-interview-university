/*
    Hash table implementation where the keys are strings.

    Author: Donald Kruse 2019
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#include "hashtable.h"



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
            mult *= ASCII_BASE_256;
            //printf("%c", key[k]);
        }
        mult = 1;
        //printf("\n");
    }

    // this code below seems like garbage...
    //printf("sum before last for-loop: %ld\n", sum);
    /*
    for (int k = 0; k < intlength*4; k++)
    {
        sum += key[k] * mult;
        mult *= 256;
    }
    */
    //printf("sum after last for-loop: %ld\n", sum);
    return abs(sum) % m;
}


/* attempts to assign random character string to str */
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


/*
    Creates the space needed for a hashtable with
    an array of pointers to NULL linked lists.
*/
hashtable* create_hashtable(int tablesize)
{
    hashtable* ht = malloc(sizeof(hashtable));
    ht->size = tablesize;
    ht->table = calloc(tablesize, sizeof(tableslot*) );
    int i;
    for (i = 0; i < tablesize; i++)
        ht->table[i] = NULL;
    ht->isfull = 0;
    return ht;
}


/* 
   Deletes a single node in a linked list of type tableslot.
   Used by delete_slot_list()
*/
tableslot* create_slot(char* nameval, int val)
{
    tableslot* slot = malloc(sizeof(tableslot));
    slot->name = nameval;
    slot->value = val;
    slot->next = NULL;
    return slot;
}


/* Deletes a linked list of type tableslot. Used by delete_hashtable() */
void delete_slot_list(tableslot* head)
{
    tableslot* tmp = NULL;
    while (head)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }
    head = NULL;
}


/* Deletes an entire hashtable and all of its linked-lists */
void delete_hashtable(hashtable* ht)
{
    int i;
    for (i = 0; i < ht->size; i++)
        delete_slot_list(ht->table[i]);
    free(ht->table);
    free(ht);
    ht = NULL;
}


/* check if a key-value pair exists */
int exists(hashtable* ht, const char* key)
{
    unsigned k = hash_fold_div(key, ht->size);

    /* return true if not null, false if null */
    return (ht->table[k] != NULL);
}


/* gets the value corresponding to `key`..
 * Returns 0 if it does not exist.
 */
int get_val(hashtable* ht, const char* key)
{
    int ret_val = 0;
    if ( exists(ht, key) )
        return ret_val;  // is zero
    int k = hash_fold_div(key, ht->size);
    return ht->table[k]->value;
}


// TODO: Search through linked-list for key
/* prints n chars on a single line with no newline at the end. */
void printn(int n, char c)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%c",c);
}
