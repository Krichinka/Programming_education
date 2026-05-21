#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define THREADS 4
#define LINES 5

char texts[THREADS][LINES][50];

void make_texts(void)
{
    for (int i = 0; i < THREADS; i++) {
        for (int j = 0; j < LINES; j++) {
            sprintf(texts[i][j], "Thread %d: line %d", i + 1, j + 1);
        }
    }
}

void *child_simple(void *arg)
{
    for (int i = 1; i <= 5; i++) {
        printf("Child thread: line %d\n", i);
    }

    return NULL;
}

void *print_text(void *arg)
{
    int num = *(int *)arg;

    for (int i = 0; i < LINES; i++) {
        printf("%s\n", texts[num][i]);
    }

    return NULL;
}

void *print_text_sleep(void *arg)
{
    int num = *(int *)arg;

    for (int i = 0; i < LINES; i++) {
        printf("%s\n", texts[num][i]);
        sleep(1);
    }

    return NULL;
}

void cleanup(void *arg)
{
    int num = *(int *)arg;
    printf("Thread %d finished\n", num + 1);
}

void *print_text_cleanup(void *arg)
{
    int num = *(int *)arg;

    pthread_cleanup_push(cleanup, arg);

    for (int i = 0; i < LINES; i++) {
        printf("%s\n", texts[num][i]);
        sleep(1);
    }

    pthread_cleanup_pop(1);

    return NULL;
}

void *sleep_sort(void *arg)
{
    int number = *(int *)arg;

    sleep(number);
    printf("%d\n", number);

    return NULL;
}

void task1(void)
{
    printf("\n--- Task 1 ---\n");

    pthread_t thread;

    pthread_create(&thread, NULL, child_simple, NULL);

    for (int i = 1; i <= 5; i++) {
        printf("Parent thread: line %d\n", i);
    }

    pthread_join(thread, NULL);
}

void task2(void)
{
    printf("\n--- Task 2 ---\n");

    pthread_t thread;

    pthread_create(&thread, NULL, child_simple, NULL);
    pthread_join(thread, NULL);

    for (int i = 1; i <= 5; i++) {
        printf("Parent thread: line %d\n", i);
    }
}

void task3(void)
{
    printf("\n--- Task 3 ---\n");

    pthread_t threads[THREADS];
    int nums[THREADS];

    for (int i = 0; i < THREADS; i++) {
        nums[i] = i;
        pthread_create(&threads[i], NULL, print_text, &nums[i]);
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
}

void task4(void)
{
    printf("\n--- Task 4 ---\n");

    pthread_t threads[THREADS];
    int nums[THREADS];

    for (int i = 0; i < THREADS; i++) {
        nums[i] = i;
        pthread_create(&threads[i], NULL, print_text_sleep, &nums[i]);
    }

    sleep(2);

    for (int i = 0; i < THREADS; i++) {
        pthread_cancel(threads[i]);
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
}

void task5(void)
{
    printf("\n--- Task 5 ---\n");

    pthread_t threads[THREADS];
    int nums[THREADS];

    for (int i = 0; i < THREADS; i++) {
        nums[i] = i;
        pthread_create(&threads[i], NULL, print_text_cleanup, &nums[i]);
    }

    sleep(2);

    for (int i = 0; i < THREADS; i++) {
        pthread_cancel(threads[i]);
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
}

void task6(void)
{
    printf("\n--- Task 6 ---\n");

    int numbers[] = {3, 1, 4, 2, 5};
    pthread_t threads[5];

    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, sleep_sort, &numbers[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }
}

int main(void)
{
    make_texts();

    task1();
    task2();
    task3();
    task4();
    task5();
    task6();

    return 0;
}