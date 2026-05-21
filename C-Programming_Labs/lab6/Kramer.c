#include <stdio.h>
               
int print_arr(int n, int matrix[n][n+1]){
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            printf("%d ", matrix[i][j]);
            if(j == n-1){printf("\n");}
            }
    }
    printf("\n");
}
 
int det(int n, int matrix[n][n+1]){
    int matrix1[n-1][n];
    int sum = 0;

    if(n == 2){return (matrix[0][0]*matrix[1][1]) - (matrix[0][1]*matrix[1][0]);}
    else{
        for(int k=0; k<n; k++){
            for(int i=0; i<n-1; i++){
                for(int j = 0; j<n-1; j++){
                    if(j<k){matrix1[i][j] = matrix[i+1][j];}
                    else if(j>=k){matrix1[i][j] = matrix[i+1][j+1];}
                    
                }
            }
            if(k%2==0){sum = sum + (((matrix[0][k])*det(n-1, matrix1)));}
            else {sum = sum - ((matrix[0][k])*det(n-1, matrix1));}
            
        }
        return sum;
    }
    
}

int deti(int n, int matrix[n][n+1]){
    int matrix1[n][n+1];
    double b = 0;
    for(int k = 0; k<n; k++){
        for(int i = 0; i<n; i++){
            for(int j = 0; j<n; j++){
                if(j == k){matrix1[i][j] = matrix[i][n];}
                else{matrix1[i][j] = matrix[i][j];}
            }
        }
        printf("x%d = %f\n", k+1, (double) det(n, matrix1)/det(n, matrix));
    }
}

int main(){
    int n = 8;
    int matrix[8][9] = {{2,6,-2,3,3,6,1,6,22},
                        {1,4,4,2,4,7,-2,3,39},
                        {3,6,7,-1,0,5,3,1,34},
                        {7,3,6,0,7,4,2,4,23},
                        {1,0,-1,2,3,6,0,-2,3},
                        {-1,0,2,6,-2,0,5,-1,26},
                        {4,5,-2,7,4,4,5,-2,17},
                        {3,3,4,6,-2,6,-2,2,37}};
    print_arr(n, matrix); 
    deti(n, matrix);
}