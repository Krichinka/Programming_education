#include "smartphones.h"

float get_time_diff(struct timeval *start, struct timeval *end) {
    return (end->tv_sec - start->tv_sec) + (end->tv_usec - start->tv_usec) / 1000000.0;
}

smartphone** make_phones(const char brands[10][30], int N){
    
    smartphone** phones = calloc(N, sizeof(smartphone));
    for (int i = 0; i < N; i++)
    {
        smartphone* phone = calloc(1, sizeof(smartphone));
        phones[i] = phone;
    }
    
    for(int i = 0; i < N; i++)
    {
        
        strcpy(phones[i]->model, brands[rand() % 10]);
        phones[i]->memory_capacity = (int)pow(2, rand()%4 + 7);
        phones[i]->battery_capacity = ((rand()%35)*100)+4000;
        phones[i]->price = ((rand()%24)*50)+399;

    }
    return phones;
}

    smartphone** phones_sort(smartphone** phones, unsigned char param, int N)
{
    for (int i = 0; i < N - 1; i++) {
        int cur = i;
        for (int j = i + 1; j < N; j++) {
            if (param == 0) {
                if (strcmp((char*)phones[j] + param, (char*)phones[cur] + param) < 0) {
                    cur = j;
                }
            } else {
                int curj = *(int*)((char*)phones[j] + param);
                int curmin = *(int*)((char*)phones[cur] + param);
                if (curj < curmin) {
                    cur = j;
                }
            }
        }
        if (cur != i) {
            smartphone* temp = phones[i];
            phones[i] = phones[cur];
            phones[cur] = temp;
        }
    }
    
    return phones;
}



void print_phones(smartphone** phones, int N)
{
    printf("%-4s %-25s %12s %14s %12s\n", "№", "Model", "Memory (GB)", "Battery (mAh)", "Price ($)");
    printf("---------------------------------------------------------------------\n");
    for (int i = 0; i < N; i++) {
        printf("%-4d %-25s %12d %14d %12d\n",
               i + 1,
               phones[i]->model,
               phones[i]->memory_capacity,
               phones[i]->battery_capacity,
               phones[i]->price);
    }
    printf("---------------------------------------------------------------------\n");
}