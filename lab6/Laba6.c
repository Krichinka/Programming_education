#include <stdlib.h>
#include <stdio.h>



int main(){
    char text[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. ccccccccccccccccw";
    int max = 0;
    int cnt = 0;
    int len = 0;
    int st = 0;
    int end = 0;
    for (int i = 0; i<sizeof(text); i++)
    {
           
        if (text[i] == 'c')
        {
            cnt++;
            if(cnt > max){max = cnt;}
        }
        else if(text[i] == ' ' || text[i] == '\0')
        {
            if(cnt == max)
            {
                end = i;
                st = i-len+1;
            }
            len = 0;
            cnt = 0;
        }
        len++;
    }
    while(st < end)
    {
        printf("%c", text[st]);
        st++;
    }
    printf("  %d\n", max);
}