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
  char Table[40];
}selection;

void affichageMenu();
void selectPath(selection *select);
void intialisationData();
void selectionMenu(int *valMenu);
void executionSelect(int valMenu, selection *select);
void gerePoint(selection *select);
void deletee(char *param, selection *trans);
void update(char *param, selection *trans);
