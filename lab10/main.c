#include "complex.h"

int main(unsigned char n)
{
    n = 3;
    complex* chisla;
    complex* Q;
    chisla = input_complex(n);
    Q = sum(&chisla[0], sum(mult(&chisla[1], &chisla[1]), sum(&chisla[1], &chisla[2])));
    print_complex(Q);
    free(Q);
    free(chisla);
}