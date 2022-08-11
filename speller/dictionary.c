// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 143024;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    node *tmp = table[index];
    while (tmp != NULL)
    {
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int value = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        value += toupper(word[i]);
    }
    return value % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // 1. Open FILE
    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        return false;
    }
    // 2. Read strings into file
    char buffer[LENGTH + 1];
    while (fscanf(input, "%s", buffer) != EOF)
    {
        // 3. Create a new node to store each particular word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, buffer);
        // 4. How we insert this node into HASH table
        int index = hash(buffer);
        // 5. Insert Node into Hash table
        // 5.1 set new node (N) to 1st element in linked list
        n->next = table[index];
        // 5.2 reset 1st element linked list to newly created note
        table[index] = n;
    }
    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // count initialized to 0 to count words in dictionary
    int count = 0;
    // loop to go through tables
    for (int i = 0; i < N; i++)
    {
        // loop to go through horizontal nodes
        node *tmp = table[i];
        while (tmp != NULL)
        {
            count++;
            tmp = tmp->next;
        }
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *tmp = cursor;
        while (cursor != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
