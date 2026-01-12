#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 8

int print_ar(int height, int width, int** matrix)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
        
}



int a = 15;

void func(void) {
    printf("global a = %d\n", a);
}

int main(void) {
    int a = 10;
    {
          int a = 20;
    }
    printf("main a = %d\n", a);
    func();
}

        