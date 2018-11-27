typedef struct bdd{
  char nom;
  int nbtable;
  char *nomtable;
  int nbelem;
  char *nomelem;
}bdd;
void affichageMenu();
void intialisationData();
void selectionMenu(int *valMenu);
void executionSelect(int valMenu);
