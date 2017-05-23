/**
* @file main.c
* @brief Fichier contenant la plante du programme.
*/

#include <stdio.h>
#include <stdlib.h>
#include "compression.h"
#include "decompression.h"

void dispError()
{
	printf("Syntaxe : \n");
	printf("\t./lzw -c fichier_a_compresser\n");
	printf("\t./lzw -d fichier_a_decompresser\n");
}

int main(int argc, char *argv[]){

	FILE *f = NULL;
	int i = 0, tailleInput, tailleTabZip, tailleTabUnzip;
	char c;
	char *input;
	char *tabUnzip;
	// int *tabZip1;

	if(argc != 3){
		dispError();
		return 1;
	}

	if(argv[1][0] == '-')
	{
		switch(argv[1][1])
		{
			case 'c':

				f = fopen(argv[2],"r");
				if (f == NULL){
					printf("Erreur lors de l'ouverture du fichier %s\n",argv[2]);
					return 1;
				}
				
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
				tailleTabZip = tailleInput;
				codage(input,tailleTabZip);

				break;

			case 'd':

				/* Lecture du fichier à decompresser */

				// f = fopen(argv[2], "r");
				// if (f == NULL){
				// 	printf("Erreur lors de l'ouverture du fichier %s\n",argv[2]);
				// 	return 1;
				// }

				// while (!feof(f)) {
				// 	c = fgetc(f);
				// 	if(c != -1){
				// 		i++;
				// 	}
				// }
					
				// rewind(f);
					
				// tailleInput = i;
				// tabZip1 = malloc(tailleInput*sizeof(char));

				// i = 0;
				// while (!feof(f)) {
				// 	c = fgetc(f);
				// 	if(c != -1){
				// 		tabZip1[i] = c;
				// 		i++;
				// 	}
				// }

				// fclose(f);

				/* Appel à décompression */
				printf("on va décompresser\n");

				int tabZip1[10] = {97, 98, 99, 257, 259, 258, 100, 101, 10, 256};
				tailleTabUnzip = tailleInput;
				tabUnzip = malloc(tailleTabUnzip*sizeof(char));
				decompression(&tailleInput,tabZip1,tabUnzip);

				printf("on a décompressé\n");


				for(int k = 0; k < tailleTabUnzip; k++)
				{
					printf("%c", tabUnzip[k]); 
				}


				break;

			default:
				dispError();
				return 1;
				break;
		}
	}else dispError();

	return 0;
}