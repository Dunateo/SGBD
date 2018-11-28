bdd: fichier.o main.o SQL.o initialisation.o
	gcc -Wall -o bdd fichier.o main.o SQL.o initialisation.o

fichier.o: fichier.c fichier.h SQL.h
	gcc -Wall -c fichier.c

initialisation.o: initialisation.c initialisation.h
	gcc -Wall -c initialisation.c

main.o: main.c fichier.h initialisation.h
	gcc -Wall -c main.c

SQL.o: SQL.c SQL.h fichier.h
	gcc -Wall -c SQL.c
