/*-------------------------------------BIBLIOTHEQUES--------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

/*----------------------------------------CONSTANTES--------------------------*/

#define CHAR_START 33

/* ----------------------------------------------------------------------------
*                                DECLARATIONS FONCTIONS
*----------------------------------------------------------------------------*/

/**
 * generateText : génère un texte de longueur textLength sur un alphabet choisi
 * 								de taille alphabetSize.
 */
void generateText(int textLength, int alphabetSize);

/* ----------------------------------------------------------------------------
*                                FONCTION PRINCIPALE
*----------------------------------------------------------------------------*/

int main(int argc, char* argv[]) {
	if(argc != 3) {
		fprintf(stderr, "Invalid number of argument\n");
	}
	
	int textLength = atoi(argv[1]);
	int alphabetSize = atoi(argv[2]);
	
	generateText(textLength, alphabetSize);
}

/* ----------------------------------------------------------------------------
*                                FONCTIONS
*-----------------------------------------------------------------------------*/

void generateText(int textLength, int alphabetSize) {
    srand((unsigned int)time(NULL));
	for(int i = 0; i < textLength; i++) {
		char character = (char) (CHAR_START + rand() % (alphabetSize));
		printf("%c", character);
	}
}


