# Il FAUT séparer chaque exercice dans son propre fichier.
# Ensuite pour compiler l'exercice de votre choix,
# appelez la commande "make EXO=exo1",
# si le fichier s'appelle exo1.c

WARNING_FLAGS = -Wall -std=gnu99

EXO = fichier
#----------------------------------------------------------------------------------------------
# cible indiquant que la cible clean doit cesser
# de fonctionner si un fichier nommé clean apparaît
# dans le dossier ("phony" = fictif)
# si un fichier nommé "clean" existe dans le dossier,
# le shell affichera "make: clean est à jour."
.PHONY: clean all
# si un fichier nommé "all" apparaît dans le dossier, la cible ne fonctionnera plus
# car le fichier sera considéré à jour (all doit être ajouté à la cible .PHONY)

# cible principale du Makefile
all: $(EXO)

$(EXO): $(EXO).o Makefile
	gcc -o $(EXO) $(EXO).o -lm -lncurses

# La variable d'environnement doit être entre parenthèses dans la commande passée au shell.
# Les { } marchent aussi bien que les ( ), perso, je préfère utiliser {} pour les variables
# définies dans le Makefile, et les () pour les variables récupérées du shell.

#----------------------------------------------------------------------------------------------
# Fichier de l'exercice courant

$(EXO).o: $(EXO).c Makefile
	gcc ${WARNING_FLAGS} -c $(EXO).c

#----------------------------------------------------------------------------------------------
#----------------------------------------------------------------------------------------------
# pour les mêmes raisons que la cible "all", clean doit être ajouté à la cible .PHONY
clean:
	rm -f *.o *~ core $(EXO)

#----------------------------------------------------------------------------------------------
