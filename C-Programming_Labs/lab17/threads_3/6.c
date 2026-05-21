#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *sleep_sort(void *arg)
{
    int number = *(int *)arg;
    sleep(number);
    printf("%d\n", number);
}

int main(void)
{
    int numbers[] = {3, 1, 4, 2, 5};
    int n = 5;
    pthread_t threads[5];

    for (int i = 0; i < n; i++) {
        pthread_create(&threads[i], NULL, sleep_sort, &numbers[i]);
    }

    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

}