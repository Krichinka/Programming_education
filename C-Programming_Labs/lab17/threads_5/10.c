#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define QUEUE_SIZE 10
#define MAX_MSG 128

#define CLIENTS 3
#define SERVERS 2
#define MSGS_COUNT 12

typedef struct {
    char data[QUEUE_SIZE][MAX_MSG + 1];
    int head;
    int tail;
    int count;
} Queue;

Queue q;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;

pthread_mutex_t msg_m = PTHREAD_MUTEX_INITIALIZER;
int msg_index = 0;

char *messages[MSGS_COUNT] = {
    "Hello",
    "How are you?",
    "Axaxaxxa",
    "Idesh gulyat?",
    "Dont think so",
    "Omg why youre so busy",
    "idk...",
    "So I dont need you anymore do anything you want",
    "Ok",
    "Ny i katis",
    "Skatertuy dorozjka!!!",
    "!!!"
};

void queue_init(void)
{
    q.head = 0;
    q.tail = 0;
    q.count = 0;
}

int msgSend(char *msg)
{
    pthread_mutex_lock(&m);

    while (q.count == QUEUE_SIZE) {
        pthread_cond_wait(&not_full, &m);
    }

    strncpy(q.data[q.tail], msg, MAX_MSG);
    q.data[q.tail][MAX_MSG] = '\0';
    int len = strlen(q.data[q.tail]);
    q.tail = (q.tail + 1) % QUEUE_SIZE;
    q.count++;
    pthread_cond_signal(&not_empty);
    pthread_mutex_unlock(&m);

    return len;
}

int msgRecv(char *buf, size_t size)
{
    pthread_mutex_lock(&m);

    while (q.count == 0) {
        pthread_cond_wait(&not_empty, &m);
    }

    strncpy(buf, q.data[q.head], size - 1);
    buf[size - 1] = '\0';
    int len = strlen(buf);
    q.head = (q.head + 1) % QUEUE_SIZE;
    q.count--;
    pthread_cond_signal(&not_full);
    pthread_mutex_unlock(&m);
    return len;
}

void *client(void *arg)
{
    while (1) {
        pthread_mutex_lock(&msg_m);

        if (msg_index >= MSGS_COUNT) {
            pthread_mutex_unlock(&msg_m);
            break;
        }

        char *msg = messages[msg_index];
        msg_index++;
        pthread_mutex_unlock(&msg_m);
        msgSend(msg);
        usleep((rand() % 2000 + 100) * 1000);
    }
}

void *server(void *arg)
{
    int id = *(int *)arg;
    char buf[200];
    int messages_for_server = MSGS_COUNT / SERVERS;

    for (int i = 0; i < messages_for_server; i++) {
        msgRecv(buf, sizeof(buf));
        printf("Server %d received: %s\n", id, buf);
        usleep((rand() % 500 + 100) * 1000);
    }
}

int main(void)
{
    srand(time(NULL));

    queue_init();
    pthread_t clients[CLIENTS];
    pthread_t servers[SERVERS];
    int server_ids[SERVERS];

    for (int i = 0; i < SERVERS; i++) {
        server_ids[i] = i + 1;
        pthread_create(&servers[i], NULL, server, &server_ids[i]);
    }

    for (int i = 0; i < CLIENTS; i++) {
        pthread_create(&clients[i], NULL, client, NULL);
    }

    for (int i = 0; i < CLIENTS; i++) {
        pthread_join(clients[i], NULL);
    }

    for (int i = 0; i < SERVERS; i++) {
        pthread_join(servers[i], NULL);
    }

    pthread_mutex_destroy(&m);
    pthread_mutex_destroy(&msg_m);
    pthread_cond_destroy(&not_empty);
    pthread_cond_destroy(&not_full);
}