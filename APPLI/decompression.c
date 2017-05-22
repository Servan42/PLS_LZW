#include "decompression.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "dictionnaire.h"
/**** à adapter avec ce qu'on va faire dans compression ****/


void concat2(char *w, int tailleW, char *a,char *out){
	int i;
	for(i = 0; i < tailleW; i++)
	{
		out[i] = w[i];
	}
	out[i] = a[0];
}

void decompression(int taille, char *tab_entree, char *tab_sortie){

	int i = 0; //index du dict
	int i2;
	int *longueur = malloc(sizeof(int));
	int *longueur2 = malloc(sizeof(int));
	char *tab = malloc(taille * sizeof(char));  //pas sur de la taille a alouer
	char *a = malloc(sizeof(char)); // un octet déclarer en string
	a = (char *) CodeVersChaine(i, longueur);
	char *w = malloc(15*sizeof(char)); // chaine d octet
	w[0]=a[0];
	char *w2 = malloc(15*sizeof(char));
	tab_sortie[0] = w[0];
	int compt = 1; //itérant du tab de sortie

	for (int i = 1; i < taille ; ++i){
		i2 = tab_entree[i+1]; // si ya un marqueur de fin sur le tableau en entrée

		if(*CodeVersChaine(i, longueur)==-1){
			w2 = (char *) CodeVersChaine(i, longueur2);
			concat2(w2, *longueur2, a, w2);
		}

		else{
			w2 = (char *) CodeVersChaine(i2, longueur2);
		}

		for(int j = 0 ; j < *longueur2 ; j++){
			tab[compt] = w2[j];
			compt++;
		}
		a[0] = w2[0];
		Inserer(SequenceVersCode((uint8_t *) w, *longueur),SequenceVersCode((uint8_t *) a,1));
		w = (char *) CodeVersChaine(i2, longueur);
	}

	tab_sortie = malloc((compt-1)*sizeof(char));
	for (int i = 0; i < compt; ++i)
	{
		tab_sortie[i] = tab[i];
	}
}