#define SIZE 9 
#include <stdio.h>
int sudoku[SIZE][SIZE] = { 
{5, 3, 4, 6, 7, 8, 9, 1, 2},
//{3, 3, 3, 3, 3, 3, 3, 3, 3}, 
{6, 7, 2, 1, 9, 5, 3, 4, 8}, 
{1, 9, 8, 3, 4, 2, 5, 6, 7}, 
{8, 5, 9, 7, 6, 1, 4, 2, 3}, 
{4, 2, 6, 8, 5, 3, 7, 9, 1}, 
{7, 1, 3, 9, 2, 4, 8, 5, 6}, 
{9, 6, 1, 5, 3, 7, 2, 8, 4}, 
{2, 8, 7, 4, 1, 9, 6, 3, 5}, 
{3, 4, 5, 2, 8, 6, 1, 7, 9} 
}; 
int  check_rows(int sudoku[9][9])
{
    int count = 0;
    for (int k = 0; k<9; k++)
    {
        for (int i = 1; i<10; i++)
        {
            for (int j = 0; j<9; j++)
            {
                if (i == sudoku[k][j]){count++;break;}
            }
        }
    }
    if (count == 81){return 1;}
    else {return 0;}
}
int  check_columns(int sudoku[9][9])
{
    int count = 0;
    for (int k = 0; k<9; k++)
    {
        for (int i = 1; i<10; i++)
        {
            for (int j = 0; j<9; j++)
            {
                if (i == sudoku[j][k]){count++;break;}
            }
        }
    }
    if (count == 81){return 1;}
    else {return 0;}
}
int  check_squares(int sudoku[9][9])
{
    int count = 0;
    for (int k = 0; k<9; k++)
    {
        for (int i = 1; i<10; i++)
        {
            for (int j = 0; j<9; j++)
            {
                if (i == sudoku[j/3][((k*3)%9)+(j%3)]){count++;break;}
            }
        }
    }
    if (count == 81){return 1;}
    else {return 0;}
}

int  is_valid_sudoku(int sudoku[9][9])
{
    if (check_rows(sudoku) * check_columns(sudoku) * check_squares(sudoku) == 1){printf("Its sudoku\n");}
    else{printf("Its not sudoku\n");}
}

int is_valid_sudoku2(int sudoku[9][9])
{
    int count = 0;
    for (int n = 0; n<3; n++)
    {
        for (int k = 0; k<9; k++)
        {
            for (int i = 1; i<10; i++)
            {
                for (int j = 0; j<9; j++)
                {
                    if ((i == sudoku[j][k]) && (n == 0)){count++;break;}
                    if ((i == sudoku[j/3][((k*3)%9)+(j%3)]) && (n == 1)){count++;break;}
                    if ((i == sudoku[k][j]) && (n == 2)){count++;break;}
                }
            }
        }
    }
    if (count == 243){printf("Its sudoku\n");}
    else {printf("Its not sudoku\n");}
}

int main()
{
    is_valid_sudoku(sudoku);
    is_valid_sudoku2(sudoku);
    printf("%d\n", check_columns(sudoku));
    printf("%d\n", check_rows(sudoku));
    printf("%d\n", check_squares(sudoku));
}