SGBD: fichier.o main.o SQL.o initialisation.o split.o
	gcc -Wall -o SGBD fichier.o main.o SQL.o initialisation.o split.o

fichier.o: fichier.c fichier.h SQL.h split.h initialisation.h
	gcc -Wall -c fichier.c

initialisation.o: initialisation.c initialisation.h
	gcc -Wall -c initialisation.c

main.o: main.c fichier.h initialisation.h
	gcc -Wall -c main.c

SQL.o: SQL.c SQL.h fichier.h initialisation.h split.h
	gcc -Wall -c SQL.c

split.o: split.h split.c
	gcc -Wall -c split.c
