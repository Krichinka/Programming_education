#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define N 500

int A[N][N];
int B[N][N];
int C[N][N];

int threads_count;

void fill_matrix(int M[N][N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            M[i][j] = 1;
        }
    }
}

void *multiply(void *arg)
{
    int id = *(int *)arg;
    int rows = N / threads_count;
    int start = id * rows;
    int end = start + rows;

    if (id == threads_count - 1) {
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

void run_test(int t_count)
{
    pthread_t threads[128];
    int ids[128];

    struct timespec start;
    struct timespec end;

    threads_count = t_count;

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < threads_count; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, multiply, &ids[i]);
    }

    for (int i = 0; i < threads_count; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double time_ms =
        (end.tv_sec - start.tv_sec) * 1000.0 +
        (end.tv_nsec - start.tv_nsec) / 1000000.0;

    printf("Threads: %d, time: %.2f ms\n", threads_count, time_ms);
}


int main(void)
{
    fill_matrix(A);
    fill_matrix(B);
    printf("N=%d\n", N);
    run_test(1);
    run_test(2);
    run_test(4);
    run_test(8);
    run_test(16);



}