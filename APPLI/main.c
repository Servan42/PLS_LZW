/**
* @file main.c
* @brief Fichier contenant la plante du programme.
*/

#include <stdio.h>
#include <stdlib.h>
#include "compression.h"
#include "decompression.h"
#include "dictionnaire.h"

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
	//int sip[2000];
	char *input;
	char *tabUnzip;

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
				printf("DICTIONNAIRE APRES CODAGE :\n");
				printf("-------------------------------\n");
				dico_print();
				printf("-------------------------------\n");
				break;
			case 'd':

				/* Lecture du fichier à decompresser */
				//printf("ok\n");

				 /*f = fopen(argv[2], "r");
				 if (f == NULL){
				 	printf("Erreur lors de l'ouverture du fichier %s\n",argv[2]);
				 	return 1;
				 }

				 while (!feof(f)) {
				 	c = fgetc(f);
				 	if(c != -1){
				 		i++;
				 	}
				 }
				 rewind(f);

				 tailleInput = i;
				 tabZip1 = malloc(tailleInput*sizeof(char));

				 i = 0;
				 while (!feof(f)) {
				 	c = fgetc(f);
				 	if(c != -1){
				 		tabZip1[i] = c;
				 		i++;
				 	}
				 }

				 fclose(f);
*/

				/* Appel à décompression */
				printf("on va décompresser\n");
				/* compressage de "abcdabd"
					donne en héxa : 30 98 8c 66 48 09 92 00
					soit en déci
				*/
				int tabZip1[8] = {48, 152, 140, 102, 72, 9, 146, 0};
				// int tabZip1[25] = {66,111,110,106,111,117,114,32,98,97,110,100,101,115,32,268,32,115,97,108,111,112,269,10,256};
				tailleTabUnzip = tailleInput;
				tabUnzip = malloc(tailleTabUnzip*sizeof(char));
				tailleInput = 8;
				decompression(&tailleInput,tabZip1,tabUnzip);
				printf("DICTIONNAIRE APRES DECODAGE :\n");
				printf("-------------------------------\n");
				// dico_print();
				printf("-------------------------------\n");
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
