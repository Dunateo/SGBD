#define NBF (sizeof table / sizeof table[0])
typedef struct bdd{
  char nom;
  int nbtable;
  char *nomtable;
  int nbelem;
  char *nomelem;
}bdd;
typedef struct selection{
  char BDD[30];
  char Table[80];
}selection;

void selectPath(selection *select);
void selectionMenu(int *valMenu);
void executionSelect(int valMenu, selection *select);
