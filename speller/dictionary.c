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
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}
