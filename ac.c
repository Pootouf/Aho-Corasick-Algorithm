#include "ac.h"

int main(void) {

}

Trie initAhoCorasick(unsigned char** wordList, int numberOfWord) {
    Trie trie = createTrie(MAX_NODE);

    for(size_t i = 0; i < numberOfWord; i++) {
        insertInTrie(trie, wordList[i]);
    }

    for(unsigned char c = 0; c < (unsigned char) UCHAR_MAX; c++) {
        createTransition(trie, FIRST_NODE, FIRST_NODE, c);
    }

    complete(trie);

    return trie;
}

void ahoCorasick(unsigned char**worldList, int numberOfWord, char* text, int textSize) {
}