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
  else if(strcmp(param,"TABLE") == 0){

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

  char ligne[100],cmd[250],cmd2[500], transips[100], **sortie;
  int n, nbt, valeur1, valinutile, nbligne = 0;
  float valfloat;

  if(strcmp(param,"COL") == 0){
      int l;
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
      //select numbers of COL to add
      do {
        printf("----------"YELLOW"nombres de colonnes?"Class"\n");
        printf(">");
        scanf("%d",&valinutile);
        printf("%d\n",valinutile );
      } while(valinutile < 0);
      //updating the struct
      trans->Table[nbt].nomElement = realloc(trans->Table[nbt].nomElement, sizeof(Element)* valinutile);
      trans->Table[nbt].TypeElement = realloc(trans->Table[nbt].TypeElement, sizeof(int)* valinutile);
      trans->Table[nbt].nbElement = trans->Table[nbt].nbElement + valinutile;
      l = n;//first value of the new tab

      for (int j = 0; j < valinutile; j++) {
        //select the type of the new element
        do{
         printf(""ROUGE"1"Class"----------"YELLOW"INT"Class"\n");
         printf(""ROUGE"2"Class"----------"YELLOW"CHAR"Class"\n");
         printf(""ROUGE"3"Class"----------"YELLOW"FLOAT"Class"\n");
         printf(""ROUGE"4"Class"----------"YELLOW"AUTO INCREMENT"Class"\n");
         printf(">");
         scanf("%d",&valeur1);
       }while (valeur1 > 4 && valeur1 <1 );
       //nom bdd
       printf(""ROUGE"Nom ?\n"Class"");
       printf(">");
       scanf("%s",ligne);


       //update name
         trans->Table[nbt].TypeElement[l] = valeur1;
         strcpy(trans->Table[nbt].nomElement[l].nom,ligne);


       //set the new col
       snprintf(cmd2, sizeof cmd2, " sed -i -e '1 s/$/%d.%s|/' %s",valeur1,ligne,cmd);
       system(cmd2);
        //set the new col to NULL
        strcpy(cmd2,"");
        snprintf(cmd2, sizeof cmd2,"sed -i -e '2,$s/$/NULL|/' %s",cmd);
        system(cmd2);
        l = l+1;


      }




  }

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
    while (fgets(transips, sizeof transips, f) != NULL) {
      nbligne = nbligne + 1;
    }
    fonctTable(transips, &sortie, &valinutile);
    fprintf(f, "\n");
    for (int i = 0; i < n; i++) {
      printf("%s\n", trans->Table[nbt].nomElement[i].nom );
      if(trans->Table[nbt].TypeElement[i] == 4){

        //if it's the first ligne we init the auto increment at 1
        if (nbligne == 1) {
          valeur1 = 1;
        }else{
          valeur1 = atoi(sortie[0]);
          valeur1 = valeur1 +1;
        }


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

  if(strcmp(param,"*") == 0){
    system("bash ./script/help.sh");
  }

}

/**
SELECT
**/
void selectt(char *param, BDD *trans){
  char cmd[250], transps[100];

  //Afficher la bdd déja présélectionné
  if(strcmp(param,"*") == 0){
    snprintf(cmd, sizeof cmd, "cd %s; ls|cut -f1 -d'.'",trans->cheminBDD);
    system(cmd);
    snprintf(cmd, sizeof cmd, "cat -s %s%s ",trans->cheminBDD,"*.txt");
    system(cmd);
    printf("\n");

  }

  //Affiche la table
  if(strcmp(param,"TABLE") == 0){
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
    if (strcmp(nom, "END")==0) break;
    //parcours du tableau de pointeurs de fonctions depart de la case À on avance tant que i ne deborde pas du tableau et que le afonction demandée ("nom") n'est pas éga au nom de la focntion dans table[i].nom.
    for (i=0; i<NBF && strcmp(table[i].nom, cmd[0]) != 0; i++) ;
    if (i < NBF){

      (*table[i].fon)(cmd[1],&trans);
    }

    else printf("Commande inconnue\n");
  }
}
