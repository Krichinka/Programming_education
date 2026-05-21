#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 8

int print_ar(int height, int width, int** matrix)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
        
}

int main()
{
    int** dynamic_matrix;
    int width = 0;
    int height = 0;
    int min[3] = {100000000, 0, 0};
    printf("Type height:");
    scanf("%d%*c", &height);
    printf("Type width:");
    scanf("%d%*c", &width);

    dynamic_matrix = malloc(height*sizeof(int*));
    if (dynamic_matrix == NULL)
    {
        printf("Memory error: code 1\n");
        return 1;
    }
    for (int i = 0; i < height; i++)
    {
        dynamic_matrix[i] = calloc(width, sizeof(int));
            if (dynamic_matrix[i] == NULL)
        {
            printf("Memory error: code 2\n");
        }
    }
    //print_ar(height, width, dynamic_matrix);

/*
    int count = 0;
    char* buffer;
    int cur_wd = 0;
    int j = 0;
    char* cur_str;
    char sep[4] = ",; ";
    buffer = malloc(width*sizeof(char)*2+1);
    if (buffer == NULL)
    {
        printf("Memory error: code 3\n");
    }
    cur_str = malloc(100*sizeof(char*));
    if (cur_str == NULL)
    {
        printf("Memory error: code 3\n");
    }
    for (int i = 0; i < height; i++)
    {
        printf("Type string %d of matrix:", i+1);
        fgets(buffer, sizeof(buffer), stdin);

        cur_str = strtok(buffer, sep);
        dynamic_matrix[i][0] = atoi(cur_str);
        printf("%s\n", buffer);
        printf("%s\n", cur_str);

        for (int j = 1; j<width; j++) 
        {
            //printf("%s\n", cur_str);
            cur_str = strtok(NULL, sep);
            //printf("%s\n", cur_str);
            //printf("%d %d\n", i, j);
            dynamic_matrix[i][j] = atoi(cur_str);
            print_ar(height, width, dynamic_matrix);
            printf("\n");
        }
        buffer = memset(buffer, 0, sizeof(char)*2);
        printf("%s\n\n", buffer);
    }
    print_ar(height, width, dynamic_matrix);*/
        
        
        





    srand((unsigned)time(NULL));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            dynamic_matrix[i][j] = rand() % 41 ; // диапазон [-20, 20]
        }
    }

    print_ar(height, width, dynamic_matrix);

    
    for (int i = 0; i<height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (min[0]>dynamic_matrix[i][j])
            {
                min[0] = dynamic_matrix[i][j];
                min[1] = i;
                min[2] = j;
            }   
        }
    }

    int **dyn_mat2;
    
    dyn_mat2 = malloc((height-1)*sizeof(int*));
    if (dyn_mat2 == NULL)
    {
        printf("Memory error: code 1\n");
    }
    for (int i = 0; i < height; i++)
    {
        dyn_mat2[i] = calloc(width, sizeof(int));
            if (dyn_mat2[i] == NULL)
        {
            printf("Memory error: code 2\n");
        }
    }

    printf("\n%d %d %d\n", min[0], min[1], min[2]);

    int k = 0;
    int m = 0;
    int count = 0;
   for (int i = 0; i<height-1; i++)
    {
        for (int j = 0; j < width-1; j++)
        {
            if (i == min[1])
            {
                k = 1;
            }
            else if (j == min[2])
            {
                m = 1;
            }
            dyn_mat2[i][j] = dynamic_matrix[i+k][j+m];
            if(dyn_mat2[i][j] == 0){count++;}

            
        }
        m = 0;
    }
    print_ar(height-1, width-1, dyn_mat2);
    int b[2];
    for(int i = 0; i<width; i++)
    {
        b[0] = dyn_mat2[0][i];
        b[1] = dyn_mat2[height-2][i];
        dyn_mat2[0][i] = b[1];
        dyn_mat2[height-2][i] = b[0];
    }

    printf("%d\n", count);


    print_ar(height-1, width-1, dyn_mat2);
    
    
    for (int i = 0; i < height; i++) free(dynamic_matrix[i]);
    free(dynamic_matrix);
}