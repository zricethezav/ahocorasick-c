#include "ahocorasick.h"

node *ahocorasick_create_node()
{
    node *new_node = (node *)malloc(sizeof(node));
    if (new_node == NULL)
    {
        return NULL;
    }
    new_node->root = 0;
    new_node->end_of_word = 0;
    new_node->index = -1;
    new_node->b = NULL;
    new_node->failure = NULL;
    for (int i = 0; i < MAX_CHARS; i++)
    {
        new_node->child[i] = NULL;
    }
    return new_node;
}

void ahocorasick_insert(node *root, const unsigned char *word, const int index)
{
    node *current = root;
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (current->child[word[i]] == NULL)
        {
            current->child[word[i]] = ahocorasick_create_node();
        }
        current = current->child[word[i]];
    }
    current->end_of_word = 1;
    current->index = index;
}

void ahocorasick_build_failure_links(node *root, int max_word_length)
{
    node **queue = (node **)malloc(max_word_length * sizeof(node *));
    int front = 0, rear = 0;

    queue[rear++] = root;
    while (front < rear)
    {
        node *current = queue[front++];
        for (int i = 0; i < MAX_CHARS; i++)
        {
            node *child = current->child[i];
            if (child && current == root)
            {
                child->failure = root;
            }
            else if (child)
            {
                node *failure = current->failure;
                while (failure && !failure->child[i])
                {
                    failure = failure->failure;
                }
                child->failure = failure ? failure->child[i] : root;
            }

            if (child)
            {
                queue[rear++] = child;
            }
        }
    }
    free(queue);
}

int ahocorasick_find_matches(node *root, const unsigned char *text, int *matchIndices)
{
    node *current = root;
    int len = strlen((char *)text);
    int numMatches = 0;
    for (int i = 0; i < len; i++)
    {
        while (current && !current->child[text[i]])
        {
            current = current->failure;
        }
        current = current ? current->child[text[i]] : root;
        node *temp = current;
        while (temp && temp->end_of_word)
        {
            matchIndices[(numMatches)++] = temp->index;
            temp = temp->failure;
        }
    }
    return numMatches;
}

void ahocorasick_free_trei(node *current)
{
    if (current == NULL)
    {
        return;
    }
    for (int i = 0; i < MAX_CHARS; i++)
    {
        ahocorasick_free_trei(current->child[i]);
    }
    free(current);
}

node *ahocorasick_create_trie(const unsigned char **dictionary, int numWords)
{
    node *root_node = ahocorasick_create_node();
    if (root_node == NULL)
    {
        return NULL;
    }
    int max_word_length = 0;

    for (int i = 0; i < numWords; i++)
    {
        int word_length = strlen((const char *)dictionary[i]);
        if (word_length > max_word_length)
        {
            max_word_length = word_length;
        }
        ahocorasick_insert(root_node, dictionary[i], i);
    }

    ahocorasick_build_failure_links(root_node, max_word_length);

    return root_node;
}