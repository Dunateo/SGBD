#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"
#include "initialisation.h"

/**
Notre fonction principale
**/
int main(int argc, char const *argv[]) {
  int valMenu = 0,etatFree, etatSelect = 0;
  BDD Base;
  intialisationData();

  do{
    affichageMenu();
    selectionMenu(&valMenu);
    executionSelect(valMenu, &Base,&etatSelect);

    //if you choose the Selection Menu I will know guys!!
    if(valMenu == 1){
      etatFree = 1;
    }

  }while (valMenu != 4);

  //check if the sruct was allocated if yes they free the pointeurs
  if(etatFree == 1){
    //vide la mémoire
    free(Base.nomBDD);
    free(Base.cheminBDD);
    free(Base.cheminTable);
    free(Base.Table);
  }


  return 0;
}
