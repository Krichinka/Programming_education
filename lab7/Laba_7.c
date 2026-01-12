#include <stdio.h>
#include <stdlib.h>
void print_array(char **arr, int N) {
    for (int i = 0; i < N; i++) {
        printf("%s\n", arr[i]);
    }
}

int main(){
    char textik[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    int count = 0;
    int max;
    char slovo[] = {};
    char** arr = NULL;
    int j = 0;
    int c = 0;
    int size = sizeof(*arr);
    arr = malloc(size);
    *arr = malloc(sizeof(char));
    if (arr == NULL){printf("error");}
    for (int i = 0; i < sizeof(textik); i++)
    {
        
        if (textik[i] == ' '){
            c = 0;
            j++;
            arr = realloc(arr, size + 8);
            size = size + 8;
        }
        else
        {
            arr[j] = realloc(arr[j], size + 1);
            arr[c][j] = textik[i];
            c++;
            size++;
        }

    }
    print_array(arr, j);
   
    
}