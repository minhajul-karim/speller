// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Declare a global trie
trie* root_node = NULL;
unsigned int num_of_loaded_words = 0;

// Create root
trie* create()
{
    /// Create a new trie
    trie* new_trie = NULL;
    new_trie = (trie*)calloc(1, sizeof(trie));

    /// Check if memory has been allocated
    if (new_trie == NULL)
    {
        fprintf(stderr, "Can not allocate memory\n");
        exit(1);
    }

    return new_trie;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary to read
    FILE* fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Error reading\n");
        exit(1);
    }

    // Declare a string of Length+2 length
    char string[LENGTH + 2];

    // Create the root node
    root_node = create();

    /// Iterate through the file by scanning each word
    while(fscanf(fp, "%s", string) != EOF)
    {
        // Loading process initiates here
        int i, index, len = strlen(string);

        // Declare a travarse node
        trie* trav = root_node;

        // Increment as we've successfully loaded a word
        num_of_loaded_words++;

        // Loop through the string
        for (i = 0; i < len; i++)
        {
            // Check if the word contains only alphabets & '
            if (string[i] >= 'a' && string[i] <= 'z')
                index = string[i] - 97;

            // Index for apostrophe
            else
                index = 26;

            // Create new node if alphabet[index] is not created
            if (trav->alphabet[index] == NULL)
            {
                trav->alphabet[index] = create();
            }

            // Travarse to next character
            trav = trav->alphabet[index];

        }

        // End of a word. Setting isWord as true
        trav->isWord = true;

        // Loading process ends here
    }

    // Close file
    fclose(fp);

    if (num_of_loaded_words > 0)
        return true;

    else
        return false;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int i, index, len = strlen(word);
    trie* trav = root_node;

    /// Loop through the word
    for (i = 0; i < len; i++)
    {
        /// Check if the word contains only alphabets & '
        if (word[i] >= 'a' && word[i] <= 'z')
            index = word[i] - 97;

        else if (word[i] >= 'A' && word[i] <= 'Z')
            index = word[i] - 65;

        else if (word[i] == '\'')
            index = 26;

        // If node word[index] is not created
        if (trav->alphabet[index] == NULL)
            return false;

        else
        {
            // Travarse to the next character
            trav = trav->alphabet[index];
        }

    }

    // End of a word. Check if isWord was set as true or false
    if (trav->isWord == true)
        return true;

    else
        return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (num_of_loaded_words > 0)
        return num_of_loaded_words;
    else
        return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Check if root_node has been allocated or not
    if (root_node != NULL)
    {
        // If allocated delete root with all corresponding children
        delete_root(root_node);
        return true;
    }
    else
        return false;
}

// Delete all root nodes using recursion
void delete_root(trie* root)
{
    for (int i = 0; i < 27; i++)
    {
        if (root->alphabet[i] != NULL)
        {
            delete_root(root->alphabet[i]);
        }
    }

    free(root);
    root = NULL;
    return;
}