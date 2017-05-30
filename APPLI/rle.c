#include <stdio.h>
#include <stdlib.h>
#include "rle.h"

/* RLE À APPLIQUÉ AVANT LA DÉCOMPRESSION : PERMET DE TRANSFORMER
				XX -> X§1
				XXXXX -> EN X§4
				11111 -> 1§4
*/

void rle(FILE *f){


	int compt = 0;
	char prec = '$';
	char c = fgetc(f);
	char c2;
	FILE* f2 = NULL;
	f2 = fopen("rle", "w");

	while(!feof(f)){

		c2 =fgetc(f);

		if(prec != c && c == c2){
			fputc(c, f2);
			fputc('$', f2);
			// printf("%c",c);
			// printf("%c",'$');
			while(c==c2 || feof(f)){
				compt++;
				prec = c;
				c = c2;
				c2 =fgetc(f);
			}
			fputc((char) compt+48, f2);
			// printf("%c",(char) compt+48);
			compt = 0;
		}

		else if(prec == c){
		}

		else{
			// printf("%c", c);
			fputc(c, f2);
		}

		prec = c;
		c = c2;
	}
	fclose(f2);
}


void elr(FILE *f){

	int compt = 0;
	char prec = '$';
	char c = fgetc(f);
	char c2;


	while(!feof(f)){

		c2 = fgetc(f);

		if (c == '$'){
			while(compt < c2-48 && !feof(f)){
				// printf("valeur de compt %d\n", compt);
				printf("%c", prec);
				// fputc(prec, f);
				compt++;
			}
			compt = 0;
			c2=fgetc(f);
		}
		else{
			printf("%c", c);
			// fputc(c, f);
		}

		prec = c;
		c = c2;
	}
}