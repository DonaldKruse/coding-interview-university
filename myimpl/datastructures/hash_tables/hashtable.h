/*
    Hash table implementation where the keys are strings.

    Author: Donald Kruse 2019
*/

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <time.h>



// get a prime: https://www.bigprimes.net/archive/prime/8/
#define PRIME1 5477
#define PRIME2 1949
// alphabet size is the base
#define ASCII_BASE_256 256



/* Hashtable data structures */
struct tableslot {
    char* name;
    int value;
    struct tableslot* next;
};
typedef struct tableslot tableslot;

struct hashtable {
    int isfull;
    int size;
    tableslot** table;     
};
typedef struct hashtable hashtable;

/* Hash function utilities */
unsigned hash_fold_div(const char* key, unsigned m);
void get_random_str(char* str, int length);


/* Hashtable utilities */
hashtable* create_hashtable(int tablesize);
tableslot* create_slot(char* nameval, int val);
void delete_slot_list(tableslot* head);
void delete_hashtable(hashtable* ht);


/* Other utilities */
void printn(int n, char c);

#endif  /* hashtable.h */
