
#ifndef DICTIONNAIRE_H
#define DICTIONNAIRE_H

#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"

#define MAX 5000

typedef int Code;

typedef struct{
  int longueur;
  char *mot;
}elem;

int ind_dico;

elem dico[MAX];

void initialiser();

Code Inserer(Code prefixe,Code mono);

uint8_t *CodeVersChaine (Code code, int *longueur);

Code SequenceVersCode (uint8_t *sequence, int longueur);

#endif
