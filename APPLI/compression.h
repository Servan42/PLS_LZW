#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <stdint.h>

void concat(uint8_t *w, int tailleW, uint8_t *a, uint8_t *out);
void display_output(int code, int *bits_restants_dans_tampon, int *tailleBitsMot, uint32_t *tampon);
void codage(uint8_t *input, int taille);

#endif 
