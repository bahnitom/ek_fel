#include <stdio.h>
#include <stdlib.h>

#define READ_OK 0
#define READ_FAIL 101

int main(void) {
    int *arr_matrixs[100];
    char arr_operators[100];
    char *op = NULL;
    int rows, cols;
    int ret = EXIT_SUCCESS;

    scanf("%d %d", &rows, &cols);
    // int matrix[rows][cols];


//    for (int r = 0; r < rows; ++r) {
//        for (int c = 0; c < cols; ++c) {
//            if(scanf("%d", &(matrix[r][c])) == 1){
//                ret = EXIT_SUCCESS;
//            }
//            else{
//                ret = EXIT_FAILURE;
//            }
//        }
//    }
//    // printing matrix
//    for (int i = 0; i < rows; i++) {
//        for (int j = 0; j < cols; j++) {
//            printf("%d ", matrix[i][j]);
//        }
//        printf("\n");
//    }
//
//    arr_matrixs[0] = (int *) matrix;
//    printf("\n");

    // reading operator
    if (scanf("%1s", op) == 1) // check symbol
    {
        arr_operators[0] = *op;
        ret = EXIT_SUCCESS;
    } else {
        ret = EXIT_FAILURE;
        //return ret;
    }
    printf("operator: %d\n", arr_operators[0]);
    printf("%s", op);
    // only printing first matrix in our matrix array
    int count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", *(arr_matrixs[0] + i + j + count));
        }
        count += 3;
        printf("\n");
    }

    return 0;
}

//#include <stdio.h>
//
//int read_all_lines_simple(char *filename, int line_size);
//
//int main(void) {
//    return read_all_lines_simple("data/pub_c08.in", 100);
//}
//
//int read_all_lines_simple(char *filename, int line_size) {
//    FILE *file_stream;
//    if ((file_stream = fopen(filename, "r")) == NULL) {
//        printf("Cannot open %s", filename);
//        return -1;
//    }
//    char line[line_size];
//    while (fgets(line, line_size, file_stream) != NULL) {
//        fprintf(stderr, "%s", line);
//    }
////    if (fclose(file_stream))
////        printf("Error closing file %s", filename);
//    return 0;
//}
