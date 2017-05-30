//FIXME : Decompression bug au pout de 856 caractères OU fait de la merde sur le 848eme

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "dictionnaire.h"
#include "decompression.h"

#define NBBITDEPART 9
//2287
//2243
//2042

// void mark(){}

uint32_t binToCode(uint8_t input, int *bits_restants_dans_tampon, int *tailleBitsMot, uint32_t *tampon, uint32_t *masque, int *decalageMasque)
{
	uint32_t resultat = 0;


	*tampon |= input << (32 - 8 - *bits_restants_dans_tampon);
	*bits_restants_dans_tampon += 8;

	if(*bits_restants_dans_tampon >= *tailleBitsMot)
	{
		*masque |= (0xFF800000 >> *decalageMasque);
		resultat = (*tampon & *masque) >> (32 - *tailleBitsMot);
		*tampon <<= *tailleBitsMot;
		*bits_restants_dans_tampon -= *tailleBitsMot;
	}

	return resultat;
}

void decompression(uint8_t *tab_entree, int taille){

	FILE *f = NULL;
	f = fopen("elr", "w");

	uint32_t i1, i2, k = 0, tailleW1 = 1, tailleW2;
	uint8_t *w1;
	uint8_t *w2;
	uint8_t a[1];

	int bits_restants_dans_tampon = 0, tailleBitsMot = NBBITDEPART;
	uint32_t tampon = 0;
	uint32_t masque = 0xFF800000;
	int decalageMasque = 0; //tailleBitsMots - NBBITDEPART
	int ind_insertion;

	initialiser();

	do
	{
		i1 = binToCode(tab_entree[k], &bits_restants_dans_tampon, &tailleBitsMot, &tampon, &masque, &decalageMasque);
		k++;
	}
	while(i1 == 0);

	//printf("%d\n",i1);
	CodeVersChaine(i1,a);
	w1 = malloc(tailleW1*sizeof(uint8_t));
	w1[0] = a[0];
	fputc(w1[0], f);
	 //printf("%c", w1[0]);

	while(i2 != 256 && k < taille)
	{

		tab_entree[k] &= 0xFF;
		// printf("tab_entree[%d] : 0x%02x\n", k, tab_entree[k]);

		// if (ind_dico == 2285) mark();
		i2 = 0;
		do
		{
			i2 = binToCode(tab_entree[k], &bits_restants_dans_tampon, &tailleBitsMot, &tampon, &masque, &decalageMasque);
			k++;
		}
		while((i2 == 0)&&(k<taille));
		if((k+1)==taille){
			i2 = 256;
		}
		//printf("%d\n",i2);


		if(i2 >= ind_dico)
		{
			tailleW2 = CodeVersLongueur(i1) + 1;
			w2 = malloc(tailleW2*sizeof(uint8_t));
			CodeVersChaine(i1,w2);
			w2[tailleW2-1] = a[0];
		}
		else
		{
			tailleW2 = CodeVersLongueur(i2);
			w2 = malloc(tailleW2*sizeof(uint8_t));
			CodeVersChaine(i2,w2);
		}

		for(int i = 0; i < tailleW2; i++) {
			//printf("%c", w2[i]);
			fputc(w2[i], f);
		}

		a[0] = w2[0];

		ind_insertion = Inserer(SequenceVersCode(w1,tailleW1),SequenceVersCode(a,1));
		if(ind_insertion >= (1 << tailleBitsMot)-2)
		{
			tailleBitsMot++;
			decalageMasque++;
			// printf("\n\nind_dico : %d | Indice insertion : %d | Augmentation de la taillebit à : %d\n\n",ind_dico,ind_insertion,tailleBitsMot);

		}

		i1 = i2;
		tailleW1 = CodeVersLongueur(i1);
		w1 = malloc(tailleW1*sizeof(uint8_t));
		CodeVersChaine(i1,w1);
	}

	fputc('\n',f);

	fclose(f);

}
