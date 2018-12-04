#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fichier.h"
#include "SQL.h"
#include "split.h"





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
Selection fichier pour lecture
**/
void selectFich(selection *select){
  //init
  char trans[10];
  char transd[10];
  char cmd[60];
  char cmdtrans[60];
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
  snprintf(select->BDD, sizeof select->BDD, "%s", trans);
  snprintf(cmd, sizeof cmd, "cd ./data/%s/; ls", select->BDD);
  //command system
  system(cmd);
  //selection
  do {
    printf("Le nom de la Table?\n");
    scanf("%s", transd);
    snprintf(cmddeux, sizeof cmddeux, "./data/%s/%s.txt",select->BDD ,transd);
  } while(fopen(cmddeux, "r") == NULL);

  //path to table
  snprintf(select->Table, sizeof select->Table, "%s.txt", transd);
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
void initialisationBDD(BDD *Base){
  int taille = 0;
  int taille2 = 0;
  int compteur = 0, cpttrans, cpt2 = 0, cpttrans2, cptTable;
  char trans[200], cmd[250];
  char **Fichiertrans,**Fichiertrans2, **FichierTable;
  FILE *f;
  selection select;
  selectFich(&select);

  //affectation nom BDD
  taille = strlen(select.BDD);
  Base->nomBDD = malloc(sizeof(char)*taille);
  strcpy(Base->nomBDD, select.BDD);
  taille = taille +10;


  //affectation chemin BDD
  Base->cheminBDD = malloc(sizeof(char)*taille);
  strcpy(Base->cheminBDD, "./data/");
  strcat(Base->cheminBDD,select.BDD);
  strcat(Base->cheminBDD,"/");

  //affectation chemin Table
  taille2 = strlen(select.Table)+14;
  Base->cheminTable = malloc(sizeof(char)*taille2);
  strcpy(Base->cheminTable, Base->cheminBDD);
  strcat(Base->cheminTable,select.Table);


  //lecture fichier
  f = fopen("./script/structure.txt","r");
  if(f == NULL){
    printf("problèmes dépendances \n" );
  }

  fscanf(f,"%d\n",&Base->nbBDD);


//compter le nombre de tables par bdd sélectionné
  while (fgets(trans, sizeof trans, f) != NULL) {
    fonctFich(trans,&Fichiertrans,&cpttrans);
    //comparaison nom bdd
    if (strcmp(Fichiertrans[0],Base->nomBDD )==0) {
      compteur++;
    }
  }
  //remise début fichier
  fseek ( f , 0 , SEEK_SET );
  //affectation structure Tables
  Base->nbTable = compteur;
  Base->Table = malloc(sizeof(Table) * Base->nbTable );
  //affectation du nom des tables
    while (fgets(trans, sizeof trans, f) != NULL) {
      fonctFich(trans,&Fichiertrans,&cpttrans);
      if (strcmp(Fichiertrans[0],Base->nomBDD )==0) {
        cpt2++;
        fonct(Fichiertrans[1],&Fichiertrans2,&cpttrans2);
        strcpy(  Base->Table[cpt2-1].nomTable,Fichiertrans2[0] );
      }
    }
    for (int i = 0; i < compteur; i++) {
      printf("%s\n",Base->Table[i].nomTable );
    }
  fclose(f);

//assignation élements
  for (int h = 0; h < Base->nbTable; h++) {
    FILE *g;
    //chaque tour de boucle pour chaque table

    snprintf(cmd, sizeof cmd, "%s%s.txt",Base->cheminBDD ,Base->Table[h].nomTable);
    printf("%s\n",Base->Table[h].nomTable );
    g = fopen(cmd,"r");
    if(g == NULL){
      printf("problèmes dépendances \n" );
    }
    //affectattion nb élements
      fscanf(g,"%s\n",trans);
  //fgets(trans, sizeof trans, f);
      fonctTable(trans,&Fichiertrans,&cpttrans);
      Base->Table[h].nbElement = cpttrans;


    Base->Table[h].nomElement = malloc(sizeof(Element)* cpttrans);
    Base->Table[h].TypeElement = malloc(sizeof(int)* cpttrans);
    //boucle qui redecompose la chaine d'avant
    for (int l = 0; l < cpttrans; l++) {
      fonct(Fichiertrans[l], &FichierTable, &cptTable);
      //son type
        Base->Table[h].TypeElement[l] = atoi(FichierTable[0]);
      //le nom de chaque élements
      strcpy(Base->Table[h].nomElement[l].nom,FichierTable[1]);

      printf("nom elem %s\n",Base->Table[h].nomElement[l].nom);

      printf("type eleme %d\n",Base->Table[h].TypeElement[l]);


    }
    printf("nb elem %d\n",Base->Table[h].nbElement);

    fclose(g);
  }







}
