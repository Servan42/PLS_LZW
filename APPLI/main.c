#include <stdio.h>
#include <stdlib.h>


void lecture_fichier(char* nom_fichier, char *tab){
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

int main(int argc, char *argv[]){

	if(argc==3){
		int taille;
	 	printf("rentrez la taille du fichier en octet :\n");
	 	scanf("%d", &taille);

	 	char *tab_entree = malloc(taille*sizeof(char));
	 	lecture_fichier(argv[1], tab_entree);
	 	// printf("%s\n", tab_entree);

	 	//apelle à compression

	}
	else{
		printf("Il faut 2 fichiers en paramètres\n");
	}

	return 1;
}