#ifndef SMARTPHONES_H
#define SMARTPHONES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>

typedef struct  
{
    char model[40];
    int memory_capacity;
    int battery_capacity;
    int price;

}smartphone;
smartphone** make_phones(const char brands[10][30], int N);
smartphone** phones_sort(smartphone** phones, unsigned char param, int N);
void print_phones(smartphone** phones, int N);
float get_time_diff(struct timeval *start, struct timeval *end);

#endif