#include <omp.h>
#include <stdio.h>
#include <stdlib.h>


int **allocate2dMatrix(int r, int c) {
    int *linear, **mat;
    int i;

     linear = (int*)malloc(sizeof(int) * r * c);
     mat = (int**)malloc(sizeof(int*) * r);
     for ( i = 0; i < r; i++)
     {
         mat[i] = &linear[i * c];
     }
     return mat;
}

void print2DMatrix(int** arr, int row, int column) {
    int n, m;
    for (n= 0; n< row; n++)
    {
        for (m = 0; m < column; m++)
        {
            printf("%d", arr[n][m]);
            printf("  ");
            
        }
        printf("\n");
    }
}

void initialaizMatrix(int** arr , int r , int c) {
    int l, m;
    for (l = 0; l < r; l++)
    {
        for (m = 0; m< c; m++)
        {
            arr[l][m] = 0;
        }
    }
}

int main(int argc, char *argv[])
{
    int myrank, numThreads; 
    int i, j;
    int **a,  **b , **c;
    int column, row;


    printf("Welcome to Matrix Addition program!\n");
    printf("Please enter dimensions of the matrix: ");
    scanf("%d %d", &row, &column);

    firstMatrix = allocat2dMatrix(row , column);
    printf("Please enter its elements: \n");
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
    
    secondMatrix = allocate2dMatrix(row_2 , column_2);
    printf("Please enter its elements: \n");
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            scanf("%d", &b[i][j]);
        }
    }
    
    resultMatrix = allocate2dMatrix(row , column);
    initialaizMatrix(c , row, column);


    #pragma omp parallel shared(a,b,c)
    {
        #pragma omp for schedule(static)
        for (i = 0; i < row; i++)
        {
            for (j = 0; j < column + rows; j++)
            {
                c[i][j] = a[i][j] + b[i][j];
            } 
        }

    }   /* end of parallel region */


    printf("Matrix Addition is : \n");
    print_Matrix(c, row, column);

}