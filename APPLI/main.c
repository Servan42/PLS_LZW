#include <stdio.h>
#include <stdlib.h>
#include "compression.h"
#include "decompression.h"


void lecture_fichier(char *nom_fichier, char *tab){
 	FILE *fichier;

 	int i = 0;
 	char c;
	fichier = fopen(nom_fichier, "r");
	if (fichier != NULL) {
		while (!feof(fichier)) {
			c=fgetc(fichier);
			// printf("%c | %i \n", tab[i], tab[i]);
			if((int) c != -1 && (int) c != 10){
				tab[i] = c;
				i++;
			}
		}
		// printf("taille : %d\n", i);
	}
	fclose(fichier);
}

void ecriture_fichier(char *nom_fichier, char *tab, int taille){
	FILE *fichier;

	fichier = fopen(nom_fichier, "w");
	if (fichier != NULL){
		for (int i = 0; i < taille; ++i){
			fputc(tab[i], fichier);
		}
	}
	fclose(fichier);
}

int main(int argc, char *argv[]){

	if(argc==3 || argc==2){
		int *taille = malloc(sizeof(int));
	 	printf("rentrez la taille du fichier en octet :\n");
	 	scanf("%d", taille);

	 	int taille1; //sauv de la taille tableau d'entrée
	 	int taille2; //sauv de la taille du tableau compressé
	 	int taille3; //sauv de la taille du tableau décompressé

	 	char *tab_entree = malloc((*taille)*sizeof(char));
	 	lecture_fichier(argv[1], tab_entree);
	 	// printf("%s\n", tab_entree);


	 	//apelle à compression
	 	taille1 = *taille;
	 	char *tab_compresse1 = malloc(taille1*sizeof(char));
	 	codage(tab_entree, taille, tab_compresse1);
	 	taille2 = *taille;

	 	char *tab_compresse = malloc(taille2*sizeof(char));
	 	for (int i = 0; i < taille2; ++i)
	 	{
	 		tab_compresse[i] = tab_compresse1[i];
	 	}
	 	ecriture_fichier("compressé.txt", tab_compresse, taille2);



	 	//apelle à décompression
	 	char *tab_decompresse1 = malloc(taille1*sizeof(char));
	 	decompression(taille,tab_compresse, tab_decompresse1);
	 	taille3 = *taille;
	 	char *tab_decompresse = malloc(taille3*sizeof(char));
	 	for (int i = 0; i < taille3; ++i)
	 	{
	 		tab_decompresse[i] = tab_decompresse1[i];
	 	}


	 	if(argc == 2){
	 		ecriture_fichier("decompressé.txt", tab_decompresse, taille3);
	 	}
	 	else{
	 		ecriture_fichier(argv[2], tab_decompresse, taille3);
	 	}
	}
	else{
		printf("Il faut 1 ou 2 fichiers en paramètres\n");
	}

	return 1;
}