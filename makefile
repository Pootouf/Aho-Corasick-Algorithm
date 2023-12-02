CC = gcc
CFLAGS = -std=c18 -Wall -Wconversion -Werror -Wextra -Wfatal-errors -Wpedantic -Wwrite-strings -O2 -fstack-protector-all -D_XOPEN_SOURCE=500
LDFLAGS = -lm
RM = rm

all: genere-texte genere-mots ac-hachage ac-matrice

genere-texte: genere-text.o
		$(CC) -o genere-texte genere-text.o $(LDFLAGS)

genere-text.o: genere-text.c
		$(CC) -c genere-text.c $(CFLAGS)
		
genere-mots: genere-word.o
		$(CC) -o genere-mots genere-word.o $(LDFLAGS)

genere-word.o: genere-word.c
		$(CC) -c genere-word.c $(CFLAGS)
		
stackTransition.o: stackTransition.c
		$(CC) -c stackTransition.c $(CFLAGS)

queue.o: queue.c
		$(CC) -c queue.c $(CFLAGS)

ac.o: ac.c Trie/trie.h stackTransition.h queue.h
		$(CC) -c ac.c $(CFLAGS)

ac-hachage: ac.o Trie/trie_hash.o stackTransition.o queue.o
		$(CC) -o ac-hachage ac.o Trie/trie_hash.o stackTransition.o queue.o $(LDFLAGS)

ac-matrice: ac.o Trie/trie_matrix.o stackTransition.o queue.o
		$(CC) -o ac-matrice ac.o Trie/trie_matrix.o stackTransition.o queue.o $(LDFLAGS)

clean:
	$(RM) *.o genere-texte genere-mots ac-hachage ac-matrice Trie/*.o
