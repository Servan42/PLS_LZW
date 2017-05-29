//FIXME : Decompression bug au pout de 856 caractères OU fait de la merde sur le 848eme

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "dictionnaire.h"
#include "decompression.h"

#define NBBITDEPART 9

void MARK(){

}
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

void decompression(int *tab, int lg){
	int i1, i2, k = 0, tailleW1 = 1, tailleW2;
	uint8_t *w1;
	uint8_t *w2;
	uint8_t a[1];

	int bits_restants_dans_tampon = 0, tailleBitsMot = NBBITDEPART;
	uint32_t tampon = 0;
	uint32_t masque = 0xFF800000;
	int decalageMasque = 0; //tailleBitsMots - NBBITDEPART
	int ind_insertion;
	uint32_t codes_decomp[MAX];
	int tmp = 0;

	/*for(int j=0;j<lg;j++){
		printf("%d\n",tab[j]);
	}*/

	initialiser();

	/*do
	{
		i1 = binToCode(tab_entree[k], &bits_restants_dans_tampon, &tailleBitsMot, &tampon, &masque, &decalageMasque);
		k++;
	}
	while(i1 == 0);*/
	i1 = tab[k];
	k++;
	codes_decomp[tmp] = i1;
	tmp++;

	CodeVersChaine(i1,a);
	w1 = malloc(tailleW1*sizeof(uint8_t));
	w1[0] = a[0];
	printf("%c", w1[0]);

	while(k < lg)
	{
		i2 = 0;
		/*do
		{
			i2 = binToCode(tab_entree[k], &bits_restants_dans_tampon, &tailleBitsMot, &tampon, &masque, &decalageMasque);
			k++;
		}
		while(i2 == 0);*/
		i2 = tab[k];
		if(i2==33){
			MARK();
		}
		//printf("i2 = %d\n",tab[k]);
		k++;
		codes_decomp[tmp] = i2;
		tmp++;

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
			printf("%c", w2[i]);
		}

		a[0] = w2[0];

		ind_insertion = Inserer(SequenceVersCode(w1,tailleW1),SequenceVersCode(a,1));
		if(ind_insertion >= (1 << tailleBitsMot)-2)
		{
			tailleBitsMot++;
			decalageMasque++;
			//printf("\n\nind_dico : %d | Indice insertion : %d | Augmentation de la taillebit à : %d\n\n",ind_dico,ind_insertion,tailleBitsMot);
		}

		i1 = i2;
		tailleW1 = CodeVersLongueur(i1);
		w1 = malloc(tailleW1*sizeof(uint8_t));
		CodeVersChaine(i1,w1);

	}

	/*printf("CODES DECOMPRESSION\n");
	for(int i=0;i<tmp;i++){
		printf("%d\n",codes_decomp[i]);
	}
	printf("-------------------\n");*/
}
