#include <stdio.h>
#include <pthread.h>

#define N 5

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

int turn = 0;

void *child(void *arg)
{
    for (int i = 1; i <= N; i++) {
        pthread_mutex_lock(&m);

        while (turn != 1) {
            pthread_cond_wait(&c, &m);
        }

        printf("Child: line %d\n", i);

        turn = 0;
        pthread_cond_signal(&c);

        pthread_mutex_unlock(&m);
    }
}

int main(void)
{
    pthread_t t;
    pthread_create(&t, NULL, child, NULL);

    for (int i = 1; i <= N; i++) {
        pthread_mutex_lock(&m);

        while (turn != 0) {
            pthread_cond_wait(&c, &m);
        }

        printf("Main: line %d\n", i);
        turn = 1;
        pthread_cond_signal(&c);
        pthread_mutex_unlock(&m);
    }

    pthread_join(t, NULL);
    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&c);
}