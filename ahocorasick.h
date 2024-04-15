#ifndef AHOCORASICK_H
#define AHOCORASICK_H

#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 256

typedef struct ac_node
{
    // root is 1 if this node is the root of the trie, 0 otherwise
    u_int8_t root;
    // root is 1 if this node is the root of the trie, 0 otherwise
    u_int8_t end_of_word;

    // b is the array of bytes at this node
    unsigned char *b;

    // Index into the original dictionary if output is 1
    int index;

    // Array of child nodes, indexed by the byte value
    struct ac_node *child[MAX_CHARS];

    // Pointer to the next node which is in the dictionary that can be reached from here following suffixes
    struct ac_node *failure;
} ac_node;

/**
 * Create a new node and return a pointer to it.
 * The node is initialized with default values.
 *
 * @return A pointer to the newly created node, or NULL if memory allocation fails.
 */
ac_node *ahocorasick_create_node();

/**
 * Insert a word into the trie.
 *
 * @param root The root of the trie.
 * @param word The word to insert.
 * @param index The index of the word in the dictionary.
 */
void ahocorasick_insert(ac_node *root, const unsigned char *word, const int index);

/**
 * Build the failure links in the trie using a BFS traversal.
 *
 * @param root The root of the trie.
 * @param max_word_length The maximum length of a word in the dictionary.
 */
void ahocorasick_build_failure_links(ac_node *root);

/**
 * Find all the words in the dictionary that are present in the text.
 *
 * @param root The root of the trie.
 * @param text The text to search for words.
 * @param matchIndices An array to store the indices of the words that are found.
 * @return number of matches found.
 */
int ahocorasick_find_matches(ac_node *root, const unsigned char *text, int **matchIndices);

/**
 * Free the memory allocated for the trie.
 *
 * @param current The current node to free.
 */
void ahocorasick_free_trei(ac_node *current);

/**
 * Create a trie from the dictionary.
 *
 * @param dictionary The dictionary of words.
 * @param numWords The number of words in the dictionary.
 * @return The root node of the created trie, or NULL if memory allocation fails.
 */
ac_node *ahocorasick_create_trie(const unsigned char **dictionary, int numWords);

#endif // AHOCORASICK_H