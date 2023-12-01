#include "ac.h"

/* ----------------------------------------------------------------------------
*                                DECLARATIONS FONCTIONS
*----------------------------------------------------------------------------*/
/**
 * getAllTransitions : renvoie une pile contenant toutes les transitions
 * 										 depuis un noeud de départ beginNode, contenues dans trie.
 */
Stack getAllTransitions(Trie trie, int beginNode);

/**
 * getStringFromFile : à partir d'un fichier fournit en paramètre, transforme
 * 										 son contenu en chaine de 
 * 										caractères
 */
static char *getStringFromFile(FILE *f);

/**
 * getAllWordsFromFile : renvoie une liste de mots contenus dans un fichier f
 * 											 où chaque ligne comporte un mot, rempli également la
 * 											 taille size.
 */
static unsigned char **getAllWordsFromFile(FILE *f, int *size);

/**
 * freeWordList : libère l'espace alloué à chaque élément de wordList.
 */
void freeWordList(unsigned char **wordList);

/* ----------------------------------------------------------------------------
*                                FONCTIONS
*----------------------------------------------------------------------------*/
int main(int argc, char **argv) {
	if(argc != 3) {
		fprintf(stderr, "Not a valid amount of parameters\n");
		exit(EXIT_FAILURE);
	}
	FILE *text = fopen(argv[2], "r");
	if(text == NULL) {
		fprintf(stderr, "Error while opening file\n");
		exit(EXIT_FAILURE);
	}
	FILE *f = fopen(argv[1], "r");
	if(f == NULL) {
		fprintf(stderr, "Error while opening file\n");
		exit(EXIT_FAILURE);
	}
	char *y = getStringFromFile(text);
	int *numberOfWord = malloc(sizeof(int));
	if(numberOfWord == NULL) {
		fprintf(stderr, "Error while opening size\n");
		exit(EXIT_FAILURE);
	}
	unsigned char **wordList = getAllWordsFromFile(f, numberOfWord);
	int textSize = (int)strlen(y); 
	ahoCorasick(wordList, *numberOfWord, y, textSize);
	return EXIT_SUCCESS;
}

void ahoCorasick(unsigned char**wordList, int numberOfWord, char* text, 
														int textSize) {
    int compteur = 0;
    int *sup = malloc(sizeof(int) * (MAX_NODE));
    if(sup == NULL) {
        fprintf(stderr, "Impossible to allocate sup\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < MAX_NODE; i++) {
        sup[i] = 0;
    }

    Trie trie = initAhoCorasick(wordList, numberOfWord, sup);
    int e = FIRST_NODE;
    for(int i = 0; i < 10; i++) {
        printf("Noeud de départ : %d\n", i);
        printf("Noeud de suppléance : %d\n", sup[i]);
    }
    for(int j = 0; j < textSize; j++) {
        int originNode = FIRST_NODE;
        while((originNode = getNodeFromCharacter(trie, e, (unsigned char)text[j]))
                                                    == NO_NODE) {
            e = sup[e];
        }
        e = originNode;
        if(isNodeFinal(trie, e) == FINAL) {
					if(sup[e] != FIRST_NODE && isNodeFinal(trie, sup[e]) == FINAL) {
						compteur++;
						printf("%d\n", sup[e]);
					}
					compteur++;
        }
    }
    free(sup);
    printf("Compteur : %d\n", compteur);
}

Trie initAhoCorasick(unsigned char** wordList, int numberOfWord, int *sup) {
    Trie trie = createTrie(MAX_NODE);
    for(size_t i = 0; i < (size_t)numberOfWord; i++) {
        insertInTrie(trie, wordList[i]);
    }
    for(unsigned char c = 0; c < (unsigned char) UCHAR_MAX; c++) {
				if(getNodeFromCharacter(trie, FIRST_NODE, c) == NO_NODE) {
					createTransitionInTrie(trie, FIRST_NODE, FIRST_NODE, c);
				}
    }
    complete(trie, sup);
    return trie;
}

void complete(Trie trie, int *sup) {
		Queue f = create();
		Stack l = getAllTransitions(trie, FIRST_NODE);
		Transition t;
		while((t = pop(l)) != NULL) {
			int targetNode = getTargetNodeFromTransition(t);
			addValue(targetNode, f);
			sup[targetNode] = FIRST_NODE;
		}
		while(!isQueueEmpty(f)) {
			int r = removeValue(f);
			freeStack(l);
			l = getAllTransitions(trie, r);
			while((t = pop(l)) != NULL) {
				int targetNode = getTargetNodeFromTransition(t);
				addValue(targetNode, f);
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
    freeStack(l);
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
	return stack;
}

static char *getStringFromFile(FILE *f) {
	char *y = malloc((size_t)INT_MAX);
	if(y == NULL) {
		fprintf(stderr, "Error while allocating\n");
		return NULL;
	}
	int currentChar = 0;
	while(currentChar < INT_MAX && fscanf(f, "%c", &y[currentChar]) == 1) {
		++currentChar;
	}
	if(!feof(f)) {
		free(y);
		fprintf(stderr, "Error while reading file text \n");
		return NULL;
	}
	return y;
}

static unsigned char **getAllWordsFromFile(FILE *f, int *size) {
	unsigned char **wordList = malloc(MAX_LINE_NUMBER * sizeof(char));
	if(wordList == NULL) {
		fprintf(stderr, "Error while allocating\n");
		free(size);
		exit(EXIT_FAILURE);
	}
	int currentInd = 0;
	unsigned char *line = malloc(sizeof(char) * MAX_LINE_LENGTH);
	if(line == NULL) {
		fprintf(stderr, "Error while allocating a line\n");
		free(size);
		free(wordList);
	}
	while((line = (unsigned char *)fgets((char *)line, MAX_LINE_LENGTH, f)) != NULL) {
		wordList[currentInd] = line;
        char* endOfLine = strchr((char *)line, '\n');
        if (endOfLine != NULL) {
            *endOfLine = '\0';
        }
		++currentInd;
		line = malloc(sizeof(char) * MAX_LINE_LENGTH);
		if(line == NULL) {
			fprintf(stderr, "Error while allocating a line\n");
			free(size);
			free(wordList);
		}
	}
	if(!feof(f)) {
		free(wordList);
		free(size);
		fprintf(stderr, "Error while reading file word\n");
		exit(EXIT_FAILURE);
	}
	*size = currentInd;
	return wordList;
}

void freeWordList(unsigned char **wordList) {
	if(wordList == NULL) {
		return;
	}
	int currentId = 0;
	while(wordList[currentId] != NULL) {
		free(wordList[currentId]);
		currentId++;
	}
}
