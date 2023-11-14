#ifndef __TABLE_TRANSITION_TRIE_H
#define __TABLE_TRANSITION_TRIE_H
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>


typedef struct _trie *Trie;

Trie createTrieForTable(int maxNode);

void insertInTrieForTable(Trie trie, unsigned char *w);

int getNodeFromCharacter(Trie trie, int beginNode, char c);

void createTransition(Trie trie, int startNode, int targetNode, char c);

int isInTrieForTable(Trie trie, unsigned char *w);

void printTrieForTable(Trie trie);

void freeTrieForTable(Trie trie);

#endif
