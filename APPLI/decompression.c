//FIXME : Decompression bug au pout de 856 caractères OU fait de la merde sur le 848eme

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "dictionnaire.h"
#include "decompression.h"

#define NBBITDEPART 9

void MARK(){

}

void decompression(int *tab, int lg){
	int i1, i2, k = 0, tailleW1 = 1, tailleW2;
	uint8_t *w1;
	uint8_t *w2;
	uint8_t a[1];

	int ind_insertion;

	initialiser();

	i1 = tab[k];
	k++;

	CodeVersChaine(i1,a);
	w1 = malloc(tailleW1*sizeof(uint8_t));
	w1[0] = a[0];
	printf("%c", w1[0]);

	while(k < lg)
	{
		i2 = 0;
		i2 = tab[k];
		k++;

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

		i1 = i2;
		tailleW1 = CodeVersLongueur(i1);
		w1 = malloc(tailleW1*sizeof(uint8_t));
		CodeVersChaine(i1,w1);

	}
}
