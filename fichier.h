#define NBF (sizeof table / sizeof table[0])
typedef struct Element{
  char nom[100];
}Element;

typedef struct Table{
  char nomTable[200];
  int nbElement;
  Element *nomElement;
  int *TypeElement;
}Table;

typedef struct BDD{
  char *nomBDD;
  int nbTable;
  int nbBDD;
  char *cheminBDD;
  char *cheminTable;
  Table *Table;
}BDD;

typedef struct selection{
  char BDD[30];
  char Table[80];
}selection;

void selectPath(selection *select);
void selectFich(selection *select);
void selectionMenu(int *valMenu);
void executionSelect(int valMenu, BDD *select, int *etatSelect);
void initialisationBDD(BDD *Base);
