#include <stdio.h>
#include <stdlib.h>


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
		int taille;
	 	printf("rentrez la taille du fichier en octet :\n");
	 	scanf("%d", &taille);

	 	char *tab_entree = malloc(taille*sizeof(char));
	 	lecture_fichier(argv[1], tab_entree);
	 	// printf("%s\n", tab_entree);

	 	//apelle à compression
	 	codage(char tab_entree, int taille, char *tab_compresse);

	 	ecriture_fichier("compressé.txt", tab_decompresse, 9);

	 	//apelle à décompression
	 	decompression(int taille2, char *tab_compresse, char *tab_compresse);
	 	// taille 2 etant la taille du tableau compressé

	 	// taille3 etant la taille du tableau decompressé
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