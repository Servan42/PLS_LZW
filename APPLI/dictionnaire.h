#ifndef DICTIONNAIRE_H
#define DICTIONNAIRE_H

typedef int Code;

void initialiser();

Code Inserer(Code prefixe,Code mono);

uint8_t *CodeVersChaine (Code code, int *longueur);

Code SequenceVersCode (uint8_t *sequence, int longueur);

#endif
