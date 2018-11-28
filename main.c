#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"
#include "initialisation.h"

/**
Notre fonction principale
**/
int main(int argc, char const *argv[]) {
  int valMenu = 0;
  selection select;
  intialisationData();
  do{
    affichageMenu();
    selectionMenu(&valMenu);
    executionSelect(valMenu, &select);
  }while (valMenu != 4);


  return 0;
}
