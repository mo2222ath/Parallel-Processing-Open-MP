#include <omp.h>
#include <stdio.h>
#include <stdlib.h>


int **allocate2dMatrix(int r, int c) {
    int *l, **m;
    int i;

     l = (int*)malloc(sizeof(int) * r * c);
     m = (int**)malloc(sizeof(int*) * r);
     for ( i = 0; i < r; i++)
     {
         m[i] = &l[i * c];
     }
     return m;
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

void initialaizMatrix(int** a , int r , int c) {
    int l, m;
    for (l = 0; l < r; l++)
    {
        for (m = 0; m< c; m++)
        {
            a[l][m] = 0;
        }
    }
}

int main(int argc, char *argv[])
{
    int i, j;
    int **a,  **b , **c;
    int column, row;


    printf("Welcome to Matrix Addition program!\n");
    printf("Please enter dimensions of the matrix: ");
    scanf("%d %d", &row, &column);

    a = allocate2dMatrix(row , column);
    printf("Please enter its elements: \n");
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }

    b = allocate2dMatrix(row , column);
    printf("Please enter its elements: \n");
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            scanf("%d", &b[i][j]);
        }
    }

    c = allocate2dMatrix(row , column);
    initialaizMatrix(c , row, column);


    #pragma omp parallel shared(a,b,c) private(i,j)
    {
        //#pragma omp for schedule(dynamic , 2)
        #pragma omp for schedule(static)
        for (i = 0; i < row; i++)
        {
            for (j = 0; j < column; j++)
            {
                c[i][j] = a[i][j] + b[i][j];
                printf ("IN thread %d  C[%d][%d] = %d \n" , omp_get_thread_num() , i, j ,c[i][j] );
            }

        }

    }   /* end of parallel region */


    printf("Matrix Addition is : \n");
    print2DMatrix(c, row, column);

}
