#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fichier.h"

struct {
  char *nom;
  void (*fon)(char *);
} table[] = {{"DELETE", deletee},{"UPDATE", update} };



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
Action selon le mode
**/
void executionSelect(int valMenu){
  int valCs = 0;

  switch (valMenu) {
    //SELECTION
    case 1:system("bash ./script/affichageBDD.sh");
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

    gerePoint();
    break;

  }
}

/**
DELETE
**/
void deletee(char *param){

  //delete la database
  if(strcmp(param,"ALL") == 0){
    system("rm -rf ./data/Bitcoins/");
    printf("suppresion\n" );
  }
  else if(strcmp(param,"TABLE") == 0){
    char table[80];
    printf("Table name ?>>" );
    scanf("%s",table);
    remove(table);

  }
  else if(strcmp(param,"LIGNE") == 0){
    char ligne[256]; //en partant du principe que chaque ligne ne fait pas plus de 256 charactères
    char cote;
    FILE * fprem;
    FILE * fdeux;
    printf("Commence par?>>" );
    scanf("%s", &cote );
    if ((fprem = fopen("./data/remi/assom.txt", "r")) == NULL)
        printf("exit\n" );

    if ((fdeux = fopen("./data/remi/assom.tmp", "w")) == NULL)
    {
        fclose(fprem);
        printf("exit\n" );
    }

    while (fgets(ligne, sizeof ligne, fIn))
    {
        if (ligne[0] != cote)
            fputs(ligne, fdeux);
    }

    fclose(fprem);
    fclose(fdeux);

    rename("./data/remi/assom.tmp", "./data/remi/assom.txt");
    remove("./data/remi/assom.tmp");
  }
}

/**
UPDATE
**/
void update(char *param){
  printf("gg ca marche\n");

}

/**
Gestion des pointeurs de fonctions
**/
void gerePoint(){
  char nom[80];
  char x[80];
  unsigned int i;
  for (;;) {
    printf("commande>>" );
    scanf("%s", nom);//fonction choisie
    if (strcmp(nom, "fin")==0) break;
    printf("paramètre>>");
    scanf("%s", x);
    //parcours du tableau de pointeurs de fonctions depart de la case À on avance tant que i ne deborde pas du tableau et que le afonction demandée ("nom") n'est pas éga au nom de la focntion dans table[i].nom.
    for (i=0; i<NBF && strcmp(table[i].nom, nom) != 0; i++) ;
    if (i < NBF)
    (*table[i].fon)(x);
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
