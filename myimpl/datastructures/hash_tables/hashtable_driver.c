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
    Main program to test hashtable and its functions.
*/
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
    const int name2age_size = 37;
    hashtable* ht_name2age = create_hashtable(name2age_size);
    for (i = 0; i < 37; i++)
        printf("ht_name2age->table[%d] = %d\n", i, ht_name2age->table[i]);

    const char* namelist[3] = {"Bill", "Ted", "Jim"};
    const int agelist[3]    = {49,      12,     20};
    printf("\n");
    printf("insert 3 times...\n");
    for (i = 0; i < 3; i++)
        insert(ht_name2age, namelist[i], agelist[i]);

    printf("print the first entries in the table...\n");
    for (i = 0; i < 37; i++)
    {
        if (ht_name2age->table[i])
            printf("k = %d: %s is %d years old\n", i, ht_name2age->table[i]->name, ht_name2age->table[i]->value);
        else
            printf("k = %d: NUll\n", i);
    }

    printf("\nCheck if the entries exist\n");
    for (i = 0; i < 3; i++)
    {
        if (exists(ht_name2age, namelist[i]))
            printf("%s exists in the table!\n", namelist[i]);
        else
            printf("%s DOES NOT exists in the table!\n", namelist[i]);
    }

    printf("\nGet value of the entries\n");
    for (i = 0; i < 3; i++)
        printf("%s gets the value %d\n", namelist[i], get_val(ht_name2age, namelist[i]));
    
    printf("\nRemove an item\n");
    printf("Removing 'Bill'\n");
    remove_item(ht_name2age, namelist[0]);

    printf("\nCheck if the entries exist\n");
    for (i = 0; i < 3; i++)
    {
        if (exists(ht_name2age, namelist[i]))
            printf("%s exists in the table!\n", namelist[i]);
        else
            printf("%s DOES NOT exists in the table!\n", namelist[i]);
    }


    delete_hashtable(ht_name2age);
    return 0;    
}
