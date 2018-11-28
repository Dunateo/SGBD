#include <stdio.h>
#include <stdlib.h>
#include "fichier.h"

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
