#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"

/**
Notre fonction principale
**/
int main(int argc, char const *argv[]) {
  int valMenu = 0;

  intialisationData();
  affichageMenu();
  selectionMenu(&valMenu);
  executionSelect(valMenu);


  return 0;
}

/**
Affichage du Menu
**/
void affichageMenu() {
  printf("#-----------------------------------------#\n");
  printf("#----------1---SELECTION------------------#\n");
  printf("#----------2---CREATE---------------------#\n");
  printf("#-----------------------------------------#\n");
}

/**
Création des dépendances du programme
**/
void intialisationData(){
  //sécurité on crée le dossier data
  system("bash ./script/initialisation.sh");
}

/**
Selection du mode
**/
void selectionMenu(int *valMenu){
  int val = 0;
  do {
    printf("Merci de Sélectionner un Menu ?\n");
    scanf("%d",&val);

  } while(val < 1 || val > 2); // deux seules valeurs que peut prendre le systeme

  *valMenu = val;
}
/**
Action selon le mode
**/
void executionSelect(int valMenu){

  switch (valMenu) {
    case 1:system("bash ./script/affichageBDD.sh");
          

    break;

    case 2:system("bash ./script/creationBDD.sh");
    break;
  }
}
