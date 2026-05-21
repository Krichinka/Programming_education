#include <stdio.h>
#include <pthread.h>

#define N 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int turn = 0;

void *child_thread(void *arg)
{
    for (int i = 1; i <= N; i++) {
        pthread_mutex_lock(&mutex);

        while (turn != 1) {
            pthread_cond_wait(&cond, &mutex);
        }

        printf("Child thread: line %d\n", i);

        turn = 0;

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main(void)
{
    pthread_t thread;

    pthread_create(&thread, NULL, child_thread, NULL);

    for (int i = 1; i <= N; i++) {
        pthread_mutex_lock(&mutex);

        while (turn != 0) {
            pthread_cond_wait(&cond, &mutex);
        }

        printf("Parent thread: line %d\n", i);

        turn = 1;

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }

    pthread_join(thread, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}