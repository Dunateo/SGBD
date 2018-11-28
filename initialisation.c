#include <stdio.h>
#include <stdlib.h>
#include "initialisation.h"

void affichageMenu() {
  printf("#-----------------------------------------#\n");
  printf("#----------1---SELECTION------------------#\n");
  printf("#----------2---CREATE---------------------#\n");
  printf("#----------3---COMMANDES------------------#\n");
  printf("#----------4---QUIT-----------------------#\n");
  printf("#-----------------------------------------#\n");
}

/**
Création des dépendances du programme
**/
void intialisationData(){
  //sécurité on crée le dossier data
  system("bash ./script/initialisation.sh");
}
