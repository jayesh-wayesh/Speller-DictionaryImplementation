/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>

#include "dictionary.h"

// Declaration of a char array to store scanned words from the dictionary
char WORD[LENGTH + 1];

// Declaration of Node pointers which will hold the base address of linked lists
node *list[HASHTABLE];

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // Finding the target linked list
    int target = hashfunc(word);
    
    // Declaring a temporary node pointer to check misspelled words
    node* temp = list[target];
    
    // Searching word in the target list 
    while (temp != NULL)
    {
        // use strcasecmp to be case insensitive
        if (strcasecmp (temp->word, word) == 0)
        {
            return true;
        }
        // switching to next node
        temp = temp->next_node;
    }
    
    return false;
}

// Declaring a variable to count the number of words in the dictionary
int word_counter = 0;
/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // open the dictionary file in reading mode
    FILE* dic = fopen(dictionary, "r");
    
    // to check any case of failure while opening file
    if (dic == NULL)
    {
        return false;
    }

    // iterating word by word through the dictionnary
    while (fscanf(dic, "%s\n", WORD) != EOF)
    {
        // Reserving memory for a new node
        node *newnode = malloc(sizeof(node));

        int slen = strlen(WORD);
        
        // Allocating memory to hold a New word
        newnode->word = (char* ) malloc(slen + 1);
        
        // Copying word to node's element
        strcpy(newnode->word, WORD);
        
        // hashing the word
        int hashed = hashfunc(WORD);

        // In case the head of this linked list is empty
        if (list[hashed] == NULL)
        {
            list[hashed] = newnode;
            
            newnode->next_node = NULL;
        }
        // otherwise
        else
        {
            newnode->next_node = list[hashed];
            
            list[hashed] = newnode;
        }
        // incrementing by one after loading each word in dic
        word_counter++;
    }
    // Closing file
    fclose(dic);
    // successful return
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // Returning total number of words loaded
    return word_counter;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < HASHTABLE; i++)
    {
        // Initiating a cursor to move inside each linked list
        node *cursor = list[i];
        
        // Clearing all the reserved memory
        while (cursor != NULL)
        {
            node* tmp = cursor;
            
            char* tmpc = cursor->word;
            
            cursor = cursor->next_node;
            
            // freeing all the memory reserved by node elements
            free(tmpc);
            
            free(tmp);
        }
    }
    // successful return
    return true;
}

/**
 * Hash function to return the index value of linked list 
 */
int hashfunc(const char* word)
{
    int index = 0;
    // finding out index value
    for (int i = 0; word[i] != '\0'; i++)
    {
        index = index + tolower(word[i]);
    }
    
    // mod by size to stay within limits
    index = index % HASHTABLE;

    return index;
}