#include "smartphones.h"
#define N 50




int main()
{
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
    smartphone** phones = make_phones(brands);
    printf("BEFORE\n");
    printf("---------------------------------------------------------------------\n");
    print_phones(phones);
    phones = phones_sort(phones, 0);
    printf("AFTER\n");
    printf("---------------------------------------------------------------------\n");
    print_phones(phones);
    for (int i = 0; i < N; i++)
    {
        free(phones[i]);
    }
    
    free(phones);
    //char*p = &phones[0];
    //*(int *)(p + 40)

}
