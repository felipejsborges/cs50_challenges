// Implements a dictionary's functionality

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>


#include "dictionary.h"

int dictionarySize = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // return true if the word is in the dictionary, false othewise
    // case insensitive -> use strcasecmp
    // we can use a "cursor" to navigate in the linked lists -> cursor = <firstItemOfLinkedList>; cursor = cursor->next; repeat till find the word or gets NULL

    // TODO
    // hash word to obatian a hash value
    int hashIndex = hash(word);

    // then access linked list at that index in the hash table
    node *cursor = table[hashIndex];
    if (cursor == NULL || !table[hashIndex])
    {
        return false;
    }

    // traverse linked list, looking for the word (strcasecmp)
    do
    {
        int result = strcasecmp(word, cursor->word);
        if (result == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    while (cursor);

    // return true if the word is in the dictionary, otherwise return false
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // notes
    // input: a word
    // output: num index 0~N-1
    // example hash functions: first letter, first two letters, math using all the letters... look online for hash functions
    // 97 ~ 122

    // TODO
    char lowerChar = tolower(word[0]);
    return ((int) lowerChar) - 97;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    // Open dictionary file
    FILE *fp = fopen(dictionary, "r");

    // check if return NULL
    if (fp == NULL)
    {
        return false;
    }

    // Read string from file on at a time
    char word[LENGTH];

    do
    {
        // get line (word)
        fscanf(fp, "%s", word);

        // make sure if "word" is a word
        if (isalpha(word[0]))
        {
            // Create a new node for each word
            node *n = malloc(sizeof(node));

            if (n == NULL)
            {
                return false;
            }

            strcpy(n->word, word);

            // Hash word to obtain a hash value
            int hashIndex = hash(word);

            // Insert node into hash table - be sure to set pointers in the correct order
            if (!table[hashIndex])
            {
                n->next = NULL;
                table[hashIndex] = n;
            }
            else
            {
                n->next = table[hashIndex]->next;
                table[hashIndex]->next = n;
            }

            // increasing dictionary size counter
            dictionarySize++;
        }
    }
    while (fgets(word, LENGTH, fp) != NULL);

    fclose(fp);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // notes
    // count every node on the created hash table, or just add a counter on load function that counts the words

    // TODO
    return dictionarySize;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    // create a cursor and run all the linked lists
    for (int i = 0; i < N ; i++)
    {
        if (table[i])
        {
            node *cursor = table[i];

            // for each node, create a tmp file
            do
            {
                // when cursor moves to the next node, free the previous, then move tmp to next
                node *tmp = cursor;
                cursor = cursor->next;
                free(tmp);
            }
            while (cursor);
        }
    }

    // be sure that all memory is unlocated in the end of the program -> valgrind ./speller texts/cat.txt OR help50 valgrind ./speller texts/cat.txt
    return true;
}
