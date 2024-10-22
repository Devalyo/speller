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

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);
    node *cursor;
    cursor = table[index];

    while(1)
    {
        if (cursor == NULL)
        {
            free(cursor);
            return false;
        }

        if((strcasecmp(cursor->word, word)) == 0)
        {
            return true;
        }

        cursor = cursor->next;

    }

}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return toupper(word[0]) - 'A';
}

int count;
// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char buffer[LENGTH + 1];


    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not open file");
        return false;
    }


    while (fscanf(dict, "%s",  buffer) != EOF)
    {
         node *cursor = malloc(sizeof(node));
         if (cursor == NULL)
         {
            printf("Memory Error");
            free(cursor);
            fclose(dict);
            return false;
         }

         strcpy(cursor->word, buffer);

         int index = hash(buffer);
         if(table[index] == NULL)
         {
            cursor->next = NULL;
            table[index] = cursor;
            count++;
         }
         else
         {
            cursor->next = table[index];
            table[index] = cursor;
            count++;
         }
    }

    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{

        return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *cursor;
    node *tmp;
    for (int i = 0; i < N; i++)
    {
        if (table[i] == NULL)
        {
            continue;
        }

        tmp    = table[i];
        cursor = tmp->next;
        while (cursor != NULL)
        {
            cursor = tmp->next;
            free(tmp);
            tmp = cursor;
        }
     }
    return true;
}
