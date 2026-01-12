#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 1000


int split(char text[LEN])
{
    char** mass;
    size = 1;
    char* buffer;
    int count = 1;
    buffer = malloc(count);
    mass = calloc(mass, size*8);
    for (int i; i<LEN; i++)
    {
        if (text[i] == ",")
    }

}
int main()
{
    char type[1];
    int f = 1;
    /*while (f == 1)
    {
        printf("compress - 1, restore - 2:\n");
        fgets(type, 1, stdin);
        if ((atoi(&type[0]) == 1) || (atoi(&type[0]) == 2)){
            printf("yeah %d\n", type[0]);
            f = 0;
        }
    }*/

    char text[LEN];
    fgets(text, LEN, stdin);
    for (int i = 0; i < LEN; i++)
    {
        printf("%c\n", text[i]);
    }
    
}
