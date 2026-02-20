#ifndef SMARTPHONES_H
#define SMARTPHONES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

typedef struct  
{
    char model[40];
    int memory_capacity;
    int battery_capacity;
    int price;

}smartphone;
smartphone** make_phones(const char brands[10][30]);
smartphone** phones_sort(smartphone** phones, unsigned char param);
void print_phones(smartphone** phones);

#endif