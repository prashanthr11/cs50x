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

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];
long long cnt = 0;
// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int indx = hash(word);
    node *cursor = table[indx]; 
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor -> word) == 0)
        {
            return true;
        }
        cursor = cursor -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int n = (int) tolower(word[0]) - 97;
    return n;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *f = fopen(dictionary, "r");
    if (f == NULL)
    {
        return false;
    }
    char temp_word[LENGTH + 1];
    while (fscanf(f, "%s\n", temp_word) != EOF)
    {
        ++cnt;
        struct node *temp = malloc(sizeof(node));
        if (temp == NULL)
        {
            return false;
        }
        strcpy(temp -> word, temp_word);
        long long loc = hash(temp_word);
        temp -> next = table[loc];
        table[loc] = temp;
    }
    fclose(f);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return cnt;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // creates two pointers to traverse the linked list and cancel its element without losing its address
    node *tmp;
    node *cursor;

    // repeats for every index in the table
    for (int i = 0; i < N; i++)
    {
        if (table[i] == NULL)
        {
            continue;
        }

        cursor = table[i];
        tmp = cursor;

        // until the end of the list keeps freeing the memory allocated in load
        while (cursor->next != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
        free(cursor);
    }
    return true;
}
