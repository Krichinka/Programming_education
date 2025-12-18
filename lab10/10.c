#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} complex;

complex* sum(complex* a, complex* b);
complex* mult(complex* a, complex* b);
void print_complex(complex* a);
complex* input_complex(unsigned char n);

complex* input_complex(unsigned char n) 
    {
        complex* chisla = malloc(n * sizeof(complex));
        
        if (chisla == NULL) 
        {
            printf("Ошибка выделения памяти!\n");
            return NULL;
        }

        if (n < 1) 
        {
            printf("Ошибка\n");
            return NULL;
        }
        
        for (int i = 0; i < n; i++) 
        {
            printf("Число %d: ", i + 1);
            scanf("%lf %lf", &chisla[i].x, &chisla[i].y);
        }
    
        return chisla;
    }

void print_complex(complex* a)
{
    printf("%lf + i%lf\n", a->x, a->y);
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
    complex* x = malloc(sizeof(complex));
    x->x = a->x * b->x;
    x->y = a->y * b->y;
    return x;
}

int main(unsigned char n)
{
    complex* chisla;
    complex* Q;
    chisla = input_complex(n);
    print_complex(&chisla[1]);
}
