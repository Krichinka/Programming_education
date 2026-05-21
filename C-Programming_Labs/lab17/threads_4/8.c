#include <stdio.h>
#include <pthread.h>

#define N 4
#define THREADS 2

int A[N][N];
int B[N][N];
int C[N][N];

void fill_matrix(int M[N][N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            M[i][j] = 1;
        }
    }
}

void print_matrix(int M[N][N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}

void *multiply(void *arg)
{
    int id = *(int *)arg;
    int rows = N / THREADS;
    int start = id * rows;
    int end = start + rows;

    if (id == THREADS - 1) {
        end = N;
    }

    for (int i = start; i < end; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;

            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main(void)
{
    pthread_t threads[THREADS];
    int ids[THREADS];
    fill_matrix(A);
    fill_matrix(B);

    for (int i = 0; i < THREADS; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, multiply, &ids[i]);
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Matrix A:\n");
    print_matrix(A);
    printf("Matrix B:\n");
    print_matrix(B);
    printf("Matrix C:\n");
    print_matrix(C);
}