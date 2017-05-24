#include "decompression.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "dictionnaire.h"

/***************** README ********************/
/*
Exemple utiliser : voir main
Pour décompresser, on veut transformer notre tableau d'octet (contenu par tab_entree) en un tableau de code int (contenue
dans tab_conv)

Pour cela on récupere d'abord la taille de tab_conv

Puis on peux créer tab_conv et le remplir

Pour finir on applique l'algo de décompression sur tab_conv

FIXME ->
	taille2 devrait valoir 5
	boucle infini dans decompression
	contenu de tab_conv normalement : {97, 98, 99, 100, 257, 100, 256} mais on a {0, 0, 97, 0}
*/


/**
* @fn void decompression(int taille, char *tab_entree, char*tab_sortie)
* @brief Algorithme de décompression LZW.
* @param[in] entier contant la taille du tableau tab_entree.
* @param[in] tab_entree Tableau de caractère contenant la totalité de l'information contenue dans le fichier à décompresser.
* @param[in, out] tab_sortie Tableau de caractère contenant la décompression des données.
*/
void decompression(int *taille, int *tab_entree, char *tab_sortie){

	initialiser(); //initialisation du dictionnaire

	#define NBBITDEPART 9

	printf("On va créer le tableau");

	int bits_restants_dans_tampon = 0, tailleBitsMot = NBBITDEPART;
	uint32_t tampon = 0;
	uint32_t masque = 0xFF800000;
	int decalageMasque = 0; //tailleBitsMot - NBBITDEPART
	int indexdico = 257;

	/* ce for nous permet de recupérer la taille de tab_conv*/

	int taille2 = 0;
	for (int k = 0; k < *taille; ++k)
	{
		printf("itération %d\n", k);
		tampon |= tab_entree[k] << (32 - 8 - bits_restants_dans_tampon);
		bits_restants_dans_tampon += 8;

		while(bits_restants_dans_tampon >= tailleBitsMot)
		{
			printf("indexico : %d\n", indexdico);
			tampon <<= tailleBitsMot;
			bits_restants_dans_tampon -= tailleBitsMot;
			indexdico++;
			taille2++;

			if(indexdico >= (1 << tailleBitsMot)-1)
			{
				printf("On doit augmenter notre nombre de bits\n");
				tailleBitsMot++;
				decalageMasque++;
			}
		}
		printf("taille2 : %d\n", taille2);
		k++;
	}
	taille2++;

	// on remplit tab_conv pour récuper le tableau des index de chaque de code
	indexdico = 257;
	bits_restants_dans_tampon = 0;
	tailleBitsMot = NBBITDEPART;
	tampon = 0;
	decalageMasque = 0;
	uint8_t *tab_conv = malloc(taille2*sizeof(char));
	for (int k = 0; k < *taille; ++k)
	{
		tampon |= tab_entree[k] << (32 - 8 - bits_restants_dans_tampon);
		bits_restants_dans_tampon += 8;

		while(bits_restants_dans_tampon >= tailleBitsMot)
		{
			masque |= (0xFF800000 >> decalageMasque);
			tab_conv[k] = (tampon & masque) >> (32 - tailleBitsMot);
			tampon <<= tailleBitsMot;
			bits_restants_dans_tampon -= tailleBitsMot;

			//l index nous permet de savoir quand on doit augmenter notre nbr de bits,
			//
			indexdico++;

			if(indexdico >= (1 << tailleBitsMot)-1)
			{
				printf("On doit augmenter notre nombre de bits\n");
				tailleBitsMot++;
				decalageMasque++;
			}
		}
		k++;
	}
	tab_conv[taille2-1] = 256;

	printf("on a crée notre tableau intermediaire\n");
	for (int i = 0; i < taille2; ++i)
	{
		printf(" valeur de tab_conv : %d\n", tab_conv[i]);
	}


	// on va récupérer les chaines à partir des codes de chaque indices de tab_conv
	int i = 0; //index du dict
	int i2;
	int longueur=1;
	int longueur2=1;
	int cond;
	uint8_t *tab = malloc(taille2* sizeof(uint8_t));  //pas sur de la taille a alouer
	longueur = CodeVersLongueur(tab_conv[i]);
	uint8_t *a = malloc(longueur*sizeof(uint8_t)); // un octet déclarer en string
	CodeVersChaine(tab_conv[i], a);
	uint8_t *w = malloc(longueur*sizeof(char)); // chaine d octet
	w[0]=a[0];
	//printf("caractere de w : %c\n", w[0]);
	uint8_t *w2 = malloc(longueur*sizeof(uint8_t));
	tab[0] = w[0];
	//printf("tabsortie 0 : %c\n",tab[0]);
	int compt = 1; //itérant du tab de sortie


	/*cond = CodeVersLongueur(tab_conv[i]);
	for(int l=0;l<200;l++){
		printf("tab : %d\n",tab_conv[l]);
	}*/

	while(longueur!=(-1)){
		// printf("Itération : %d\n", i);
		//printf("\n");
		//printf("On rentre dans le while pour tab_conv de %d : %d\n", i, tab_conv[i]);
		// printf("%s\n",);
		i2 = i+1; // si ya un marqueur de fin sur le tableau en entrée
		cond = CodeVersLongueur(tab_conv[i2]);
		//printf("cond : %d\n", cond);
		if(cond==0){
			//printf("on rentre dans le if\n");
			longueur2 = CodeVersLongueur(tab_conv[i]);
			free(w2);
			w2 = malloc(longueur2*sizeof(uint8_t));
			//printf("w2 = %p\n",w2);
			CodeVersChaine(tab_conv[i], w2);
			longueur2++;
			w2[i+1] = a[0];
			w2[longueur2] = a[0];
		}

		else{
			//printf("on rentre dans le else\n");
			longueur2 = CodeVersLongueur(tab_conv[i2]);
			if(longueur2!=-1){
				free(w2);
				w2 = malloc(longueur2*sizeof(uint8_t));
				//printf("w2 = %p\n",w2);
				CodeVersChaine(tab_conv[i2], w2);
			}
		}

		//printf("On écrit dans le tab de sortie\n");
		for(int j = 0 ; j < longueur2 ; j++){
			//printf(" %d : %c |\n", compt, w2[j]);
			tab[compt] = w2[j];
			compt++;
		}
		// printf("ok0\n");
		longueur = CodeVersLongueur(tab_conv[i2]);
		if(longueur2!=-1){
			a[0] = w2[0];
			// printf("ok1\n");
			Inserer(SequenceVersCode(w, longueur),SequenceVersCode(a,1));	//ajout de mot au dictionnaire
			//printf("val w : %p\n",w);
			free(w);
			w = malloc(longueur*sizeof(uint8_t));
			CodeVersChaine(tab_conv[i2], w);
		}
		i += 1;
		// printf("tableau de sortie élément %d : %c\n",i, tab[i]);
	}
	printf("On arrive à la fin du while\n");
	tab_sortie = malloc((compt-1)*sizeof(uint8_t));
	for (int i = 0; i < compt; ++i)
	{
		tab_sortie[i] = tab[i];
		// printf("tableau de sortie élément %d : %c\n",i, tab[i]);
	}
	taille2 = compt;
	//dico_print();
}
