#include "ac.h"

/* ----------------------------------------------------------------------------
*                                DECLARATIONS FONCTIONS
*----------------------------------------------------------------------------*/
/**
 * getAllTransitions : renvoie une pile contenant toutes les transitions
 * 										 depuis un noeud de départ beginNode, contenues dans trie.
 */
Stack getAllTransitions(Trie trie, int beginNode);

/* ----------------------------------------------------------------------------
*                                FONCTIONS
*----------------------------------------------------------------------------*/
int main(void) {

}

void ahoCorasick(unsigned char**worldList, int numberOfWord, char* text, 
														int textSize) {
		int sup[MAX_NODE];
		Trie trie = initAhoCorasick(wordList, numberOfWord, sup);
		int e = FIRST_NODE;
		for(int j = 0; j < textSize; j++) {
			int originNode;
			while((originNode = getNodeFromCharacter(trie, e, text[j])) == NO_NODE) {
				e = sup[e];
			}
			e = originNode;
			if(isNodeFinal(trie, e) == FINAL) {
				printf("Il y a une occurrence\n");
			}
		}
}

Trie initAhoCorasick(unsigned char** wordList, int numberOfWord, int *sup) {
    Trie trie = createTrie(MAX_NODE);
    for(size_t i = 0; i < numberOfWord; i++) {
        insertInTrie(trie, wordList[i]);
    }
    for(unsigned char c = 0; c < (unsigned char) UCHAR_MAX; c++) {
        createTransition(trie, FIRST_NODE, FIRST_NODE, c);
    }
    complete(trie, sup);
    return trie;
}

void complete(Trie trie, int *sup) {
		Queue f = create();
		Stack l = getAllTransitions(trie, FIRST_NODE);
		while((Transition t = pop(stack)) != NULL) {
			int targetNode = getTargetNodeFromTransition(t);
			addValue(targetNode, queue);
			sup[targetNode] = FIRST_NODE;
		}
		while(!isQueueEmpty(f)) {
			int r = removeValue(f);
			freeStack(l);
			l = getAllTransitions(trie, r);
			while((Transition t = pop(stack)) != NULL) {
				int targetNode = getTargetNodeFromTransition(t);
				addValue(targetNode, queue);
				int s = sup[r];
				int originNode;
				while((originNode = getNodeFromCharacter(trie, s, 
															getCharacterFromTransition(t))) == NO_NODE){
					s = sup[s];
				}
				sup[getTargetNodeFromTransition(t)] = originNode;
				if(isNodeFinal(trie, originNode) == FINAL) {
					setNodeFinal(trie, getTargetNodeFromTransition(t));
				}
			}
		}
}

/* ----------------------------------------------------------------------------
*                                 OUTILS
*----------------------------------------------------------------------------*/
Stack getAllTransitions(Trie trie, int beginNode) {
	Stack stack = createStack();
	for(unsigned char a = 0; a < UCHAR_MAX; a++) {
		int targetNode = getNodeFromCharacter(trie, beginNode, a);
		if(targetNode != beginNode && targetNode != NO_NODE) {
			push(stack, beginNode, a, targetNode);
		}
	}
	return stakc;
}
