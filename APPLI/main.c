#include <stdio.h>
#include <stdlib.h>
#include "compression.h"
#include "decompression.h"

int main(int argc, char *argv[]){

	FILE *f = NULL;
	FILE *f2 = NULL;
	FILE *f3 = NULL;

	if(argc != 2){
		printf("Le programme prend un fichier à compresser en argument\n");
		return 1;
	}

	 f = fopen(argv[1],"r");
	 if (f == NULL){
	 	printf("Erreur lors de l'ouverture du fichier\n");
	 	return 1;
	 }

	 int i = 0, tailleInput, tailleTabZip, tailleTabUnzip;
	 char c;
	 char *input;
	 char *tabZip;
	 char *tabUnzip;
		
	 /* Lecture du fichier */

	while (!feof(f)) {
		c = fgetc(f);
		if(c != -1){
			i++;
		}
	}
		
	rewind(f);
		
	tailleInput = i;
	input = malloc(tailleInput*sizeof(char));

	i = 0;
	while (!feof(f)) {
		c = fgetc(f);
		if(c != -1){
			input[i] = c;
			i++;
		}
	}

	 fclose(f);

	 /* Appel à codage */

	tabZip = malloc(tailleInput*sizeof(char));
	tailleTabZip = tailleInput;

	// printf("Coucou\n");

	codage(input,&tailleTabZip,tabZip);



	// for(int k = 0; k < tailleTabZip; k++)
	// {
	// 	printf("%c(%i)", tabZip[k],tabZip[k]); 
	// }
	// printf("bye\n");

	/* Stocakge de la compression dans un fichier */

	f2 = fopen("zip", "w");
	for(int k = 0; k < tailleTabZip; k++)
	{
		fputc(tabZip[k], f2); 
	}

	fclose(f2);

	/* Appel à décompression */

	tailleTabUnzip = tailleInput;
	tabUnzip = malloc(tailleTabUnzip*sizeof(char));
	decompression(&tailleTabZip,tabZip,tabUnzip);

	/* Stockage de la decompression dans un fichier */

	f3 = fopen("unzip", "w");
	for(int k = 0; k < tailleTabUnzip; k++)
	{
		fputc(tabUnzip[k], f3); 
	}

	fclose(f3);

	return 0;
}