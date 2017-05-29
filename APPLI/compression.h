#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <stdint.h>

void concat(char *w, int tailleW, char *a,char *out);
void display_output(int code, int *bits_restants_dans_tampon, int *tailleBitsMot, uint32_t *tampon);
void codage(char *input, int taille);

#endif
