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
#include <assert.h>


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
tableslot* create_slot(const char* nameval, int val)
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
int exists(hashtable* ht, const char* name)
{
    unsigned key = hash_fold_div(name, ht->size);

    /* return true if not null, false if null */
    assert(key < ht->size);
    if (search_tableslot_list(ht->table[key], name))
      return 1;
    else
      return 0;
}


/* gets the value corresponding to `key`..
 * Returns 0 if it does not exist.
 */
int get_val(hashtable* ht, const char* name)
{
    int ret_val = 0;
    int key = hash_fold_div(name, ht->size);
    if ( !exists(ht, name) )
        return ret_val;  // is zero
    assert(key < ht->size);
    tableslot* ts = search_tableslot_list(ht->table[key], name);
    if (ts)
      return ts->value;
    return 0;
}


/* Returns a pointer to the slot in a list with corresponding unhashed key `name` */
tableslot* search_tableslot_list(tableslot* ts_head, const char* name)
{
    tableslot* tmp = ts_head;
    int cmpval;
    while (tmp)
    {
        cmpval = strcmp(name, tmp->name);
        if (cmpval == 0) // they are equal
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}


void insert(hashtable* ht, const char* name, int age)
{
    unsigned key = hash_fold_div(name, ht->size);
    assert(key < ht->size);
    if (ht->table[key] == NULL)
      ht->table[key] = create_slot(name, age);
    else
        append(ht->table[key], name, age);
}


/*
 *  Appends slot to the end of a list.
 */
void append(tableslot* ts_head, const char* name, int age)
{
    assert(ts_head);
    tableslot* tmp = ts_head;
    tableslot* end = create_slot(name, age);
    while (tmp->next)
      tmp = tmp->next;
    assert(tmp->next == NULL);
    tmp->next = end;
}
      


/* searches and removes an item from a list if found */
void remove_from_list(tableslot** ts_head_ref, const char* name)
{
    tableslot* head = *ts_head_ref;
    tableslot* tmp = head;
    tableslot* prev = NULL;
    int cmpval;  // for string comparison
    
    // check if head is the item
    cmpval = strcmp(tmp->name, name);
    if (cmpval == 0) // equality
    {
        *ts_head_ref = tmp->next;
        free(tmp);
        return;
    }

    // search for item
    while (tmp && (cmpval = strcmp(tmp->name, name) != 0) )
    {
        prev = tmp;
        tmp = tmp->next;
    }
    
    // not found
    if (tmp == NULL)
      return;
    
    // found
    prev->next = tmp->next;
    free(tmp);
}
        
/*
 * remove an item from the hashtable if it exisits..
 */
void remove_item(hashtable* ht, const char* name)
{
    unsigned key = hash_fold_div(name, ht->size);
    assert(key < ht->size);
    remove_from_list(&(ht->table[key]), name);
}


void print_hashtable(hashtable* ht)
{
    int i;
    tableslot* tmp = NULL;
    for (i = 0; i < ht->size; i++)
    {
        if (ht->table[i] == NULL)
        {
            printf("key = %d:    NULL\n", i);
            continue;
        }
        printf("key = %d:\n", i);
        tmp = ht->table[i];
        while (tmp)
        {
           printf("    %s : %d\n", tmp->name, tmp->value);
           tmp = tmp->next;
        }
    }
}

/* prints n chars on a single line with no newline at the end. */
void printn(int n, char c)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%c",c);
}
