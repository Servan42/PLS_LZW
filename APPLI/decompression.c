//FIXME : Decompression bug au pout de 856 caractères OU fait de la merde sur le 848eme

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "dictionnaire.h"
#include "decompression.h"

#define NBBITDEPART 9

void ouiouioui(){}

uint32_t binToCode(uint8_t input, int *bits_restants_dans_tampon, int *tailleBitsMot, uint32_t *tampon, uint32_t *masque)
{
	uint32_t resultat = 0;

	*tampon |= input << (32 - 8 - *bits_restants_dans_tampon);
	*bits_restants_dans_tampon += 8;

	if(*bits_restants_dans_tampon >= *tailleBitsMot)
	{
		// printf("valaur de masque %x\n", *masque);
		resultat = (*tampon & *masque) >> (32 - *tailleBitsMot);
		*tampon <<= *tailleBitsMot;
		*bits_restants_dans_tampon -= *tailleBitsMot;
	}

	return resultat;
}

void decompression(uint8_t *tab_entree, int taille){


	int DEBUG = 509;
	int compt = 0;

	int i1, i2, k = 0, tailleW1 = 1, tailleW2;
	uint8_t *w1;
	uint8_t *w2;
	uint8_t a[1];

	int bits_restants_dans_tampon = 0, tailleBitsMot = NBBITDEPART;
	uint32_t tampon = 0;
	uint32_t masque = 0xFF800000;

	initialiser();

	do
	{
		i1 = binToCode(tab_entree[k], &bits_restants_dans_tampon, &tailleBitsMot, &tampon, &masque);
		k++;
	}
	while(i1 == 0);

	CodeVersChaine(i1,a);
	w1 = malloc(tailleW1*sizeof(uint8_t));
	w1[0] = a[0];
	printf("%c", w1[0]);

	while(k < taille)
	{
		// printf("%d ", compt);
		if(compt==255){
		// printf("moment qui bug\n");
		}

		i2 = 0;
		do
		{
			i2 = binToCode(tab_entree[k], &bits_restants_dans_tampon, &tailleBitsMot, &tampon, &masque);
			k++;
		}
		while(i2 == 0);

		// printf("i2 : %d et ind_dico : %d\n", i2, ind_dico);
		if(i2 >= ind_dico)
		{	
			// printf("on rentre dans le if\n");
			tailleW2 = CodeVersLongueur(i1) + 1;
			w2 = malloc(tailleW2*sizeof(uint8_t));
			CodeVersChaine(i1,w2);
			w2[tailleW2-1] = a[0];
		}
		else
		{
			// printf("on rentre dans le else\n");
			tailleW2 = CodeVersLongueur(i2);
			w2 = malloc(tailleW2*sizeof(uint8_t));
			CodeVersChaine(i2,w2);
		}

		for(int i = 0; i < tailleW2; i++){
			printf("%c", w2[i]);
		}
		compt++;
		a[0] = w2[0];
		if(Inserer(SequenceVersCode(w1,tailleW1),SequenceVersCode(a,1)) >= (1 << tailleBitsMot)-1)
		{
			tailleBitsMot++;
			masque = masque >> 1;
			masque += 0x80000000;
		}

		i1 = i2;
		tailleW1 = CodeVersLongueur(i1);
		w1 = malloc(tailleW1*sizeof(uint8_t));
		CodeVersChaine(i1,w1);

		if(ind_dico == DEBUG) ouiouioui();
		// printf("a : %c w2 : %s, w : %s\n",a[0], w2, w1);
		// printf("\n");
	}

}