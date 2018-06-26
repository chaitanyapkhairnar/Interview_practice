/*
 * This file contains the hash table implementation for storing strings.
 * It contains a function to calculate hash of the given string and data
 * structure to store this string hash value pair.
 */

#include <stdio.h>
#include <stdlib.h>

/* Linked list node */
typedef struct ll_node {
    char *string;            /* Actual String */
    struct ll_node *next;    /* Next pointer */
}ll_node;

/*
 * Hash table struct which contains an array of linked lists.
 * The index of the table is the hash value calculated for the
 * string. We use linked list to handle collision of hash values.
 */
typedef struct hashTable {
    long int size;             /* Size of the hash table */
    struct ll_node **table;    /* Array of linked list head pointers */
}hashTable;

/*
 * Function to create a hash table.
 */
hashTable* createHashTable(long int size) {
    hashTable *hashT = NULL;
    /* First allocate memory to the pointer */
    hashT = (hashTable*)malloc(sizeof(hashTable));
    /* Now allocate memory to the table */
    hashT->table = (ll_node**)malloc(sizeof(ll_node*)*size);
    /* Now point all the nodes in table array to null.
     * Note that we are not allocating memory to the nodes
     * here. That will be done when we actually add strings to the table.
     */
    for(int i=0; i<size; i++) {
        hashT->table[i] = NULL;
    }
    hashT->size = size;
    return hashT;
}

/*
 * Function to calculate hash value of given string for the
 * given hashtable
 */
long int computeHash(char *str, hashTable *ht) {
    unsigned long int hash = 0;
    int i = 0;

    while(i < strlen(str)) {
        hash = hash << 8;
        hash = hash + str[i];
        i++;
    }

    int hashVal = hash % ht->size;

    return hashVal;
}

/*
 * Function to store string in the hash table
 */
void storeInHashTable(char *str, hashTable *ht) {
    long int hashVal = computeHash(str, ht);
    if(ht->table[hashVal] == NULL) {
        ht->table[hashVal] = (ll_node*)malloc(sizeof(ll_node));
        strcpy(str, ht->table[hashVal]->string);
        ht->table[hashVal]->next = NULL;
    } else {
        ll_node *temp = (ll_node*)malloc(sizeof(ll_node));
        strcpy(str, temp->string);
        temp->next = ht->table[hashVal];
        ht->table[hashVal] = temp;
    }
}
