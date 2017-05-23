#include "decompression.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "dictionnaire.h"
/**** FIXME à adapter avec ce qu'on va faire dans compression ****/


/**
* @fn void decompression(int taille, char *tab_entree, char*tab_sortie)
* @brief Algorithme de décompression LZW.
* @param[in] entier contant la taille du tableau tab_entree.
* @param[in] tab_entree Tableau de caractère contenant la totalité de l'information contenue dans le fichier à décompresser.
* @param[in, out] tab_sortie Tableau de caractère contenant la décompression des données.
*/
void decompression(int *taille, int *tab_entree, char *tab_sortie){

	uint8_t *var = NULL;
	int i = 0; //index du dict
	int i2;
	int *longueur = malloc(sizeof(int));
	int *longueur2 = malloc(sizeof(int));
	uint8_t *tab = malloc((*taille) * sizeof(uint8_t));  //pas sur de la taille a alouer
	uint8_t *a = malloc(sizeof(uint8_t)); // un octet déclarer en string
	CodeVersChaine(i, longueur, a);
	uint8_t *w = malloc(15*sizeof(uint8_t)); // chaine d octet
	w[0]=a[0];
	uint8_t *w2 = malloc((*longueur)*sizeof(uint8_t));
	tab_sortie[0] = w[0];
	int compt = 1; //itérant du tab de sortie

	initialiser(); //initialisation du dictionnaire

	i = 1;
	uint8_t *val = malloc(15*sizeof(uint8_t));
	CodeVersChaine(i, longueur, var);

	while(*longueur!=(-1)){
		i2 = tab_entree[i+1]; // si ya un marqueur de fin sur le tableau en entrée

		CodeVersChaine(i, longueur, var);
		if(*longueur==-1){
			free(w2);
			w2 = malloc((*longueur)*sizeof(uint8_t));
			CodeVersChaine(i, longueur2+1, w2);
			w2[i+1] = a[0];
			w2[(*longueur2)+1] = a[0];
		}

		else{
			free(w2);
			w2 = malloc((*longueur)*sizeof(uint8_t));
			CodeVersChaine(i2, longueur2, w2);
		}

		for(int j = 0 ; j < *longueur2 ; j++){
			tab[compt] = w2[j];
			compt++;
		}
		a[0] = w2[0];
		Inserer(SequenceVersCode((uint8_t *) w, *longueur),SequenceVersCode((uint8_t *) a,1));	//ajout de mot au dictionnaire
		CodeVersChaine(i2, longueur, w);
		i++;
		CodeVersChaine(i, longueur, var);
	}

	tab_sortie = malloc((compt-1)*sizeof(uint8_t));
	for (int i = 0; i < compt; ++i)
	{
		tab_sortie[i] = tab[i];
	}
	*taille = compt;
}