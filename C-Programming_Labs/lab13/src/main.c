#include "smartphones.h"
#define N 10

int main()
{
    struct timeval start, end;
    gettimeofday(&start, NULL);
    const char brands[10][30] = {
        "samsung s25 ultra",
        "huawei mate xt",
        "honor x50",
        "tecno camon c20",
        "oppo find x3 ultra",
        "vivo x300 pro",
        "nothing phone 2",
        "xiaomi mi 15 ultra",
        "asus rog phone 7",
        "iphone 5s"
    };
    srand(time(NULL)); 
    smartphone** phones = make_phones(brands, N);
    printf("BEFORE\n");
    printf("---------------------------------------------------------------------\n");
    print_phones(phones, N);
    gettimeofday(&start, NULL);
    phones = phones_sort(phones, 0, N);
    gettimeofday(&end, NULL);
    float time = get_time_diff(&start, &end);

    printf("AFTER\n");
    printf("---------------------------------------------------------------------\n");
    print_phones(phones, N);
    printf("Прошло: %f сек\n", time);
    printf("Data:  %ld байт\n", N*sizeof(smartphone));
    for (int i = 0; i < N; i++)
    {
        free(phones[i]);
    }
    
    free(phones);
}
