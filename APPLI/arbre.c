#include "arbre.h"

p_arbre Initialiser_arbre(Code code, p_arbre gauche, p_arbre droite){
	p_arbre a = malloc(sizeof(arbre));
	a->code = code;
	a->gauche = gauche ;
	a->droite = droite ;
 	return a; 
}

p_arbre inserer_gauche(int code, p_arbre *tree){
	p_arbre i = Initialiser_arbre( code, (*tree)->gauche, NULL);
	(*tree)->gauche = i;
	return tree;
}

p_arbre inserer_droite(int code, p_arbre *tree){
	p_arbre i = Initialiser_arbre( code, NULL, (*tree)->droite);
	(*tree)->droite = i;
	return tree; 
}

void print_arbre(p_arbre tree, int niveau ){
	int i; 

	if (tree==NULL) {printf("erreur lors de l'affichage de l'arbre");}

	else {

		print_arbre (tree->droite,niveau+1) ;
	
		for (i = 0; i < niveau; i++)
		  printf ("\t") ;
		printf (" %d (%d)\n\n", a->code, niveau) ;

		print_arbre (tree->gauche, niveau+1) ;
        }
  return ;
		
}


	
	
