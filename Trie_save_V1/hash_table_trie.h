#ifndef __HASH_TABLE_TRIE_H
#define __HASH_TABLE_TRIE_H
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>


typedef struct _trie *Trie;

Trie createTrieForHash(int maxNode);

void insertInTrieForHash(Trie trie, unsigned char *w);

int getNodeFromCharacter(Trie trie, int beginNode, char c);

int isInTrieForHash(Trie trie, unsigned char *w);

void printTrieForHash(Trie trie);

void freeTrieForHash(Trie trie);

#endif
