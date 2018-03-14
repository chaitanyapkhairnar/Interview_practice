/*
 * This file contains source code for all basic operations
 * on trie data structure.
 *
 * Trie is a tree datastructure. Unlike binary tree, it can have
 * multiple children nodes (even more than 2). Trie is mainly used
 * for data re'trie'val. Each node of trie has an array of pointers
 * pointing to its children and a boolean field 'isEndOfWord' to
 * point out that it marks the end of word.
 * Searching for a word or inserting a word takes O(m) time where m is
 * the length of word. The only disadvantage is the space requirements.
 * For English alphabets, it takes O(26*key_length*no_of_keys) space.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 26
/* Trie datastructure */
typedef struct trie_node {
    struct trie_node *children[SIZE];
    bool isEndOfWord;
}trie_node;

/* Function to initialize and get a new Trie Node */
trie_node* trie_get_node(void) {
    trie_node *new_node = (trie_node*)malloc(sizeof(trie_node));
    new_node->isEndOfWord = false;
    for(int i=0;i<SIZE;i++) {
        new_node->children[i] = NULL;
    }
    return new_node;
}

/* Function to insert a word(key) in the trie */
void trie_insert_key(trie_node *root, char *string) {
    int len = strlen(string);
    trie_node *temp = root;
    for(int i=0;i<len;i++) {
        /* Get the numeric value of index from the character */
        int index = string[i] - 'a';

        /* Check if this character is already present in the
         * trie. If children[index] is not NULL, that means this
         * character is present. If not present, create a new node
         * for this character and continue for next character. If
         * present, then no need to add new node, just continue to next
         * character.
         */
        if(!temp->children[index]) {
            temp->children[index] = trie_get_node();
        }
        temp = temp->children[index];
    }
    /* This is the last node for the word, so mark this node as
     * isEndOfWord.
     */
    temp->isEndOfWord = true;
}

/* Function to search for a word(key) in the trie.
 * It returns true if word is present else returns false.
 */
bool trie_search_key(trie_node *root, char *string) {
    int len = strlen(string);
    trie_node *temp = root;
    for(int i=0;i<len;i++) {
        int index = string[i] - 'a';
        if(!temp->children[index]) {
            /* Character not found. return false */
            return false;
        }
        temp = temp->children[index];
    }
    /* If we reach here, that means we have found all
     * the characters in the given string in the trie.
     * We need to check if this last character node is
     * end of word. If yes, this word is present. If not,
     * Then this is just the prefix for some another word
     * and our word is not present.
     */
    if(temp->isEndOfWord == true) {
        return true;
    } else {
        return false;
    }
}

int main(void) {
    char *strings[8];
    for(int i=0;i<8;i++) {
        strings[i] = (char*)malloc(sizeof(char)*10);
    }
    trie_node *root = trie_get_node();

    strcpy(strings[0], "the");
    strcpy(strings[1], "a");
    strcpy(strings[2], "there");
    strcpy(strings[3], "answer");
    strcpy(strings[4], "any");
    strcpy(strings[5], "by");
    strcpy(strings[6], "bye");
    strcpy(strings[7], "their");

    for(int i=0;i<8;i++) {
        trie_insert_key(root, strings[i]);
    }

    bool result;
    result = trie_search_key(root, "the");
    if(result) {
        printf("Key found\n");
    } else {
        printf("Key not found\n");
    }

    result = trie_search_key(root, "these");
    if(result) {
        printf("Key found\n");
    } else {
        printf("Key not found\n");
    }

    result = trie_search_key(root, "their");
    if(result) {
        printf("Key found\n");
    } else {
        printf("Key not found\n");
    }

    return 0;
}
