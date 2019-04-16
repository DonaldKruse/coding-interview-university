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



// get a prime: https://www.bigprimes.net/archive/prime/8/
#define PRIME1 5477
#define PRIME2 1949


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


struct tableslot {
    char* name;
    int value;
    struct tableslot* next;
};

typedef struct tableslot tableslot;

struct hashtable
{
    int isfull;
    int size;
    tableslot** table;     
};
typedef struct hashtable hashtable;

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


tableslot* create_slot(char* nameval, int val)
{
    tableslot* slot = malloc(sizeof(tableslot));
    slot->name = nameval;
    slot->value = val;
    slot->next = NULL;
    return slot;
}


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

void delete_hashtable(hashtable* ht)
{
    int i;
    for (i = 0; i < ht->size; i++)
        delete_slot_list(ht->table[i]);
    free(ht->table);
    free(ht);
    ht = NULL;
}


int main()
{
    int table4[PRIME2]; // counts the nuber of collisions - 1 of the hash;
    int table8[PRIME2]; // counts the nuber of collisions - 1 of the hash;
    int table16[PRIME2]; // counts the nuber of collisions - 1 of the hash;
    int table32[PRIME2]; // counts the nuber of collisions - 1 of the hash;
    int i;
    // init the tables to zero
    for(i = 0; i < PRIME2; i++) 
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
        table4[hash_fold_div(str4, PRIME2)]++;
        //printf("i = %d: h(%s) = %u\n", i, str4, hash_fold_div(str4, PRIME));
    }
    // save data
    FILE* fi;
    char* finame4 = "testTable4.txt";
    fi = fopen(finame4,"w");
    if (!fi)
    {
        printf("could not open %s\n", finame4);
        exit(-1);
    }
    for (i = 0; i < PRIME2; i++)
        fprintf(fi, "%d %u\n", i, table4[i]);

    fclose(fi);
    free(str4);
    free(str8);
    free(str16);
    free(str32);   

    // create hash table
    printf("testing hash table...\n");
    int name2age_size = 37;
    hashtable* ht_name2age = create_hashtable(name2age_size);
    for (i = 0; i < 37; i++)
        printf("ht_name2age->table[%d] = %d\n", i, ht_name2age->table[i]);

    ht_name2age->table[0] = create_slot("Bill", 42);
    ht_name2age->table[0]->next = create_slot("Ted", 23);
    delete_hashtable(ht_name2age);
    
    return 0;    
}
