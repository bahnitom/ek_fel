#include <stdio.h>
#include <stdlib.h>

// macros
#define LENGTH 10
#define ERROR_HISTOGRAM 100
#define ERROR_MALLOC 101
#define ERROR_REALLOC 102

// functions
int read_input(int capacity, int load, int *arr_lines);
int check_first_numb(int first_numb);

int main(int argc, char *argv[])
{
    int capacity = LENGTH;
    int load = 0;
    int cols;

    // allocate memory for 10 int numbers
    int numb;
    int *arr_line = calloc(capacity, sizeof(int));

    if (arr_line == NULL) /*error malloc, for sure*/
    {
        fprintf(stderr, "Error malloc\n");
        exit(ERROR_MALLOC);
    }
    // malloc ok ---> continue scanning numbers
    else
    {
        while (scanf("%d", &numb) == 1)
        {
            if (load >= capacity) /*array is full*/
            {
                int *tmp = realloc(arr_line, (capacity * 2) * sizeof(int));
                if (tmp == NULL) /*error realloc, for sure*/
                {
                    fprintf(stderr, "Error realloc\n");
                    free(arr_line);
                    arr_line = NULL;
                    load = 0;
                    break;
                    // return ERROR_REALLOC;
                }
                capacity *= 2; /*double size array*/
                arr_line = tmp;
            }
            arr_line[load] = numb;
            if (load == 0)
            {
                check_first_numb(arr_line[0]);
            }
            load++;
        }
    }
    check_first_numb(arr_line[0]);
    cols = arr_line[0];

    // only printing array
    for (int i = 0; i < load; i++)
    {
        printf("%d ", arr_line[i]);
    }
    printf("\n");

    free(arr_line);
    return 0;
}

int check_first_numb(int first_numb)
{
    if (first_numb <= 0)
    {
        fprintf(stderr, "Error: Chyba histogramu!\n");
        exit(ERROR_HISTOGRAM);
    }
    else
        return 0;
}

int read_input(int capacity, int load, int *arr_lines){
    // paste function


}