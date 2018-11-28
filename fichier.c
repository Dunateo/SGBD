#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fichier.h"
#include "SQL.h"


/**
Selection du mode
**/
void selectionMenu(int *valMenu){
  int val = 0;
  do {
    printf("Merci de Sélectionner un Menu ?\n");
    scanf("%d",&val);

  } while(val < 1 || val > 4);// deux seules valeurs que peut prendre le systeme

  *valMenu = val;
}

/**
Selection du directory
**/
void selectPath(selection *select){
  //init
  char trans[10];
  char transd[10];
  char cmd[40];
  char cmdtrans[30];
  char cmddeux[100];
  strcpy(select->BDD,"");
  strcpy(select->Table,"");
  //selection
  do {
    printf("Le nom de la sélection ?\n");
    scanf("%s", trans);
    snprintf(cmdtrans, sizeof cmdtrans, "cd ./data/%s/", trans);
  } while(system(cmdtrans) != 0);

  //ajout des chemins
  snprintf(select->BDD, sizeof select->BDD, "./data/%s/", trans);
  snprintf(select->Table, sizeof select->Table, "./data/%s/", trans);
  snprintf(cmd, sizeof cmd, "cd %s; ls", select->BDD);
  //command system
  system(cmd);
  //selection
  do {
    printf("Le nom de la Table?\n");
    scanf("%s", transd);
    snprintf(cmddeux, sizeof cmddeux, "%s%s.txt",select->BDD ,transd);
  } while(fopen(cmddeux, "r") == NULL);

  //path to table
  strcat(select->Table, transd);
  strcat(select->Table, ".txt");
  printf("Voici votre sélection :%s\n",select->Table );

}

/**
Action selon le mode
**/
void executionSelect(int valMenu, selection *select){
  int valCs = 0;

  switch (valMenu) {
    //SELECTION
    case 1:system("bash ./script/affichageBDD.sh");
      selectPath(select);
    break;


    //CREATE
    case 2:

    printf("1----------BDD\n");
    printf("2----------TABLE\n");
    scanf("%d",&valCs);
    if(valCs == 1){
      system("bash ./script/creationBDD.sh");
      valCs = 0;
    }
    else if(valCs == 2){
      system("bash ./script/creationTable.sh");
      valCs = 0;
    }
    break;

    //COMMANDES
    case 3:
    //on vérifie si l'ultilisateur à sélectionné un directory
      if(strcmp(select->BDD,"") == 0){
        printf("IMPOSSIBLE MALHEUREUX SELECTIONNE UNE BDD\n");
      }
      else{
        gerePoint(select);
      }

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


}
