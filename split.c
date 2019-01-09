#include <stdio.h>
#include <stdlib.h>


int longChaine(char *chaine)
{
	int i = 0;

	while(chaine[i] != '\0')
	{
		i++;
	}

	return i;
}


void nbSeparation(char *chaine, int *nbSep, int position[50],char sep)
{
	int i = 0, j = 0;

	while(chaine[i] != '\0')
	{
		if(chaine[i] == sep)
		{
			(*nbSep)++;
			position[j] = i+1;
			j++;
		}

		i++;
	}

	if(*nbSep == 0)
	{
		position[j] = longChaine(chaine)+1;
		(*nbSep)++;
	}
}


int compChaine(char *chaine1, char *chaine2)
{
	int verif = 0;

	if(longChaine(chaine1) == longChaine(chaine2))
	{
		for(int i = 0;i < longChaine(chaine1); i++)
		{
			if(chaine1[i] == chaine2[i])
			{
				verif++;
			}
			else
			{
				return -1;
			}
		}
	}
	else
	{
		return -1;
	}

	if( verif == longChaine(chaine1) && verif == longChaine(chaine2))
	{
		return 0;
	}
	else
	{
		return -1;
	}
}


void copieChaine(char *dest, char *src)
{
	int i;

	for(i = 0;src[i] != '\0'; ++i)
	{
		dest[i] = src[i];
	}

	dest[i] = '\0';
}


void chaine(char *chaine, int *lgChaine, int *nbSep, int position[50], char sep)
{
	if(*nbSep != 0)
	{
		*nbSep = 0;
	}

	*lgChaine = longChaine(chaine);

	nbSeparation(chaine,nbSep,position,sep);
}


void initResult(int *lgChaine, char ***resultat, int position[50], int *nbSep)
{
	(*resultat) = (char **)malloc(sizeof(char *)*(*nbSep + 1));

	for(int j = 0;j <= *nbSep; j++)
	{
		if(j == 0)
		{
			(*resultat)[j] = (char *)malloc(sizeof(char)*((position[j]+1)));
		}
		else if(j < *nbSep && j != 0)
		{
			(*resultat)[j] = (char *)malloc(sizeof(char)*(position[j]-position[j-1]+1));
		}
		else
		{
			(*resultat)[j] = (char *)malloc(sizeof(char)*(*lgChaine-position[j-1]+2));
		}
	}
}


void sousChaine(char *chaine, int *lgChaine, char **resultat, int position[20], int *nbSep)
{
	int i,j,k;

	for(j = 0;j <= *nbSep; j++)
	{
		if(j == 0 && position[j] != 1)
		{
			for(i = 0,k = 0;i < position[j]-1; i++,k++)
			{
				resultat[j][k] = chaine[i];

			}

			resultat[j][k] = '\0';
		}
		else if(j < *nbSep && j != 0)
		{
			for(i = position[j-1],k = 0;i < position[j]-1; i++, k++)
			{
				resultat[j][k] = chaine[i];
			}

			resultat[j][k] = '\0';
		}
		else if(j == *nbSep)
		{
			for(i = position[j-1],k = 0;i < *lgChaine; i++,k++)
			{
				resultat[j][k] = chaine[i];
			}

			resultat[j][k] = '\0';
		}
	}
}


int Fill(char *chaine, char sep)
{
	int i,empty = 0;

	for(i = 0;i < longChaine(chaine); i++)
	{
		if(chaine[i] == sep)
		{
			empty ++;
		}
		else
		{
			break;
		}
	}

	if(empty == longChaine(chaine) && empty != 0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}


void fonct(char *info, char ***R, int *nb)
{
	int lg = 0,nbSep = 0,i,posit[50];

	char **result;
	char sep = '.';


	if(info == NULL)
	{
		printf("Chaine nulle\n");
	}
	else if(Fill(info,sep) != 0)
	{
		//printf("Chaine remplie de séparateurs\n");
	}
	else if(info[0] != '\0' && info != NULL)
	{
		// SEPARATION SOUS CHAINE

		chaine(info,&lg,&nbSep,posit,sep);

		initResult(&lg,&result,posit,&nbSep);

		sousChaine(info,&lg,result,posit,&nbSep);

		// AFFICHAGE SOUS CHAINE

		for(i = 0;i <= nbSep; i++)
		{
			if((posit[nbSep] != longChaine(result[i])) && compChaine(result[i],"") != 0)
			{
				//printf("Sous chaine %d = %s\n",i,result[i]);
			}
		}

		*R = result;
		*nb = nbSep;
	}
	else
	{
		printf("Chaine vide\n");
	}
}

void fonctFich(char *info, char ***R, int *nb)
{
	int lg = 0,nbSep = 0,i,posit[50];

	char **result;
	char sep = '/';


	if(info == NULL)
	{
		printf("Chaine nulle\n");
	}
	else if(Fill(info,sep) != 0)
	{
		//printf("Chaine remplie de séparateurs\n");
	}
	else if(info[0] != '\0' && info != NULL)
	{
		// SEPARATION SOUS CHAINE

		chaine(info,&lg,&nbSep,posit,sep);

		initResult(&lg,&result,posit,&nbSep);

		sousChaine(info,&lg,result,posit,&nbSep);

		// AFFICHAGE SOUS CHAINE

		for(i = 0;i <= nbSep; i++)
		{
			if((posit[nbSep] != longChaine(result[i])) && compChaine(result[i],"") != 0)
			{
				//printf("Sous chaine %d = %s\n",i,result[i]);
			}
		}

		*R = result;
		*nb = nbSep;
	}
	else
	{
		printf("Chaine vide\n");
	}
}

void fonctTable(char *info, char ***R, int *nb)
{
	int lg = 0,nbSep = 0,i,posit[50];

	char **result;
	char sep = '|';


	if(info == NULL)
	{
		printf("Chaine nulle\n");
	}
	else if(Fill(info,sep) != 0)
	{
		//printf("Chaine remplie de séparateurs\n");
	}
	else if(info[0] != '\0' && info != NULL)
	{
		// SEPARATION SOUS CHAINE

		chaine(info,&lg,&nbSep,posit,sep);

		initResult(&lg,&result,posit,&nbSep);

		sousChaine(info,&lg,result,posit,&nbSep);

		// AFFICHAGE SOUS CHAINE

		for(i = 0;i <= nbSep; i++)
		{
			if((posit[nbSep] != longChaine(result[i])) && compChaine(result[i],"") != 0)
			{
				//printf("Sous chaine %d = %s\n",i,result[i]);
			}
		}

		*R = result;
		*nb = nbSep;
	}
	else
	{
		printf("Chaine vide\n");
	}
}

void fonctEspace(char *info, char ***R, int *nb)
{
	int lg = 0,nbSep = 0,i,posit[50];

	char **result;
	char sep = ' ';


	if(info == NULL)
	{
		printf("Chaine nulle\n");
	}
	else if(Fill(info,sep) != 0)
	{
		//printf("Chaine remplie de séparateurs\n");
	}
	else if(info[0] != '\0' && info != NULL)
	{
		// SEPARATION SOUS CHAINE

		chaine(info,&lg,&nbSep,posit,sep);

		initResult(&lg,&result,posit,&nbSep);

		sousChaine(info,&lg,result,posit,&nbSep);

		// AFFICHAGE SOUS CHAINE

		for(i = 0;i <= nbSep; i++)
		{
			if((posit[nbSep] != longChaine(result[i])) && compChaine(result[i],"") != 0)
			{
				//printf("Sous chaine %d = %s\n",i,result[i]);
			}
		}

		*R = result;
		*nb = nbSep;
	}
	else
	{
		printf("Chaine vide\n");
	}
}
