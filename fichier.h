#define NBF (sizeof table / sizeof table[0])
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
void gerePoint();
void deletee(char *param);
void update(char *param);
