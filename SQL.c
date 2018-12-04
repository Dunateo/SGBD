#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fichier.h"
#include "SQL.h"
#include "split.h"

struct {
  char *nom;
  void (*fon)(char *, BDD *);
} table[] = {{"DELETE", deletee},{"UPDATE", update},{"HELP", helpp},{"INSERT", insert},{"SELECT", selectt} };

/**
DELETE
**/
void deletee(char *param, BDD *trans){
  char cmd[200];
  //delete la database
  if(strcmp(param,"ALL") == 0){
    snprintf(cmd, sizeof cmd, "rm -rf %s", trans->cheminBDD);
    system(cmd);
    printf("suppresion %s\n", trans->cheminBDD );
  }
  //delete table
  else if(strcmp(param,"TABLE") == 0){

    snprintf(cmd, sizeof cmd, "rm %s", trans->cheminTable);
    system(cmd);
    printf("suppresion %s\n", trans->cheminTable);

  }
  //delete ligne
  else if(strcmp(param,"LIGNE") == 0){
    char ligne[256]; //en partant du principe que chaque ligne ne fait pas plus de 256 charactères
    snprintf(cmd, sizeof cmd, "%s.tmp", trans->cheminTable);
    char cote;
    FILE * fprem;
    FILE * fdeux;
    printf("mot?>>" );
    scanf("%s", &cote );
    printf("Suppresion de %c dans %s\n", cote, trans->cheminTable );

    if ((fprem = fopen(trans->cheminTable, "r")) == NULL)
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

    rename(cmd, trans->cheminTable);
    remove(cmd);
  }
}

/**
UPDATE
**/
void update(char *param, BDD *trans){

  char cmd[200];
  char mot[30];
  char new[30];

  if(strcmp(param,"ALL") == 0){

            snprintf(cmd, sizeof cmd, "cat %s",trans->cheminTable);
            system(cmd);
            printf("Modifier?>>");
            scanf("%s",mot);
            printf("NewMot?>>");
            scanf("%s",new);
            snprintf(cmd, sizeof cmd, "sed -i -e 's/%s/%s/g' %s",mot,new,trans->cheminTable);
            system(cmd);
  }

}
/**
INSERT
**/
void insert(char *param, BDD *trans){
  char ligne[50];
  if(strcmp(param,"LIGNE") == 0){
    FILE * f;
    f=fopen(trans->cheminTable,"a+");
    if(f == NULL){
      printf("Impossible d'ouvrir la table\n");
    }
    fprintf(f, "\n");
    for (int i = 0; i < 3; i++) {
      printf("param %d\n", i );
      scanf("%s",ligne);
      fprintf(f, "%s|",ligne);
    }



    fclose(f);
  }
}
/**
HELP
**/
void helpp(char *param, BDD *trans){
  system("bash ./script/help.sh");
}

/**
SELECT
**/
void selectt(char *param, BDD *trans){
  char cmd[150];
  printf("%s\n", trans->cheminBDD );
  printf("%s\n", param );
  //Afficher la bdd déja présélectionné
  if(strcmp(param,"*") == 0){
    snprintf(cmd, sizeof cmd, "ls %s",trans->cheminBDD);
    system(cmd);
    snprintf(cmd, sizeof cmd, "cat -s %s%s ",trans->cheminBDD,"*.txt");
    system(cmd);
    printf("\n");

  }
  //Affiche la table déja préselectionné
  if(strcmp(param,"TABLE") == 0){
      snprintf(cmd, sizeof cmd, "cat -s %s",trans->cheminTable);
      system(cmd);
      printf("\n");
  }
}


/**
Gestion des pointeurs de fonctions
**/
void gerePoint(BDD *select){
  char **cmd;
  char nom[100];
  int nb;
  BDD trans;
  trans = *select;
  printf("%s\n", trans.cheminTable );
  unsigned int i;
  for (;;) {
    printf("commande>>" );
    scanf("%s", nom);//fonction choisie
    fonct(nom, &cmd, &nb);
    if (strcmp(nom, "END")==0) break;
    //parcours du tableau de pointeurs de fonctions depart de la case À on avance tant que i ne deborde pas du tableau et que le afonction demandée ("nom") n'est pas éga au nom de la focntion dans table[i].nom.
    for (i=0; i<NBF && strcmp(table[i].nom, cmd[0]) != 0; i++) ;
    if (i < NBF)
      (*table[i].fon)(cmd[1],&trans);
    else printf("Commande inconnue\n");
  }
}
