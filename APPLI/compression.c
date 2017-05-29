/**
* @file compression.c
* @brief Fichier contenant l'algorithme de compression.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "compression.h"
#include "dictionnaire.h"

#define NBBITDEPART 9

/**
* @fn void concat(char *w, int tailleW, char *a,char *out)
* @brief Fonction permettant de concatener une chaine de caractère et un caractère. Ce dernier doit être contenu dans un tableau à 1 case.
* @param[in] w Tableau de caractère reprsésantant le prefixe à concatener.
* @param[in] tailleW Entier contenant la taille du tableau w.
* @param[in] a Tableau de caractère de taille 1 contenant le caractère à concatener avec w.
* @param[in, out] out Tableau de taille tailleW + 1 contenant la concaténation de w et a.
*/
void concat(char *w, int tailleW, char *a,char *out)
{
	int i;
	for(i = 0; i < tailleW; i++)
	{
		out[i] = w[i];
	}
	out[i] = a[0];
}

/**
* @fn void display_output(int code, int *bits_restants_dans_tampon, int *tailleBitsMot, uint32_t *tampon)
* @brief Fonction qui met en forme l'affichage du tableau de code.
* @param[in] code Entier correspondant a un index du dictionnaire.
* @param[in,out] bits_restants_dans_tampon Entier représentant le nombre de bits libres dans le tampon.
* @param[in,out] tailleBitsMot Entier représantant la taille des des mots binaires correspondant aux indexes du dictionnaire.
* @param[in,out] tampon Entier représantant le tampon de sortie, dans le quel on stock/extrait les valeurs à afficher.
* @param[in,out] spacing Entier permettant la gestion des espaces dans le format de sortie
*/
void display_output(int code, int *bits_restants_dans_tampon, int *tailleBitsMot, uint32_t *tampon)
{
	uint32_t resultat;

	while(*bits_restants_dans_tampon >= 8)
	{
		resultat = (*tampon & 0xFF000000) >> 24;
		printf("%c",resultat);
		*tampon = *tampon << 8;
		*bits_restants_dans_tampon -= 8;
	}

	*tampon |= code << (32 - *tailleBitsMot - *bits_restants_dans_tampon);
	resultat = (*tampon & 0xFF000000) >> 24;
	printf("%c",resultat);
	*tampon = *tampon << 8;
	*bits_restants_dans_tampon += *tailleBitsMot - 8;
}


/**
* @fn void codage(char *input, int taille, char *output)
* @brief Algorithme de compression LZW.
* @param[in] input Tableau de caractère contenant la totalité de l'information contenue dans le fichier à compresser.
* @param[in] taille Entier contant la taille du tableau input.
*/
void codage(char *input, int taille)
{
	char *w;
	char *wa;
	char a[1];
	int i, tailleW = 1, k = 0;
	int code;
	int bits_restants_dans_tampon = 0;
	int tailleBitsMot = NBBITDEPART;
	uint32_t tampon = 0;

	initialiser();//ok

	w = malloc(tailleW*sizeof(char));
	w[0] = input[0];
	for(i = 1 ; i < taille ; i++)
	{
		// if(i == 5429) {}
		a[0] = input[i];

		wa = malloc((tailleW+1)*sizeof(char));
		concat(w,tailleW,a,wa);

		if(SequenceVersCode(wa,tailleW+1) != -1)
		{
			tailleW++;
			w = malloc(tailleW*sizeof(char));
			for(int j = 0; j < tailleW; j++) w[j] = wa[j];
		}
		else
		{
			code = SequenceVersCode(w,tailleW);

			display_output(code, &bits_restants_dans_tampon, &tailleBitsMot, &tampon);

			while(ind_dico >= (1 << tailleBitsMot)-1)
			{
				(tailleBitsMot)++;
				// printf("\n\nind_dico : %d | Augmentation de la taillebit à : %d\n\n",ind_dico,tailleBitsMot);
			}

			Inserer(SequenceVersCode(w,tailleW),SequenceVersCode(a,1));
			tailleW = 1;

			w = malloc(tailleW*sizeof(char));
			w[0] = a[0];
			k++;
		}

	}

	code = SequenceVersCode(w,tailleW);
	display_output(code, &bits_restants_dans_tampon, &tailleBitsMot, &tampon);

	code = 256;
	display_output(code, &bits_restants_dans_tampon, &tailleBitsMot, &tampon);

	printf("%c",(tampon & 0xFF000000) >> 32 - bits_restants_dans_tampon);

	free(w);
	free(wa);
}
