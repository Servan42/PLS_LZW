#ifndef DECOMPRESSION_H
#define DECOMPRESSION_H

#include <stdint.h>

uint32_t binToCode(uint8_t input, int *bits_restants_dans_tampon, int *tailleBitsMot, uint32_t *tampon, uint32_t *masque, int *decalageMasque);
void decompression(int *tab, int lg);

#endif
