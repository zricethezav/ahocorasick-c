# Aho-Corasick Library

C implementation of the [Aho-Corasick algorithm](https://en.wikipedia.org/wiki/Aho%E2%80%93Corasick_algorithm) for efficient string matching. It allows you to search for multiple patterns simultaneously in a given text. 


### Example:
```c
#include "ahocorasick.h"
#include <stdio.h>

int main()
{
    const unsigned char *dictionary[] = {
        (unsigned char *)"he",
        (unsigned char *)"she",
        (unsigned char *)"his",
        (unsigned char *)"hers"};

    int numWords = sizeof(dictionary) / sizeof(dictionary[0]);
    node *root = ahocorasick_create_trie(dictionary, numWords);

    unsigned char *text = (unsigned char *)"she looked at this example";

    int *matchIndices = (int *)malloc(numWords * sizeof(int));
    int numMatches = ahocorasick_find_matches(root, text, matchIndices);
    for (int i = 0; i < numMatches; i++)
    {
        printf("%s\n", dictionary[matchIndices[i]]);
    }
    ahocorasick_free_trei(root);
    return 0;
}
```
