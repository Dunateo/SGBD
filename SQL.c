#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fichier.h"
#include "SQL.h"
#include "initialisation.h"
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
  else if(strcmp(param,"TABLES") == 0){

    snprintf(cmd, sizeof cmd, "rm %s", trans->cheminTable);
    system(cmd);
    printf("suppresion %s\n", trans->cheminTable);

  }
  //delete ligne
  else if(strcmp(param,"LINE") == 0){
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
  char ligne[50],cmd[250], transips[100], **sortie;
  int n, nbt, valeur1, valinutile;
  float valfloat;

  if(strcmp(param,"LINE") == 0){
    FILE * f;
    //selection table
      snprintf(cmd, sizeof cmd, "cd %s; ls|cut -f1 -d'.'",trans->cheminBDD);
      system(cmd);
      printf("Entrer nom Table>>");
      scanf("%s",transips );
      //on test si la table existe si oui on l'affiche
      for (int i = 0; i < trans->nbTable; i++) {
        if(strcmp(transips,trans->Table[i].nomTable) == 0){
          snprintf(cmd, sizeof cmd, "%s%s.txt",trans->cheminBDD,trans->Table[i].nomTable);
          n = trans->Table[i].nbElement;
          nbt = i;
        }
      }
    f=fopen(cmd,"a+");

    if(f == NULL){
      printf("Impossible d'ouvrir la table\n");
    }
    fscanf(f,"%s\n",transips);
    fonctTable(transips, &sortie, &valinutile);
    fprintf(f, "\n");
    for (int i = 0; i < n; i++) {
      printf("%s\n", trans->Table[nbt].nomElement[i].nom );
      if(trans->Table[nbt].TypeElement[i] == 4){
        valeur1 = atoi(sortie[0]);
        valeur1 = valeur1 +1;
        fprintf(f, "%d|",valeur1);
      }
      else if(trans->Table[nbt].TypeElement[i] == 3){
        scanf("%f",&valfloat);
        fprintf(f, "%f|",valfloat);
      }
      else if(trans->Table[nbt].TypeElement[i] == 2){
        scanf("%s",ligne);
        fprintf(f, "%s|",ligne);
      }
      else if(trans->Table[nbt].TypeElement[i] == 1){
        scanf("%d",&valeur1);
        fprintf(f, "%d|",valeur1);
      }


    }



    fclose(f);
  }
}
/**
HELP
**/
void helpp(char *param, BDD *trans){

  if(strcmp(param,"ALL") == 0){
    system("bash ./script/help.sh");
  }

}

/**
SELECT
**/
void selectt(char *param, BDD *trans){
  char cmd[250], transps[100];

  //Afficher la bdd déja présélectionné
  if(strcmp(param,"ALL") == 0){
    snprintf(cmd, sizeof cmd, "cd %s; ls|cut -f1 -d'.'",trans->cheminBDD);
    system(cmd);
    snprintf(cmd, sizeof cmd, "cat -s %s%s ",trans->cheminBDD,"*.txt");
    system(cmd);
    printf("\n");

  }

  //Affiche la table
  if(strcmp(param,"TABLES") == 0){
    //selection table
      snprintf(cmd, sizeof cmd, "cd %s; ls|cut -f1 -d'.'",trans->cheminBDD);
      system(cmd);
      printf("Entrer nom Table>>");
      scanf("%s",transps );
      //on test si la table existe si oui on l'affiche
      for (int i = 0; i < trans->nbTable; i++) {
        if(strcmp(transps,trans->Table[i].nomTable) == 0){
          snprintf(cmd, sizeof cmd, "cat -s %s%s.txt",trans->cheminBDD,trans->Table[i].nomTable);
        }
      }
      if(strcmp(cmd," ") == 0){
        printf("La table sélectionné n'existe pas\n" );
      }
      else{
        printf("\n");
        system(cmd);
      }

      printf("\n");
  }
}

/**
SET le caractère en trop à NULL
**/
void enleveCara(char *chaine){
  int taille, n;
  taille = strlen(chaine);
  n=taille%4;
  if(n<=1){
    chaine[taille-1]=NULL;
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
  unsigned int i;
  for (;;) {
      printf(""PURPLE"%s"Class">>",trans.nomBDD );
      scanf("%s", nom );//fonction choisie
    fonct(nom, &cmd, &nb);
    enleveCara(cmd[1]);
    if (strcmp(nom, "END")==0) break;
    //parcours du tableau de pointeurs de fonctions depart de la case À on avance tant que i ne deborde pas du tableau et que le afonction demandée ("nom") n'est pas éga au nom de la focntion dans table[i].nom.
    for (i=0; i<NBF && strcmp(table[i].nom, cmd[0]) != 0; i++) ;
    if (i < NBF){

      (*table[i].fon)(cmd[1],&trans);
    }

    else printf("Commande inconnue\n");
  }
}
