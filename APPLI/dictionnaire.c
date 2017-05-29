#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "dictionnaire.h"

void initialiser()
{
	ind_dico = 0;

	for(ind_dico = 0; ind_dico < 256; ind_dico++)
	{
		dico[ind_dico].longueur = 1;
		dico[ind_dico].mot = malloc(sizeof(char));
		dico[ind_dico].mot[0] = ind_dico;
	}
	for(ind_dico = 256; ind_dico < MAX; ind_dico++)
	{
		dico[ind_dico].longueur = 0;
		dico[ind_dico].mot = NULL;
	}
	ind_dico = 257;
}

/* Ajoute la sequence d'octet prefixe.mono. Renvoie son code */
Code Inserer(Code prefixe, Code mono)
{
	int i;
	dico[ind_dico].longueur = dico[prefixe].longueur + dico[mono].longueur;
	dico[ind_dico].mot = malloc((dico[prefixe].longueur + 1)*sizeof(char));
	for(i = 0; i < dico[prefixe].longueur; i++)
	{
		dico[ind_dico].mot[i] = dico[prefixe].mot[i];
	}
	dico[ind_dico].mot[i] = dico[mono].mot[0];
	ind_dico++;

	/* Bornes du dico */
	if(ind_dico == (1 << 16)-10){
		printf("Je réinitialise\n");
		int longueur = dico[prefixe].longueur + dico[mono].longueur;
		char *tab = malloc((dico[prefixe].longueur + 1)*sizeof(char));
		for(i = 0; i < dico[prefixe].longueur; i++)
		{
			tab[i] = dico[prefixe].mot[i];
		}
		tab[i] = dico[mono].mot[0];
		initialiser();
		dico[ind_dico].longueur = longueur;
		dico[ind_dico].mot = malloc(longueur*sizeof(char));
		for(i = 0; i < longueur; i++)
		{
			dico[ind_dico].mot[i] = tab[i];
		}
		ind_dico++;
	}

	return ind_dico-1;
}

/* Renvoie sequence et affecte la longueur associée à code */
void CodeVersChaine(Code code, uint8_t *val)
{
	for(int i = 0; i < dico[code].longueur; i++)
	{
		val[i] = dico[code].mot[i];
	}
}

int CodeVersLongueur(Code code)
{
	return dico[code].longueur;
}

Code SequenceVersCode(uint8_t *sequence, int longueur)
{
	int i = 0, found = 0, code;
	while(!found && i <= ind_dico)
	{
		if(dico[i].longueur == longueur)
		{
			found = 1;
			for(int j = 0; j < longueur; j++)
			{
				found &= dico[i].mot[j] == sequence[j];
			}
			if(found) code = i;
		}
		i++;
	}
	if(!found) code = -1;
	return code;
}

void dico_print()
{
	for(int i = 0; i < ind_dico; i ++)
	{
		printf("%i : ",i );
		for(int j = 0; j < dico[i].longueur; j++)
		{
			printf("%c(%i)",dico[i].mot[j],dico[i].mot[j]);
		}
		printf("\n");
	}
}

void dico_print_small()
{
	for(int i = 257; i < ind_dico; i ++)
	{
		printf("%i : ",i );
		for(int j = 0; j < dico[i].longueur; j++)
		{
			printf("'%c'(%i)",dico[i].mot[j],dico[i].mot[j]);
		}
		printf("\n");
	}
}

// int main(int argc, char const *argv[])
// {
// 	initialiser();
// 	Inserer(97,98);
// 	Inserer(33,20);
// 	Inserer(258,102);
// 	dico_print_small();
// 	return 0;
// }
