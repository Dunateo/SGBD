#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "fichier.h"

struct {
  char *nom;
  void (*fon)(char *);
} table[] = {{"DELETE", deletee},{"UPDATE", update} };

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
  }while (valMenu != 4);


  return 0;
}

/**
Affichage du Menu
**/
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
Action selon le mode
**/
void executionSelect(int valMenu){

  switch (valMenu) {
    case 1:system("bash ./script/affichageBDD.sh");
    break;

    case 2:system("bash ./script/creationBDD.sh");
    break;

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
    rmdir("../data/remi/");
    printf("suppresion\n" );
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
