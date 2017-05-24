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

	initialiser(); //initialisation du dictionnaire

	int i = 0; //index du dict
	int i2;
	int longueur=1;
	int longueur2=1;
	int cond;
	uint8_t *tab = malloc((*taille) * sizeof(uint8_t));  //pas sur de la taille a alouer
	longueur = CodeVersLongueur(tab_entree[i]);
	uint8_t *a = malloc(longueur*sizeof(uint8_t)); // un octet déclarer en string
	CodeVersChaine(tab_entree[i], a);
	uint8_t *w = malloc(longueur*sizeof(char)); // chaine d octet
	w[0]=a[0];
	//printf("caractere de w : %c\n", w[0]);
	uint8_t *w2 = malloc(longueur*sizeof(uint8_t));
	tab[0] = w[0];
	//printf("tabsortie 0 : %c\n",tab[0]);
	int compt = 1; //itérant du tab de sortie


	/*cond = CodeVersLongueur(tab_entree[i]);
	for(int l=0;l<200;l++){
		printf("tab : %d\n",tab_entree[l]);
	}*/

	while(longueur!=(-1)){
		//printf("\n");
		//printf("On rentre dans le while pour tab_entree de %d : %d\n", i, tab_entree[i]);
		// printf("%s\n",);
		i2 = i+1; // si ya un marqueur de fin sur le tableau en entrée
		cond = CodeVersLongueur(tab_entree[i2]);
		//printf("cond : %d\n", cond);
		if(cond==0){
			//printf("on rentre dans le if\n");
			longueur2 = CodeVersLongueur(tab_entree[i]);
			free(w2);
			w2 = malloc(longueur2*sizeof(uint8_t));
			//printf("w2 = %p\n",w2);
			CodeVersChaine(tab_entree[i], w2);
			longueur2++;
			w2[i+1] = a[0];
			w2[longueur2] = a[0];
		}

		else{
			//printf("on rentre dans le else\n");
			longueur2 = CodeVersLongueur(tab_entree[i2]);
			free(w2);
			w2 = malloc(longueur2*sizeof(uint8_t));
			//printf("w2 = %p\n",w2);
			CodeVersChaine(tab_entree[i2], w2);
		}

		//printf("On écrit dans le tab de sortie\n");
		for(int j = 0 ; j < longueur2 ; j++){
			//printf(" %d : %c |\n", compt, w2[j]);
			tab[compt] = w2[j];
			compt++;
		}
		//a[0] = w2[0];
		Inserer(SequenceVersCode(w, longueur),SequenceVersCode(a,1));	//ajout de mot au dictionnaire
		longueur = CodeVersLongueur(tab_entree[i2]);
		//printf("val w : %p\n",w);
		free(w);
		w = malloc(longueur*sizeof(uint8_t));
		CodeVersChaine(tab_entree[i2], w);
		i++;
	}

	tab_sortie = malloc((compt-1)*sizeof(uint8_t));
	for (int i = 0; i < compt; ++i)
	{
		tab_sortie[i] = tab[i];
		printf("tableau de sortie élément %d : %c\n",i, tab[i]);
	}
	*taille = compt;
	//dico_print();
}
