#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int* arr_matrixs[100];
    char operators[100];
    int numb, rows, cols;
    int counter = 0;
    scanf("%d %d", &rows, &cols);
    int matrix[rows][cols];

    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            scanf("%d", &(matrix[r][c]));
        }
    }
    for(int i = 0; i < rows; i++){
        for (int j =0; j < cols; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    arr_matrixs[0] = *matrix;
    printf("\n");
    printf("%d ", *arr_matrixs[0]);






    /* printf("%d %d\n", rows, cols);
    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            printf("%d ", matrix[r][c]);
        }
        printf("\n");
    } */
    return 0;
}