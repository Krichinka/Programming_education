#include <stdio.h>
#include <pthread.h>

void *thread_func(void *arg)
{
    for (int i = 1; i <= 5; i++) {
        printf("Child thread: line %d\n", i);
    }
}

int main(void)
{
    pthread_t thread;

    pthread_create(&thread, NULL, thread_func, NULL);

    pthread_join(thread, NULL);

    for (int i = 1; i <= 5; i++) {
        printf("Parent thread: line %d\n", i);
    }
}