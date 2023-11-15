#include "table_transition_trie.h"

#define DEFAULT_VALUE -1



//Définition des structures --------------------------------------------

struct _trie {
	int maxNode; /* Nombre maximal de noeuds du trie */
	int nextNode; /* Indice du prochain noeud disponible */
	int **transition; /* matrice de transition */
	char *finite; /* etats terminaux */
};






//Définition des méthodes ----------------------------------------------

Trie createTrieForTable(int maxNode) {
	Trie trie = malloc(sizeof(struct _trie));
	if(trie == NULL) {
		fprintf(stderr, "Impossible to create variable");
		return NULL;
	}
	
	trie->maxNode = maxNode;
	trie->nextNode = 1;
	trie->transition = malloc((size_t)(maxNode) * sizeof(int*));
	if(trie->transition == NULL) {
		fprintf(stderr, "Impossible to create variable");
		freeTrieForTable(trie);
		return NULL;
	}
	trie->finite = malloc((size_t)maxNode * sizeof(char));
	if(trie->finite == NULL) {
		fprintf(stderr, "Impossible to create variable");
		freeTrieForTable(trie);
		return NULL;
	}
	for(int i = 0; i < maxNode; i++) {
		trie->transition[i] = malloc(UCHAR_MAX * sizeof(int));
		if(trie->transition[i] == NULL) {
			fprintf(stderr, "Impossible to create variable");
			freeTrieForTable(trie);
			return NULL;
		}
		for(int j = 0; j < UCHAR_MAX; j++) {
			trie->transition[i][j] = DEFAULT_VALUE;
		}
		
		trie->finite[i] = '0';
	}
	return trie;
}

void insertInTrieForTable(Trie trie, unsigned char *w) {
	if(w == NULL) {
		fprintf(stderr, "Impossible d'insérer un mot inexistant");
		return;
	}
	if(trie == NULL) {
		fprintf(stderr, "Impossible d'insérer dans un arbre inexistant");
		return;
	}
	int currentCharacter = 0;
	int currentNode = 0;
	while(w[currentCharacter] != '\0') {
		int nextNodeForWord;
		if((nextNodeForWord = getNodeFromCharacter(trie, currentNode, w[currentCharacter])) != -1) {
			currentNode = nextNodeForWord;
		} else {
			if(trie->nextNode >= trie->maxNode) {
				fprintf(stderr, "Nombre maximal d'état atteint, arrêt\n");
				return;
			}
			createTransition(trie, currentNode, trie->nextNode, w[currentCharacter]);
			currentNode = trie->nextNode;
			trie->nextNode++;
		}
		currentCharacter++;
	}
	trie->finite[currentNode] = '1';
}

int isInTrieForTable(Trie trie, unsigned char *w) {
	if(w == NULL || trie == NULL) {
		return 0;
	}
	int currentCharacter = 0;
	int currentNode = 0;
	int nextNodeForWord;
	while(w[currentCharacter] != '\0' && (nextNodeForWord = 
	getNodeFromCharacter(trie, currentNode, w[currentCharacter])) != -1) {
		currentNode = nextNodeForWord;
		currentCharacter++;
	}
	if( w[currentCharacter] != '\0') {
		return 0;
	}
	return trie->finite[currentNode] == '1' ? 1 : 0;
}


int getNodeFromCharacter(Trie trie, int beginNode, char c) {
	return trie->transition[beginNode][c];
}

void createTransition(Trie trie, int startNode, int targetNode, char c) {
	int isNewNode = 1;
	for(int i = 0; i < UCHAR_MAX; i++) {
		if(trie->transition[targetNode][i] != -1) {
			isNewNode = 0;
			if(trie->nextNode >= trie->maxNode) {
				fprintf(stderr, "Nombre maximal d'état atteint, arrêt\n");
				return;
			}
			break;
		}
	}
	trie->transition[startNode][c] = targetNode;
}


void printTrieForTable(Trie trie) {
	printf("Max Node : %d\n", trie->maxNode);
	printf("Next Node : %d\n", trie->nextNode);
	
	printf("\nMatrice : \n");
	for(int i = 0; i < trie->maxNode; i++) {
		for(int j = 0; j < UCHAR_MAX; j++) {
			printf("[%d] ", trie->transition[i][j]);
		}
		printf("\n");
	}
	
	printf("\nEtats terminaux:\n");
	for(int i = 0; i < trie->maxNode; i++) {
		printf("Noeuds %d : %c\n", i, trie->finite[i]);
	}
}


void freeTrieForTable(Trie trie) {
	if(trie == NULL) {
		return;
	}
	if(trie->transition != NULL) {
		for(int i = 0; i < trie->maxNode; i++) {
			if(trie->transition[i] == NULL) {
				return;
			}
			free(trie->transition[i]);
		}
		free(trie->transition);
	}
	if(trie->finite != NULL) {
		free(trie->finite);
	}
	free(trie);
}
