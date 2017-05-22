#ifndef DICTIONNAIRE_H
#define DICTIONNAIRE_H

#define MAX 5000;

typedef int Code;

typedef struct{
  char *mot;
}elem;

elem dico[MAX];

void initialiser();

Code Inserer(Code prefixe,Code mono);

uint8_t *CodeVersChaine (Code code, int *longueur);

Code SequenceVersCode (uint8_t *sequence, int longueur);

#endif
