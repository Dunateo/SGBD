#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fichier.h"

struct {
  char *nom;
  void (*fon)(char *, selection *);
} table[] = {{"DELETE", deletee},{"UPDATE", update},{"HELP", help} };



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
DELETE
**/
void deletee(char *param, selection *trans){
  char cmd[200];
  //delete la database
  if(strcmp(param,"ALL") == 0){
    snprintf(cmd, sizeof cmd, "rm -rf %s", trans->BDD);
    system(cmd);
    printf("suppresion BDD\n" );
  }
  //delete table
  else if(strcmp(param,"TABLE") == 0){

    snprintf(cmd, sizeof cmd, "rm %s", trans->Table);
    system(cmd);
    printf("suppresion %s\n", trans->Table);

  }
  //delete ligne
  else if(strcmp(param,"LIGNE") == 0){
    char ligne[256]; //en partant du principe que chaque ligne ne fait pas plus de 256 charactères
    snprintf(cmd, sizeof cmd, "%s.tmp", trans->Table);
    char cote;
    FILE * fprem;
    FILE * fdeux;
    printf("Commence par?>>" );
    scanf("%s", &cote );
    if ((fprem = fopen(trans->Table, "r")) == NULL)
        printf("exit\n" );

    if ((fdeux = fopen(cmd, "w")) == NULL)
    {
        fclose(fprem);
        printf("exit\n" );
    }

    while (fgets(ligne, sizeof ligne, fprem))
    {
        if (ligne[0] != cote)
            fputs(ligne, fdeux);
    }

    fclose(fprem);
    fclose(fdeux);

    rename(cmd, trans->Table);
    remove(cmd);
  }
}

/**
UPDATE
**/
void update(char *param, selection *trans){

  char cmd[200];
  char mot[30];
  char new[30];

  if(strcmp(param,"ALL") == 0){

            snprintf(cmd, sizeof cmd, "cat %s",trans->Table);
            system(cmd);
            printf("Modifier?>>");
            scanf("%s",mot);
            printf("NewMot?>>");
            scanf("%s",new);
            snprintf(cmd, sizeof cmd, "sed -i -e 's/%s/%s/g' %s",mot,new,trans->Table);
            system(cmd);
  }

}

/**
HELP
**/
void help(char *param, selection *trans){
  system("bash ./script/help.sh");
}

/**
Gestion des pointeurs de fonctions
**/
void gerePoint(selection *select){
  char nom[80];
  char x[80];
  selection trans;
  trans = *select;
  unsigned int i;
  for (;;) {
    printf("commande>>" );
    scanf("%s", nom);//fonction choisie
    if (strcmp(nom, "fin")==0) break;
    printf("paramètre>>");
    scanf("%s", x);
    if(strcmp(x, "")==0){
      strcpy(x,"rien");
    }
    //parcours du tableau de pointeurs de fonctions depart de la case À on avance tant que i ne deborde pas du tableau et que le afonction demandée ("nom") n'est pas éga au nom de la focntion dans table[i].nom.
    for (i=0; i<NBF && strcmp(table[i].nom, nom) != 0; i++) ;
    if (i < NBF)
    (*table[i].fon)(x,&trans);
    else printf("Commande inconnue\n");
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
