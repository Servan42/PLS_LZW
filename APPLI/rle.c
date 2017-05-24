#include <stdio.h>
#include <stdlib.h>

/* RLE À APPLIQUÉ AVANT LA DÉCOMPRESSION : PERMET DE TRANSFORMER
				XX -> X§1
				XXXXX -> EN X§4
				11111 -> 1§4
*/

void rle(char *fichier){

	FILE *f = NULL;
	f = fopen(fichier,"r");
	int i = 0;
	char c;

	if(f==NULL){
		printf("ERREUR : Problème lors de l'ouverture du fichier\n");
		exit(-1);
	}

	/* Lecture du fichier */

	// récupération du nombre de caractères
	while (!feof(f)) {
		c = fgetc(f);
		if(c != -1){
			i++;
		}
	}
	rewind(f);

	// on crée le tableau dans lequel on stock nos caractères
	int tailleInput = i;
	char *input = malloc(tailleInput*sizeof(char));

	//on stock les caractères lu dans notre fichier dans le tableau
	i = 0;
	while (!feof(f)) {
		c = fgetc(f);
		if(c != -1){
			input[i] = c;
			i++;
		}
	}
	fclose(f);

	i = 0;
	int tailleOutput = 0;
	char prec = '$';

	// on calcul la taille de notre tableau de sortie
	while(i < tailleInput){
		// printf("itération  : %d\n", i);

		if(prec == input[i]){
			// on fait rien
		}

		else if(input[i] == input[i+1]){
			tailleOutput = tailleOutput + 3;
		}

		else{
			tailleOutput++;
		}
		prec = input[i];
		i++;
		// printf("valeur de tailleOutput : %d\n", tailleOutput);
	}

	/* test de la valeur des tailles : ok */
	// printf("taille input : %d\n", tailleInput);
	// printf("taille output : %d\n", tailleOutput);


	char *output = malloc(tailleOutput*(sizeof(char)));
	int indexIn = 0;
	int indexOut = 0;
	int compt = 0;
	prec = '$';

	// printf("Le tableau input\n");
	// for (int i = 0; i < tailleInput; ++i)
	// {
	// 	printf("%c", input[i]);
	// }
	// printf("\n");

	// printf("initialisation des variables faites\n");

	while(indexIn < tailleInput){

		// printf("On est à l'itération %d\n", indexIn);
		// printf("valeur de prec : %c\ninput[i] : %c\ninput[i+1] : %c", prec, input[indexIn], input[i+1]);
		if(prec != input[indexIn] && input[indexIn] == input[indexIn+1]){
			// printf("On rentre dans le if\n");
			output[indexOut] = input[indexIn];
			output[indexOut+1] = '$';
			while(input[indexIn]==input[indexIn+1]){
				// printf("Valeur de compt : %c\n", compt-'0');
				compt++;
				indexIn++;
			}
			output[indexOut+2] = (char) compt+48;
			indexOut = indexOut + 3;
			compt = 0;
		}

		else if(prec == input[i]){
			// printf("On rentre dans le esle if\n");
			// on fait rien
		}

		else{
			output[indexOut] = input[indexIn];
			indexOut++;
		}
		prec = input[indexIn];
		indexIn++;
	}
	printf("On a précompressé notre tableau\n");


	// for(int i = 0 ; i < tailleOutput ; i++){
	// 	printf("%c", output[i]);
	// }

}


void elr(char *fichier){
	FILE *f = fopen(fichier,"r");

	if (f==NULL) { printf("ERREUR \n");}
	
/* Lecture du fichier */
	char c; int i=0;
	// récupération du nombre de caractères
	while (!feof(f)) {
		c = fgetc(f);
		if(c != -1){
			i++;
		}
	}
	rewind(f);

	// on crée le tableau dans lequel on stock nos caractères
	int tailleInput = i;
	char * input = malloc(tailleInput*sizeof(char));

	//on stock les caractères lu dans notre fichier dans le tableau
	i = 0;
	while (!feof(f)) {
		c = fgetc(f);
		if(c != -1){
			input[i] = c;
			i++;
		}
	}
	fclose(f);

//on va compter tailleOutput

	printf("tailleInput vaut : %d \n", tailleInput);

	for (int i = 0; i<tailleInput; i++){
	printf("fichier en entrée %c \n", input[i]);
	}

	int tailleOutput = 0; // tailleOutput sera notre tailleOuput
	int p = 0;
	while(p<tailleInput){
		// printf("valeur de p : %d\n", p);
		if (input[p]=='$'){
			// printf("On rentre dans le if\n");
			// printf("input[p+1] : %c\n", input[p+1]);
			tailleOutput = tailleOutput + input[p+1] - 48;
			p = p+2 ;
		}
		else {
			// printf("On rentre dans le else\n");
			tailleOutput = tailleOutput + 1 ;
			p++;
		}
		// printf("taille output a chaque itération : %d\n", tailleOutput);
	}
	
	printf("tailleOutput vaut : %d \n", tailleOutput);

	char * output = malloc(tailleOutput*(sizeof(char)));


//coeur du ERL 
	int indexIn = 0;
	int indexOut = 0;
	int compt = 0;
	while(indexIn<tailleInput){
		printf("itération %d\n",indexIn);
		if (input[indexIn]=='$'){
			printf("input[indexIn+1] : %c\n", input[indexIn+1]);
			while(compt<input[indexIn+1] - 48){
				// printf("valeur de compt %d\n", compt);
				output[indexOut] = input[indexIn-1];
				indexOut++;
				compt++;
			}
			compt = 0;
			indexIn++;
		}
		else{
			output[indexOut]=input[indexIn];
			indexOut++;
		}
		indexIn++;
	}

	printf("resultat final\n");
	for (int i = 0; i<tailleOutput; i++){
		printf("%c", output[i]);
	}
	printf("\n");
}