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
static unsigned char **getAllWordsFromFile(FILE *f, size_t *size);

/**
 * freeWordList : libère l'espace alloué à chaque élément de wordList.
 */
void freeWordList(unsigned char **wordList, size_t size);

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
        fclose(text);
		exit(EXIT_FAILURE);
	}
	char *y = getStringFromFile(text);
    if(y == NULL) {
        fclose(f);
        fclose(text);
        exit(EXIT_FAILURE);
    }
    size_t textSize = strlen(y);
	size_t numberOfWord = 0;
	unsigned char **wordList = getAllWordsFromFile(f, &numberOfWord);

	ahoCorasick(wordList, (int)numberOfWord, y, (int)textSize);

    free(y);
    freeWordList(wordList, numberOfWord);
    fclose(f);
    fclose(text);
	return EXIT_SUCCESS;
}

void ahoCorasick(unsigned char**wordList, int numberOfWord, char* text, 
														int textSize) {
    int compteur = 0;
    int sup[MAX_NODE];

    int numberOfOccurrencies[MAX_NODE];

    Trie trie = initAhoCorasick(wordList, numberOfWord, sup, numberOfOccurrencies);
    int e = FIRST_NODE;

    for(int j = 0; j < textSize; j++) {
        int originNode = FIRST_NODE;
        while((originNode = getNodeFromCharacter(trie, e, (unsigned char)text[j]))
                                                    == NO_NODE) {
            e = sup[e];
        }
        e = originNode;
        if(numberOfOccurrencies[e] != 0) {
            compteur += numberOfOccurrencies[e];
        }
    }
    freeTrie(trie);
    printf("%d\n", compteur);
}

Trie initAhoCorasick(unsigned char** wordList, int numberOfWord, int *sup, int* numberOfOccurrencies) {
    Trie trie = createTrie(MAX_NODE);
    for(size_t i = 0; i < (size_t)numberOfWord; i++) {
        insertInTrie(trie, wordList[i]);
        numberOfOccurrencies[getLastNode(trie)] = 1;
    }
    for(unsigned char c = 0; c < (unsigned char) UCHAR_MAX; c++) {
        if(getNodeFromCharacter(trie, FIRST_NODE, c) == NO_NODE) {
            createTransitionInTrie(trie, FIRST_NODE, FIRST_NODE, c);
        }
    }
    complete(trie, sup, numberOfOccurrencies);
    return trie;
}

void complete(Trie trie, int *sup, int* numberOfOccurrencies) {
    Queue f = create();
    Stack l = getAllTransitions(trie, FIRST_NODE);
    Transition t;
    while((t = pop(l)) != NULL) {
        int targetNode = getTargetNodeFromTransition(t);
        addValue(targetNode, f);
        sup[targetNode] = FIRST_NODE;
        freeTransition(t);
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
            int p = getTargetNodeFromTransition(t);
            sup[p] = originNode;
            numberOfOccurrencies[p] += numberOfOccurrencies[sup[p]];
            freeTransition(t);
        }
    }
    freeQueue(f);
    freeStack(l);
}

/* ----------------------------------------------------------------------------
*                                 OUTILS
*----------------------------------------------------------------------------*/
Stack getAllTransitions(Trie trie, int beginNode) {
	Stack stack = createStack();
	for(unsigned char a = 0; (int)a < UCHAR_MAX; a++) {
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
    y[currentChar] = '\0';
	if(!feof(f)) {
		free(y);
		fprintf(stderr, "Error while reading file text \n");
		return NULL;
	}
	return y;
}

static unsigned char **getAllWordsFromFile(FILE *f, size_t *size) {
	unsigned char **wordList = calloc(sizeof(char), MAX_LINE_NUMBER);
	if(wordList == NULL) {
		fprintf(stderr, "Error while allocating\n");
		exit(EXIT_FAILURE);
	}
	size_t currentInd = 0;
	unsigned char *line = calloc(sizeof(char), MAX_LINE_LENGTH);
	if(line == NULL) {
		fprintf(stderr, "Error while allocating a line\n");
        freeWordList(wordList, currentInd);
        exit(EXIT_FAILURE);
	}
	while(fgets((char *)line, MAX_LINE_LENGTH, f) != NULL) {
		wordList[currentInd] = line;
        char* endOfLine = strchr((char *)line, '\n');
        if (endOfLine != NULL) {
            *endOfLine = '\0';
        }
		++currentInd;
		line = calloc(sizeof(char), MAX_LINE_LENGTH);
		if(line == NULL) {
			fprintf(stderr, "Error while allocating a line\n");
            freeWordList(wordList, currentInd);
            exit(EXIT_FAILURE);
		}
	}
    free(line);
	if(!feof(f)) {
        freeWordList(wordList, currentInd);
		fprintf(stderr, "Error while reading file word\n");
		exit(EXIT_FAILURE);
	}
	*size = currentInd;
	return wordList;
}

void freeWordList(unsigned char **wordList, size_t size) {
	if(wordList == NULL) {
		return;
	}
	for(size_t i = 0; i < size; i++) {
		free(wordList[i]);
	}
    free(wordList);
}
