#ifndef COMPLEX_H
#define COMPLEX_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float x;
    float y;
} complex;

complex* sum(complex* a, complex* b);
complex* mult(complex* a, complex* b);
void print_complex(complex* a);
complex* input_complex(unsigned char n);

#endif