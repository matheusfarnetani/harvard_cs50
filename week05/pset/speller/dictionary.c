// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;
unsigned int countWord = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hashIndex = hash(word);
    node *cursor = table[hashIndex];

    // Loop through list searching for word
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // Read strings from file (one at a time)
    char word[LENGTH + 1];
    while (fscanf(dict, "%s", word) != EOF)
    {
        // Create a new node for each word
        node *newNode = malloc(sizeof(node));
        if (newNode == NULL)
        {
            return false;
        }

        // Copy word into the new node
        strcpy(newNode->word, word);

        // Get index using hash function
        int hashIndex = hash(word);

        // Check if the linked list is empty
        if (table[hashIndex] == NULL)
        {
            // Point the new node to NULL
            newNode->next = NULL;
        }
        else
        {
            // Point the new node to the first node of the linked list
            newNode->next = table[hashIndex];
        }

        // Set header to new node
        table[hashIndex] = newNode;

        // Updated number of words that has been read
        countWord++;
    }

    // Close file
    fclose(dict);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return countWord;
}


// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }

        free(cursor);
    }

    return true;
}