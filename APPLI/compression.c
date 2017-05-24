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
//TODO Ajouter un espace tous les 4 caractères.
void display_output(int code, int *bits_restants_dans_tampon, int *tailleBitsMot, uint32_t *tampon, int *spacing)
{
	uint32_t resultat;

	while(code >= (1 << *tailleBitsMot)-1)
	{
		(*tailleBitsMot)++;
	}

	while(*bits_restants_dans_tampon >= 8)
	{
		resultat = (*tampon & 0xFF000000) >> 24;
		//printf("||||||||%d||||||||||\n",resultat);
		// if (*spacing >= 2)
		// {
		// 	printf(" ");
		// 	*spacing = 0;
		// }
		printf("%c",resultat);
		// (*spacing)++;
		*tampon = *tampon << 8;
		*bits_restants_dans_tampon -= 8;
	}

	*tampon |= code << (32 - *tailleBitsMot - *bits_restants_dans_tampon);
	resultat = (*tampon & 0xFF000000) >> 24;
	// if (*spacing >= 2)
	// {
	// 	printf(" ");
	// 	*spacing = 0;

	// }
	printf("%c",resultat);
	// (*spacing)++;
	*tampon = *tampon << 8;
	*bits_restants_dans_tampon += *tailleBitsMot - 8;
}

// void impression(char * v, int lg){
// 	for(int i=0;i<lg;i++){
// 		printf("%c",v[i]);
// 	}
// }

/**
* @fn void codage(char *input, int taille, char *output)
* @brief Algorithme de compression LZW.
* @param[in] input Tableau de caractère contenant la totalité de l'information contenue dans le fichier à compresser.
* @param[in] taille Entier contant la taille du tableau input.
*/
void codage(char *input, int taille)
{
	int ind;
	char *w;
	char *wa;
	char a[1];
	int i, tailleW = 1, k = 0;
	int output[2000];
	int code;
	int bits_restants_dans_tampon = 0;
	int tailleBitsMot = NBBITDEPART;
	uint32_t tampon = 0;
	int spacing = 0;

	initialiser();//ok

	w = malloc(tailleW*sizeof(char));
	w[0] = input[0];
	//printf("Taille : %d\n",taille);
	for(i = 1 ; i < taille ; i++)
	{
		//printf("ok1");
		//printf("Je rentre dans le for\n");
		a[0] = input[i];

		wa = malloc((tailleW+1)*sizeof(char));
		concat(w,tailleW,a,wa);

		if(SequenceVersCode(wa,tailleW+1) != -1)
		{
			/*printf("J'ai trouvé ");
			impression(wa,tailleW+1);
			printf(" dans le dicitonnaire\n");*/
			tailleW++;
			w = malloc(tailleW*sizeof(char));
			for(int j = 0; j < tailleW; j++) w[j] = wa[j];
			/*printf("W devient : ");
			impression(w,tailleW);
			printf("\n");*/
		}
		else
		{
			//printf("Le mot envoyé à SequenceVersCode : %s\n",w);
			//printf("La taille envoyée à SequenceVersCode : %d\n",tailleW);

			code = SequenceVersCode(w,tailleW);

			display_output(code, &bits_restants_dans_tampon, &tailleBitsMot, &tampon, &spacing);
			output[k] = SequenceVersCode(w,tailleW);
			Inserer(SequenceVersCode(w,tailleW),SequenceVersCode(a,1));
			tailleW = 1;

			w = malloc(tailleW*sizeof(char));
			w[0] = a[0];
			k++;

		}

	}

	output[k] = SequenceVersCode(w,tailleW);
	output[k+1] = 256;
	int tailsqle = k+2;
	/*for(int i=0;i<tailsqle;i++){
		printf("%d\n",output[i]);
	}*/
	code = SequenceVersCode(w,tailleW);
	display_output(code, &bits_restants_dans_tampon, &tailleBitsMot, &tampon, &spacing);

	code = 256;
	display_output(code, &bits_restants_dans_tampon, &tailleBitsMot, &tampon, &spacing);

	printf("%c",(tampon & 0xFF000000) >> 32 - bits_restants_dans_tampon);
	// printf(" 00\n");
	free(w);
	free(wa);
}
