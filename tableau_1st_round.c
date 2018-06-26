/*
 * Given a book, produce a list of the 1000 most common words in the book.
 */

#define hashTableSize 1000000;

typedef struct ll_node {
    char *word;
    int count;
    struct ll_node *next;
}ll_node;

int getHash(char *word) {
    int i=0;
    int hashVal = 0;
    for(i=0; i<strlen(word); i++) {
        hashVal = hashVal << 8;
        hashVal = hashVal + word[i];
    }
    return hashVal % hashTableSize;
}

typedef struct hashTable {
    int size;
    ll_node **table;
}hashTable;

void addWordtoHashTable(hashTable *ht, int index, char* word) {
    if(ht->table[index] == NULL) {
        ll_node *newNode = malloc(sizeof(ll_node));
        strcpy(newNode->word, word);
        newNode->count = 1;
        newNode->next = NULL;
        ht->table[index] = newNode;
    } else {
        ll_node *temp = ht->table[index];
        while(strcmp(temp->word, word)) {
            temp = temp->next;
            if(!temp) {
                break;
            }
        }
        if(temp) {
            temp->count++;
        } else {
            ll_node *newNode = malloc(sizeof(ll_node));
            strcpy(newNode->word, word);
            newNode->count = 1;
            newNode->next = ht->table[index];
            ht->table[index] = newNode;
        }
    }
}

int getCount(char *word, hashTable *ht) {
    int index = getHash(word);
    ll_node *temp = ht->table[index];
    while(strcmp(temp->word, word)) {
        temp = temp->next;
        if(!temp) {
            break;
        }
    }
    if(temp) {
        return temp->count;
    } else {
        return -1;
    }
}

typedef struct heap_st {
    char *word;
    int count;
}


void addToHeap(char* word, char **heap) {

}

char** getCommonWords(char **book, int num_of_words) {
    hashTable *ht;

    for(int i=0; i<num_of_words; i++) {
        int wordHash = getHash(book[i]);
        addWordtoHashTable(ht, wordHash, book[i]);
        }
    }

    // We use a minHeap here of size 1000 and traverse the words and store them in the heap

    char* heap[1000];

    for(int i=0; i<num_of_words; i++) {
        if(!isHeapFull) {
            addToHeap(book[i], heap);
        } else {
            if(getCount(book[i], ht) > getTopofHeap(heap)) {
                addToHeap(book[i], heap);
            }
        }
    }

    return heap;
}
