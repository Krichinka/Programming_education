#include <stdio.h>
#include <pthread.h>

void *print_lines(void *arg)
{
    char **lines = (char **)arg;

    for (int i = 0; i < 5; i++) {
        printf("%s\n", lines[i]);
    }
}

int main(void)
{
    pthread_t threads[4];
    char *text1[5] = {
        "Thread 1: line 1",
        "Thread 1: line 2",
        "Thread 1: line 3",
        "Thread 1: line 4",
        "Thread 1: line 5"
    };
    char *text2[5] = {
        "Thread 2: line 1",
        "Thread 2: line 2",
        "Thread 2: line 3",
        "Thread 2: line 4",
        "Thread 2: line 5"
    };
    char *text3[5] = {
        "Thread 3: line 1",
        "Thread 3: line 2",
        "Thread 3: line 3",
        "Thread 3: line 4",
        "Thread 3: line 5"
    };
    char *text4[5] = {
        "Thread 4: line 1",
        "Thread 4: line 2",
        "Thread 4: line 3",
        "Thread 4: line 4",
        "Thread 4: line 5"
    };
    pthread_create(&threads[0], NULL, print_lines, text1);
    pthread_create(&threads[1], NULL, print_lines, text2);
    pthread_create(&threads[2], NULL, print_lines, text3);
    pthread_create(&threads[3], NULL, print_lines, text4);
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);
    pthread_join(threads[3], NULL);
}