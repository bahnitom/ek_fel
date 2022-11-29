#include <stdio.h>
#include <stdlib.h>

#define LENGTH 10
#define ERROR_MALLOC 101
#define ERROR_REALLOC 102

int main(int argc, char *argv[])
{
    int capacity = LENGTH;
    int load = 0;
    int numb;

    // allocate memory for 10 int numbers
    int *arr_line = malloc(capacity * sizeof(int));

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
            load++;
        }
    }
    for (int i = 0; i < load; i++)
    {
        printf("%d ", arr_line[i]);
    }
    printf("\n");
    free(arr_line);
    return 0;
}
