CC = gcc
CFLAGS = -std=c18 -Wall -Wconversion -Werror -Wextra -Wfatal-errors -Wpedantic -Wwrite-strings -O2 -fstack-protector-all -D_XOPEN_SOURCE=500
LDFLAGS = -lm
RM = rm

all: genere-text genere-word

genere-text: genere-text.o
		$(CC) -o genere-text genere-text.o $(LDFLAGS)

genere-text.o: genere-text.c
		$(CC) -c genere-text.c $(CFLAGS)
		
genere-word: genere-word.o
		$(CC) -o genere-word genere-word.o $(LDFLAGS)

genere-word.o: genere-word.c
		$(CC) -c genere-word.c $(CFLAGS)

clean:
	$(RM) *.o genere-text genere-word
