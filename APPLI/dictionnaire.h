
#ifndef DICTIONNAIRE_H
#define DICTIONNAIRE_H

#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"

#define MAX 65535

typedef int Code;

typedef struct{
  int longueur;
  char *mot;
}elem;

int ind_dico;

elem dico[MAX];

void dico_print();

void initialiser();

int CodeVersLongueur(Code code);

Code Inserer(Code prefixe,Code mono);

void CodeVersChaine (Code code, uint8_t *val);

Code SequenceVersCode (uint8_t *sequence, int longueur);

#endif
