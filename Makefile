bdd: fichier.o main.o
	gcc -Wall -o bdd fichier.o main.o

fichier.o: fichier.c fichier.h
	gcc -Wall -c fichier.c

main.o: main.c fichier.h
	gcc -Wall -c main.c
