#include "hash_table_trie.h"

#define HASH_RATIO (4/3)



//Définition des structures --------------------------------------------

struct _list {
	int startNode, /* etat de depart de la transition */
	targetNode; /* cible de la transition */
	unsigned char letter; /* etiquette de la transition */
	struct _list *next; /* maillon suivant */
};

typedef struct _list *List;

struct _trie {
	int maxNode; /* Nombre maximal de noeuds du trie */
	int nextNode; /* Indice du prochain noeud disponible */
	List *transition; /* listes d’adjacence */
	char *finite; /* etats terminaux */
};





//Définition des méthodes ----------------------------------------------


int getHashValue(int i, unsigned char c, int maxSize) {
	return (c*11 + i *53) % maxSize;
}

Trie createTrieForHash(int maxNode) {
	Trie trie = malloc(sizeof(struct _trie));
	if(trie == NULL) {
		fprintf(stderr, "Impossible to create variable");
		return NULL;
	}
	
	trie->maxNode = maxNode;
	trie->nextNode = 1;
	
	size_t size = (size_t)(maxNode * HASH_RATIO);
	trie->transition = malloc(size * sizeof(List));
	if(trie->transition == NULL) {
		fprintf(stderr, "Impossible to create variable");
		freeTrieForHash(trie);
		return NULL;
	}

	
	trie->finite = malloc((size_t)maxNode * sizeof(char));
	if(trie->finite == NULL) {
		fprintf(stderr, "Impossible to create variable");
		freeTrieForHash(trie);
		return NULL;
	}
	for(int i = 0; i < trie->maxNode; i++) {
		trie->finite[i] = '0';
	}
	return trie;
}

void insertInTrieForHash(Trie trie, unsigned char *w) {
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
		int nextNode = getNodeFromCharacter(trie, currentNode, w[currentCharacter]);
		if(nextNode == -1) {
			if (trie->nextNode >= trie->maxNode) {
				fprintf(stderr, "Nombre maximal d'état atteint, arrêt\n");
				return;
			}
			List newElement = malloc(sizeof(struct _list));
			if(newElement == NULL) {
				fprintf(stderr, "Impossible to create a new element for list");
				exit(EXIT_FAILURE);
			}
			
			newElement->startNode = currentNode;
			newElement->letter = w[currentCharacter];
			newElement->targetNode = trie->nextNode;
			newElement->next = NULL;
			
			int hashValue = getHashValue(beginNode,c, trie->maxNode * HASH_RATIO);
			List list = trie->transition[hashValue];
			while(list != NULL && list->next != NULL) {
				list = list->next;
			}
			
			if(list != NULL) {
				list->next = newElement;
			} else {
				trie->transition[hash_value] = newElement;
			}
			
			currentNode = trie->nextNode;
			trie->nextNode++;
		} else {
			currentNode = nextNode;
		}
		currentCharacter++;
	}
	trie->finite[currentNode] = '1';
	
}

int isInTrieForHash(Trie trie, unsigned char *w) {
	if(w == NULL || trie == NULL) {
		return 0;
	}
	int currentCharacter = 0;
	int currentNode = 0;
	while(w[currentCharacter] != '\0') {
		int nextNode = getNodeFromCharacter(trie, currentNode, w[currentCharacter]);
		if(nextNode == -1) {
			return 0;
		} else {
			currentNode = nextNode;
		}
		currentCharacter++;
	}
	return trie->finite[currentNode] == '0' ? 0 : 1;
}

int getNodeFromCharacter(Trie trie, int beginNode, char c) {
	int hashValue = getHashValue(beginNode, c, trie->maxNode * HASH_RATIO);
	List list = trie->transition[hashValue];
	while(list != NULL && (list->startNode != beginNode || list->letter != c)) {
		list = list->next;
	}
	if(list == NULL) {
		return -1;
	} else {
		return list->targetNode;
	}
}


void printTrieForHash(Trie trie) {
	printf("Taille du tableau : %d \n", trie->maxNode * HASH_RATIO);
	printf("Max Node : %d\n", trie->maxNode);
	printf("Next Node : %d\n", trie->nextNode);
	
	printf("\nTable de hachage : \n");
	for(int i = 0; i < trie->maxNode * HASH_RATIO; i++) {
		List list = trie->transition[i];
		while(list != NULL) {
			printf("Position dans le tableau : %d \n", i);
			printf("Numéro du noeud de départ : %d \n", list->startNode);
			printf("Valeur de la transition : %c \n", list->letter);
			printf("Numéro du noeud cible : %d \n\n", list->targetNode);
			list = list->next;
		}
		printf("\n");
	}
	
	printf("\nEtats terminaux:\n");
	for(int i = 0; i < trie->maxNode; i++) {
		printf("Noeuds %d : %c\n", i, trie->finite[i]);
	}
}

void freeTrieForHash(Trie trie) {
	if(trie == NULL) {
		return;
	}
	if(trie->transition != NULL) {
		for(int i = 0; i < trie->maxNode * HASH_RATIO; i++) {
			if(trie->transition[i] == NULL) {
				continue;
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






