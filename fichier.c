#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fichier.h"

/**
Notre fonction principale
**/
int main(int argc, char const *argv[]) {
  int valMenu = 0;

  intialisationData();
  do{
    affichageMenu();
    selectionMenu(&valMenu);
    executionSelect(valMenu);
  }while (valMenu != 3);


  return 0;
}

/**
Affichage du Menu
**/
void affichageMenu() {
  printf("#-----------------------------------------#\n");
  printf("#----------1---SELECTION------------------#\n");
  printf("#----------2---CREATE---------------------#\n");
  printf("#----------3---QUIT-----------------------#\n");
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

  } while(val < 1 || val > 3); // deux seules valeurs que peut prendre le systeme

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
/**
Lecture du fichier de structure
**/
void initialisationBDD(bdd *Base){
  FILE *f;
  int countBDD;
  f = fopen("../script/structure.txt","r");
  if(f == NULL)
		printf("fichier non ouvert\n");
  Base = malloc(sizeof(bdd)*)

}
