#include <stdio.h>
#include <stdlib.h>


void lecture_fichier(char* nom_fichier, char *tab){
 	FILE *fichier;

 	int i = 0;
	fichier = fopen(nom_fichier, "r");
	if (fichier != NULL) {
		while (!feof(fichier)) {
			tab[i]=fgetc(fichier);
			printf("%c | %i \n", tab[i], tab[i]);
			i++;
		}
	}
	fclose(fichier);
}

int main(int argc, char *argv[]){

	if(argc==2){
		int taille;
	 	printf("rentrez la taille du fichier en octet :\n");
	 	scanf("%d", &taille);

	 	char *tab_entree = malloc(taille*sizeof(char));
	 	lecture_fichier(argv[1], tab_entree);
	 	// printf("%s\n", tab_entree);

	 	//apelle à compression

	}
	else{
		printf("Manque le fichier en argument !\n");
	}

	return 1;
}