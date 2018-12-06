#include <stdio.h>
#include <stdlib.h>
#include "initialisation.h"

void affichageMenu() {
  printf("#-----------------------------------------#\n");
  printf("#----------"ROUGE"1"Class"---"YELLOW"SELECTION"Class"------------------#\n");
  printf("#----------"ROUGE"2"Class"---"YELLOW"CREATE"Class"---------------------#\n");
  printf("#----------"ROUGE"3"Class"---"YELLOW"COMMANDES"Class"------------------#\n");
  printf("#----------"ROUGE"4"Class"---"YELLOW"QUIT"Class"-----------------------#\n");
  printf("#-----------------------------------------#\n");
}

/**
Création des dépendances du programme
**/
void intialisationData(){
  //sécurité on crée le dossier data
  printf("\033c\n");
  system("bash ./script/initialisation.sh");
}
