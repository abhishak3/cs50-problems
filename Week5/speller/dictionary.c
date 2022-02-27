// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
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
const unsigned int N = 260;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //converting to lowercase
    int wordlen = strlen(word); // word length
    char copy[wordlen + 1];
    copy[wordlen] = '\0'; // null terminating
    for (int i = 0; i < wordlen; i++)
    {
        copy[i] = tolower(word[i]);
    }


    // hash of given word
    int index = hash(copy);

    // searching the word in the index of table returned from hash
    node *ptr = table[index];
    while (ptr != NULL)
    {
        if (!strcmp(ptr->word, copy))
        {
            return true;
        }
        ptr = ptr->next; // incrementing pointer
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //converting to lowercase
    int wordlen = strlen(word); // word length
    char copy[wordlen + 1];
    copy[wordlen] = '\0'; // null terminating
    for(int i = 0; i < wordlen; i++)
    {
        copy[i] = tolower(word[i]);
    }


    // starting letter of word
    int index = (copy[0] - 'a') * 10;

    // calculating offset with respect to length of word
    int offset = wordlen - 5;

    if (offset < 0)
    {
        offset = 0;
    }
    else if (offset > 9)
    {
        offset = 9;
    }

    return index + offset;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dic = fopen(dictionary, "r");

    // if can't open dictionary
    if (dic == NULL)
    {
        return false;
    }
    else
    {
        char word[LENGTH + 1]; // word buffer
        //while(!feof(dic))
        while (fgets(word, LENGTH + 2, dic))
        {
            // storing word in buffer
            word[strcspn(word, "\r\n")] = '\0';

            // computing index for word in buffer
            unsigned int index = hash(word);

            // new node for word and loading it into table
            node *new_node = malloc(sizeof(node));
            strcpy(new_node->word, word);
            new_node->next = table[index];
            table[index] = new_node;
        }
        fclose(dic);
        return true;
    }
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int count = 0;
    //traversing through each index of table
    for (int i = 0; i < N; i++)
    {
        // traversing through each node
        node *ptr = table[i];
        while (ptr != NULL)
        {
            count++;
            ptr = ptr->next;
        }
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //traversing through each index of table
    for (int i = 0; i < N; i++)
    {
        //traversing through each node
        node *ptr = table[i];
        while (ptr != NULL)
        {
            node *temp = ptr;
            ptr = ptr->next;
            free(temp);
        }
    }
    return true;
}

