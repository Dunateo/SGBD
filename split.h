int longChaine(char *chaine); // Renvoi la longueur de la chaine
void nbSeparation(char *chaine, int *nbSep, int position[10],char sep); // Renvoi le nombre de séparateurs ainsi que leur position dans la chaine
int compChaine(char *chaine1, char *chaine2); // Compare 2 chaines : -1 si différentes et 0 si égales
void copieChaine(char *dest, char *src); // Copie une chaine dans une autre
void chaine(char *chaine, int *lgChaine, int *nbSep, int position[10], char sep); // Renvoi la longueur de la chaine et le nombre de séparateurs ainsi que leur position dans la chaine
void initResult(int *lgChaine, char ***resultat, int position[10], int *nbSep); // Initialise une variable résultat qui contiendra les différentes sous chaine
void sousChaine(char *chaine, int *lgChaine, char **resultat, int position[10], int *nbSep); // Divise la chaine principale en sous chaine
int Fill(char *chaine, char sep); // Vérifie la composition de la chaine  : -1 si que des séparateurs et 0 autre
void fonct(char *info, char ***R, int *nb); //
void fonctFich(char *info, char ***R, int *nb);
void fonctTable(char *info, char ***R, int *nb);
void fonctEspace(char *info, char ***R, int *nb);
