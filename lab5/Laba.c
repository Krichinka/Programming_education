#include <stdio.h>

int print_arr(int matrix[], int n){
    for(int i = 0; i<n; i++){
        printf("%d ", matrix[i]);
    }
    printf("\n");
}

int Is_soversh(int a){
    int m = 0;
    for(int i = 1; i<a; i++)
    {
        if(a%i == 0){m = m + i;}
    }
    if(m == a){return 1;}
    else{return 0;}
}

int Is_prost(int a){
    int f = 0;
    for(int i = 2; i<a-1; i++)
    {
        if(a%i == 0)
        {
            f = 1;
            return 0; 
            break;}
    }
    if(f == 0){return 1;}
}

int main(){
    int n;
    int b,d,c;
    int f1 = 1;
    int f2 = 1;
    int index1 = -1;
    int index2 = -1;
    scanf("%d", &n);
    int matrix[n];
    for(int i = 0; i<n; i++){
        scanf("%d", &b);
        matrix[i] = b;
    }
    for(int i = 0; i<n; i++)
    {if(Is_soversh(matrix[i]) == 1){
        f1 = 0;
        index1 = i;
        d = matrix[i];
        printf("%d %d hyrt\n", matrix[i], index1);
        break;
    }}
    for(int i = n-1; i>=0; i--)
    {if(Is_prost(matrix[i]) == 1){
        f2 = 0;
        index2 = i;
        c = matrix[i];
        printf("%d %d hyt\n", matrix[i], index2);
        break;
    }}  
    if(f1 == 0 && f2 == 0){matrix[index2] = d;matrix[index1] = c;print_arr(matrix, n);}
    else{printf("Ne poluchilos(((");}
    
    
    
}
