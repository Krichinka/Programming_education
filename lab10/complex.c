#include "complex.h"

complex* input_complex(unsigned char n) 
    {
        complex* chisla = malloc(n * sizeof(complex));
        
        if (chisla == NULL) 
        {
            printf("Ошибка выделения памяти!\n");
            return NULL;
        }

        if (n == 0) 
        {
            printf("Ошибка\n");
            return NULL;
        }
        
        for (int i = 0; i < n; i++) 
        {
            printf("Число %d: ", i + 1);
            scanf("%f %f", &chisla[i].x, &chisla[i].y);
        }
    
        return chisla;
    }

void print_complex(complex* a)
{
    printf("%.2f + %.2f*i\n", a->x, a->y);
}

complex* sum(complex* a, complex* b)
{
    complex* x = malloc(sizeof(complex));
    x->x = a->x + b->x;
    x->y = a->y + b->y;
    return x;
}

complex* mult(complex* a, complex* b)
{
    float m = a->x;
    float k = a->y;
    complex* temp = malloc(sizeof(complex));
    temp->x = (a->x * b->x) - (a->y * b->y);
    temp->y = (a->x * b->y) + (a->y * b->x);
    return temp;
}
