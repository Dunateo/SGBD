#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fichier.h"
#include "SQL.h"

struct {
  char *nom;
  void (*fon)(char *, selection *);
} table[] = {{"DELETE", deletee},{"UPDATE", update},{"HELP", help} };

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
