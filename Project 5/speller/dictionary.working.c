// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include "dictionary.h"

// Represents a node in a hash table, the nodes in the table are linked lists.
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

//Global Variable for Size
int dicsize = 0;

// Number of buckets in hash table
const unsigned int N = 572; //first two letters, excluding any combination with w,y,x,z as the second, so 22 possible combinations for each letter, so 26 * 22 = 572

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int checkindex = 0;
    struct node *cursor;

    /* node *cursor = malloc(sizeof(node)); //allocate memory size of node
    if (cursor == NULL)
    {
        printf("memory allocation error during node creation");
        return false;
    } */

    checkindex = hash(word);
    cursor = table[checkindex];

    if (table[checkindex] != NULL)
    {
    //traverse the linked list at the index location in the hash table
        do{
            if (strcasecmp(word,cursor->word) == 0)
            {
                return true;
            }
             cursor = cursor->next;

        }while (cursor != NULL);
    }

    //free(cursor);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int index1 = 0; //needs to generate appropriate starting position?
    unsigned int index2 = 0; //add this value to index 1
    unsigned int realindex = 0;
    int n = 1; // index at second letter in "word"
    // simple equation to denote spot in hash table. 26 spots, 0 ~ 25. First letter should derive spot in table. Just do ASCII conversion.
    // Decided to do something hella specific tbh.
    // HASH FUNCTION DOES
    // ignores words with the same starting letters and treats as first letter
    // ignores words where the second letter is w, x, y, z and treats as first letter
    // total combinations is then aa, ab ~~~ av, 22 combinations, so first arrays go from 0 ~ 21, *

    if (strlen(word) == 1)
    {
        index1 = (tolower(word[0])%97)*22; // gets appropriate starting location in hash table
        index2 = 0;
        realindex = index1 + index2;
        return realindex;
    }

    //Catch is apostraphe is somehow the second character.
    if (word[1] == 39)
    {
        //printf("apostraphe detected in second character, increment to next letter");
        n++;
    }

    //if first and second letter are the same, return index for corresponding first letter
    if (tolower(word[0]) == word[n])
    {
       index1 = (tolower(word[0])%97)*22; // gets appropriate starting location in hash table
       index2 = 0;
       realindex = index1 + index2;
       return realindex;
    }

    // check if second letter is w,x,y,z, if true, return index for corresponding first letter
    else if (word[n] == 119 || word[n] == 120 || word[n] == 121 || word[n] == 122) // check if second letter is w,x,y,z
    {
       index1 = (tolower(word[0])%97)*22; // gets appropriate starting location in hash table
       index2 = 0;
       realindex = index1 + index2;
       return realindex;
    }

    else
    {
        index1 = (tolower(word[0])%97)*22; // gets appropriate starting location in hash table
        index2 = (tolower(word[n])%97);
        realindex = index1 + index2;
        return realindex;
    }

    printf("HASH FAILURE");
    return 0;

}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    // OPEN DICTIONARY FILE
    // CREATE NEW NODE FOR EACH WORD
    // HASH WORD TO OBTAIN HASH VALUE
    // INSERT NODE INTO HASH TABLE AT THAT LOCATION

    //PER THE SPEC, NO WORD IS GREATER THAN LENGTH
    char *wordholder = (char*)malloc(sizeof(char) * LENGTH + 1);
    if (wordholder == NULL)
    {
        printf("memory allocation error during node creation");
        return false;
    }

    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Inappropriate file being loaded");
        return false;
    }

    node *n = malloc(sizeof(node)); //allocate memory size of node
    if (n == NULL)
    {
        printf("memory allocation error during node creation");
        return false;
    }

    while (fscanf(file, "%s", wordholder) != EOF)
    {
        strcpy(n->word, wordholder); //take parameter word (see typedef of node structure) and set it to word in wordholder

        unsigned int index = hash(wordholder);

        n->next = table[index];
        table[index] = n;


        // free(n);
        n = malloc(sizeof(node)); //allocate memory size of node
        if (n == NULL)
        {
            printf("memory allocation error during node creation");
            return false;
        }

        free(wordholder);
        wordholder = (char*)malloc(sizeof(char) * LENGTH + 1);
        if (wordholder == NULL)
        {
            printf("memory allocation error during node creation");
            return false;
        }
        
        // PRINT THE WORDS IN EACH LINKED LIST AT EACH INDEX
        for (node *tmp = table[index]; tmp != NULL; tmp = tmp->next)
        {
            printf("%s ", tmp->word);
        }
        printf("\n");
        dicsize++;
    }

    fclose(file);
    free(n);
    free(wordholder);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // done returns global variable dicsize
    return dicsize;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{

    struct node *freecursor;
    struct node *tmp;

    for (int i = 0; i < N; i++)
    {
        //initialize positions of cursors
        if (table[i] != NULL)
        {
            tmp = table[i];
            freecursor = table[i];
            do
            {
                tmp = freecursor;
                freecursor = freecursor->next;
                free(tmp);
            }while(freecursor != NULL);
        }
    }

    return true;
}
