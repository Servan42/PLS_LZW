#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "dictionnaire.h"

//comme en MN
//Dans notre structure, descendre à gauche revient à changer la lettre de la position courante
//Descendre à droite correspond à avancer d'une lettre et donc à "valider" la précédente
typedef struct arbre_t{
	Code code; // le code de compression correspondant
	struct arbre_t * gauche; //suite du mot à gauche
	struct arbre_t * droite; //suite du mot à droite
}arbre, *p_arbre;

void imprimer_arbre(p_arbre tree);

p_arbre Initialiser_arbre( Code code, p_arbre gauche , p_arbre droite ) ;

p_arbre inserer_gauche(int code, p_arbre *tree);

p_arbre inserer_droite(int code, p_arbre *tree);

int nombre_elt_arbre(p_arbre tree);



