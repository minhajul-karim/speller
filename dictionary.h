// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// Structure for trie
typedef struct _trie
{
    struct _trie* alphabet[27];
    bool isWord;
}
trie;

// Prototypes
bool check(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
trie* create();
void delete_root(trie* root_node);
bool unload(void);

#endif // DICTIONARY_H
