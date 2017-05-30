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

void mark(){

}

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
* @fn void codage(char *input, int taille, char *output)
* @brief Algorithme de compression LZW.
* @param[in] input Tableau de caractère contenant la totalité de l'information contenue dans le fichier à compresser.
* @param[in] taille Entier contant la taille du tableau input.
*/
void codage(uint8_t *input, int taille)
{
	uint8_t *w;
	uint8_t *wa;
	uint8_t a[1];
	int i, tailleW = 1, k = 0;
	int code;
	initialiser();//ok

	w = malloc(tailleW*sizeof(char));
	w[0] = input[0];
	for(i = 1 ; i < taille ; i++)
	{
		mark();

		a[0] = input[i];

		//printf("a[0] = %c\n",a[0]);

		wa = malloc((tailleW+1)*sizeof(uint8_t));
		concat(w,tailleW,a,wa);

		if(SequenceVersCode(wa,tailleW+1) != -1)
		{
			tailleW++;
			w = malloc(tailleW*sizeof(uint8_t));
			for(int j = 0; j < tailleW; j++) w[j] = wa[j];
		}
		else
		{
			code = SequenceVersCode(w,tailleW);

			printf("%d\n",code);

			Inserer(SequenceVersCode(w,tailleW),SequenceVersCode(a,1));
			tailleW = 1;

			w = malloc(tailleW*sizeof(uint8_t));
			w[0] = a[0];
			k++;
		}

	}
	code = SequenceVersCode(w,tailleW);
	printf("%d\n",code);
	code = 256;
	printf("%d\n",code);
	free(w);
	free(wa);

	int m=0;
}
